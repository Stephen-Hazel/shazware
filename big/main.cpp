// big.cpp

#include "../../stv/os.h"


struct {char ch;  char bg [12*12+1];} Font [] = {
{'A', "   AAAAAA   "
      "  AAAAAAAA  "
      " AA      AA "
      "AA        AA"
      "AA        AA"
      "AA        AA"
      "AAAAAAAAAAAA"
      "AAAAAAAAAAAA"
      "AA        AA"
      "AA        AA"
      "AA        AA"
      "AA        AA"},

{'B', "BBBBBBBBBBB "
      "BBBBBBBBBBBB"
      "BB        BB"
      "BB        BB"
      "BB       BB "
      "BBBBBBBBBBB "
      "BBBBBBBBBB  "
      "BB       BB "
      "BB        BB"
      "BB        BB"
      "BBBBBBBBBBBB"
      "BBBBBBBBBBB "},

{'C', " CCCCCCCCCC "
      "CCCCCCCCCCCC"
      "CC        CC"
      "CC          "
      "CC          "
      "CC          "
      "CC          "
      "CC          "
      "CC          "
      "CC        CC"
      "CCCCCCCCCCCC"
      " CCCCCCCCCC "},

{'D', "DDDDDDDDDD  "
      "DDDDDDDDDDD "
      "DD       DDD"
      "DD        DD"
      "DD        DD"
      "DD        DD"
      "DD        DD"
      "DD        DD"
      "DD        DD"
      "DD       DDD"
      "DDDDDDDDDDD "
      "DDDDDDDDDD  "},

{'E', "EEEEEEEEEEEE"
      "EEEEEEEEEEEE"
      "EE          "
      "EE          "
      "EE          "
      "EEEEEE      "
      "EEEEEE      "
      "EE          "
      "EE          "
      "EE          "
      "EEEEEEEEEEEE"
      "EEEEEEEEEEEE"},

{'F', "FFFFFFFFFFFF"
      "FFFFFFFFFFFF"
      "FF          "
      "FF          "
      "FF          "
      "FFFFFF      "
      "FFFFFF      "
      "FF          "
      "FF          "
      "FF          "
      "FF          "
      "FF          "},

{'G', " GGGGGGGGGG "
      "GGGGGGGGGGGG"
      "GG        GG"
      "GG          "
      "GG          "
      "GG          "
      "GG     GGGGG"
      "GG     GGGGG"
      "GG        GG"
      "GG        GG"
      "GGGGGGGGGGGG"
      " GGGGGGGGGG "},

{'H', "HH        HH"
      "HH        HH"
      "HH        HH"
      "HH        HH"
      "HH        HH"
      "HHHHHHHHHHHH"
      "HHHHHHHHHHHH"
      "HH        HH"
      "HH        HH"
      "HH        HH"
      "HH        HH"
      "HH        HH"},

{'I', "IIIIIIIIIIII"
      "IIIIIIIIIIII"
      "     II     "
      "     II     "
      "     II     "
      "     II     "
      "     II     "
      "     II     "
      "     II     "
      "     II     "
      "IIIIIIIIIIII"
      "IIIIIIIIIIII"},

{'J', "JJJJJJJJJJJJ"
      "JJJJJJJJJJJJ"
      "     JJ     "
      "     JJ     "
      "     JJ     "
      "     JJ     "
      "     JJ     "
      "     JJ     "
      "JJ   JJ     "
      "JJ   JJ     "
      "JJJJJJJ     "
      " JJJJJ      "},

{'K', "KK       KKK"
      "KK      KKK "
      "KK     KKK  "
      "KK    KKK   "
      "KK   KKK    "
      "KKKKKKK     "
      "KKKKKKK     "
      "KK   KKK    "
      "KK    KKK   "
      "KK     KKK  "
      "KK      KKK "
      "KK       KKK"},

{'L', "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LL          "
      "LLLLLLLLLLLL"
      "LLLLLLLLLLLL"},

{'M', "MM        MM"
      "MMM      MMM"
      "MMMM    MMMM"
      "MMMMM  MMMMM"
      "MM MMMMMM MM"
      "MM  MMMM  MM"
      "MM   MM   MM"
      "MM        MM"
      "MM        MM"
      "MM        MM"
      "MM        MM"
      "MM        MM"},

{'N', "NN        NN"
      "NNN       NN"
      "NNNN      NN"
      "NNNNN     NN"
      "NN NNN    NN"
      "NN  NNN   NN"
      "NN   NNN  NN"
      "NN    NNN NN"
      "NN     NNNNN"
      "NN      NNNN"
      "NN       NNN"
      "NN        NN"},

{'O', " OOOOOOOOOO "
      "OOOOOOOOOOOO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OO        OO"
      "OOOOOOOOOOOO"
      " OOOOOOOOOO "},

{'P', "PPPPPPPPPPP "
      "PPPPPPPPPPPP"
      "PP        PP"
      "PP        PP"
      "PP        PP"
      "PPPPPPPPPPPP"
      "PPPPPPPPPPP "
      "PP          "
      "PP          "
      "PP          "
      "PP          "
      "PP          "},

{'Q', "  QQQQQQQQ  "
      " QQQQQQQQQQ "
      "QQ        QQ"
      "QQ        QQ"
      "QQ        QQ"
      "QQ        QQ"
      "QQ        QQ"
      "QQ    QQ  QQ"
      "QQ     QQ QQ"
      "QQ      QQQQ"
      " QQQQQQQQQQ "
      "  QQQQQQQ QQ"},

{'R', "RRRRRRRRRRR "
      "RRRRRRRRRRRR"
      "RR        RR"
      "RR        RR"
      "RR        RR"
      "RRRRRRRRRRRR"
      "RRRRRRRRRRR "
      "RR    RR    "
      "RR     RR   "
      "RR      RR  "
      "RR       RR "
      "RR        RR"},

{'S', " SSSSSSSSSS "
      "SSSSSSSSSSSS"
      "SS        SS"
      "SS          "
      "SSS         "
      " SSSSSSSSS  "
      "  SSSSSSSSS "
      "         SSS"
      "          SS"
      "SS        SS"
      "SSSSSSSSSSSS"
      " SSSSSSSSSS "},

{'T', "TTTTTTTTTTTT"
      "TTTTTTTTTTTT"
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "
      "     TT     "},

{'U', "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UU        UU"
      "UUUUUUUUUUUU"
      " UUUUUUUUUU "},

{'V', "VV        VV"
      "VV        VV"
      "VV        VV"
      "VV        VV"
      "VV        VV"
      "VV        VV"
      "VV        VV"
      "VV        VV"
      " VV      VV "
      "  VVV  VVV  "
      "   VVVVVV   "
      "    VVVV    "},

{'W', "WW        WW"
      "WW        WW"
      "WW        WW"
      "WW        WW"
      "WW        WW"
      "WW   WW   WW"
      "WW  WWWW  WW"
      "WW WWWWWW WW"
      "WWWWW  WWWWW"
      "WWWW    WWWW"
      "WWW      WWW"
      "WW        WW"},

{'X', "XX        XX"
      "XXX      XXX"
      " XXX    XXX "
      "  XXX  XXX  "
      "   XXXXXX   "
      "    XXXX    "
      "    XXXX    "
      "   XXXXXX   "
      "  XXX  XXX  "
      " XXX    XXX "
      "XXX      XXX"
      "XX        XX"},

{'Y', "YY        YY"
      "YYY      YYY"
      " YYY    YYY "
      "  YYY  YYY  "
      "   YYYYYY   "
      "    YYYY    "
      "     YY     "
      "     YY     "
      "     YY     "
      "     YY     "
      "     YY     "
      "     YY     "},

{'Z', "ZZZZZZZZZZZZ"
      "ZZZZZZZZZZZZ"
      "        ZZZ "
      "       ZZZ  "
      "      ZZZ   "
      "     ZZZ    "
      "    ZZZ     "
      "   ZZZ      "
      "  ZZZ       "
      " ZZZ        "
      "ZZZZZZZZZZZZ"
      "ZZZZZZZZZZZZ"},

{'1', "     11     "
      "    111     "
      "   1111     "
      "     11     "
      "     11     "
      "     11     "
      "     11     "
      "     11     "
      "     11     "
      "     11     "
      "  11111111  "
      "  11111111  "},

{'2', " 2222222222 "
      "222222222222"
      "22        22"
      "          22"
      "         222"
      "       222  "
      "     222    "
      "   222      "
      " 222        "
      "222         "
      "222222222222"
      "222222222222"},

{'3', " 3333333333 "
      "333333333333"
      "33        33"
      "          33"
      "          33"
      "       3333 "
      "       3333 "
      "          33"
      "          33"
      "33        33"
      "333333333333"
      " 3333333333 "},

{'4', "      444   "
      "     4444   "
      "    44 44   "
      "   44  44   "
      "  44   44   "
      " 44444444444"
      "444444444444"
      "       44   "
      "       44   "
      "       44   "
      "       44   "
      "       44   "},

{'5', "555555555555"
      "555555555555"
      "55          "
      "55          "
      "55          "
      "555555555   "
      "5555555555  "
      "         55 "
      "          55"
      "          55"
      "555555555555"
      "55555555555 "},

{'6', " 6666666666 "
      "666666666666"
      "66        66"
      "66          "
      "66          "
      "66666666666 "
      "666666666666"
      "66        66"
      "66        66"
      "66        66"
      "666666666666"
      " 6666666666 "},

{'7', "777777777777"
      "777777777777"
      "77       77 "
      "        77  "
      "       77   "
      "      77    "
      "     77     "
      "     77     "
      "     77     "
      "     77     "
      "     77     "
      "     77     "},

{'8', " 8888888888 "
      "888888888888"
      "88        88"
      "88        88"
      " 88      88 "
      "  88888888  "
      "  88888888  "
      " 88      88 "
      "88        88"
      "88        88"
      "888888888888"
      " 8888888888 "},

{'9', " 9999999999 "
      "999999999999"
      "99        99"
      "99        99"
      "99        99"
      "999999999999"
      " 99999999999"
      "          99"
      "          99"
      "99        99"
      "999999999999"
      " 9999999999 "},

{'0', "  00000000  "
      " 0000000000 "
      "00       000"
      "00      0 00"
      "00     0  00"
      "00    0   00"
      "00   0    00"
      "00  0     00"
      "00 0      00"
      "000       00"
      " 0000000000 "
      "  00000000  "},

{'!', "     !!     "
      "    !!!!    "
      "    !!!!    "
      "    !!!!    "
      "    !!!!    "
      "    !!!!    "
      "     !!     "
      "     !!     "
      "     !!     "
      "            "
      "     !!     "
      "     !!     "},

{'@', "  @@@@@@@@  "
      " @        @ "
      "@          @"
      "@       @  @"
      "@   @@@@@  @"
      "@  @    @  @"
      "@  @    @  @"
      "@  @    @  @"
      "@   @@@@@  @"
      "@       @@@ "
      " @          "
      "  @@@@@@@@@@"},

{'#', "   ##  ##   "
      "   ##  ##   "
      "   ##  ##   "
      "############"
      "############"
      "   ##  ##   "
      "   ##  ##   "
      "############"
      "############"
      "   ##  ##   "
      "   ##  ##   "
      "   ##  ##   "},

{'$', "     $$     "
      " $$$$$$$$$$ "
      "$$   $$   $$"
      "$$   $$     "
      "$$   $$     "
      " $$$$$$     "
      "     $$$$$$ "
      "     $$   $$"
      "     $$   $$"
      "$$   $$   $$"
      " $$$$$$$$$$ "
      "     $$     "},

{'%', "%%%       %%"
      "%%%      %%%"
      "        %%% "
      "       %%%  "
      "      %%%   "
      "     %%%    "
      "    %%%     "
      "   %%%      "
      "  %%%       "
      " %%%        "
      "%%%      %%%"
      "%%       %%%"},

{'^', "     ^^     "
      "    ^^^^    "
      "   ^^  ^^   "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "},

{'&', "  &&&&      "
      " &&  &&     "
      " && &&      "
      "  &&&       "
      "  &&&       "
      " && &&      "
      "&&   &&     "
      "&&    &&  &&"
      "&&     &&&& "
      " &&    &&&  "
      "  &&&&&& && "
      "          &&"},

{'*', "**        **"
      " **      ** "
      "  **    **  "
      "   **  **   "
      "    ****    "
      "************"
      "************"
      "    ****    "
      "   **  **   "
      "  **    **  "
      " **      ** "
      "**        **"},

{'(', "        ((  "
      "       ((   "
      "      ((    "
      "     ((     "
      "     ((     "
      "     ((     "
      "     ((     "
      "     ((     "
      "     ((     "
      "      ((    "
      "       ((   "
      "        ((  "},

{')', "  ))        "
      "   ))       "
      "    ))      "
      "     ))     "
      "     ))     "
      "     ))     "
      "     ))     "
      "     ))     "
      "     ))     "
      "    ))      "
      "   ))       "
      "  ))        "},

{'-', "            "
      "            "
      "            "
      "            "
      "------------"
      "------------"
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "},

{'_', "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "____________"
      "____________"},

{'=', "            "
      "            "
      "            "
      "============"
      "============"
      "            "
      "============"
      "============"
      "            "
      "            "
      "            "
      "            "},

{'+', "     ++     "
      "     ++     "
      "     ++     "
      "     ++     "
      "     ++     "
      "++++++++++++"
      "++++++++++++"
      "     ++     "
      "     ++     "
      "     ++     "
      "     ++     "
      "     ++     "},

{';', "            "
      "            "
      "            "
      "    ;;;     "
      "    ;;;     "
      "            "
      "            "
      "    ;;;     "
      "    ;;;     "
      "   ;;;      "
      "            "
      "            "},

{':', "            "
      "            "
      "            "
      "    :::     "
      "    :::     "
      "            "
      "            "
      "    :::     "
      "    :::     "
      "            "
      "            "
      "            "},

{'\'',"     ''     "
      "     ''     "
      "    ''      "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "},


{'"', "   ""  ""   "
      "   ""  ""   "
      "  ""  ""    "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "},

{',', "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "    ,,,     "
      "    ,,,     "
      "   ,,,      "},

{'<', "       <<   "
      "      <<    "
      "     <<     "
      "    <<      "
      "   <<       "
      "  <<        "
      "  <<        "
      "   <<       "
      "    <<      "
      "     <<     "
      "      <<    "
      "       <<   "},

{'.', "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "     ...    "
      "     ...    "},

{'>', "  >>        "
      "   >>       "
      "    >>      "
      "     >>     "
      "      >>    "
      "       >>   "
      "       >>   "
      "      >>    "
      "     >>     "
      "    >>      "
      "   >>       "
      "  >>        "},

{'/', "          //"
      "         // "
      "        //  "
      "       //   "
      "      //    "
      "     //     "
      "    //      "
      "   //       "
      "  //        "
      " //         "
      "//          "
      "            "},

{'?', "   ??????   "
      "  ??    ??  "
      " ??      ?? "
      "         ?? "
      "        ??  "
      "       ??   "
      "      ??    "
      "     ??     "
      "     ??     "
      "            "
      "     ??     "
      "     ??     "},

{' ', "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "
      "            "}
};

bool Ital;

void Wd (char *wd)
// do a word in our font that's 12x12 with 2 spaces btw letters
{ char c;
  TStr buf;
  BStr b;
  ulong i, j, len, line;
   StrCp (buf, wd);   len = StrLn (buf);
   line = 14*len + (Ital ? 11 : 0);
   for (i = 0;  i < len;  i++) {       // replace word's letter w font index
      c = CHUP (buf [i]);
      for (j = 0;  j < BITS (Font);  j++)
         if (c == Font [j].ch)  {buf [i] = j;  break;}
      if (j >= BITS (Font))  buf [i] = BITS (Font)-1;      // not found?  space
   }
   for (i = 0;  i < 12;  i++) {        // build scan lines of our word's chars
      MemSet (b, ' ', sizeof (b));
      for (j = 0;  j < len;  j++)
         MemCp (& b [j*14 + (Ital ? (11-i): 0)],
                & Font [SC(int,buf [j])].bg [i*12], 12);
      b [line] = '\0';
      puts (b);
   }
   puts ("\n");
}


int main (int argc, char *argv [])
{ int i = 1;
   if ((argc > 2) && (! StrCm (argv [1], CC("-i"))))  {Ital = true;  i++;}
   for (;  i < argc;  i++)  Wd (argv [i]);
   return 0;
}
