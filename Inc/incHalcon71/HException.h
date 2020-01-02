/*****************************************************************************
 * HException.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Error handling
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.13 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */



#ifndef H_EXCEPTION_H
#define H_EXCEPTION_H


namespace Halcon {


class HException;

// Handler for user defined exception handling.
// Used with InstallHHandler()
typedef void (*Handler)(const Halcon::HException &exception);


// Makros to generate an exception with file name and line number

#define H_EXCEPTION(PROC,VAL) { \
  Halcon::HException hexc = Halcon::HException(__FILE__,__LINE__,PROC,VAL); \
  hexc.React();}

#define H_EXCEPTIONF(PROC,ERR_NUM,ERR_TEXT) { \
  Halcon::HException hexc = Halcon::HException(__FILE__,__LINE__,PROC, \
                                               ERR_NUM,ERR_TEXT); \
  hexc.React();}


/* defines how to protect critical database accesses 
 *---------------------------------------------------------------------------*/
#ifdef H_PARALLEL            /* parallel Halcon: lock the global proc handle */

#define H_ENTER_CPP_CS HLockGlobalProcHandle
#define H_LEAVE_CPP_CS HUnlockGlobalProcHandle

#else
#ifdef _REENTRANT           /* thread save Halcon: H_SYNC_*_CRITICAL_SECTION */

#define H_ENTER_CPP_CS H_SYNC_ENTER_CRITICAL_SECTION
#define H_LEAVE_CPP_CS H_SYNC_LEAVE_CRITICAL_SECTION

#else                        /* not parallel, not thread save: no protection */

#define H_ENTER_CPP_CS
#define H_LEAVE_CPP_CS

#endif
#endif

#define HTextExLock(PROC) {       \
  H_ENTER_CPP_CS;                 \
  Herror err = PROC;              \
  if (err != H_MSG_OK) {          \
    char err_text[MAX_STRING];    \
    (void)HMessage(err,err_text); \
    H_LEAVE_CPP_CS;               \
    H_EXCEPTION("",err_text);     \
    H_ENTER_CPP_CS;               \
  }                               \
  H_LEAVE_CPP_CS;                 \
}

#define HTextEx(PROC) {           \
  Herror err = PROC;              \
  if (err != H_MSG_OK) {          \
    char err_text[MAX_STRING];    \
    (void)HMessage(err,err_text); \
    H_LEAVE_CPP_CS;               \
    H_EXCEPTION("",err_text);     \
  }                               \
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
