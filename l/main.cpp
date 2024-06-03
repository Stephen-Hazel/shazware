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

TStr Top, FN [512*1024];   ubyt4 TopLn, NFN;
bool OpDot, OpDir;
char OpSrt;


bool DoDir (void *ptr, char dfx, char *fn)
{  (void)ptr;
   if ((dfx == 'f') && (NFN < BITS (FN)))  StrCp (FN [NFN++], & fn [TopLn]);
   return false;
}


int Cmp (void *v1, void *v2)
{ char *s1 = (char *)v1, *s2 = (char *)v2, *p;
  TStr  d1, d2, x1, x2, t1, t2;
  int   sl1, sl2, x;
   if (OpSrt == 's') {                 // by size
      MemCp (x1, s1, 10);   x1 [10] = '\0';
      MemCp (x2, s2, 10);   x2 [10] = '\0';
      if (x = StrCm (x1, x2))  return x;
   }
   if (OpSrt == 't') {                 // by datetime
      MemCp (x1, & s1 [11], 15);   x1 [15] = '\0';
      MemCp (x2, & s2 [11], 15);   x2 [15] = '\0';
      if (x = StrCm (x1, x2))  return x;
   }
   s1 += 31;   s2 += 31;
   StrCp (d1, s1);   Fn2Path (d1);                         // get subdir
   StrCp (d2, s2);   Fn2Path (d2);
   StrCp (x1, s1);   FnExt (t1, x1);                       // get .ext
   StrCp (x2, s2);   FnExt (t2, x2);
   for (sl1 = 0, p = d1;  p = StrCh (p, '/');  p++)   sl1++;
   for (sl2 = 0, p = d2;  p = StrCh (p, '/');  p++)   sl2++;
   x = sl2 - sl1;                       if (x)  return x;  // #subdir desc
   x = StrCm (d1, d2);                  if (x)  return x;  // subdir order
   x = StrCm (t1, t2);                  if (x)  return x;  // by .ext
   return StrCm (s1, s2);                                  // by fn
}


//______________________________________________________________________________
int main (int argc, char *argv [])
{ File  f;
  TStr  tm, nw, ar, szs, s;
  ubyt4 sz, i, nd;
  Path  p;
DBGTH("l");
   if (getcwd (Top, sizeof (TStr)) == nullptr)
      {DBG ("getcwd failed");   return 99;}
   *ar = '\0';   if (argc >= 2) StrCp (ar, argv [1]);      // parse args
   OpDot = StrCh (ar, '.') ? true : false;
   OpDir = StrCh (ar, 'd') ? true : false;
   OpSrt = '\0';   if (StrCh (ar, 's'))  OpSrt = 's';
                   if (StrCh (ar, 't'))  OpSrt = 't';
   TopLn = StrLn (Top) + 1;
DBG("OpDot=`b OpDir=`b OpSrt=`c Top=`s", OpDot, OpDir, OpSrt, Top);

   nd = 0;
   if (OpDir)  f.DoDir (Top, nullptr, DoDir);
   else {
            nd = (ubyt4) p.DLst (Top, & FN [0],  65535);
      NFN = nd + (ubyt4) p.FLst (Top, & FN [nd], 65535);
      for (i = 0;  i < nd;  i++)  StrAp (FN [i], CC("/"));
   }
DBG("nfn=`d", NFN);
   if (! OpDot)  for (i = 0;  i < NFN;  i++)
      if (StrSt (FN [i], CC("/.")) || (FN [i][0] == '.'))
         MemCp (& FN [i], & FN [i+1], sizeof (FN [0]) * (--NFN - i));

   Now (nw);
   for (i = 0;  i < NFN;  i++) {       // get datetime,size
      if ((StrLn (FN [i])+32) >= sizeof (TStr))
         {DBG ("fn too long `s", FN [i]);   return 99;}
      StrFmt (s, "`s/`s", Top, FN [i]);
      if (i < nd)  StrCp (szs, CC("        --"));
      else {
         sz = f.Size (s);              // len 10
         StrFmt (szs, "`>10d", sz);
      }
      f.TmStr (tm, s);                 // len 19
      StrCp (s, FN [i]);               // s ends up at [31]
      StrFmt (FN [i], "`s `s `s", szs, tm, s);
   }

   Sort (FN, NFN, sizeof (FN [0]), Cmp);

   for (i = 0;  i < NFN;  i++) {
      if (! MemCm (nw, & FN [i][11], 8))    // overwrite w 'today'
         MemCp (& FN [i][11], CC("   today"), 8);
      printf ("%s\n", FN [i]);
   }
   return 0;
}
