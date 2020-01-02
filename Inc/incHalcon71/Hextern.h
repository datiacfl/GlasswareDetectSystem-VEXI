/*****************************************************************************
 * Hextern.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: external variables and some global procedures for 
 *              language interfaces
 *
 * (c) 1996-2001 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.28 $
 * $Date: 2001/05/14 12:54:25 $
 *
 */

#ifndef HEXTERN_H
#define HEXTERN_H

#if defined(__cplusplus)
extern "C" {
#endif

/* global variables for image processing                                     */
extern HLibExport H_SYS_INFO_READ_ONLY HROInfo; /* global read-only data     */
extern HLibExport H_OPERATOR_INFO HProcInfo[MAX_PROC]; 
                                                /* procedures description    */
extern HLibExport INT          HDoLogo;         /* logo when starting HALCON */
extern HLibExport INT          HDoLowError;     /* error messages of HALCON  */
extern HLibExport INT          HDoLicenseError; /* license msgs of HALCON    */
extern HLibExport H_LANG_INFO  HLangInfo; /* functions of language interface */
extern HLibExport Hproc_handle HGlobalProcHandle; /* global proc_handle      */
                                                /* for database functions    */
extern HLibExport H_SYS_INFO_SHARED my_sys_info_shared;  /* gl. HALCON var.s */
/* remark: the structure above contains global HALCON system variables       */
/* which are (in the normal case) exclusively accessible via a valid         */
/* procedure handle and by using specific functions of the HALCON-Lib        */
/* source code file HInstance.c; those functions contain synchronization     */
/* mechanisms to guarantee a correct access to the variables even in case of */
/* a parallel/multithreaded/reentrant HALCON version.                        */
/* Nevertheless the structure is propagated here so that it also can be used */
/* directly, but this should be done VERY CAREFULLY!! At the moment it is    */
/* only used directly within HDevelop, which means no problem, because       */
/* HDevelop works strictly sequentially, i.e. it calls all HALCON            */
/* operators one after another;                                              */

/*****************************************************************************/
/*                        Interface Procedures                               */
/*****************************************************************************/
extern LIntExport void   HSystem(void);



#if defined(__cplusplus)
}
#endif

#endif
