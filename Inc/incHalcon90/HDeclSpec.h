/*****************************************************************************
 * HDeclSpec.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Windows DLL specifications
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.15 $
 * $Date: 2008/12/06 13:36:26 $
 *
 */


#ifndef HALCON_DECL_SPEC_H
#define HALCON_DECL_SPEC_H

#if defined(_WIN32) && !defined (_NODLL)
#if defined(_HLibDLL)
#define HLibExport __declspec(dllexport)
#else
#define HLibExport __declspec(dllimport)
#endif
#if defined(_LIntDLL)
#define LIntExport __declspec(dllexport)
#else
#define LIntExport __declspec(dllimport)
#endif
#define HUserExport  __declspec(dllexport)
#define HUserImport __declspec(dllimport)
#else /* not _WIN32 */
#define HLibExport 
#define LIntExport 
#define HUserExport 
#define HUserImport
#endif /* not _WIN32 */

#endif
