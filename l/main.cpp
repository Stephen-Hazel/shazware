/* l.cpp - list off files (like ls but, rrr, my prefs)
   defaults:
       listing only cur dir;  no dot files;  sort by dirVfile,type,name
       (don't ever list .git or .old dirs)
   .  list dot files too
   d  list subdirs too
   s  (Srt)  sort by size
   t         sort by datetime desc
*/

#include "stv/os.h"

TStr  Top,    FN [512*1024];
ubyt4 TopLn, NFN;
char  Srt;


bool DoDir (void *ptr, char dfx, char *fn)
{  (void)ptr;
   if ((dfx == 'f') && (NFN < BITS (FN)))  StrCp (FN [NFN++], & fn [TopLn]);
   return false;
}


int Cmp (void *v1, void *v2)
{ char *s1 = (char *)v1, *s2 = (char *)v2, *p;
  TStr  d1, d2, x1, x2, t1, t2;
  int   n1, n2, sl1, sl2, x, min;
   if (Srt == 's') {                   // by size
      MemCp (x1, s1, 10);   x1 [10] = '\0';
      MemCp (x2, s2, 10);   x2 [10] = '\0';
      if (x = StrCm (x1, x2))  return x;
   }
   if (Srt == 't') {                   // by datetime
      MemCp (x1, & s1 [11], 15);   x1 [15] = '\0';
      MemCp (x2, & s2 [11], 15);   x2 [15] = '\0';
      if ((*x1 != ' ') && (*x2 == ' '))  return -1;
      if ((*x1 == ' ') && (*x2 != ' '))  return  1;        // today, yest :/
      if (x = StrCm (x1, x2))  return x;
   }
   s1 += 31;   s2 += 31;
   StrCp (d1, s1);    Fn2Path (d1);                        // get subdir
   StrCp (d2, s2);    Fn2Path (d2);
   n1 = StrLn (d1);   n2 = StrLn (d2);                     // n len
   for (sl1 = 0, p = s1;  p = StrCh (p, '/');  p++)   sl1++;
   for (sl2 = 0, p = s2;  p = StrCh (p, '/');  p++)   sl2++;
   StrCp (x1, s1);    FnExt (t1, x1);                      // get .ext
   StrCp (x2, s2);    FnExt (t2, x2);
//DBG("s1=`s s2=`s sl1=`d sl2=`d d1=`s d2=`s t1=`s t2=`s",
//s1, s2, sl1, sl2, d1, d2, t1, t2);
   min = n1;   if (n2 < min)  min = n2;
   if (! MemCm (d1, d2, min)) {             // if minlen subdir match
      x = sl2 - sl1;     if (x)  return x;  // #subdir desc
   }
   x = StrCm (d1, d2);   if (x)  return x;  // subdir order
   x = StrCm (t1, t2);   if (x)  return x;  // by .ext
   return StrCm (s1, s2);                   // by fn
}


//______________________________________________________________________________
int main (int argc, char *argv [])
{ File  f;
  char *a;
  TStr  tm, szs, s, td, yd;
  ubyt4 sz, i, nd;
  Path  p;
  bool  dot, dir, x, rats;
DBGTH("l");
   if (getcwd (Top, sizeof (TStr)) == nullptr)
      {DBG ("getcwd failed");   return 99;}
DBG("init top=`s", Top);
   dot = dir = x = rats = false;   Srt = '\0';

   for (i = 1;  i < argc;  i++) {      // parse args
      a = & argv [i][0];
      if (a [1] == '\0') {
         if      (*a == '.')  dot = true;   // .  show .dotfiles
         else if (*a == 'd')  dir = true;   // d  deep dir list
         else if (*a == 'x')  x   = true;   // x  just dir/filename
         else if (*a == 's')  Srt = 's';    // s  sort by size
         else if (*a == 't')  Srt = 't';    // t  sort by datetime
      }
      else  {StrAp (Top, CC("/"));   StrAp (Top, a);}
   }
DBG(".=`b d=`b x=`b srt=`c top=`s", dot, dir, x, Srt, Top);

// list em
   TopLn = StrLn (Top) + 1;
   nd = 0;
   if (dir)  f.DoDir (Top, nullptr, DoDir);      // deep
   else {                                        // flat
            nd = (ubyt4) p.DLst (Top, & FN [0],  65535);
      for (i = 0;  i < nd;  i++)  StrAp (FN [i], CC("/"));
      NFN = nd + (ubyt4) p.FLst (Top, & FN [nd], 65535);
   }
   if (NFN == BITS (FN))  rats = true;

DBG("pre . nfn=`d nd=`d rats=`b", NFN, nd, rats);
   if (! dot)  for (i = 0;  i < NFN;) {
      StrCp (s, FN [i]);   Fn2Name (s);
      if (StrSt (FN [i], CC("/.")) || (s [0] == '.'))
            MemCp (& FN [i], & FN [i+1], sizeof (FN [0]) * (--NFN - i));
      else  i++;
   }
DBG("nfn=`d nd=`d", NFN, nd);

// get size n datetime
   Now (td);   Now (yd, -60*60*24);
   for (i = 0;  i < NFN;  i++) {
      if ((StrLn (FN [i])+32) >= sizeof (TStr))
         {DBG ("fn too long `s", FN [i]);   return 99;}
      StrFmt (s, "`s/`s", Top, FN [i]);

      if (i < nd)  StrCp (szs, CC("        --"));
      else {sz = f.Size (s);   StrFmt (szs, "`>10d", sz);}      // len 10

      f.TmStr (tm, s);                 // len 19  n overwrite today,yest
      if (! MemCm (tm, td, 8))  MemCp (tm, CC("   today"), 8);
      if (! MemCm (tm, yd, 8))  MemCp (tm, CC("    yest"), 8);

      StrCp (s, FN [i]);               // s ends up at [31]
      StrFmt (FN [i], "`s `s `s", szs, tm, s);
   }
DBG("got sz,dt nfn=`d nd=`d", NFN, nd);

   Sort (FN, NFN, sizeof (FN [0]), Cmp);
DBG("sorted nfn=`d", NFN, nd);

// dump em
   for (i = 0;  i < NFN;  i++)  printf ("%s\n", & FN [i][x ? 31 : 0]);
   if (rats)  printf ("ran outa space for filenames :(\n");

   return 0;
}
