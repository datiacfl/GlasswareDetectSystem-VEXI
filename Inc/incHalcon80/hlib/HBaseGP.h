/*****************************************************************************
 * HBaseGB.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Basic tools
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.26 $
 * $Date: 2006/12/08 12:25:12 $
 *
 */


#ifndef HBASEGP_H
#define HBASEGP_H


#if defined(__cplusplus)
extern "C" {
#endif
 
extern HLibExport Herror HSetImageTime(Hproc_handle proc_handle,Himage *image);
  
extern HLibExport Herror HImageName2Type(const char *str, INT *kind);
  
extern HLibExport Herror HPrepNewImage(Hproc_handle proc_handle, INT width,
                                       INT height);
  
extern HLibExport double Hatan2(double x, double y);

extern HLibExport Herror HIncrRL(Hproc_handle proc_handle);

extern HLibExport Herror HIncrRLNum(Hproc_handle proc_handle, size_t num);

extern HLibExport Herror HCopyData(const void *source, void *destination,
                                   size_t size);

extern HLibExport Herror HSetData(void *c, INT val, size_t size);

extern HLibExport Herror HClearData(VOIDP c, size_t size);

extern HLibExport Herror HCopyImage(Himage *in, Himage *out);

extern HLibExport Herror HClearImage(Himage *image);

extern HLibExport Herror HSetImage(Himage *image, double grayval);

extern HLibExport Herror HAdaptImsize(Hproc_handle proc_handle, INT width,
                                      INT height);

extern HLibExport Herror HFreeTmpImage(Hproc_handle proc_handle,
                                       Himage *image);

extern HLibExport Herror HTmpImage(Hproc_handle proc_handle, Himage *image,
                                   INT kind, INT width, INT height,
                                   HBOOL clear); 

extern HLibExport Herror HFreeLocalImage(Hproc_handle proc_handle,
                                         Himage *image);

extern HLibExport Herror HLocalImage(Hproc_handle proc_handle, Himage *image,
                                     INT kind, INT width, INT height,
                                     HBOOL clear);

extern HLibExport Herror HCrImage(Hproc_handle proc_handle, Hkey key_in,
                                  INT num, INT typ, INT width, INT height,
                                  Hkey *key_out, Himage *image);

extern HLibExport Herror HCrImageMKey(Hproc_handle proc_handle,
                                      Hkey key_in[], INT num_keys,
                                      INT num, INT typ, INT width, 
                                      INT height, Hkey *key_out,
                                      Himage *image);

extern HLibExport Herror HFreeImage(Hproc_handle proc_handle, Himage *image);

extern HLibExport Herror HNewImage(Hproc_handle proc_handle, Himage *image,
                                   INT kind, INT width, INT height);

extern HLibExport Herror HNewImagePtr(Hproc_handle proc_handle, Himage *image,
                                      INT kind, INT width, INT height,
                                      VOIDP data, HBOOL initImg);

extern HLibExport Herror HSortDouble(Hproc_handle proc_handle, double *Array,
                                     int first, int last, HBOOL ascending);

#if defined(__cplusplus)
}
#endif


#endif
