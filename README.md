
# shazware -- [S]teve [HAZ]el's soft[WARE]

environment:  Qt c++ on Kubuntu, RasPi64, ChromeOS

Uses my stv library of c++ assumed to be in ../../stv/*
add ../../stv/os.cpp, ui.cpp, uiKey.cpp

Also note that font comes from ~/.config/StephenHazel/NEd.conf 's
font and fontpt lines  (or defaults to Monospace 14 and 30 rows)

a .deb for kubuntu and raspi are in the zRelease dir (ignore the resta the junk)

--------------------------------------------------------------------------------

## todo
   NEd needs a find previous :/
   
--------------------------------------------------------------------------------

## big

dumps a big font to the ole console

* console app

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

look in top dir and all files (including those in subdirs) for a text string

#### todo

* spin off dir search in a thread with "busy" and cancel button

--------------------------------------------------------------------------------

## l

my replacement for ls - i know i know - leave me be

* console app

--------------------------------------------------------------------------------

## ned (Nifty text EDitor)

an old school 80 columns monospace (ONLY!) text editor.
originally on the C=64 in 6510 asm.
Then to C on Amiga500,
then msdos,
then MacClassic,
then on win95/10 in barely C++
then on chromeos with Qt, then on kubutu, then RasPi64

#### todo

* find - find all at start with count (maybe cache of row,cols?)
         if FindStr exists,
            pos/count right after filename
            hilite all on screen
      list of FindStr's, not just 1.  sepd by ||| ?
      during replace, if it won't fit within line, warn but don't stop

* get ridda Qt6 runtime error messages on chromeos and see what can be fixed

--------------------------------------------------------------------------------

## recent

list file mod dates under a top dir (like ls -ltr but all subdirs, nicer format)

* console app

--------------------------------------------------------------------------------

## renem

rename all files under a top dir with text editing

#### todo

* find better way for opening text editor...

--------------------------------------------------------------------------------

## undup

find and kill duplicate files in a top level dir (and subdirs, etc)

#### todo
* need to spin off the dup checking in a sep thread with a
 "wait" and cancel button dialog
  cuz i think that's killin it (often sigh)

* and find the PROPER way to pop a text editor on linux
  (is there a proper way??)

--------------------------------------------------------------------------------
