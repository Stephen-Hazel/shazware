// RenEm.cpp - rename a buncha files at once via text editor

#include "renem.h"

TStr Top, FNm [128*1024];  ubyt4 NFNm;
TStr      FN2 [128*1024];
File Fo;


bool DoDir (void *ptr, char dfx, char *fn)
// find any files and put em in F[]
{  (void)ptr;
   if ((dfx == 'f') && (NFNm < BITS (FNm)))  StrCp (FNm [NFNm++], fn);
   return false;
}


char *DoRec (char *buf, ubyt2 len, ubyt4 pos, void *ptr)
// parse a record of the file
{ BStr rec;
   (void)ptr;   (void)len;
   FN2 [pos][0] = '\0';
   if (StrCm (buf, & FNm [pos][StrLn (Top)+1], 'x')) {
      Fo.Put (StrFmt (rec, "'`s' => '`s/`s'\n", FNm [pos], Top, buf));
      StrFmt (FN2 [pos], "`s/`s", Top, buf);
   }
   return NULL;
}


void RenEm::Go ()
{ File  f;
  TStr  fn, buf, cmd;
  char *p;
  ubyt4 i, b;
   StrCp (Top, UnQS (ui->ledDir->text ()));
   NFNm = 0;
   f.DoDir (Top, this, DoDir);
DBG ("`d files", NFNm);
   Sort (FNm, NFNm, sizeof (FNm [0]), StrCm2);

// save
   StrFmt (fn, "`s.txt", Top);
   if (! f.Open (fn, "w"))  {DBG ("can't write file=`s", fn);   return;}

   b = StrLn (Top) + 1;
   for (i = 0; i < NFNm; i++)
      {StrCp (buf, & FNm [i][b]);   StrAp (buf, CC("\n"));   f.Put (buf);}
   f.Shut ();
   if (system (StrFmt (cmd, "xdg-open `p", fn)))  {}

   if (Gui.YNo ("rename (IN PLACE !), save, and click Yes when done editing",
                "RenEm?")) {
      StrFmt (buf, "`s_RenEm.txt", Top);
      if (! Fo.Open (buf, "w"))  {DBG ("can't write file=`s", buf);   return;}

      if ((p = f.DoText (fn, NULL, DoRec)))
         {Fo.Shut ();   DBG (p);   return;}
      Fo.Shut ();
      if (system (StrFmt (cmd, "xdg-open `p", buf)))  {}

      if (Gui.YNo ("Gonna -DO- RenEm", "Ok?"))
         for (i = 0; i < NFNm; i++)  if (FN2 [i][0])  Fo.ReNm (FNm [i], FN2[i]);
      f.Kill (buf);
   }
   f.Kill (fn);
   qApp->quit ();
}


void RenEm::Dir ()
{ TStr s;
   StrCp (s, UnQS (ui->ledDir->text ()));
   if (Gui.AskDir (s, "Pick a top directory"))  ui->ledDir->setText (s);
}


//______________________________________________________________________________
void RenEm::Init ()
{ TStr d;
   StrCp (d, Gui.Arg (0));
   if (! *d)  if (getcwd (d, sizeof (TStr)) == nullptr)  *d = '\0';

   Gui.WinLoad ();
   connect (ui->btnDir, SIGNAL (clicked ()), this, SLOT (Dir ()));
   connect (ui->btnGo,  SIGNAL (clicked ()), this, SLOT (Go  ()));

   if (*d)  ui->ledDir->setText (d);
}

void RenEm::Quit ()
{  Gui.WinSave ();  }

int main (int argc, char *argv [])
{ QApplication a (argc, argv);
  RenEm w;
  int r;
   App.Init (CC("shazware"), CC("renem"), CC("RenEm"));
   Gui.Init (& a, & w, 'f');   w.Init ();
  int rc = Gui.Loop ();        w.Quit ();
   return rc;
}
