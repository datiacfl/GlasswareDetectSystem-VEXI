/*****************************************************************************
 * CIPXLDPoly.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Extended Line Description: Polygons
 *
 * (c) 1996-2003 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.16 $
 * $Date: 2003/09/16 08:59:16 $
 *
 */


#ifndef CIPXLDPOLY_H
#define CIPXLDPOLY_H

#define APPROX_CONT_RAMER     1
#define APPROX_CONT_RAY       2
#define APPROX_CONT_SATO      3

#if defined(__cplusplus)
extern "C" {
#endif


extern HLibExport Herror HXLDFreePolygon(Hproc_handle proc_id, Hpoly *poly);

extern HLibExport Herror HXLDPolygon(Hproc_handle proc_id, Hcont *cont,
                                     Hkey key, INT selection, float alpha,
				     Hpoly **poly);
extern HLibExport Herror HXLDSplitContPoly(Hproc_handle proc_id, Hpoly **poly,
                                           INT4 num_poly, Hcont **result,
					   INT4 *num_result);
extern HLibExport Herror HXLDSplitCont(Hproc_handle proc_id, Hpoly **poly,
                                       INT4 num_poly, INT4 weight,
                                       INT4 smooth, Hcont **result,
                                       INT4 *num_result);
extern HLibExport Herror HXLDAffineTransPoly(Hproc_handle proc_id,
                                             Hpoly *poly_in, Hpoly **poly_out,
                                             Hhom_mat_2d matrix);

extern HLibExport double square(double x);
extern HLibExport double euklid(double l1, double c1, double l2, double c2);
extern HLibExport double steigung(double l1, double c1, double l2, double c2);
extern HLibExport double abstand(double l1, double c1, double l2, double c2,
                                 double l, double c);


#if defined(__cplusplus)
}
#endif


#endif
