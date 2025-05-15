// ftx.cpp

#include "ftx.h"

void FTx::DClk (int row, int col)
{ BStr fn, fs, pf, pa; (void)col;
//DBG("DClk bgn r=`d", row);
   if (row == -1)  return;

   StrCp (fn, UnQS (ui->tblList->item (row, 0)->text ()));
   StrCp (fs, UnQS (ui->ledFind->text ()));
   StrFmt (pf, "`s/`s", _dir, fn);
   App.Spinoff (StrFmt (pa, "ned `p `s", pf, fs));
}


void FTx::Clik ()
{ ulong row, r, got = 0, o, m, sln;
  BStr  s1, buf;
  TStr  s, s2;
  char *sp, *psp, *tr, *nt;
  bool  go;
  StrArr tx (CC("txt"), 200000, 100000*sizeof (TStr));
  QColor bl, pi (CC("#FF0080"));
   row = ui->tblList->currentRow ();
//DBG("Clik bgn r=`d", row);
   if (row == SC(ulong,-1))  return;

   StrCp (s2, UnQS (ui->tblList->item (row, 0)->text ()));
   StrCp (s, _dir);   StrAp (s, CC("/"));   StrAp (s, s2);
   sln  = StrLn (_s);

//DBG("fn=`s str=`s", s, _s);
   nt = tx.Load (s);
//DBG("nt=`s", nt?nt:"");
//tx.Dump ();
  CtlText te (ui->txtShow);
   bl = te.Fg ();
   te.Clr ();   te.SetFg (bl);
   if (nt) {
      te.Add (
         CC("...doesn't seem to be a regular text file\n\n"));
      return;
   }
   for (r = 0;  r < tx.num;  r++)  if (StrSt (tx.str [r], _s)) {
//DBG("r=`d ngot=`d", r, got);
      if (got >= 100)
         {te.Add (CC("\n\nENOUGH !!\n"));   break;}

   // div-er if already got any
      if (got) {
         te.SetFg (pi);
         te.Add (CC("________\n\n"));
         te.SetFg (bl);
      }

   // draw pre-find
      m = 4;   if (r < m)  m = r;
      for (o = 0;  o < m;  o++)
         te.Add (
            StrFmt (s1, "        `s\n", tx.str [r-m+o]));

   // draw 1st found row
      tr = tx.str [r];
      StrFmt (s1, "`>6d  `s\n", r+1, tr);
      tr = & s1 [8];   psp = s1;
      while ((sp = StrSt (tr, _s))) {  // hilite match spots
         MemCp (buf, psp, sp-psp);   buf [sp-psp] = '\0';
         te.Add (buf);   te.SetFg (pi);
         MemCp (buf, sp, sln);   buf [sln] = '\0';
         te.Add (buf);   te.SetFg (bl);
         tr = psp = sp + sln;
      }
      if (*psp)  te.Add (psp);

      for (go = true;  go;) {
         got++;
         if (got >= 100)
            {te.Add (CC("\n\nENOUGH !!\n"));   break;}

      // see if another happens within 4+4 rows, if so do mid n it");
         go = false;
         for (o = 1;  (o <= 9) && (r+o < tx.num);  o++)
            if (StrSt (tx.str [r+o], _s))  {go = true;   break;}
         if (go) {
         // pre-find2
            for (m = 1;  m < o;  m++)
               te.Add (
                  StrFmt (s1, "        `s\n", tx.str [r+m]));

         // 2nd+ found row
            r += o;
            tr = tx.str [r];
            StrFmt (s1, "`>6d  `s\n", r+1, tr);
            tr = & s1 [8];   psp = s1;
            while ((sp = StrSt (tr, _s))) {      // hilite match spots
               MemCp (buf, psp, sp-psp);   buf [sp-psp] = '\0';
               te.Add (buf);
               te.SetFg (pi);
               MemCp (buf, sp, sln);   buf [sln] = '\0';
               te.Add (buf);
               te.SetFg (bl);
               tr = psp = sp + sln;
            }
            if (*psp)  te.Add (psp);
         }
      }

   // draw post-find
      m = 4;   if (r+m >= tx.num)  m = tx.num - r - 1;
      for (o = 0;  o < m;  o++)
         te.Add (
            StrFmt (s1, "        `s\n", tx.str [r+1+o]));
   }
}


