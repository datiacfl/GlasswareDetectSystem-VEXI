/*****************************************************************************
 * IOWIN32Window.h
 ***************************************************************************** 
 *
 * Project:      HALCON/libhalcon
 * Author:       J. Cmarits
 * Description:  header file for Windows NT-specific IO-files  
 *
 * (c) 1996-2003 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.18 $
 * $Date: 2004/11/05 09:07:13 $
 *
 */


#ifndef IOWIN32WINDOW_H
#define IOWIN32WINDOW_H


#include "Halcon.h"




/* FENSTER EXTRABYTES OFFSET */
#define  HALCON_DWNDINDEX  0

  
#define CoordCheckOn(PROC_HANDLE) HBOrGV(PROC_HANDLE,HGcheck,CHECK_TEXT)
#define CoordCheckOff(PROC_HANDLE) HBAndGV(PROC_HANDLE,HGcheck,(~CHECK_TEXT))
#define CoordCheck(proc_handle, ResultC) \
              {INT4 che_ck;\
              HReadGV(proc_handle, HGcheck, &che_ck);\
              ResultC = (che_ck & CHECK_TEXT); }
              /* should error be returned if coordinates are out of range */
#define ColorCheck(proc_handle, Result) \
              {INT4 che_ck;\
              HReadGV(proc_handle, HGcheck, &che_ck);\
              Result = (che_ck & CHECK_COLOR); }
              /* should error be returned if color is used on a b/w-terminal */
#define  EIGHT           8
#define  FOUR            4
#define  ONE             1

#define  UNDERSCORE        0
#define  INVISIBLE         1

#define  RETURN          13
#define  BACKSPACE       127

/* fuer Visual: class */
#define  TrueColor       1
#define  StaticGray      2
#define  StaticColor     3


typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} IOLut;              /* current color table */



/*
typedef struct {
  EXTLOGPEN extLogpen;
  DWORD     line_pattern[MAX_LINE_PATTERN];  /* if LineDoubleDash* /
} HEXTLOGPEN;              

*/


typedef struct {
  HBOOL   alloc;      /* structure allocated */
  HBOOL   text;       /* text-(TRUE) oder graphics-window */
  HBOOL   fixed;      /* fixed pixel */
  int     pixel;      /* current value of (fixed) pixel ;*/
  /* index(Palette) oder farbreferenz (kein Palette, TRUECOLOR)*/
  short   line_width; /* width for linedrawing */
  int     line_style; /* LineSolid, LineDoubleDash */
  DWORD   line_pattern[MAX_LINE_PATTERN];  /* if LineDoubleDash*/
  int     line_pattern_num; /* number of line_pattern */
  int     border;     /* border width */
  int     width;      /* width of window */
  int     height;     /* height of window */
  int     code;       /* Halcon-code for window */
  HWND    window;
  int     cursor;     /* index of cursor in CURSOR */
  INT4_8  dwCursor;   /* windowsCursor*/
  int     tshape;     /* index of textcursor */
  int     screen;     /* Screen - Descriptor */
  int     disp;       /* Index Display in DDescr */
  int     mode;       /* Zeichenfunktion in X-Codierung */ 

  /* die nachfolgenden Daten muessen wieder geloescht werden in WM_CLOSE */
  HDC     hdc;  
  HDC     bdc;        /* Graphikkontext dieser wird gesichert*/
  HBITMAP hBitmap;    /* sichern der erzeugten Bitmap die zum Zeichnen */
                      /* verwednet wird*/
  HPEN    hOldPen;    /* alter Stift  wird gesichert*/
  HBRUSH  hOldBrush;  /* alter Pinsel wird gesichert*/
  HBITMAP hOldBitmap; /* sichern der erzeugten Bitmap die zum Zeichnen */
                      /* verwendet wird*/
  HFONT   hOldFont;   /* alter Font wird gesichert*/

  int     crs_x;            /* Textcursor-Position X */
  int     crs_y;            /* Textcursor-Position Y */
  /* Cursorpositionen sind rel. zu INNEREM */
  /* FONT */
  int     fontindex;        /* index in Glob.Var. loaded_font[] */
  HBOOL   fontused;         /* wurde schon mal in dem Font geschrieben */
  char    paint[30];        /* paint mode */
  int     thresh;           /* for paint mode threshold */
  long    back;             /* Hintergrundfarbe; braucht man f. */
  /* Clear bei buffer */
  char    back_color[40];
  char    border_color[40];
  int     openmode;         /* visible,invisible,transparent,... */
  int     lut;              /* Index der LUT in D[]->LUTs */
  HBOOL   fixed_lut;        /* TRUE <=> fixierte LUT (Farbbilder!) */
  float   hue,saturation,intensity;
  float   gamma;            /* Gamma Korrektur */
  HBOOL   smooth_image_d; /* Wird gerade ein Bild mit Color-Recovery */
  /* in diesem Fenster angezeigt? */
  HBOOL   draw_direct;      /* no call of InvalidateRect */
  HBOOL   extern_window;    /* extern created window*/ 
  RECT    invalidate_rect;  /* rectangle mit dem Bereich zum updaten */
} WDescr;


        
        
typedef struct {
  int      lut_index; /* index of lut in LUT if !privat */
  int      created;  /* 0,1,2,... */
  HPALETTE map;   /* lut; if (map != NULL) => exists */
  HBOOL    is_used;  /* TRUE if in use */
  HBOOL    privat;   /* only one window is allowed */
  HBOOL    map_ok;   /* not used with fix */
  int      num_user; /* number of windows usings the map 1..n */
  IOLut    lut[256]; /* values of lut */
} LUT_DESCR;


          
          
typedef struct {
  int class;
} Visual; /* nachbildung von X-Windows */




typedef struct {
  char          name[30]; /* Name mit dem Display geoeffnet wurde */
  int           width;    /* Groesse des Bildschirms */
  int           height;   /* Groesse des Bildschirms */
  int           planes;   /* Anzahl Ebenen */
  Visual        vis;      /* default Visual */
  int           num_grey; /* Anzahl darstellbare Grauwerte */
  HBOOL         alloc;    /* Struktur belegt/frei */
  HBOOL         init_lut; /* you have to init at first SetLut */
  LUT_DESCR     LUTs[MAX_LUT_SAVE];
  unsigned long PrivateLutCells[MAX_NUM_GREY];
  unsigned long SharedLutCells[MAX_GRAPHIC_COLOR];
  int           NumGrey;    /* number of private grey values in the Lut */
  int           NumGraphicColors;  /* number of Halcon graphic colors */
  unsigned char XGreyTab[256];     /* for IOxDispGrey() */
  HBOOL         own_lut;
  HBOOL         UsedByHalcon[256]; /* Halcon entries in Lut */
  HBOOL         use_hp_smoothing;  /* Soll Color Recovery auf den */
                                   /* HP Maschinen verwendet werden? */
} DDescr;

        
        
typedef struct {
  char *pszWinCursorName;       /* Cursorname von MS_WINDOWS IDC_xxx */
  char name[MAX_CURSOR_LENGTH]; /* Interner Cursorname */
} IOCursor;

        
        
typedef struct {
  HBOOL   alloc;      /* schon Cursor fuer Window */
  char*   CursorName; /* Cursor Name */
  HCURSOR hcursor;    /* handle to cursor*/
} DCurs;

        
        
typedef struct {
  HBOOL alloc;        /* schon font fuer das Window*/
  char  szHFName[50]; /* Fontname_PointSize*/
  int   nAnzUsed;
} DFont;

            

#endif
