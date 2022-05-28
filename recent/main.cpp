// recent.cpp - list off recent files (<30 days old) in a dir into ./recent.txt

#include "../../stv/os.h"

TStr Top, FNm [512*1024];   ulong NFNm;

bool DoDir (void *ptr, char dfx, char *fn)
{  (void)ptr;
   if ((dfx == 'f') && (NFNm < BITS (FNm)))  StrCp (FNm [NFNm++], fn);
   return false;
}

int Cmp (void *v1, void *v2)           // by str date desc
{ char *s1 = (char *)v1, *s2 = (char *)v2;
   return  StrCm (s2, s1);
}


//______________________________________________________________________________
int main (int argc, char *argv [])
{ File  f;
  TStr  ts;
  ulong i, b;
   if (argc >= 2)  StrCp (Top, argv [1]);
   else if (getcwd (Top, sizeof (TStr)) == nullptr)  *Top = '\0';

   f.DoDir (Top, nullptr, DoDir);
DBG("`d files", NFNm);

   b = StrLn (Top) + 1;
   for (i = 0; i < NFNm; i++) {         // get datetimes
      if ((StrLn (FNm [i])-b+21) >= sizeof (TStr))  DBG("fn too long", FNm [i]);
      else {
         f.TmStr (ts, FNm [i]);
         StrCp (& FNm [i][20], & FNm [i][b]);
         MemCp (FNm [i], ts, 19);
         FNm [i][19] = ' ';
      }
   }
   Sort (FNm, NFNm, sizeof (FNm [0]), Cmp);

// show
   for (i = 0;  i < NFNm;  i++)  printf ("%s\n", FNm [i]);
   return 0;
}
