/*****************************************************************************
 * Hconfig.h
 *****************************************************************************
 *
 * Project:      HALCON (libhalcon)
 * Description:  Operating system dependent data
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.15 $
 * $Date: 2004/06/24 14:40:40 $
 *
 */

#ifndef HCONFIG_H
#define HCONFIG_H

#ifndef LANGUAGE
#ifdef GERMAN_VERSION
#define DEF_LANGUAGE         "german"
#else
#ifdef ENGLISH_VERSION
#define DEF_LANGUAGE         "english"
#else
#define DEF_LANGUAGE         "english"
#endif
#endif
#else
#define DEF_LANGUAGE         "LANGUAGE"
#endif

#ifdef _WIN32
#define FILE_SEP             "\\"
#define FILE_SEP_C           '\\'
#define ENV_SEP              ";"
#define ENV_SEP_C            ';'
#define DEF_WINDOW_TYPE      WIN32WINDOW_S
#else
#define FILE_SEP             "/"
#define FILE_SEP_C           '/'
#define ENV_SEP              ":"
#define ENV_SEP_C            ':'
#define DEF_WINDOW_TYPE      XWINDOW_S
#endif 

#define DEF_BACKING_STORE    TRUE
#define DEF_SINGLE_LUT       FALSE  /* one LUT per screen (DECWindow: FALSE) */
#ifdef __alpha
#define DEF_ONLY_LINES       FALSE  /* in IOx11DispChord */
#else
#define DEF_ONLY_LINES       TRUE   /* in IOx11DispChord */
#endif


#ifdef _WIN32
#ifndef _WIN32_WCE
#define DEF_IMAGE_DIR        "C:\\Program Files\\MVTec\\Halcon\\images"
#define DEF_HELP_DIR         "C:\\Program Files\\MVTec\\Halcon\\help"
#define DEF_REFERENCE_DIR    "C:\\Program Files\\MVTec\\Halcon\\doc\\ps\\reference"
#define DEF_HTML_DIR         "C:\\Program Files\\MVTec\\Halcon\\doc\\html\\reference"
#define DEF_FILTER_DIR       "C:\\Program Files\\MVTec\\Halcon\\filter"
#define DEF_OCR_DIR          "C:\\Program Files\\MVTec\\Halcon\\ocr"
#define DEF_LUT_DIR          "C:\\Program Files\\MVTec\\Halcon\\lut"
#define DEF_LICENSE_DIR      "C:\\Program Files\\MVTec\\Halcon\\license"
#define DEF_CALIB_DIR        "C:\\Program Files\\MVTec\\Halcon\\calib"
#else
#define DEF_IMAGE_DIR        "\\Program Files\\MVTec\\Halcon\\images"
#define DEF_HELP_DIR         "\\Program Files\\MVTec\\Halcon\\help"
#define DEF_REFERENCE_DIR    "\\Program Files\\MVTec\\Halcon\\doc\\ps\\reference"
#define DEF_HTML_DIR         "\\Program Files\\MVTec\\Halcon\\doc\\html\\reference"
#define DEF_FILTER_DIR       "\\Program Files\\MVTec\\Halcon\\filter"
#define DEF_OCR_DIR          "\\Program Files\\MVTec\\Halcon\\ocr"
#define DEF_LUT_DIR          "\\Program Files\\MVTec\\Halcon\\lut"
#define DEF_LICENSE_DIR      "\\Program Files\\MVTec\\Halcon\\license"
#define DEF_CALIB_DIR        "\\Program Files\\MVTec\\Halcon\\calib"
#endif
#else
#define DEF_IMAGE_DIR        "/usr/local/halcon/images:."
#define DEF_HELP_DIR         "/usr/local/halcon/help"
#define DEF_REFERENCE_DIR    "/usr/local/halcon/doc/ps/reference"
#define DEF_HTML_DIR         "/usr/local/halcon/doc/html/reference"
#define DEF_FILTER_DIR       "/usr/local/halcon/filter"
#define DEF_OCR_DIR          "/usr/local/halcon/ocr"
#define DEF_LUT_DIR          "/usr/local/halcon/lut"
#define DEF_LICENSE_DIR      "/usr/local/halcon/license"
#define DEF_CALIB_DIR        "/usr/local/halcon/calib"
#endif


#define DEF_FONT             "fixed"
#define INIT_ALLOC           (1024*1024*1) /* Default amount for allocation */


#ifdef VMS
#define DEF_IMAGE_DIR        "dua0:[user.bild]"
#define DEF_FONT             "-Adobe-Courier-Medium-R-Normal--10-100-75-75-M-60-ISO8859-1"
#endif

#ifdef SPARC
#undef INIT_ALLOC
#define INIT_ALLOC           0 /* Default amount for allocation */
#endif

#ifdef ULTRIX
#undef INIT_ALLOC
#define INIT_ALLOC           0 /* Default amount for allocation */
#endif

#ifdef NeXT
#undef DEF_WINDOW_TYPE
#define DEF_WINDOW_TYPE      IMAGE_WINDOW_S
#endif

#ifdef IRIS
#endif


#ifdef DECSTA
#define DEF_IMAGE_DIR         "/bilder/"
#define DEF_BACKING_STORE     TRUE 
#endif


#endif
