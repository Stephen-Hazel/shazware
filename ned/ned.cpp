// ned.cpp

#include "ned.h"

// all those damn global variables that Ned uses...   sue me.
pmem   MemTop;                         // memory related stuff
prow   Row [MAX_ROW];
ubyt2  FreeRows;
ubyt2  CsrRow, EndRow;                 // cursor related stuff
ubyte  CsrCol, ScrRow, EndScr;
bool   Over, Sqnc;                     // nasty mode stuff
ubyt2  BlkBgnRow, BlkEndRow;           // block related stuff
ubyte  BlkBgnCol, BlkEndCol;
TStr   FindStr, RplcStr, FName;        // strings
ubyte  FindLen, RplcLen;
key    KeySqnc [MAX_SQNC];             // seqence (macro) stuff
ubyte  SqncLen;
char   KeyMode, *KMMsg, *KMBuf, KM1;
bool (*KMCmd)();
row    Info, Empt;
ScrDef Scr;


//------------------------------------------------------------------------------
#define CPINK    CC("#FF0080")
#define CDKBLUE  CC("#002050")
#define CDPBLUE  CC("#004080")
#define CTURQ    CC("#00FFFF")
#define CWHITE   CC("#FFFFFF")

void Ro2Scr (prow pro, ubyte y, ubyte bgn, ubyte end, bool flip)
{ ubyte ln = 0;
  TStr  s;
   if (bgn  < pro->Len) {
      ln = pro->Len - bgn;   if (ln > end-bgn+1)  ln = end-bgn+1;
      MemCp (s, pro->Col + bgn, ln);
   }
   MemSet (& s [ln], ' ', end-bgn+1-ln);
   s [end-bgn+1] = '\0';
  char *f, *b;
   if (y) {                            // text  cursor / normal
      if (flip)  {f = CWHITE;    b = CPINK;  }
      else       {f = CTURQ;     b = CDKBLUE;}
   }
   else {                              // info  cursor / status
      if (flip)  {f = CDKBLUE;   b = CTURQ;  }
      else       {f = CWHITE;    b = CDPBLUE;}
   }
  QColor fc (f), bc (b);
  QPen   penf (fc), penb (bc);
  QBrush            brs  (bc);
  QPainter p (Scr.pm);
   p.setFont (Gui.W ()->font ());
   p.setPen (penb);   p.setBrush (brs);
   p.drawRect (bgn*Scr.wLn/80, y*Scr.hCh, (end-bgn+1)*Scr.wLn/80, Scr.hCh);
   p.setPen (penf);
   p.drawText (bgn*Scr.wLn/80, y*Scr.hCh+Scr.hBL, s);
}


void PutIt ()
{ TStr fn;
   if (Scr.pm == nullptr)  return;     // no pixmap yet so scram

  ubyt2 r = CsrRow - ScrRow;           // put changed rows
//DBG("PutIt `d-`d", Scr.min, Scr.max);
   for (ubyte i = Scr.min;  i <= Scr.max;  i++)
      Ro2Scr ((r+i < EndRow) ? Row [r+i] : & Empt, i+1, 0, 79, false);

   if (KeyMode)                        // put info - row, col, modes
        StrFmt (Info.Col, "`s`s", KMMsg, (KeyMode == 's') ? KMBuf : "");
   else StrFmt (Info.Col, "row=`d col=`d`s`s  `s",
           CsrRow+1, CsrCol+1, Over ? " [over]" : "",
                               Sqnc ? " [sqnc]" : "", FnName (fn, FName));
   Info.Len = SC(ubyte,StrLn (Info.Col));
   Ro2Scr (& Info, 0, 0, 79, false);

   if (KeyMode == 's')                 // put shown cursor
        Ro2Scr (& Info, 0, Info.Len, Info.Len, true);
   else Ro2Scr ((CsrRow < EndRow) ? Row [CsrRow] : & Empt,
                ScrRow+1, CsrCol, CsrCol, true);
   Gui.W ()->update ();
}


// UI update funcs -------------------------------------------------------------
void PutScr ()  {Scr.min = 0;   Scr.max = EndScr;}    // just redo it all

void PutRow (ubyte r)                  // try to just do sooome o da lines
{  if (r < Scr.min) Scr.min = r;
   if (r > Scr.max) Scr.max = r;
}

