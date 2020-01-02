/*****************************************************************************
 * HBase.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Basic definitions for Halcon, Halcon/C, Halcon/C++
 *              and other language interfaces
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.24 $
 * $Date: 2007/02/12 14:20:18 $
 *
 */



#ifndef HBASE_H
#define HBASE_H

/*****************************************************************************/
/* Parameter passing (Control parameters)                                    */
/*****************************************************************************/
#define LONG_PAR         1       /* Parameter type: long                     */
#define FLOAT_PAR        2       /* Parameter type: float                    */
#define STRING_PAR       4       /* Parameter type: string                   */
#define INT_PAR      LONG_PAR    /* Parameter type: int                      */
#define DOUBLE_PAR  FLOAT_PAR    /* Parameter type: double                   */
#define UNDEF_PAR       32       /* Parameter type: no defined type          */
#define POINTER_PAR     64       /* Parameter type: pointer to any type      */
#define TUPLE_PAR      128       /* Parameter type: pointer to tuple         */
#define ANY_PAR          7       /* Parameter type: arbitrary                */


/*****************************************************************************/
/* Return values of HALCON operators in the case of no error (messages)      */
/*****************************************************************************/
#define H_MSG_TRUE        2       /* TRUE                                    */
#define H_MSG_FALSE       3       /* FALSE                                   */
#define H_MSG_VOID        4       /* Stop processing                         */
#define H_MSG_FAIL        5       /* Call failed                             */


/*****************************************************************************/
/* Constants and basic types                                                 */
/*****************************************************************************/
#define MAX_TUPLE_LENGTH 1000000   /* max. length of a tuple                 */
#define MAX_STRING       1024      /* max. length of a string                */

typedef UINT4            Herror;   /* Type function values (error messages)  */

typedef  long *Hkey;               /* primary key in DB (for iconic objects) */
#define  UNDEF_KEY   (Hkey)(0)     /* Undefined iconic object                */
		 

/*****************************************************************************/
/* Structures for passing parameters between language interface and core     */
/*****************************************************************************/
typedef union 
{
  INT4_8  l;              /* 4/8 byte integer                       (input)  */
  double  f;              /* 8 byte real                            (input)  */
  char    *s;             /* pointer to trings                      (input)  */
} Hpar;                   /* parameter passing for the C interface           */

typedef union 
{
  INT4_8  *l;             /* 4/8 byte integer                       (output) */
  double  *f;             /* 8 byte real                            (output) */
  char    *s;             /* pointer to strings                     (output) */
  VOIDP   p;              /* pointer to var. of any type (e.g. tuple)(output)*/
} Hvar;                   /* parameter passing for the C interface           */

typedef struct
{
  Hpar   par;             /* values                                          */
  INT1   type;            /* type flag                                       */
} Hcpar;                  /* parameter passing for the C interface           */

typedef struct
{
  Hvar   var;             /* values                                          */
  UINT1  type;            /* type flag                                       */
} Hcvar;                  /* parameter passing for the C interface           */

typedef struct
{
  Hcpar   *element;       /* tuple element(s)                                */
  INT4_8  num_el;         /* number of used elements                         */
  INT4_8  length;         /* total length of array (incl. unused elements)   */
} Hctuple;                /* for managing output control parameters          */

typedef struct
{
  Hcvar   *variables;     /* variables (of application) to write back values */
  Hcpar   *element;       /* tuple element(s)                                */
  INT4_8  num_el;         /* number of used elements                         */
  INT4_8  length;         /* total length of array (incl. unused elements)   */
} Hcvtuple;               /* for passing control parameter variables from    */
                          /* the language to the core interface              */


/*****************************************************************************/
/* Bool constants                                                            */
/*****************************************************************************/
#ifndef TRUE
#define TRUE             1
#else
#undef  TRUE
#define TRUE             1
#endif

#ifndef FALSE
#define FALSE            0
#else
#undef  FALSE
#define FALSE            0
#endif


/*****************************************************************************/
/* Pixel types of HALCON images                                              */
/*****************************************************************************/
#define UNDEF_IMAGE   (INT)0     /* Type not defined                         */
#define BYTE_IMAGE    (INT)1     /* Type: 1 byte per pixel (0..255)          */
#define INT4_IMAGE    (INT)2     /* Type: 4 bytes per pixel (INT4)           */
#define LONG_IMAGE    (INT)2     /* Type: 4 bytes per pixel (INT4)           */
#define FLOAT_IMAGE   (INT)4     /* Type: 4 bytes per pixel (float)          */
#define DIR_IMAGE     (INT)8     /* Type: edge direction 0..180 and 255      */
#define CYCLIC_IMAGE  (INT)16    /* Type: 0..255 cyclic                      */
#define INT1_IMAGE    (INT)32    /* Type: -127..127                          */
#define COMPLEX_IMAGE (INT)128   /* Type: 2 float images                     */
#define INT2_IMAGE    (INT)512   /* Type: 2 bytes (short)                    */
#define UINT2_IMAGE   (INT)1024  /* Type: 2 bytes (unsigned short)           */
#define VF_IMAGE      (INT)2048  /* Type: 2 FLOAT_IMAGE images (vectors)     */


/*****************************************************************************/
/* HALCON procedure (operator) handle                                        */
/*****************************************************************************/
/* This data structure contains all informations about an instance of an     */
/* HALCON operator or an HALCON thread derived from an HALCON operator       */
/* instance. The contained information describes the processing context of   */
/* HALCON operators (e.g. parameter values, debugging information, etc.).    */
/*****************************************************************************/
typedef void *Hproc_handle;


/*****************************************************************************/
/* data types for handling pthreads (POSIX threads) and mutex variables      */
/*****************************************************************************/
typedef void*          H_pthread_t;            /* pthread handle             */
typedef void*          H_pthread_mutex_t;      /* pthread mutex data type    */
typedef void*          H_pthread_cond_t;       /* pthread condition variable */
	
#endif