char Buf [8*1024*1024];                // buffer a file to search for str _s

bool DoDir (void *ptr, char dfx, char *fn)
// find any files and put em in _tb
{ File  f;
//DBG("DoDir  dfx=`c fn='`s'", dfx, fn);
   if (dfx != 'f')  return false;
  ulong ln = f.Load (fn, Buf, sizeof (Buf));
  FTx  *me = (FTx *)ptr;
   if (MemSt (Buf, me->_s, ln))  me->_tb->Add (fn);
   return false;
}


static int TblCmp (void *p1, void *p2)
{  return StrCm (*((char **)p1), *((char **)p2));  }


void FTx::Find ()
// list off files in this dir w matching str;  show em;  search 1st
{ File f;
  StrArr tb (CC("FNLst"), 20000, 13000*sizeof(TStr));
   StrCp (_dir, UnQS (ui->ledDir->text ()));
   StrCp (_s,   UnQS (ui->ledFind->text ()));
//DBG("Find dir=`s s=`s", _dir, _s);
   if (*_s == '\0')  {Gui.Hey ("I need a string to find...");   return;}

   _tb = & tb;
   f.DoDir (_dir, this, DoDir);
//DBG("found `d", tb.num);
   Sort (tb.str, tb.num, sizeof (tb.str [0]), TblCmp);
   ui->tblList->hide ();
   ui->tblList->clearContents ();
   ui->tblList->setRowCount (tb.num);
  QTableWidgetItem *it;
   for (ulong i = 0;  i < tb.num;  i++) {
      it = ui->tblList->item (i, 0);
      if (! it) {
         it = new QTableWidgetItem;
         ui->tblList->setItem (i, 0, it);
      }
      it->setText (& tb.str [i][StrLn (_dir)+1]);
   }
   ui->tblList->resizeColumnsToContents ();
   ui->tblList->show ();

   if (tb.num)  {ui->tblList->selectRow (0);   Clik ();}
}


void FTx::Dir ()
{ TStr s;                              // pick dir ta search
   StrCp (s, UnQS (ui->ledDir->text ()));
   if (Gui.AskDir (s, "Pick a top directory"))
      {ui->ledDir->setText (s);   StrCp (_dir, s);}
}


//------------------------------------------------------------------------------
void FTx::Init ()
{  StrCp (_s, Gui.Arg (0));   StrCp (_dir, Gui.Arg (1));
   if (! *_dir)  App.CfgGet (CC("ftx_dir"), _dir);
   if (! *_dir)  StrCp (_dir, CC("/home/sh/src/pcheetah/"));
   ui->spl->setSizes (QList<int>() << 100 << 300);
   Gui.WinLoad (ui->spl);
  CtlTabl t;
   t.Init (ui->tblList, "Filename\0");
   ui->tblList->horizontalHeader ()->setSectionResizeMode(QHeaderView::Stretch);
   connect (ui->btnDir,  & QPushButton::clicked,     this, & FTx::Dir);
   connect (ui->btnFind, & QPushButton::clicked,     this, & FTx::Find);
   connect (ui->ledFind, & QLineEdit::returnPressed, this, & FTx::Find);
   connect (ui->tblList, & QTableWidget::itemSelectionChanged,
                                                            this, & FTx::Clik);
   connect (ui->tblList, & QTableWidget::cellDoubleClicked, this, & FTx::DClk);
   if (*_dir)  ui->ledDir->setText (_dir);
   if (*_s)   {ui->ledFind->setText (_s);   Find ();}
}

void FTx::Quit ()
{  App.CfgPut (CC("ftx_dir"), _dir);   Gui.WinSave (ui->spl);  }

int main (int argc, char *argv [])
{ QApplication a (argc, argv);
  FTx w;
DBGTH("FTx");
   App.Init ();   Gui.Init (& a, & w, "FTx", 'f');   w.Init ();
  int rc = Gui.Loop ();                              w.Quit ();
   return rc;
}
