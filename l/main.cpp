// l.cpp - list off files (like ls but, rrr, better?)

#include "../../stv/os.h"

TStr Top, FNm [512*1024];   ulong NFNm;
bool NoDot;

bool DoDir (void *ptr, char dfx, char *fn)
{  (void)ptr;
   if (NoDot && StrSt (fn, CC("/.")))  return false;
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
  TStr  tm, nw, ar, s;
  ulong sz, i, b;
  bool  to = true;                     // show only time cuz all today
   if (getcwd (Top, sizeof (TStr)) == nullptr)
      {DBG ("getcwd failed");   return 99;}
   *ar = '\0';   if (argc >= 2) StrCp (ar, argv [1]);      // parse args
   NoDot = StrCh (ar, '.') ? true : false;

   f.DoDir (Top, nullptr, DoDir);
DBG("`d files nodot=`b", NFNm, NoDot);

   Now (nw);   
   b = StrLn (Top) + 1;
   for (i = 0; i < NFNm; i++) {         // get datetime,size
      if ((StrLn (FNm [i])-b+32) >= sizeof (TStr))
         {DBG ("fn too long `s", FNm [i]);   return 99;}
      sz = f.Size (FNm [i]);           // len 10
      f.TmStr (tm, FNm [i]);           // len 19
      if (MemCm (tm, nw, 8))  to = false;
      StrCp (s,  & FNm [i][b]);
      StrFmt (FNm [i], "`>10d `s `s", sz, tm, s);
   }
   Sort (FNm, NFNm, sizeof (FNm [0]), Cmp);

// show
   b = 0;   if (NFNm)  while (FNm [0][b] == ' ')  b++;
   for (i = 0;  i < NFNm;  i++) {
      MemCp (s, & FNm [i][11+9], 6);   s [6] = '\0';
      if (to) {                                       // squish to time only
         MemCp (& FNm [i][11], s, 6);
         StrCp (& FNm [i][11+6], & FNm [i][30]);
      }
      else if (! MemCm (nw, & FNm [i][11], 8)) {      // overwrite today
         StrFmt (tm, "   today `s    ", s);
         MemCp (& FNm [i][11], tm, StrLn (tm)); 
      }      
      printf ("%s\n", & FNm [i][b]);
   }
   return 0;
}
