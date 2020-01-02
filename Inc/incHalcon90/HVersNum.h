/*****************************************************************************
 * HVersNum.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Current version of the HALCON library
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.49 $
 * $Date: 2008/12/09 09:48:07 $
 *
 */


#ifndef HLIB_VERSION
#define HLIB_VERSION          "9.0"
#endif

#ifndef HLIB_VERSION_NUM
#define HLIB_VERSION_NUM      9.0
#endif

#ifndef HLIB_LAST_UPDATE
#define HLIB_LAST_UPDATE      "09.12.2008"
#endif

#ifndef HLIB_REVISION
#define HLIB_REVISION         ""
#endif

#ifndef HALCON_VERSION_CODE
#define HALCON_VERSION_CODE 0x090000
#endif

#ifndef HALCON_VERSION
#define HALCON_VERSION(major,minor,revision) \
  (((major)<<16) + ((minor)<<8) + (revision))
#endif