bool PutBlk ()
// flash the blocked text:
// if part of block is visible, flip each char in block, pause, then restore
{ sbyt2 topScr, botScr;
  ubyte bgnCol, endCol;
  ubyt2 i, r;
   botScr = (topScr = SC(sbyt2,CsrRow-ScrRow)) + EndScr;   // Row[] indexes
   if ((BlkBgnRow >= botScr) || (BlkEndRow <= topScr))  return true;

   if ((botScr = BlkEndRow-topScr) > EndScr) botScr = EndScr;
   if ((topScr = BlkBgnRow-topScr) < 0)      topScr = 0;   // Scrn indexes
   if (BlkBgnCol == BlkEndCol)  {bgnCol = 0;          endCol = 79;}
   else                         {bgnCol = BlkBgnCol;  endCol = BlkEndCol;}
   for (r = SC(ubyt2,CsrRow-ScrRow+topScr), i = SC(ubyt2,topScr);
        i <= botScr;  i++, r++)
      Ro2Scr ((r < EndRow) ? Row [r] : & Empt, SC(ubyte,i+1),
              bgnCol, endCol, true);
   Gui.W ()->update ();   Zzz (125);   // 1/8 sec i hope
   PutScr ();   PutIt ();              // and restore
   return true;
}


//------------------------------------------------------------------------------
void JotDn (char Key)
// if OverWrite, if nonspace, define the col and overwrite the char.
//               else if on a defined col, overwrite a space, ShrinkLen.
// else insert a col, if nonspace, define the col and put the char in.
// Put ScrRow.
// go Rit, else Rtrn.
{  if (Over) {
      if (Key != ' ')    {if (ExtendSpc (CsrRow, SC(ubyte,CsrCol+1)))
                             *(CsrRowPtr() + CsrCol) = Key;}
      else
         if (CsrCol < CsrRowLen ())
           {*(CsrRowPtr () + CsrCol) = ' ';  ShrinkLen (CsrRow);}
   }
   else {
      if (InsCols (CsrRow, CsrCol, 1)) {
         if (Key != ' ') {if (ExtendSpc (CsrRow, SC(ubyte,CsrCol+1)))
                             *(CsrRowPtr () + CsrCol) = Key;}
      }
   }
   PutRow (ScrRow);
   if (! Rit ())  Rtrn ();
}


void DoKeyC (key k)                    // just askin for a character
{  if ((k & 0xFF80) == 0)
      {*KMBuf = ToUpper (k & 0x7F);  KeyMode = '\0';  (*KMCmd)();}
}


void DoKeyS (key k)                    // askin for a string
// if 1st key is ascii, reset.
// if key is a backspace, ...backspace.
// when return is hit, terminate string and exit.
// else if it fits, put it in.
{ ubyte ln = SC(ubyte,StrLn (KMBuf));
   if (KM1) {  // if first keypress is ascii, redo buf
      KM1 = '\0';
      if ((k & 0xFF80) == 0)  {*KMBuf = '\0';   ln = 0;}
   }
   if      (k == BSP_KEY)  {if (ln)  KMBuf [ln-1] = '\0';}
   else if (k == RET_KEY)  {KeyMode = '\0';   (*KMCmd)();}
   else if ((k & 0xFF80) == 0)
      if ((StrLn (KMMsg) + ln) < 79)
         {KMBuf [ln] = k & 0x7F;   KMBuf [ln+1] = '\0';}
}


void DoKey (key Key)
// first check for special keymode...
// if printing key, jot it down
// else search for the Map string, do it.
// if in Sqnc mode, if non 'TglSqnc' key, add key to KeySqnc
//                  turn off Sqnc if max is hit.
{ ubyt2  i = CmdLen;
  ubyte *map;
   Scr.min = Scr.max = ScrRow;
   if      (KeyMode == 's')  {DoKeyS (Key);   PutIt ();   return;}
   else if (KeyMode == 'c')  {DoKeyC (Key);   PutIt ();   return;}
   if ((Key & 0xFF80) == 0)  JotDn (SC(char,Key));
   else
      for (i = 0;  i < CmdLen;  i++)  if (CmdMap [i].Key == Key) {
         map = CmdMap [i].Map;
         while ( (*Cmd [*map++])() )  ;     // Yesss!  try THAT in COBOL...
         break;
      }
   if (Sqnc) {                              // recording a sequence
      if ((i >= CmdLen) || (Cmd [*(CmdMap [i].Map)] != TglSqnc))
         KeySqnc [SqncLen++] = Key;
      if (SqncLen == MAX_SQNC)  Sqnc = 0;   // rats - too long :(
   }
   PutIt ();
}


//______________________________________________________________________________
void NEd::keyPressEvent (QKeyEvent *e)
{ KeyMap km;
  key    k;
   if ((k = km.Map (e->modifiers (), e->key ())))  DoKey (k);
}


