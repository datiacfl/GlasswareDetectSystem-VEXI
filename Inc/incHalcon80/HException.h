/*****************************************************************************
 * HException.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Error handling
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.16 $
 * $Date: 2007/05/09 19:09:39 $
 *
 */



#ifndef H_EXCEPTION_H
#define H_EXCEPTION_H

#include "HSync.h"

namespace Halcon {


class HException;

// Handler for user defined exception handling.
// Used with InstallHHandler()
typedef void (*Handler)(const Halcon::HException &exception);


// Makros to generate an exception with file name and line number

#define H_EXCEPTION(PROC,VAL) {                                             \
  H_SYNC_DEF_INT(num_locks);                                                \
                                                                            \
  H_SYNC_LEAVE_ALL_CS_LOCKS(num_locks);                                     \
  Halcon::HException hexc = Halcon::HException(__FILE__,__LINE__,PROC,VAL); \
  hexc.React();                                                             \
  H_SYNC_REENTER_ALL_CS_LOCKS(num_locks);                                   \
}

#define H_EXCEPTIONF(PROC,ERR_NUM,ERR_TEXT) {                           \
  H_SYNC_DEF_INT(num_locks);                                            \
                                                                        \
  H_SYNC_LEAVE_ALL_CS_LOCKS(num_locks);                                 \
  Halcon::HException hexc = Halcon::HException(__FILE__,__LINE__,PROC,  \
                                               ERR_NUM,ERR_TEXT);       \
  hexc.React();                                                         \
  H_SYNC_REENTER_ALL_CS_LOCKS(num_locks);                               \
}


/* defines how to protect critical database accesses 
 *---------------------------------------------------------------------------*/
#ifdef H_PARALLEL            /* parallel Halcon: lock the global proc handle */
# define H_ENTER_CPP_CS 
# define H_LEAVE_CPP_CS 
#else
# ifdef _REENTRANT          /* thread save Halcon: H_SYNC_*_CRITICAL_SECTION */

#  define H_ENTER_CPP_CS H_SYNC_ENTER_CRITICAL_SECTION
#  define H_LEAVE_CPP_CS H_SYNC_LEAVE_CRITICAL_SECTION

# else                       /* not parallel, not thread save: no protection */

#  define H_ENTER_CPP_CS 
#  define H_LEAVE_CPP_CS

# endif
#endif


#define HCppCreateHProc(PROC_HANDLE)            \
  {                                             \
    Herror err;                                 \
    err = HCreateHProc(-1,&(PROC_HANDLE));       \
    if (err != H_MSG_OK) {                      \
      char err_text[MAX_STRING];                \
      (void)HMessage(err,err_text);             \
      H_LEAVE_CPP_CS;                           \
      H_EXCEPTION("",err_text);                 \
    }                                           \
  }

#define HCppDeleteHProc(PROC_HANDLE)                  \
  {                                                   \
    Herror err;                                       \
    err = HDeleteHProc((PROC_HANDLE),FALSE,H_MSG_OK); \
    if (err != H_MSG_OK) {                            \
      char err_text[MAX_STRING];                      \
      (void)HMessage(err,err_text);                   \
      H_LEAVE_CPP_CS;                                 \
      H_EXCEPTION("",err_text);                       \
    }                                                 \
  }


#define HTextExLock(PROC) {                     \
    Hproc_handle_ ph;                           \
    H_ENTER_CPP_CS;                             \
    HCppCreateHProc(ph);                        \
    Herror err = PROC; /* the procedure call */ \
    if (err != H_MSG_OK) {                      \
      char err_text[MAX_STRING];                \
      (void)HMessage(err,err_text);             \
      HDeleteHProc(ph,FALSE,H_MSG_OK);          \
      H_LEAVE_CPP_CS;                           \
      H_EXCEPTION("",err_text);                 \
    }                                           \
    else                                        \
    {                                           \
      H_LEAVE_CPP_CS;                           \
    }                                           \
  }

#define HTextEx(PROC_HANDLE,PROC) {               \
    Herror err = PROC;                            \
    if (err != H_MSG_OK) {                        \
      char err_text[MAX_STRING];                  \
      (void)HMessage(err,err_text);               \
      HDeleteHProc((PROC_HANDLE),FALSE,H_MSG_OK); \
      H_LEAVE_CPP_CS;                             \
      H_EXCEPTION("",err_text);                   \
    }                                             \
  }


class LIntExport HException {
public:
  HException(const HException &except);
  HException(const char *f, Hlong l, const char *p, Herror e, const char *m);
  HException(const char *f, Hlong l, const char *p, const char *m);
  HException(const char *f, Hlong l, const char *p, Herror e);
  ~HException();
  
  void           React(void);
  static Handler InstallHHandler(Handler proc);
  // default exception handler
  void           PrintException(void);
  
  HException     &operator = (const HException &except);
  
  static Handler handler;   /* handler in use */
  Hlong           line;      /* line number where error occured */
  const char     *file;     /* file name where error occured */
  const char     *proc;     /* Name of procedure/operator */
  Herror         err;       /* error number */
  char           *message;  /* error text */
private:
};


}


#endif
