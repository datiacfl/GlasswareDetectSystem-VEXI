/*****************************************************************************
 * HSync.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Synchronisation macros for Windows/NT
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.15 $
 * $Date: 2004/07/02 14:46:58 $
 *
 */


#ifndef _HSYNC_H

/* WIN32 */
#if defined (_WIN32)

#include "windows.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (_MAKE_H_THREAD_SAFE) && ! defined (_NODLL)
extern LIntExport CRITICAL_SECTION	csHalcon;
#define H_SYNC_ENTER_CRITICAL_SECTION	EnterCriticalSection(&csHalcon);
#define H_SYNC_LEAVE_CRITICAL_SECTION	LeaveCriticalSection(&csHalcon);
#define H_SYNC_CRITICAL_SECTION_DEF     CRITICAL_SECTION csHalcon;
#else
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#endif

#if defined(__cplusplus)
}
#endif
#else  /* end of part WIN32 */

/* SUN Solaris, SGI-Irix, HP-UX (10.30 or higher), Linux: */
#if defined (__sgi) || defined(__sun) || defined(__linux) || defined(HPPA2) \
    || defined(__alpha)

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (_MAKE_H_THREAD_SAFE) && ! defined (_NODLL)
#include "hlib/HCriticalSection.h"
#define H_SYNC_LEAVE_CRITICAL_SECTION  HLeaveCriticalSectionG();
#define H_SYNC_ENTER_CRITICAL_SECTION  HEnterCriticalSectionG();
#define H_SYNC_CRITICAL_SECTION_DEF
#else
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#endif

#if defined(__cplusplus)
}
#endif

/* HP-UX 9.xx  and all others: */
#else
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#endif

#endif /* end of section: not Windows OS */

#endif /* _HSYNC_H */
