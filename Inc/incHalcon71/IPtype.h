/*****************************************************************************
 * IPtype.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Types for image processing and language interfaces
 *
 * (c) 1996-2003 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.33 $
 * $Date: 2004/07/20 07:53:47 $
 *
 */


#ifndef IPTYPE_H
#define IPTYPE_H



typedef  UINT1 HBOOL;                  /* TRUE (1) or FALSE (0) */
typedef  UINT1 HBYTE;                  /* unsigned Byte */


/****************************************************************************/
/*  Types for images                                                        */
/****************************************************************************/

typedef void* (*HImageAllocProc)(size_t size);
typedef void  (*HImageFreeProc)(void *mem);

typedef struct {
  float re;                  /* real part                                   */
  float im;                  /* imaginary part                              */
} HComplexPixel;
        
typedef struct {
  INT2 *p;                   /* pointer to gray vales                       */
  INT1 num_bits;             /* number of used bits                         */
} HInt2Pixel;

typedef struct {
  UINT2 *p;                  /* pointer to gray vales                       */
  INT1  num_bits;            /* number of used bits                         */
} HUInt2Pixel;

typedef struct { 
  INT1 *row;                 /* row direction                               */
  INT1 *col;                 /* column direction                            */
} HXYPixel;      

typedef struct {
  HBYTE *b;                  /* 'Gray values' = index in LUTS               */
  INT   num_lut;             /* Length of look up table                     */
  HBYTE red[256];
  HBYTE green[256];
  HBYTE blue[256];
} HLutPixel;

typedef union { 
  HBYTE         *b;         /* 0..255 (BYTE_IMAGE)                          */
  HBYTE         *z;         /* 0..255 mod 256 (CYCLIC_IMAGE)                */
  HBYTE         *d;         /* orientation 0..180 (DIR_IMAGE)               */
  INT1          *i;         /* -127..126 (INT1_IMAGE)                       */
  INT4          *l;         /* 4 byte integer (LONG_IMAGE)                  */
  float         *f;         /* 4 byte real (FLOAT_IMAGE)                    */
  HXYPixel      xy;         /* displacement vector field (XY_IMAGE)         */
  HComplexPixel *c;         /* complex image (COMPLEX_IMAGE)                */
  HLutPixel     lut;        /* byte with LUT (LUT_IMAGE)                    */
  HInt2Pixel    s;          /* 2 bytes with sign (INT2_IMAGE)               */
  HUInt2Pixel   u;          /* 2 bytes without sign (UINT2_IMAGE)           */
} HPixelImage;

typedef struct { 
  INT         kind;         /* pixel type                                   */
  HPixelImage pixel;        /* pixel data                                   */
  INT         width;        /* image width                                  */
  INT         height;       /* image height                                 */
  HImageFreeProc free_proc; /* function for deallocating image data         */
  HBOOL       free;         /* free image data when deleting image          */
  /* time of creation of image                                              */
  UINT2       msec;         /* milliseconds 0..999                          */
  UINT1       sec;          /* seconds 0..59                                */
  UINT1       min;          /* minutes 0.59                                 */
  UINT1       hour;         /* 0..23                                        */
  UINT1       day;          /* 1..31                                        */
  UINT2       yday;         /* 1..366                                       */
  UINT1       mon;          /* 1..12                                        */
  UINT2       year;         /* 19xx                                         */
} Himage;

/* Information file for HALCON image file format (.exp)                     */
typedef struct {
  INT4 width;               /* width of image                               */
  INT4 kind;                /* Pixel type                                   */
  INT4 height;              /* height of image                              */
  char info[1000-4];        /* for further use                              */
} Himage_exp;  


typedef HBYTE *Hbits;       /* Binary image                                 */


/****************************************************************************/
/*                       Regionen                                           */
/****************************************************************************/


/* Index range for coordinates of run length regions                        */
#define MIN_COORD INT2_MIN
#define MAX_COORD INT2_MAX


/* Data type for a single run of a region encoded with runlength encoding   */
typedef struct { 
  INT2 l;                   /* line number (row) of run                     */
  INT2 cb;                  /* column index of beginning of run             */
  INT2 ce;                  /* column index of ending of run                */ 
} Hrun;

/* vertical run */
typedef struct { 
  INT2 c;                   /* column index of run                          */
  INT2 lb;                  /* row index of beginning of run                */
  INT2 le;                  /* row index of ending of run                   */
} Hvrun;

#define SHAPE_RECTANGLE1     (UINT1)1
#define SHAPE_RECTANGLE2     (UINT1)2
#define SHAPE_CIRCLE         (UINT1)3
#define SHAPE_ELLIPSE        (UINT1)4

