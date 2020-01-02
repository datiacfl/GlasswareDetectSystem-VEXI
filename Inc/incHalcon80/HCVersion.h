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
 * $Revision: 1.38 $
 * $Date: 2007/03/27 11:40:33 $
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
#    include <sys/time.h>
#  else
struct timezone
{
  int tz_minuteswest;   /* minutes W of Greenwich */
  int tz_dsttime;       /* type of dst correction */
};

struct timeval {
  long tv_sec;   /* seconds */
  long tv_usec;  /* microseconds */
};
#  endif /* !TRIMEDIA && ! _TMS320C6X */

/* network */
#  if defined(TRIMEDIA)
#    include <tmlib/rpc_socket.h>
#  endif /* TRIMEDIA */
#  ifdef HC_NO_IO_SOCKET /* no network */
#    ifdef _TMS320C6X
#      include <c6x.h>
#      if defined(HC_BIG_ENDIAN) || (__BYTE_ORDER == __BIG_ENDIAN)
#        define ntohl(x) (x)
#        define ntohs(x) (x)
#      else
#        define ntohl(x) _swap4(x)
#        define ntohs(x) ((unsigned short int)((((x)&0x00ff)<<8)| \
                                               (((x)&0xff00)>>8)))
#      endif
#      define htonl(x) ntohl(x)
#      define htons(x) ntohs(x)
#    endif
#  else
#    include <netinet/in.h>
#  endif

/* file i/o */
#  ifdef _TMS320C6X
#    include <file.h>
#  else
#    include <fcntl.h>
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
#    endif /*TRIMEDIA*/

/* string handling */
#  ifndef TRIMEDIA
#    define stricmp(s1,s2) strcasecmp(s1,s2)
#    define strnicmp(s1,s2,l) strncasecmp(s1,s2,l)
#  else
#    define stricmp(s1,s2) strcmp(s1,s2)
#    define strnicmp(s1,s2,l) strncmp(s1,s2,l)
#  endif

#else /* _WIN32 */

#  include <windows.h>
#  ifndef _WIN32_WCE
#    include <io.h>
#  endif

/* network */
#  include <winsock.h>

/* file i/o */
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
#if defined(_TMS320C6X)
#  define DYN_OBJ_EXTENSION "none"
#endif
#endif
#endif
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

#endif /* #ifdef __cplusplus .. else */

#endif
