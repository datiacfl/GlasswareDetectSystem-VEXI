/*****************************************************************************
 * HCLib.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Basic system interface functions
 *
 * (c) 1996-2002 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.13 $
 * $Date: 2002/08/01 08:14:17 $
 *
 */


#ifndef HCLIB_H
#define HCLIB_H


#if defined(__cplusplus)
extern "C" {
#endif
   

extern HLibExport Herror HMallocInfo(INT4_8 *mcalls);

extern HLibExport char *HStrstr(const char *haystack, const char *needle);

extern HLibExport time_t  Htime(time_t *t);

extern HLibExport clock_t Hclock(void);

extern HLibExport double HCountSeconds(void);

extern HLibExport void *Hmalloc(size_t size);

extern HLibExport void Hfree(void *ptr);

extern HLibExport UINT4 Hsleep(double seconds);

extern HLibExport double HDrand48(void);

extern HLibExport void HSrand48(INT4 seed);

extern HLibExport INT4_8 HNrand48(UINT2 seed[]);


#if defined(__cplusplus)
}
#endif


#endif
