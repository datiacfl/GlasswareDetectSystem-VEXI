/*****************************************************************************
 * HVersNum.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Current version of the HALCON library
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.31 $
 * $Date: 2007/04/29 12:45:13 $
 *
 */


#ifndef HLIB_VERSION
#define HLIB_VERSION          "8.0"
#endif

#ifndef HLIB_VERSION_NUM
#define HLIB_VERSION_NUM      8.0
#endif

#ifndef HLIB_LAST_UPDATE
#define HLIB_LAST_UPDATE      "15.05.2007"
#endif

#ifndef HLIB_REVISION
#define HLIB_REVISION         ""
#endif

#ifndef HALCON_VERSION_CODE
#define HALCON_VERSION_CODE 0x080000
#endif

#ifndef HALCON_VERSION
#define HALCON_VERSION(major,minor,revision) \
  (((major)<<16) + ((minor)<<8) + (revision))
#endif
