/* l.cpp - list off files (like ls but, rrr, my prefs)
   defaults:
       listing only cur dir;  no dot files;  sort by dirVfile,type,name
       (don't ever list .git or .old dirs)
   .   OpDot  list dot files too
   d   OpDir  list subdirs too
   s   OpSrt  sort by size
   t          sort by datetime desc
*/

#include "stv/os.h"

TStr Top, FNm [512*1024];   ubyt4 NFNm;
bool OpDot, OpDir, LsX;
char OpSrt;


bool DoDir (void *ptr, char dfx, char *fn)
{  (void)ptr;
   if ((! OpDot) && StrSt (fn, CC("/.")))  return false;
   if ((! OpDir) && (dfx == 'x'))
      if (! LsX)  LsX = 'y';
   if (LsX)  return false;

   if ((dfx == 'f') && (NFNm < BITS (FNm)))  StrCp (FNm [NFNm++], fn);
// if ((dfx == 'd') && (NFNm < BITS (FNm))) {StrCp (FNm [NFNm],   fn);
//                                           StrAp (FNm [NFNm++], CC("/"));}
   return false;
}


int Cmp (void *v1, void *v2)
{ char *s1 = (char *)v1, *s2 = (char *)v2;
  TStr  d1, d2, x1, x2, t1, t2;
  int   x;
   if (OpSrt == 's')  if (x = StrCm (s1, s2))  return x;   // by size

   if (OpSrt == 't') {                 // by datetime desc
      MemCp (x1, & s1 [11], 15);   x1 [15] = '\0';
      MemCp (x2, & s2 [11], 15);   x2 [15] = '\0';
      if (x = StrCm (x1, x2))  return x;
   }

   s1 += 31;   s2 += 31;
   StrCp (d1, s1);   Fn2Path (d1);                         // get subdir
   StrCp (d2, s2);   Fn2Path (d2);
   StrCp (x1, s1);   FnExt (t1, x1);                       // get .ext
   StrCp (x2, s2);   FnExt (t2, x2);
   x = (*d1 == '\0') - (*d2 == '\0');   if (x)  return x;  // subdir b4 curdir
   x = StrCm (d1, d2);                  if (x)  return x;  // subdir order
   x = StrCm (t1, t2);                  if (x)  return x;  // by .ext
   return StrCm (s1, s2);                                  // by fn
}


//______________________________________________________________________________
int main (int argc, char *argv [])
{ File  f;
  TStr  tm, nw, ar, s;
  ubyt4 sz, i, b;
DBGTH("l");
   if (getcwd (Top, sizeof (TStr)) == nullptr)
      {DBG ("getcwd failed");   return 99;}
   *ar = '\0';   if (argc >= 2) StrCp (ar, argv [1]);      // parse args
   OpDot = StrCh (ar, '.') ? true : false;
   OpDir = StrCh (ar, 'd') ? true : false;
   OpSrt = '\0';   if (StrCh (ar, 's'))  OpSrt = 's';
                   if (StrCh (ar, 't'))  OpSrt = 't';

   f.DoDir (Top, nullptr, DoDir);
DBG("`d files OpDot=`b OpDir=`b OpSrt=`c", NFNm, OpDot, OpDir, OpSrt);

   Now (nw);
   b = StrLn (Top) + 1;
   for (i = 0; i < NFNm; i++) {        // get datetime,size
      if ((StrLn (FNm [i])-b+32) >= sizeof (TStr))
         {DBG ("fn too long `s", FNm [i]);   return 99;}
      sz = f.Size (FNm [i]);           // len 10
      f.TmStr (tm, FNm [i]);           // len 19
      StrCp (s,  & FNm [i][b]);        // s ends up at [31]
      StrFmt (FNm [i], "`>10d `s `s", sz, tm, s);
   }
   Sort (FNm, NFNm, sizeof (FNm [0]), Cmp);

// show
   for (i = 0;  i < NFNm;  i++) {
      if (! MemCm (nw, & FNm [i][11], 8))   // overwrite w 'today'
         MemCp (& FNm [i][11], CC("   today"), 8);
      printf ("%s\n", FNm [i]);
   }
   return 0;
}
