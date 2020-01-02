/*****************************************************************************
 * HDeclSpec.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Windows NT DLL specifications
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.14 $
 * $Date: 2004/06/24 14:36:02 $
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