void NEd::wheelEvent (QWheelEvent  *e)
{ int j = e->angleDelta ().y () / 40;
//DBG("mousewheel=`d ScrRow=`d CsrRow=`d, EndRow=`d EndScr=`d",
//j, ScrRow, CsrRow, EndRow, EndScr);
   if (j >   EndScr )  j =  EndScr;
   if (j < (-EndScr))  j = -EndScr;
   if (j >= 0) {                    // scroll up
      if (CsrRow != ScrRow)
         {if (CsrRow < (j + ScrRow)) CsrRow = ScrRow;   else CsrRow -= j;}
   }
   else {                           // scroll down
      if (EndRow > (EndScr+1)) {
        ubyt2 t = EndRow-1 - (EndScr-ScrRow);
         if (CsrRow != t)
            {if ((CsrRow + j) > t)   CsrRow = t;        else CsrRow -= j;}
      }
      else if (CsrRow != ScrRow) CsrRow = ScrRow;
   }
   PutScr ();   PutIt ();
}


void NEd::paintEvent (QPaintEvent *e)
{  Q_UNUSED (e);   if (Scr.pm == nullptr)  return;
//DBG("repaint");
  QPainter p (this);
   p.drawPixmap (0, 0, Scr.pm->width (), Scr.pm->height (), *Scr.pm);
}


void NEd::resizeEvent (QResizeEvent *e)
{  if (! Scr.hCh)  return;             // not ready yet :(
  int h = e->size ().height () / Scr.hCh;
//DBG("resize h=`d", h);
   if (h < 4)  h = 4;                  // at LEAST info n 3 rows
   if (h != EndScr+2) {
      EndScr = SC(ubyte,h-2);   h *= Scr.hCh;
      delete Scr.pm;   Scr.pm = new QPixmap (Scr.wLn, h);
      PutScr ();   PutIt ();
   }
}


//______________________________________________________________________________
//0 "HDMI-1" QRect(0,36 1080x1884) Qt::ScreenOrientation(PortraitOrientation) 60
//^ raspi
//#include <QDebug>
//for (int i = 0;  i < scrLs.size ();  i++)
//qDebug () << i << scrLs [i]->name () << scrLs [i]->availableGeometry ()
//<< scrLs [i]->orientation () << scrLs [i]->refreshRate ();

void NEd::Init ()                      // font MUST BE MONOSPACE FIXED WIDTH !!
{ ubyte nr;
  ubyt2 i;
  TStr  s;
  char *f;
   Gui.WinLoad ();
  QFontMetrics fm (Gui.A ()->font ());      // 80 cols - ONLY EVER !!!
   MemSet (s, 'A', 80);   s [80] ='\0';
   Scr.wLn = SC(ubyt2,fm.horizontalAdvance (s));      // cuz monospace can have
   Scr.hCh = SC(ubyt2,fm.height ()+1);                // fractional width sigh
   Scr.hBL = SC(ubyt2,fm.ascent ());
   setMinimumSize  (Scr.wLn/4, Scr.hCh*4);
   setMaximumWidth (Scr.wLn);
   nr = Gui.W ()->size ().height () / Scr.hCh - 1;
//DBG("wLn=`d wCh=`d+`d/80 hCh=`d hBL=`d rows=`d\n"
//    "ascent=`d descent=`d height=`d leading=`d linesp=`d",
//Scr.wLn, Scr.wLn/80, Scr.wLn%80, Scr.hCh, Scr.hBL, nr,
//fm.ascent(), fm.descent(), fm.height(), fm.leading(), fm.lineSpacing());
   EndScr = nr-1;   Scr.pm = new QPixmap (Scr.wLn, (nr+1)*Scr.hCh);
   StrCp (FName, Gui.Arg (0));   StrCp (s,  Gui.Arg (1));   Load ();
   if (*s) {
      if ((i = St2In (s)))  {MoveToMid (i-1, 0);   PutScr ();}
      else {
         for (f = s, FindLen = 0;  *f && (FindLen < 80);  FindLen++)
            FindStr [FindLen] = CHUP (*f++);
         FindStr [FindLen] = '\0';
         FindNxt ();
      }
   }
   PutScr ();   PutIt ();
}

void NEd::Quit ()
{  Gui.WinSave ();  }

int main (int argc, char *argv [])
{ QApplication a (argc, argv);
  NEd w;
   App.Init ();   Gui.Init (& a, & w, "NEd", 'f');   w.Init ();
  int rc = Gui.Loop ();                              w.Quit ();
   return rc;
}
