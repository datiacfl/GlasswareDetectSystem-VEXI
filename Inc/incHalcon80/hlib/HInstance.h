/*****************************************************************************
 * HInstance.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Author:      M. Lueckenhaus
 * Description: Handling of HALCON operator instances and HALCON threads;
 *              providing procedural access to global context variables;
 *              this form of access allows parallel processing of
 *              numerous Halcon operators.
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.19 $
 * $Date: 2007/02/27 09:28:23 $
 *
 */


#ifndef HINSTANCE_H
#define HINSTANCE_H


#if defined(__cplusplus)
extern "C" {
#endif

/* -------- H_INSTANCE_INFO_EXCLUSIVE - */
#define HGobj_images			1
#define HGdef_obj_images		2
#define HGInpObjList			3
#define HGInpObjNum			4
#define HGnum_obj			7 /* for compatibility reasons */
#define HGInpCtrlList			9
#define HGctrl_inherited                10
#define HGusedOCP                       16
#define HGOutpCtrlList                  17
#define HGStringMem			19
#define HGLastStringMem			20
#define HGMem_handle                    21
#define HGDB_handle                     22

/* -------- H_INSTANCE_INFO_SHARED ---- */
#define HGinp_obj			23
#define HGoutp_obj			24
#define HGinp_ctrl   			25
#define HGoutp_ctrl	 		26
#define HGNewFilter			27
#define HGnf_inp_key                    28
#define HGnf_index                      29
#define HGnf_img_type                   30
#define HGnf_out                        31
#define HGnf_image1                     32
#define HGnf_image2                     33
#define HGnf_num                        34
#define HGnf_num_alloc                  35
#define HGmutex_NewFil                  36

#define HGCompactObj                    41
#define HGLangIntID                     98

/* -------- H_SYS_INFO_EXCLUSIVE ------ */
#define HGimsize			37
#define HGWidth				38
#define HGHeight			39
#define HGCurrentRL			40

/* -------- H_SYS_INFO_SHARED --------- */
/* CompactObj / 41 moved INSTANCE_INFO_SHARED */ 
#define HGDBInit			42
#define HGcheck                         43
#define HGNoObjResult			44
#define HGEmptyObjResult		45
#define HGWindowName			46
#define HGIconName			47
#define HGWinBackColor			48
#define HGWinBorderColor		49
#define HGXPackage			50
#define HGBackingStore		        51
#define HGGraphicBorderWidth		52
#define HGNumGrey			53
#define HGNumGraphicColors              54
#define HGNumGreyPercentage             55
#define HGNumGraphicColorsPercentage    56
#define HGUserDefinedColors             57
#define HGDrawMode			58
#define HGIgnoreColormap		59
#define HGUpdateLUT			60
#define HGInt2Bits                      61
#define HGStoreEmptyRegion		62
#define HGClipRegion			63
#define HGInitNewImage			64
#define HGNeighbour			65
#define HGFlushGraphic			66
#define HGFlushFile			67
#define HGTestRegImaInters		68
#define HGPixelRatio			69
#define HGWidthMult			70
#define HGHeightMult			71
#define HGZoomPixel			72
#define HGPixelWidth			73
#define HGPixelHeight			74
#define HGImageDir			75
#define HGHelpDir		        76
/* Reference & HTML dir obsolete (77/78) */
#define HGLicenseDir			79
#define HGLUTDir			80
#define HGFilterDir			81
#define HGOCRDir			82
#define HGCalibDir                      83
#define HGLS_R                          84
#define HGOnlyLines                     85
#define HGDoIntZoom                     86
#define HGUsedModules                   87
#define HGmutex_flexlm                  88
#define HGmutex_ChUsMod                 89
#define HGmutex_boot                    90
#define HGmutex_measure                 91
#define HGmutex_socket                  92
#define HGmutex_strtok                  93
#define HGmutex_ltime                   94
#define HGmutex_graphics                96
#define HGmutex_fft                     97
/* LangIntID / 98 added to INSTANCE_INFO_SHARED */ 

/* -------- HALCON_PROC_HANDLE -------- */
#define HGproc_index			98

/*--- H_INSTANCE_INFO_SHARED add on --- */
#define HGnf_rem_inp_keys               110
 
/*--- H_SYS_INFO_SHARED add on --- */
#define HGmutex_lapack                  150


/* HAccessGlVar - access to global HALCON context variables                  */
extern HLibExport Herror HAccessGlVar(Hproc_handle proc_handle, INT element,
				      HBYTE to_do, VOIDP r_value, 
				      double w_value, char *w_string,
				      Hkey w_key, INT4_8 index);
/* HCheckObjNum - check whether specified object number is in range          */
extern HLibExport HBOOL HCheckObjNum(Hproc_handle proc_handle,INT par_num,
                                     INT4_8 obj_num);
/* HFreeGlVarRefs - giving free reference versions of global var. structures */
extern HLibExport Herror HFreeGlVarRefs(void);
/* HCreateHProc - create a new HALCON operator call instance                 */
extern HLibExport Herror HCreateHProc(INT4 current_idx, 
                                      Hproc_handle *proc_handle);
/* HDeleteHProc - delete a HALCON operator call instance                     */
extern HLibExport Herror HDeleteHProc(Hproc_handle proc_handle,HBOOL last, 
                                      Herror proc_result);
/* HCreateHThread - create new HALCON-thread by derivation of operator call  */
extern HLibExport Herror HCreateHThread(Hproc_handle proc_handle,
                                        Hproc_handle *thread_id);
/* HDeleteHThread - delete a HALCON thread (give free data structures)       */
extern HLibExport Herror HDeleteHThread(Hproc_handle proc_handle, 
                                        Herror proc_result);
/* HInitHProc - initialize all global var.s of a operator instance/thread    */
extern HLibExport Herror HInitHProc(Hproc_handle proc_handle, 
                                    HBOOL new_operator);
/* HUpdateHProc -update all global var.s of a cached operator instance/thread*/
extern HLibExport Herror HUpdateHProc(Hproc_handle proc_handle);

/* HProcCacheSize - return the current number of cached procedure handles
 * (-1 if global cache was not initialized)                                  */
extern HLibExport Herror HProcCacheSize(INT4_8 *size);
/* HFreeHProcCache - free all cached procedure handles                       */
extern HLibExport Herror HFreeHProcCache(void);
/* HFreeHProcCache - free all temporary memory blocks                        */
extern HLibExport Herror HProcCacheFreeAllTmpMemBlocks(void);

/* HINT: you don't get initialized, ready to use proc_handles from following 
 *       functions, but only the stored structures created and deleted once 
 *       before. */
/* HPopProcCache - get a proc_handle from cache stack */
extern HLibExport void HPushProcCache(Hproc_handle proc_handle);
/* HPushProcCache - put a proc_handle on cache stack */
extern HLibExport Hproc_handle HPopProcCache(void);


#if defined(__cplusplus)
}
#endif


#endif