/* Bit-array to check if a feature of a region was calculated               */
typedef struct {
  unsigned int shape               : 1;
  unsigned int is_convex           : 1;
  unsigned int is_filled           : 1;
  unsigned int is_connected4       : 1;
  unsigned int is_connected8       : 1;
  unsigned int is_thin             : 1;
  unsigned int circularity         : 1;
  unsigned int compactness         : 1;
  unsigned int contlength          : 1;
  unsigned int convexity           : 1;
  unsigned int phi                 : 1;
  unsigned int elliptic_axis       : 1;   /* ra, rb                         */
  unsigned int elliptic_shape      : 1;   /* ra_, rb_                       */
  unsigned int excentricity        : 1;   /* anisometry,bulkiness,str_faktor*/
  unsigned int moments             : 1;   /* m11, m20, m02, ia, ib          */
  unsigned int center_area         : 1;   /* row, col, area                 */
  unsigned int smallest_rectangle1 : 1;   /* row1,col1,row2,col2            */
  unsigned int smallest_rectangle2 : 1;   /* row_rect, col_rect, phi_rect,  */
					  /* length1, length2               */
  unsigned int smallest_circle     : 1;   /* row_circle, col_circle, radius */
  unsigned int min_max_chord       : 1;   /* longest/shortest run           */
  unsigned int min_max_chord_gap   : 1;   /* longest/shortest run (holes)   */
} HFeatureFlags;


/* Shape feature caching inside the region structure                        */
typedef struct { 
  union {
    HFeatureFlags single;
    long          all;      /* if possible use 64 bits!                     */
  }               def;
  UINT1 shape;              /* SHAPE_*                                      */
  HBOOL is_convex;
  HBOOL is_filled;
  HBOOL is_connected4;
  HBOOL is_connected8;
  HBOOL is_thin;            /* one pixel thin                               */
  float circularity;
  float compactness;
  float contlength;
  float convexity;
  float phi;
  float ra, rb;             /* elliptic_axis                                */
  float ra_, rb_;           /* elliptic_shape                               */
  float anisometry, bulkiness, structure_factor;
  float m11, m20, m02, ia, ib;
  float row, col;
  INT4  area;
  INT2  row1,col1,row2,col2;
  float row_rect, col_rect, phi_rect, length1, length2;
  float row_circle, col_circle, radius;
  INT2  min_chord, max_chord;
  INT2  min_chord_gap, max_chord_gap;
} HRegFeature;
  
/* Dummy region; used to calculate the minimum amount of memory needed      */
typedef struct { 
  HBOOL       is_compl;     /* region is complement                         */
  INT4        num;          /* number of runs                               */
  INT4        num_max;      /* maximum number of runs                       */
  HRegFeature feature;      /* already processed features                   */
  Hrun        rl[1];        /* array of runs                                */
} Hrlregion_min;

typedef struct { 
  HBOOL       is_compl;     /* region is complement                         */
  INT4        num;          /* number of runs                               */
  INT4        num_max;      /* maximum number of runs                       */
  HRegFeature feature;      /* already processed features                   */
  Hrun        rl[RL_LENGTH];/* array of runs                                */
} Hrlregion;


/* vertical runlength encoding */
typedef struct { 
  HBOOL       is_compl;     /* region is complement                         */
  INT4        num;          /* number of runs                               */
  INT4        num_max;      /* maximum number of runs                       */
  HRegFeature feature;      /* already processed features                   */
  Hvrun       rc[RL_LENGTH];/* array of runs                                */
} Hvrlregion;

/* Data structure for fast single pixel access for Hrlregion regions        */
typedef struct { 
  INT2  min,max;            /* Min/Max row index                            */
  Hrun  *rl;                /* pointer to runs of the region                */
  INT4  *first;             /* array of index values (row begin)            */
  INT4  *last;              /* array of index values (row end)              */
  HBOOL *no_row;            /* is there this row available?                 */
} Hrlaccess;


/****************************************
 *
 ****************************************/ 
               
/* Simple contour type */
typedef struct {
  INT2 cl[MAX_CONTOUR_LENGTH];  /* row values                               */
  INT2 cc[MAX_CONTOUR_LENGTH];  /* columns values                           */
  INT4 num;                     /* length of contour (number of points)     */
} Hcontour;

/* Short simple contour */
typedef struct {
  INT2 cl[MAX_CONTOURS_LENGTH]; /* row values                               */
  INT2 cc[MAX_CONTOURS_LENGTH]; /* columns values                           */
  INT4 num;                     /* length of contour (number of points)     */
} Hscontour;

/* simple contour with float coordinates                                    */
typedef struct {
  float row[MAX_CONTOUR_LENGTH]; /* row values                              */
  float col[MAX_CONTOUR_LENGTH]; /* columns values                          */
  INT4  num;                     /* length of contour (number of points)    */
} Hfcontour;

