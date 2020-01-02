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
 * $Revision: 1.17 $
 * $Date: 2007/05/09 19:09:27 $
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
extern HLibExport CRITICAL_SECTION	csHalcon;
#define H_SYNC_ENTER_CRITICAL_SECTION	EnterCriticalSection(&csHalcon);
#define H_SYNC_LEAVE_CRITICAL_SECTION	LeaveCriticalSection(&csHalcon);
#define H_SYNC_CRITICAL_SECTION_DEF   CRITICAL_SECTION csHalcon;
#define H_SYNC_DEF_INT(VARIABLE)      int VARIABLE
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)                  \
{                                                               \
  int idx;                                                      \
                                                                \
  (GetNumLocks) = 0;                                            \
  RTL_CRITICAL_SECTION *cs = (RTL_CRITICAL_SECTION *)&csHalcon; \
  if(GetCurrentThreadId() == (DWORD)cs->OwningThread)           \
  {                                                             \
    (GetNumLocks) = cs->RecursionCount;                         \
    for(idx=cs->RecursionCount; idx>0; idx--)                   \
    {                                                           \
      H_SYNC_LEAVE_CRITICAL_SECTION;                            \
    }                                                           \
  }                                                             \
}

#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)                   \
{                                                               \
  int idx;                                                      \
  for(idx=0; idx<(NumLocks); idx++)                             \
  {                                                             \
    H_SYNC_ENTER_CRITICAL_SECTION;                              \
  }                                                             \
}

#else
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)
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
#define H_SYNC_DEF_INT(VARIABLE) int (VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)                  \
{                                                               \
  GetNumLocks = 0;                                              \
  while(HLeaveCriticalSectionG()==H_MSG_OK)                     \
  {                                                             \
    GetNumLocks++;                                              \
  }                                                             \
}
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)                   \
{                                                               \
  int idx;                                                      \
  for(idx=0; idx<NumLocks; idx++)                               \
  {                                                             \
    HEnterCriticalSectionG();                                   \
  }                                                             \
}

#else
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)
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
