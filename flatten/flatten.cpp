// flatten.cpp

#include "flatten.h"

bool DoDir (void *ptr, char dfx, char *fn)
// find any files and put em in _tb
{ Flatten *me = (Flatten *)ptr;
//DBG("DoDir dfx=`c fn='`s'", dfx, fn);
   if (dfx == 'f')  me->_tb->Add (fn);
   return false;
}

TStr DLst [1024];

void Flatten::Go ()
// list off files in this dir;  rename em flat;  kill dirs
{ ulong i, j;
  File  f;
  bool  dor;
  TStr  d, fn2;
  StrArr tb (CC("FNLst"), 65536, 20000*sizeof(TStr));
   StrCp (d, UnQS (ui->ledDir->text ()));
DBG("Find dir=`s", d);
   _tb = & tb;   f.DoDir (d, this, DoDir);
DBG("found `d", tb.num);
   for (i = 0;  i < tb.num;  i++) {
      StrCp (fn2, tb.str [i]);  dor = false;
      for (j = StrLn (d)+1;  j < StrLn (fn2);  j++)   // turn / into _ ta flatn
         if (fn2 [j] == '/')  {fn2 [j] = '_';  dor = true;}
      if (dor)  f.ReNm (tb.str [i], fn2);
   }
  Path fd;
   j = fd.DLst (d, DLst, BITS (DLst));
   for (i = 0;  i < j;  i++)  fd.Kill (StrFmt (fn2, "`s/`s", d, DLst [i]));
   Gui.Quit ();
}


void Flatten::Dir ()
{ TStr s;
   StrCp (s, UnQS (ui->ledDir->text ()));
   if (Gui.AskDir (s, "Pick a top directory"))  ui->ledDir->setText (s);
}


//------------------------------------------------------------------------------
void Flatten::Init ()
{ TStr  d;
   Gui.WinLoad ();   
   StrCp (d, Gui.Arg (0));
   if (*d == '\0')  if (getcwd (d, sizeof (TStr)) == nullptr)  *d = '\0';
   if (*d)  ui->ledDir->setText (d);
   connect (ui->btnDir, SIGNAL(clicked()), this, SLOT (Dir()));
   connect (ui->btnGo,  SIGNAL(clicked()), this, SLOT (Go()));
}


void Flatten::Quit ()  {Gui.WinSave ();}


int main (int argc, char *argv [])
{ QApplication a (argc, argv);
  Flatten w;
   App.Init ("Flatten");   Gui.Init (& a, & w);   w.Init ();
  int rc = Gui.Loop ();                           w.Quit ();
   return rc;
}
