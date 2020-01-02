/*****************************************************************************
 * HCVersion.h
 ***************************************************************************** 
 *
 * Project:     HALCON
 * Description: Adaption of HALCON to different operating systems
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.49 $
 * $Date: 2008/12/06 13:36:26 $
 *
 */

#ifndef HCVERSION_H
#define HCVERSION_H

/* 
 * These files are always included
 */
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

typedef   void*   VOIDP; 

#ifndef _WIN32

#  ifndef _TMS320C6X
#    include <unistd.h>
#    include <sys/types.h>
#  else
#    include <stdint.h>
#    include <stddef.h>
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
#  endif

/* time */
#  if !defined(TRIMEDIA) && !defined(_TMS320C6X)
#    if defined(__vxworks)
#      include <sys/times.h>
#    else
#      include <sys/time.h>
#    endif /* __vxworks */
#  else
struct timezone
{
  int tz_minuteswest;   /* minutes W of Greenwich */
  int tz_dsttime;       /* type of dst correction */
};

#    if !defined(_B_TIME_H_)
struct timeval {
    int     tv_sec;         /* seconds */
    int     tv_usec;        /* and microseconds */
};
#    endif
#  endif /* !TRIMEDIA && ! _TMS320C6X */

/* file i/o */
#  ifdef _TMS320C6X
#    include <file.h>
#  else
#    include <sys/types.h>
#    include <sys/stat.h>
#    ifdef __vxworks
#      define S_ISLNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#    endif
#    include <dirent.h>
#    include <fcntl.h>
#  endif
#  ifndef F_OK
#    define F_OK	0x00            /* existence only */
#  endif
#  define  FOM_READ    "r"
#  define  FOM_WRITE   "w"
#  define  FOM_APPEND  "a"
#  if !defined(TRIMEDIA) && !defined(_TMS320C6X)
#    define  FOM_READB   FOM_READ
#    define  FOM_WRITEB  FOM_WRITE
#    define  FOM_APPENDB FOM_APPEND
#  else
#    define  FOM_READB   "rb"
#    define  FOM_WRITEB  "wb"
#    define  FOM_APPENDB "ab"
#  endif /*TRIMEDIA*/

/* string handling */
#  if !defined(TRIMEDIA) && !defined(_TMS320C6X)
#    define stricmp(s1,s2) strcasecmp(s1,s2)
#    define strnicmp(s1,s2,l) strncasecmp(s1,s2,l)
#  else
#    define stricmp(s1,s2) strcmp(s1,s2)
#    define strnicmp(s1,s2,l) strncmp(s1,s2,l)
#  endif

#else /* _WIN32 */

#  define _WINSOCKAPI_ /* use winsock2 */
#  include <windows.h>
#  ifndef _WIN32_WCE
#    include <io.h>
#  endif

/* file i/o */
#  ifndef _WIN32_WCE
#    include <fcntl.h>
#    ifndef POSIX /* map ANSI names to POSIX */
#      define O_RDONLY        _O_RDONLY
#      define O_WRONLY        _O_WRONLY
#      define O_RDWR          _O_RDWR
#      define O_APPEND        _O_APPEND
#      define O_CREAT         _O_CREAT
#      define O_TRUNC         _O_TRUNC
#      define O_EXCL          _O_EXCL
#      define O_TEXT          _O_TEXT
#      define O_BINARY        _O_BINARY
#      define O_RAW           _O_BINARY
#      define O_TEMPORARY     _O_TEMPORARY
#      define O_NOINHERIT     _O_NOINHERIT
#      define O_SEQUENTIAL    _O_SEQUENTIAL
#      define O_RANDOM        _O_RANDOM
#    endif
#  endif
#  include <sys/stat.h>
#  ifndef F_OK
#    define F_OK	0x00            /* existence only */
#  endif
#  ifndef X_OK
#    define X_OK	0x00            /* executable -> existence only with NT */
#  endif
#  ifndef R_OK
#    define R_OK	0x04            /* read permission */
#  endif
#  ifndef W_OK
#    define W_OK	0x02            /* write permission */
#  endif
#  ifndef RW_OK
#    define RW_OK	R_OK | W_OK     /* read and write permission */
#  endif
#  ifndef WR_OK
#    define WR_OK	RW_OK           /* read and write permission */
#  endif
#  define  FOM_READ    "r"
#  define  FOM_READB   "rb"
#  define  FOM_WRITE   "w"
#  define  FOM_WRITEB  "wb"
#  define  FOM_APPEND  "a"
#  define  FOM_APPENDB "ab"

/* string handling */
#  define stricmp(s1,s2) _stricmp(s1,s2)
#  define strnicmp(s1,s2,l) _strnicmp(s1,s2,l)

#endif /* ! _WIN32 */

#ifdef __FreeBSD__
#  include <sys/signal.h>
#  define log2(A) 1.442695*log((A))
#  define SIGCLD SIGCHLD		/* Signal handling */
#  define RTLD_LAZY 1		/* for dlopen */
#endif


#ifdef BERKELEY
#  include <malloc.h>
#  include <values.h>
#  define SEEK_SET 0
#  define SEEK_CUR 1
#  define SEEK_END 2
#endif


#ifndef CLOCKS_PER_SEC
#  define CLOCKS_PER_SEC   1000000
#endif


#if defined(__sgi) || defined(__sun) || defined(__alpha) || defined(__linux) || defined(__FreeBSD__)
#  define DYN_OBJ_EXTENSION "so"
#else
#if defined(__hpux)
#  define DYN_OBJ_EXTENSION "sl"
#else
#if defined(_WIN32)
#  define DYN_OBJ_EXTENSION "dll"
#else
#if defined(_TMS320C6X) || defined(__vxworks)
#  define DYN_OBJ_EXTENSION "none"
#endif
#endif
#endif
#endif

#if defined(_WIN64) || defined (__x86_64__) || defined(_M_AMD64)
#define HC_HAS_INT8_IMAGE
#endif



/* A define for inline functions. */
#ifdef __cplusplus

#define H_INLINE inline

#else

#if defined(_WIN32) || defined(__alpha) || defined(__sgi)
#  define H_INLINE __inline
#else
#if defined(__linux)
#  define H_INLINE __inline__
#else
#if defined(__sun)
#  define H_INLINE inline
#else
#  define H_INLINE
#endif
#endif
#endif

#ifndef HC_DEBUG
#define HASSERT(ASSERTION)
#else
#include <assert.h>
#define HASSERT(ASSERTION) assert(ASSERTION)
#endif

#endif /* #ifdef __cplusplus .. else */

#endif
