#ifndef NED_H
#define NED_H

#include "../../stv/ui.h"
#include "../../stv/uiKey.h"

#include <QPainter>

#define MAX_ROW    (32000)   // max # of rows Ned will hold
#define ROWS2GRAB  (64)      // rows to alloc at a time (must % MAX_ROW!!!)
#define MAX_SQNC   (80)      // maximum keys in a sequence
#define TAB_LEN    (3)       // # of spaces to turn tabs into on load/paste

typedef struct {key Key;   ubyte Map [3];}  cmdmap;

typedef struct {ubyte Len;   char Col [80];}  row;
typedef struct memTag {row Mem [ROWS2GRAB];   memTag *Nxt;} mem;
typedef row  *prow;
typedef char *pcol;          // pointer to a particular row's columns
typedef mem  *pmem;

typedef struct {QPixmap *pm;   ubyt2 wLn, hCh, hBL;   ubyte min, max;} ScrDef;
typedef struct {ubyt2 ro;   ubyte co;} FPosDef;

// all those nasty globs...
extern pmem   MemTop;                     // memory management
extern prow   Row [];
extern ubyt2  FreeRows;
extern ubyt2  CsrRow, EndRow;             // scrolling, cursor pos
extern ubyte  CsrCol, ScrRow, EndScr;
extern bool   Over, Sqnc;                 // those damn flag type vars
extern ubyt2  BlkBgnRow, BlkEndRow;       // block marking params
extern ubyte  BlkBgnCol, BlkEndCol;
extern char   FindStr [], RplcStr [], FName [];  // strings
extern ubyte  FindLen,    RplcLen;
extern FPosDef F [100000];
extern ubyt4   FLn;
extern key    KeySqnc [];                 // (weak) macro control
extern ubyte  SqncLen;
extern bool (*Cmd [])();                  // command key mapping
extern cmdmap CmdMap [];
extern ubyte  CmdLen;
extern char   KeyMode, *KMMsg, *KMBuf, KM1;
extern bool (*KMCmd)();
extern row    Info, Empt;
extern ScrDef Scr;


// Ned UI stuff
void PutRow  (ubyte ScrPos);
void PutScr  ();
bool PutBlk  ();               // ...this guy is one of the BlkCmds
void JotDn   (char Key);
void DoKey   (key Key);

// declarations for SubCmds.c
char  ToUpper   (char c);
bool  StrICmp   (char *str, pcol col);
ubyt2 St2In     (char *Str);
void  In2St     (ubyt2 Int, ubyte Len, char *Str);
ubyte CsrRowLen (void);
pcol  CsrRowPtr (void);
bool  OnScr     (ubyt2 Ro);
void  MoveTo    (ubyt2 Ro, ubyte Co);
void  MoveToMid (ubyt2 Ro, ubyte Co);
bool  ExtendSpc (ubyt2 Ro, ubyte Ln);
void  ShrinkEnd (void);
void  ShrinkLen (ubyt2 Ro);
bool  InsRows   (ubyt2 Ro, ubyt2 Ln);
void  DelRows   (ubyt2 Ro, ubyt2 Ln);
bool  InsCols   (ubyt2 Ro, ubyte Co, ubyte Ln);
void  DelCols   (ubyt2 Ro, ubyte Co, ubyte Ln);
bool  CopyCols  (ubyt2 SRo, ubyte SCo, ubyt2 DRo, ubyte DCo, ubyte Ln);
bool  MoveCols  (ubyt2 SRo, ubyte SCo, ubyt2 DRo, ubyte DCo, ubyte Ln);

// all the standard Ned Cmds...
bool Rit(), Lft(), Up(), Dn(), Top(), Bot(), BlkHop(), PgUp(), PgDn(),
     WrdRit(), WrdEnd(), WrdLft(),
     TglOver(), TglWrap(), Del(), Tab(), Cntr (), Rtrn(), Split(),
     InsRow(), DelRow(), DelWrdRit(), DelWrdLft(),
     BlkBgn(), BlkEnd(), BlkAll(),
     BlkRit(), BlkLft(),
     BlkDel(), BlkCopy(), BlkMove(), BlkFmt (),
     BlkCpy(), BlkPst(), BlkSum(),
     Find(), ReFind (), FindNxt(), FindPrv(), Rplc(), RplcNxt (),
     Wipe(), Load(), Save(), SaveAs(), Quit(),
     UnDelRow(), TglSqnc(), RptSqnc(), UpCase(), LoCase(), EndCmd();


//------------------------------------------------------------------------------
class NEd: public QMainWindow {
   Q_OBJECT
public:
   explicit NEd (QWidget *parent = nullptr): QMainWindow (parent)  {}
           ~NEd ()  {Wipe ();   if (Scr.pm)  delete Scr.pm;}
   void Init (), Quit ();

protected:
   void wheelEvent    (QWheelEvent  *e);
   void keyPressEvent (QKeyEvent    *e);
   void paintEvent    (QPaintEvent  *e);
   void resizeEvent   (QResizeEvent *e);
};

#endif // NED_H