/* simple contour with long coordinates and variable allocation length */
typedef struct {
  INT4 *row;     /* row values                           */
  INT4 *col;     /* columns values                       */
  INT4 num;      /* length of contour (number of points) */
  INT4 max_num;  /* allocated points of contour          */
} Hlcontvar;

/* simple contour with short coordinates and variable allocation length */
typedef struct {
  INT2 *row;     /* row values                           */
  INT2 *col;     /* columns values                       */
  INT4 num;      /* length of contour (number of points) */
  INT4 max_num;  /* allocated points of contour          */
} Hscontvar;

/* simple contour with float coordinates and variable allocation length */
typedef struct {
  float *row;    /* row values                           */
  float *col;    /* columns values                       */
  INT4 num;      /* length of contour (number of points) */
  INT4 max_num;  /* allocated points of contour          */
} Hfcontvar;

/* Countour as chain code                                                   */
typedef struct {
  INT2  l,c;                     /* Start point (row,column)                */
  HBYTE cc[MAX_CHAIN_LENGTH];    /* array of chain code                     */
  INT4  num;                     /* length of contour (number of points)    */
} Hchain_code;

	
/* line (start and end point)                                               */
typedef struct {
  float row1, col1;         /* Start point                                  */
  float row2, col2;         /* End point                                    */
} Hline;

/* Array of lines                                                           */
typedef struct {
  INT4  num;
  Hline line[MAX_CONTOUR_LENGTH];
} Hlines;

/* Dummy (to check the minimum amount of memory)                            */
typedef struct {
  INT4  num;
  Hline line[1];
} Hlines_min;


/****************************************************************************/
/*                       Distribution                                       */
/****************************************************************************/

typedef INT4 Hhisto_abs[256];

typedef float Hhisto_rel[256];

#define MAX_DISTR   (2*256+1)
#define NULL_DISTR  256

typedef INT4 Hdistrib_abs[MAX_DISTR];

typedef float Hdistrib_rel[MAX_DISTR];



/****************************************************************************/
/*              Misc. image processing                                      */
/****************************************************************************/

/* Convolution (Convol and FFT)                                             */
typedef struct {
  INT4  f;
  INT4  gk[MAX_WC_NUM]; 
} Hconv_mask_s;

/* 2 dimensional convolution masks                                          */
typedef struct {
  INT2 min_row,max_row;
  INT2 min_col,max_col;
  INT4 norm;
  INT4 num;
  INT2 row[MAX_CONVOL];
  INT2 col[MAX_CONVOL];
  INT4 koor[MAX_CONVOL];
  INT4 m[MAX_CONVOL];
} Hconv_mask_2;

/* 1 dimensional convolution masks                                          */
typedef struct {
  INT4 min_col,max_col;
  INT4 norm;
  INT4 num;
  INT4 col[MAX_CONVOL];
  INT4 m[MAX_CONVOL];
} Hconv_mask_1;


/* Color (name plus RGB values)                                             */
typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  char          name[MAX_COLOR_NAME_LENGTH];
} Hcolor;



/****************************************************************************/
/*                  Extended Line Description (XLD)                         */
/****************************************************************************/

#define MAX_CONT_NUM      50000     /* Maximum number of contours           */
#define MAX_CONT_LEN      20000     /* Maximum length of contour            */
#define MAX_POLY_NUM      50000     /* Maximum number of polygons           */


/****************************************************************************/
/* XLD-Object Contour                                                       */
/****************************************************************************/

typedef enum cont_class {
  cont_unknown,     /* unknown                                              */
  cont_no_junc,     /* neither start nor end point points are junctions     */
  cont_start_junc,  /* start point is a junction                            */
  cont_end_junc,    /* end point is a junction                              */
  cont_both_junc,   /* both start and end point are junctions               */
  cont_closed       /* closed contour                                       */
} Hcont_class;

typedef struct cont_attrib {
  char  *name;      /* name of the attribute                                */
  float *val;       /* value of the attribute (per point)                   */
} Hcont_attrib;

typedef struct cont_global_attrib {
  char  *name;      /* name of the global attribute                         */
  float val;        /* value of the attribute (per contour)                 */
} Hcont_global_attrib;

typedef struct cont_type {
  INT4                num;        /* number of points along the contour     */
  float               *row;       /* points / row indices (y coordinates)   */
  float               *col;       /* points / column indices (x coord.)     */
  Hcont_class         cont_class; /* contour class                          */
  INT4                num_attrib; /* number of additional attributes        */
  Hcont_attrib        *attribs;   /* additional attributes (for each point) */
  INT4                num_global; /* number of additional global attributes */
  Hcont_global_attrib *global;    /* additional attributes (per contour)    */
  INT4                h;          /* auxiliary (temporary)                  */
} Hcont;


/****************************************************************************/
/* XLD-Objects: polygons                                                    */
/****************************************************************************/

