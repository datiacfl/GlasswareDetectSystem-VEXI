/*****************************************************************************
 * IOx11Window.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: X-Windows Interface: Basic definitions
 *
 * (c) 1996-2001 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.14 $
 * $Date: 2001/06/18 10:49:16 $
 *
 */


#ifndef IOX11WINDOW_H
#define IOX11WINDOW_H


#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/XShm.h>


#define  CoordCheckOn(PROC_HANDLE) HBOrGV(PROC_HANDLE,HGcheck,CHECK_TEXT)
#define  CoordCheckOff(PROC_HANDLE) HBAndGV(PROC_HANDLE,HGcheck,(~CHECK_TEXT))

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

#define  UNDERSCORE 	 0
#define  INVISIBLE  	 1

#define  RETURN          13
#define  BACKSPACE       127


typedef struct {
          unsigned char    red;
	  unsigned char    green;
	  unsigned char    blue;
	  
	} IOLut;              /* current color table */




typedef struct {
          HBOOL   alloc;      /* structure allocated */
	  HBOOL   text;       /* text-(TRUE) oder graphics-window */
	  HBOOL   fixed;      /* fixed pixel */
	  int     pixel;      /* current value of (fixed) pixel */
	  short   line_width; /* width for linedrawing */
	  int     line_style; /* LineSolid, LineDoubleDash */
	  short   last_line_width; /* width for linedrawing */
	  int     last_line_style; /* LineSolid, LineDoubleDash */
	  char    line_pattern[MAX_LINE_PATTERN];   /* if LineDoubleDash */
	  int     line_pattern_num; /* number of line_pattern */
	  int     border;     /* border width */
          int     width;      /* width of window */
	  int     height;     /* height of window */
	  int	  code;	      /* Halcon-code for window */
	  Window  window;     /* window - descriptor */
	  int     cursor;     /* index of cursor in CURSOR */
	  int     tshape;     /* index of textcursor */
	  int     screen;     /* Screen - Descriptor */
	  int     disp;       /* Index Display in DDescr */
	  int     mode;       /* Zeichenfunktion in X-Codierung */ 
	  GC      gc;         /* Graphikkontext */
	  int     crs_x;      /* Textcursor-Position X */
	  int     crs_y;      /* Textcursor-Position Y */
			      /* Cursorpositionen sind rel. zu INNEREM */
	  XFontStruct *font;  /* index in Glob.Var. loaded_font[] */
	  char    paint[30];  /* paint mode */
	  int     thresh;     /* for paint mode threshold */
	  HBOOL	  fontused;   /* wurde schon mal in dem Font geschrieben */
	  long	  back;       /* Hintergrundfarbe; braucht man f. Clear */
			      /* bei buffer */
	  char    back_color[40];
	  char    border_color[40];
	  int	  openmode;   /* visible,invisible,transparent,... */
	  int     lut;        /* Index der LUT in D[]->LUTs */
	  HBOOL   fixed_lut;  /* TRUE <=> fixierte LUT (Farbbilder!) */
	  float   hue,saturation,intensity;
	  float   gamma;      /* Gamma Korrektur */
          HBOOL   smooth_image_d; /* Wird gerade ein Bild mit Color-Recovery */
                                  /* in diesem Fenster angezeigt? */
          HBOOL   shm;              /* Do we use shared mem in the window? */
          XImage  *image;           /* Regular image (not using shared mem). */
          XImage  *shm_image;       /* Shared memory image. */
          XShmSegmentInfo *shminfo; /* Shared memory descriptor. */
        } WDescr;

typedef struct {
	  int       lut_index; /* index of lut in LUT if !privat */
	  int       created;   /* 0,1,2,... */
	  Colormap  map;       /* lut; if (map != NULL) => exists */
	  HBOOL     is_used;   /* TRUE if in use */
	  HBOOL     privat;    /* only one window is allowed */
	  HBOOL     map_ok;    /* not used with fix */
	  int       num_user;  /* number of windows usings the map 1..n */
	  IOLut     lut[256];  /* values of lut */
	  } LUT_DESCR;

typedef struct {
	  Display   *display;    /* Verbindung zum Server */
	  char      name[80];    /* Name mit dem Display geoeffnet wurde */
          int       width;       /* Groesse des Bildschirms */
	  int       height;      /* Groesse des Bildschirms */
	  int       planes;      /* Anzahl Ebenen */
	  Visual    *vis;        /* default Visual */
          XVisualInfo vis_info;  /* Info ueber's Visual */
          int       red_shift;   /* Wie will der Server                */
          int       green_shift; /* die Kanaele der Echtfarbenbilder   */
          int       blue_shift;  /* hingeschoben haben?                */
          int       red_clip;    /* Wie will der Server die Kanaele    */
          int       green_clip;  /* der Echtfarbenbilder abgeschnitten */
          int       blue_clip;   /* haben (durch Rechts-Shifts)?       */
	  int       num_grey;    /* Anzahl darstellbare Grauwerte */
	  HBOOL     alloc;       /* Struktur belegt/frei */
	  HBOOL     init_lut;    /* you have to init at first SetLut */
	  LUT_DESCR LUTs[MAX_LUT_SAVE];
	  unsigned long PrivateLutCells[MAX_NUM_GREY];
	  unsigned long SharedLutCells[MAX_GRAPHIC_COLOR];
	  int       NumGrey;    /* number of private grey values in the Lut */
	  int       NumGraphicColors; /* number of Halcon graphic colors     */
	  unsigned char  XGreyTab[256];  /* for IOxDispGrey() */
	  HBOOL     own_lut;
	  HBOOL     UsedByHalcon[256];   /* Halcon entries in Lut */
          HBOOL     use_hp_smoothing;    /* Soll Color Recovery auf den */
                                         /* HP Maschinen verwendet werden? */
          Colormap  smooth_map;          /* Falls ja steht hier die Colormap */
          Visual    *smooth_visual;      /* mit dem zugehoerigen Visual */
          XColor    smooth_colors[256];  /* und den zugehoerigen Farben */
          HBOOL     shm;                 /* Can the display use shared mem? */
	} DDescr;

typedef struct {
	  int       num;                     /* log. Nummer von X-Window */
	  char      name[MAX_CURSOR_LENGTH]; /* Interner Cursorname */
        } IOCursor;

typedef struct {
	  HBOOL      alloc;    /* schon Cursor fuer Window */
	  Cursor    cursor;   /* Cursor ID */
        } DCurs;



#endif
