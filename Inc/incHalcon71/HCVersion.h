/*****************************************************************************
 * HCVersion.h
 ***************************************************************************** 
 *
 * Project:     Halcon
 * Description: Adaption of HALCON to different operating systems
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.34 $
 * $Date: 2005/07/20 11:16:59 $
 *
 */

#ifndef HCVERSION_H
#define HCVERSION_H

typedef   void*   VOIDP; 

/* 
 * The files are alway included
 */
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>


#ifndef _WIN32
#include <unistd.h>
#ifndef TRIMEDIA
#include <sys/time.h>
#endif /*TRIMEDIA*/
#endif

#ifdef _WIN32
#include <stdlib.h>
#include <float.h>
#include <windows.h>
#ifndef _WIN32_WCE
#include <io.h>
#endif

/* RunTimeFunction: access */
#ifndef F_OK
#define F_OK	0x00            /* existence only */
#endif
#ifndef X_OK
#define X_OK	0x00            /* executable -> existance only with NT */
#endif
#ifndef R_OK
#define R_OK	0x04            /* read  persmission */
#endif
#ifndef W_OK
#define W_OK	0x02            /* write permission */
#endif
#ifndef RW_OK
#define RW_OK	R_OK | W_OK     /* read and write permission */
#endif
#ifndef WR_OK
#define WR_OK	RW_OK           /* read and write permission */
#endif

/* FILE IO */
#define  FOM_READ    "r"
#define  FOM_READB   "rb"
#define  FOM_WRITE   "w"
#define  FOM_WRITEB  "wb"
#define  FOM_APPEND  "a"
#define  FOM_APPENDB "ab"

#else
#ifndef TRIMEDIA
#define  FOM_READ    "r"
#define  FOM_READB   FOM_READ
#define  FOM_WRITE   "w"
#define  FOM_WRITEB  FOM_WRITE
#define  FOM_APPEND  "a"
#define  FOM_APPENDB FOM_APPEND
#else
#define  FOM_READ    "r"
#define  FOM_READB   "rb"
#define  FOM_WRITE   "w"
#define  FOM_WRITEB  "wb"
#define  FOM_APPEND  "a"
#define  FOM_APPENDB "ab"
#endif /*TRIMEDIA*/
#endif


#ifdef SUNRISE
#include <stdlib.h>
#include <sys/resource.h>
#include <float.h>
#include <values.h>
#endif


#ifdef __sgi
#include <stdlib.h>
#endif


#ifdef NeXT
#include <float.h>
#include <sys/resource.h>
#include <libc.h>
#endif


#ifdef __linux
#include <malloc.h>
#include <values.h>
#endif


#ifdef __FreeBSD__
#include <float.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>
#define log2(A) 1.442695*log((A))
#define SIGCLD SIGCHLD		/* Signal handling */
#define RTLD_LAZY 1		/* for dlopen */
#endif


#ifdef BERKELEY
#include <malloc.h>
#include <values.h>
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#include <sys/types.h>
#endif




#ifdef SPARC
#ifndef DBL_MAX
#define DBL_MAX    MAXDOUBLE
#endif
#ifndef DBL_MIN
#define DBL_MIN    MINDOUBLE
#endif
#ifndef FLT_MAX
#define FLT_MAX    MAXFLOAT
#endif
#ifndef FLT_MIN
#define FLT_MIN    MINFLOAT
#endif
#endif


#ifdef VAX
#endif


#ifdef __sun
#include <stdlib.h>
#endif


#ifdef SYSV
#include <stdlib.h>
#include <float.h>
#include <unistd.h>
#endif



#ifdef DECS
#include <float.h>
#endif

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC   1000000
#endif

#ifndef FLT_EPSILON
#define FLT_EPSILON 1E-5
#endif


#if defined(__sgi) || defined(__linux)
#define  INT1_MIN    SCHAR_MIN
#define  INT1_MAX    SCHAR_MAX
#else
#define  INT1_MIN    CHAR_MIN
#define  INT1_MAX    CHAR_MAX
#endif

#define  UINT1_MAX   UCHAR_MAX
#define  INT2_MIN    SHRT_MIN
#define  INT2_MAX    SHRT_MAX
#define  UINT2_MAX   USHRT_MAX
#define  UINT2_MIN   0

#define  INT4_MIN    INT_MIN
#define  INT4_MAX    INT_MAX
#define  UINT4_MAX   UINT_MAX
#ifndef _WIN64
#define  INT4_8_MAX  LONG_MAX
#define  UINT4_8_MAX ULONG_MAX
#else
#define  INT4_8_MAX  _I64_MAX
#define  UINT4_8_MAX _UI64_MAX
#endif


#ifndef RAND_MAX
#define RAND_MAX   MAXINT
#endif


#ifndef TRIMEDIA
#ifdef _WIN32
#define stricmp(s1,s2) _stricmp(s1,s2)
#define strnicmp(s1,s2,l) _strnicmp(s1,s2,l)
#else
#define stricmp(s1,s2) strcasecmp(s1,s2)
#define strnicmp(s1,s2,l) strncasecmp(s1,s2,l)
#endif
#else
#define stricmp(s1,s2) strcmp(s1,s2)
#define strnicmp(s1,s2,l) strncmp(s1,s2,l)
#endif /*TRIMEDIA*/


#if defined(__sgi) || defined(__sun) || defined(__alpha) || defined(__linux) || defined(__FreeBSD__)
#define DYN_OBJ_EXTENSION "so"
#else
#if defined(__hpux)
#define DYN_OBJ_EXTENSION "sl"
#else
#if defined(_WIN32)
#define DYN_OBJ_EXTENSION "dll"
#endif
#endif
#endif


#endif
