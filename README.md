
# shazware -- [S]teve [HAZ]el's soft[WARE]

environment:  Qt c++ in a flatpak

Uses my stv library of c++ assumed to be in ../stv
CMakeList.txt s have ../../stv/os.cpp, ../../stv/ui.cpp, etc

--------------------------------------------------------------------------------

## fp2sh

* console app

```
php script to make a bunch of short bash scripts in current dir 
of all flatpak commands on your system
Or you could just do this manually, too:
   /usr/bin/flatpak run --branch=master --arch=x86_64 --command=big 
	                     --file-forwarding app.shaz.util  $@
	                     
(sorry for it being in php - i'm just not a fan of python)
```

--------------------------------------------------------------------------------

## big

* console app

dumps a big "font" to the ole console

```
    sh@penguin:~/src$ big how are you
    HH        HH   OOOOOOOOOO   WW        WW
    HH        HH  OOOOOOOOOOOO  WW        WW
    HH        HH  OO        OO  WW        WW
    HH        HH  OO        OO  WW        WW
    HH        HH  OO        OO  WW        WW
    HHHHHHHHHHHH  OO        OO  WW   WW   WW
    HHHHHHHHHHHH  OO        OO  WW  WWWW  WW
    HH        HH  OO        OO  WW WWWWWW WW
    HH        HH  OO        OO  WWWWW  WWWWW
    HH        HH  OO        OO  WWWW    WWWW
    HH        HH  OOOOOOOOOOOO  WWW      WWW
    HH        HH   OOOOOOOOOO   WW        WW


       AAAAAA     RRRRRRRRRRR   EEEEEEEEEEEE
      AAAAAAAA    RRRRRRRRRRRR  EEEEEEEEEEEE
     AA      AA   RR        RR  EE
    AA        AA  RR        RR  EE
    AA        AA  RR        RR  EE
    AA        AA  RRRRRRRRRRRR  EEEEEE
    AAAAAAAAAAAA  RRRRRRRRRRR   EEEEEE
    AAAAAAAAAAAA  RR    RR      EE
    AA        AA  RR     RR     EE
    AA        AA  RR      RR    EE
    AA        AA  RR       RR   EEEEEEEEEEEE
    AA        AA  RR        RR  EEEEEEEEEEEE


    YY        YY   OOOOOOOOOO   UU        UU
    YYY      YYY  OOOOOOOOOOOO  UU        UU
     YYY    YYY   OO        OO  UU        UU
      YYY  YYY    OO        OO  UU        UU
       YYYYYY     OO        OO  UU        UU
        YYYY      OO        OO  UU        UU
         YY       OO        OO  UU        UU
         YY       OO        OO  UU        UU
         YY       OO        OO  UU        UU
         YY       OO        OO  UU        UU
         YY       OOOOOOOOOOOO  UUUUUUUUUUUU
         YY        OOOOOOOOOO    UUUUUUUUUU


    sh@penguin:~/src$ big -i man
               MM        MM     AAAAAA     NN        NN
              MMM      MMM    AAAAAAAA    NNN       NN
             MMMM    MMMM   AA      AA   NNNN      NN
            MMMMM  MMMMM  AA        AA  NNNNN     NN
           MM MMMMMM MM  AA        AA  NN NNN    NN
          MM  MMMM  MM  AA        AA  NN  NNN   NN
         MM   MM   MM  AAAAAAAAAAAA  NN   NNN  NN
        MM        MM  AAAAAAAAAAAA  NN    NNN NN
       MM        MM  AA        AA  NN     NNNNN
      MM        MM  AA        AA  NN      NNNN
     MM        MM  AA        AA  NN       NNN
    MM        MM  AA        AA  NN        NN
```

--------------------------------------------------------------------------------

## flatten

flatten all the files in the subdirs of a top dir into the top dir as
subdir1_subsubdir1_filename.txt

--------------------------------------------------------------------------------

## ftx

Find Text

look for a text string in top dir and all files of subdirs

--------------------------------------------------------------------------------

## l

* console app

my replacement for ls - i know i know - leave me be

--------------------------------------------------------------------------------

## ned (Nifty text EDitor)

an old school 80 columns monospace (ONLY!) text editor.
originally on the C=64 in 6510 asm.
Then to C on Amiga500,
then msdos,
then MacClassic,
then on win95/10 in barely C++
then on chromeos with Qt, then on kubutu, then RasPi64

--------------------------------------------------------------------------------

## recent

* console app

list file mod dates under a top dir (like ls -ltr but all subdirs, nicer format)

--------------------------------------------------------------------------------

## renem

rename all files under a top dir with text editing

--------------------------------------------------------------------------------

## undup

find and kill duplicate files in a top level dir (and subdirs, etc)

--------------------------------------------------------------------------------
