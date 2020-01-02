/*****************************************************************************
 * CIPXLDPara.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Extended Line Description: Parallels
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *                  Neherstr. 1, 81675 Muenchen, Germany
 * 
 *****************************************************************************
 * 
 * $Revision: 1.13 $
 * $Date: 2000/02/24 15:48:59 $
 *
 */


#ifndef CIPXLDPARA_H
#define CIPXLDPARA_H


#if defined(__cplusplus)
extern "C" {
#endif


extern HLibExport Herror HXLDFreeParallel(Hproc_handle proc_id, 
					  Hpara_poly *para);
extern HLibExport Herror HXLDFreeModParallel(Hproc_handle proc_id, 
					     Hmod_para *mod_para);
extern HLibExport Herror HXLDFreeExtParallel(Hproc_handle proc_id, 
					     Hext_para *ext_para);

extern HLibExport Herror HXLDGenModPara(Hproc_handle proc_id, Hpara_poly **para_poly,
                             INT4 num_para, HBYTE *image, int width,
                             int height, double quality, int min, int max,
                             double alpha);
extern HLibExport Herror HXLDExtModPara(Hproc_handle proc_id, Hmod_para *mod_para,
                             INT4 num, HBYTE *image, int width, int height,
                             int min, int max, double alpha);
extern HLibExport Herror HXLDInfoPara(Hproc_handle proc_id, Hpara_poly **para_poly,
                           INT4 num_para, HBYTE *image, int width, int height,
                           double *quality, double *grey, double *standard);
extern HLibExport Herror HXLDParallels(Hproc_handle proc_id, Hpoly **poly, Hkey *poly_key,
                            INT4 num_poly, double len, double dist,
                            double alpha, HBOOL merge);
extern HLibExport Herror HXLDMaxPara(Hproc_handle proc_id, Hext_para **ext_para,
                          INT4 num_para);

extern HLibExport double minimum(double a, double b);
extern HLibExport double maximum(double a, double b);
extern HLibExport double overlap(double ax1, double ay1, double ax2, double ay2,
                      double bx1, double by1, double bx2, double by2,
                      double alpha1, double alpha2);


#if defined(__cplusplus)
}
#endif


#endif