typedef struct lin_seg_type {
  float row,col;  /* control points of the polygon                          */
  float length;   /* length of the line from the current to the next point  */
  float phi;      /* orientation (rad) of this line                         */
  Hkey  ref;      /* data base key of the underlying contour                */
  INT4  first;    /* index of the first point of the underlying contour     */
  INT4  last;     /* index of the last contour point                        */
} Hline_seg;

typedef struct poly_type {
  INT4      num_line;  /* number of lines                                   */
  INT4      len_line;  /* maximum number of lines (size of the array lines) */
  Hline_seg *lines;    /* control points of the polygon                     */
} Hpoly;


/****************************************************************************/
/* XLD-Objects: parallels                                                   */
/****************************************************************************/

typedef struct para_poly_type {
  Hkey   poly1;      /* Pointer to 1st polygon of the relation (P1)         */
  Hkey   poly2;      /* Pointer to 2nd polygon of the relation (P2)         */
  INT4   first1;     /* Index of the start line segm. of the parallel in P1 */
  INT4   last1;      /* Index of the end line segment of the parallel in P1 */
  INT4   first2;     /* Index of the start line segm. of the parallel in P2 */
  INT4   last2;      /* Index of the end line segment of the parallel in P2 */
  double quality;    /* Measure of the degree of parallelism of the polygons*/
} Hpara_poly;


/****************************************************************************/
/* XLD-Objects parallel object borders                                      */
/****************************************************************************/

typedef struct mod_para_type {
  Hkey  poly1;       /* Pointer to 1st polygon of the relation (P1)         */
  Hkey  poly2;       /* Pointer to 2nd polygon of the relation (P2)         */
  INT4  first1;      /* Index of the start line segm. of the parallel in P1 */
  INT4  last1;       /* Index of the end line segment of the parallel in P1 */
  INT4  first2;      /* Index of the start line segm. of the parallel in P2 */
  INT4  last2;       /* Index of the end line segment of the parallel in P2 */
  float first1_dist; /* Half distance of the first line of P1 to P2         */
  float last1_dist;  /* Half distance of the last line of P1 to P2          */
  float first2_dist; /* Half distance of the first line of P2 to P1         */
  float last2_dist;  /* Half distance of the last line of P2 to P1          */
  INT2  dir1;        /* Position of P1 relative to P2:                      */
                     /*   dir1 = 1: P2 is to the right of P1                */
                     /*   dir1 = -1: P2 is to the left of P1                */
  INT2  dir2;        /* Position of P2 relative to P1:                      */
                     /*   dir2 = 1: P1 is to the right of P2                */
                     /*   dir2 = -1: P1 is to the left of P2                */
} Hmod_para;

/****************************************************************************/
/* XLD-Objects Extended object borders                                      */
/****************************************************************************/

typedef struct ext_para_type {
  Hkey poly1;        /* Pointer to 1st polygon of the relation (P1)         */
  Hkey poly2;        /* Pointer to 2nd polygon of the relation (P2)         */
  INT4 first1;       /* Index of the start line segm. of the parallel in P1 */
  INT4 last1;        /* Index of the end line segment of the parallel in P1 */
  INT4 first2;       /* Index of the start line segm. of the parallel in P2 */
  INT4 last2;        /* Index of the end line segment of the parallel in P2 */
} Hext_para;


/****************************************************************************/
/* Homogeneous coordiantes: Hhom_mat_[23]d / Hproj_mat_2d                   */
/****************************************************************************/
typedef double Hhom_mat_2d[2][3];
typedef double Hhom_mat_3d[3][4];
typedef double Hproj_mat_2d[3][3];



/****************************************************************************/
/* 1D-Functions                                                             */
/****************************************************************************/

typedef struct {
  INT4  num;          /* Number of elements in x and y                      */
  float *x;           /* Array of the x-values of the function (always set) */
  float *y;           /* Array of the y-values of the function              */
  float xmin;         /* Minimum x value (always set)                       */
  float xmax;         /* Maximum x value (always set)                       */
  float xdist;        /* Distance of x-values if they are equidistant       */
  HBOOL is_equidist;  /* Are the x-values equidistant?                      */
} Hfunction_1d;




/****************************************************************************/
/*  Parameter passing (inside library and for language interfaces)          */
/****************************************************************************/
                 
typedef union {
  INT4_8 *l;                /* 4-8 Byte integer                             */
  double *f;                /* 8 Byte real                                  */
  char   *s;                /* Pointer to string                            */
} DPHpar;                   /* For HALCON/C                                 */

                 
typedef union {
  INT4_8  l;                /* 4-8 Byte integer                             */
  double  f;                /* 8 Byte real                                  */
  char    *s;               /* Pointer to string                            */
} DVHpar;                   /* For HALCON/C                                 */




#endif
