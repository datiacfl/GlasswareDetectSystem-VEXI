/*****************************************************************************
 * HIntDef.h
 *****************************************************************************
 *
 * Project:     Halcon/libhalcon
 * Description: Definition of integer data types
 *              These definitions can be controlled by the compiler
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *  $Revision: 1.9 $
 *  $Date: 2004/11/24 16:00:54 $
 *
 */

#ifndef HINTDEF_H
#define HINTDEF_H

#ifndef _WIN32
#define  INT      int               /* integer, signed   2-8 Byte      */
#define  UINT     unsigned int      /* integer, unsigned 2-8 Byte      */
#endif

#ifndef _INT16
#define _INT16   short
#endif

#ifndef _INT32
#define _INT32   int
#endif

#ifndef _INT64
#ifndef _WIN64
#define _INT64   long
#else
#define _INT64   __int64
#endif
#endif

#ifndef _MACHINE_WORD
#ifndef _WIN64
#define _MACHINE_WORD  long
#else
#define _MACHINE_WORD  __int64
#endif
#endif

#ifndef _DOUBLE8
#define DOUBLE8 double
#else
#ifndef TRIMEDIA
#define DOUBLE8 _DOUBLE8
#else
#define DOUBLE8 long double
#endif
#endif


#ifdef __sgi
#define  INT1     signed char       /* integer, signed 1 Byte         */
#else
#define  INT1     char              /* integer, signed 1 Byte         */
#endif
#define  UINT1    unsigned char     /* integer, unsigned 1 Byte       */
#define  INT2     _INT16            /* integer, signed 2 Byte         */
#define  UINT2    unsigned _INT16   /* integer, unsigned 2 Byte       */
#define  INT4     _INT32            /* integer, signed 4 Byte         */
#define  UINT4    unsigned _INT32   /* integer, unsigned 4 Byte       */
#define  INT4_8   _INT64            /* integer, signed 4-8 Byte       */
#define  UINT4_8  unsigned _INT64   /* integer, unsigned 4-8 Byte     */
#define  MACHINE_WORD  _MACHINE_WORD  /* only for memory management   */
				      /* (HAlloc.c)                   */


typedef INT4_8 Hlong;


#ifdef _WIN64
#define LONG_FORMAT "I64"
#else
#define LONG_FORMAT "l"
#endif


#endif
