/*****************************************************************************
 * CIPXLDCont.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Extended Line Description: Contours
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.47 $
 * $Date: 2004/11/19 15:52:22 $
 *
 */


#ifndef CIPXLDCONT_H
#define CIPXLDCONT_H


#if defined(__cplusplus)
extern "C" {
#endif
   
/* defines for HXLDSelectCont () */
#define SEL_LENGTH_XLD_CONT        1
#define SEL_DIRECTION_XLD_CONT     2
#define SEL_CURVATURE_XLD_CONT     3
#define SEL_CLOSED_XLD_CONT        4
#define SEL_EXTREME_DIST_XLD_CONT  5
#define SEL_OPEN_XLD_CONT          6

/* defines for global regression line attributes */
#define NR_NAME        "regr_norm_row"
#define NC_NAME        "regr_norm_col"
#define DIST_NAME      "regr_dist"
#define MEAN_DIST_NAME "regr_mean_dist"
#define DEV_DIST_NAME  "regr_dev_dist"

/*  defines for HXLDGenParallelContours() */
#define PARCONT_REGRESSION 1
#define PARCONT_ANGLE      2
#define PARCONT_GRADIENT   3

/* Number of points to compute the regression line with in
   HXLDGenParallelContours() */
#define PARCONT_REGRPOINTS 5

/*  defines for HXLDFetchAngle() */
#define SELECT_ABSOLUT    1         /* Absolute Winkel ausgeben */
#define SELECT_RELATIV    2         /* Relative Winkel ausgeben */
#define SELECT_RANGE      1         /* Winkel der Spanne ausgeben */
#define SELECT_MEAN       2         /* mittl. Winkel ueber Spanne ausgeben */
#define SELECT_REGRESS    3         /* Steigung der besten Regressionsger. */

/*Faktor fuer maximale Groesse von cont_out in 
Abhaengigkeit der Groesse von cont_in in Funktionen 
CIPClipContXLD() und HXLDClipCont() */
#define CONT_OUT_FAC 10         

/*Faktor fuer minimale Groesse von cont_out in 
in Funktionen CIPClipContXLD() und HXLDClipCont() */
#define MIN_CONT_OUT_NUM 1000           

/* Defines for HXLDGenCont(): */
#define SELECT_FILTER     1         /* Konturen nur filtern */
#define SELECT_GENERAL_1  2         /* generalisiere gefilterte Konturen */
#define SELECT_GENERAL_2  3         /* erhalte eingeschlossene Abschnitte */

/* Defines for HXLDGenRegionContour: */
#define XLD_FILL     0
#define XLD_MARGIN   1

/* Defines for HContourToBorder,HXLDGenContRegion und CIPGenContRegionXLD: */
#define CONT_CENTER        1
#define CONT_BORDER        2
#define CONT_BORDER_HOLES  3


extern HLibExport void HXLDContNormals(INT4 m, INT4 n, float *x, float *y,
                                       float *nx, float *ny);
extern HLibExport Herror HXLDGenParallelContours(Hproc_handle proc_id,
                                                 Hcont *cont, Hcont **cont_ret,
                                                 INT mode, double distance);
extern HLibExport Herror HAllocXLDCont(Hproc_handle proc_id, Hcont **cont,
                                       size_t num_points);
extern HLibExport Herror HAllocXLDContRC(Hproc_handle proc_id, Hcont *cont,
                                         size_t num_points);
extern HLibExport Herror HCopyXLDCont(Hproc_handle proc_id, Hcont *cont_in,
                                      HBOOL preserve_attribs, 
                                      HBOOL preserve_global_attribs, 
                                      Hcont **cont_out);
extern HLibExport Herror HCopyXLDContPart(Hproc_handle proc_id, Hcont *cont_in,
                                          INT4_8  min_index, INT4_8 max_index,
                                          HBOOL preserve_attribs, 
                                          HBOOL preserve_global_attribs,
                                          Hcont **cont_out);
extern HLibExport Herror HFreeXLDCont(Hproc_handle proc_id, Hcont *cont);
extern HLibExport Herror HLookupXLDContAttrib(Hcont *cont, char *name, 
                                              INT4 *indx);
extern HLibExport Herror HAddXLDContAttrib(Hproc_handle proc_id, 
                                           Hcont *cont, char *name,
                                           INT4 *indx);
extern HLibExport Herror HLookupXLDContGlobalAttrib(Hcont *cont, char *name,
                                                    INT4 *indx);
extern HLibExport Herror HAddXLDContGlobalAttrib(Hproc_handle proc_id,
                                                 Hcont *cont, char *name,
                                                 INT4 *indx);
extern HLibExport Herror HXLDFreeContour(Hproc_handle proc_id, Hcont *cont);

extern HLibExport Herror HAllocLContVarLocal(Hproc_handle proc_handle, 
                                             Hlcontvar **cont, 
                                             INT4 num_points);
extern HLibExport Herror HFreeLContVarLocal(Hproc_handle proc_handle,
                                            Hlcontvar *cont);
extern HLibExport Herror HReallocLContVarLocal(Hproc_handle proc_handle, 
                                               Hlcontvar *cont, 
                                               INT4 num_points);
extern HLibExport Herror HAllocSContVarLocal(Hproc_handle proc_handle, 
                                             Hscontvar **cont, 
                                             INT4 num_points);
extern HLibExport Herror HFreeSContVarLocal(Hproc_handle proc_handle,
                                            Hscontvar *cont);
extern HLibExport Herror HReallocSContVarLocal(Hproc_handle proc_handle, 
                                               Hscontvar *cont, 
                                               INT4 num_points);
extern HLibExport Herror HAllocFContVarLocal(Hproc_handle proc_handle, 
                                             Hfcontvar **cont, 
                                             INT4 num_points);
extern HLibExport Herror HFreeFContVarLocal(Hproc_handle proc_handle,
                                            Hfcontvar *cont);
extern HLibExport Herror HReallocFContVarLocal(Hproc_handle proc_handle, 
                                               Hfcontvar *cont, 
                                               INT4 num_points);


extern HLibExport Herror HXLDGenBin(Hproc_handle proc_id, Hrlregion *region,
                                    HBYTE **image, INT4 *width, INT4 *height,
                                    INT4 *add_row, INT4 *add_col);
extern HLibExport Herror HXLDGenCont(Hproc_handle proc_id, HBYTE *Pict,
                                     INT4 width, INT4 height, INT4 add_row,
                                     INT4 add_col, INT4 min_cont_len,
                                     INT mode, Hcont **Contours, INT4 *number);
extern HLibExport Herror HXLDFetchAngle(Hcont *Cont, INT a_mode, INT c_mode,
                                        INT4 lookaround, float *angles);
extern HLibExport Herror HXLDContLen(Hcont *Cont, INT4 *length);
extern HLibExport Herror HXLDContInfo(Hcont **cont_in, INT4_8 num,
                                      INT4 *length, float *nx, float *ny,
                                      float *dist,
                                      float *mean, float *deviation,
                                      double *fpx, double *fpy,
                                      double *lpx, double *lpy);
extern HLibExport Herror HXLDSelectCont(Hproc_handle proc_id, Hcont **cont_in,
                                        Hcont **cont_out, INT4 num_in,
                                        INT4 *num_out, INT mode, double min1,
                                        double max1, double min2, double max2);
extern HLibExport Herror HXLDContRegress(Hproc_handle proc_id, Hcont **in_cont,
                                         Hcont **out_cont, INT4 num_cont,
                                         INT mode, INT4 iteration);
extern HLibExport Herror HXLDRegressionsGerade(INT4 n, double *x, double *y, 
                                               double *xm, double *ym, 
                                               double *c, double *s);
extern HLibExport Herror HXLDFloatRegressionsGerade(INT4 n, float *x, float *y,
                                                    double *xm, double *ym,
                                                    double *c, double *s);
extern HLibExport Herror HXLDRegressionWeighted(INT4 n, double *x, double *y,
                                                double *weight, double *xm,
                                                double *ym, double *c,
                                                double *s);
extern HLibExport Herror HXLDFloatRegressionWeighted(INT4 n, float *x,
                                                     float *y, double *weight,
                                                     double *xm, double *ym,
                                                     double *c, double *s);
extern HLibExport Herror HXLDRegressionLineOutlier(Hproc_handle  proc_id,
                                                   INT n, double *x, double *y,
                                                   INT iterations,
                                                   INT suppressOutliers,
                                                   double ClippFactor,
                                                   double *xm, double *ym,
                                                   double *c, double *s,
                                                   double *weight);
extern HLibExport Herror HXLDFloatRegressionLineOutlier(Hproc_handle proc_id,
                                                        INT n, float *x,
                                                        float *y,
                                                        INT iterations, 
                                                        INT suppressOutliers,
                                                        double ClippFactor,
                                                        double *xm, double *ym,
                                                        double *c, double *s,
                                                        double *weight);
extern HLibExport Herror HXLDComputeNormalContour(INT4 num, float *x, float *y,
                                                  INT4 pos, double *nx,
                                                  double *ny);
extern HLibExport Herror HXLDSelectLocalMax(Hcont *cont, HBYTE *image,
                                            INT width, INT height,
                                            double min_perc, INT4 min_diff,
                                            INT4 distance,
                                            HBOOL *is_local_max);
extern HLibExport Herror HXLDSmooth(INT4 m, INT4 n, float *xx, float *yy,
                                    float *x, float *y);
extern HLibExport Herror HXLDSmoothContours(Hproc_handle proc_id, Hcont *cont,
                                            Hcont **cont_out,
                                            INT4 num_rpoints);
extern HLibExport Herror HXLDClipCont(Hproc_handle proc_id, Hcont **cont_in,
                                      INT4 num_in, Hcont **cont_out,
                                      INT4 *num_out, INT4 row1, INT4 col1,
                                      INT4 row2, INT4 col2, INT4 cont_out_num);
extern HLibExport Herror HXLDCropCont(Hproc_handle proc_handle, 
                                      Hcont **cont_in, INT4 num_in,
                                      Hcont ***cont_out_pt, INT4 *num_out, 
                                      double row1, double col1, double row2,
                                      double col2, HBOOL close_cont);

extern HLibExport Herror HXLDAffineTransCont(Hproc_handle proc_id,
                                             Hcont *cont_in, Hcont **cont_out,
                                             Hhom_mat_2d matrix);
extern HLibExport Herror HXLDProjectiveTransCont(Hproc_handle proc_id,
                                                 Hcont *cont_in,
                                                 Hcont **cont_out,
                                                 Hproj_mat_2d matrix);
extern HLibExport double winkel(INT c_mode, Hcont *Cont, INT4 index,  
                                INT4 dist);
extern HLibExport Herror HContourToBorder(Hproc_handle handle,
                                          Hcontour *inp, Hfcontour *outp,
                                          INT mode);
extern HLibExport Herror HXLDGenContRegion(Hproc_handle proc_handle,
                                           Hrlregion *region, 
                                           Hcont ***cont_out_pt, 
                                           INT4 *num_out,
                                           INT neigh,
                                           INT mode);
extern HLibExport Herror HGenContPolygonRoundedXLD(Hproc_handle proc_handle,
                                                   Hfcontour *cont_in, 
                                                   double *radius,
                                                   double sample_width, 
                                                   Hfcontour *cont_out);
extern HLibExport Herror HContourToPixels(Hproc_handle proc_handle,
                                          float *row, float *col, INT4 num,
                                          INT  mode, Hlcontvar *pixcont);
extern HLibExport Herror HXLDGenRegionContour(Hproc_handle proc_handle, 
                                              float *row, float *col, INT4 num,
                                              INT mode, Hrlregion **region);
extern Herror HDCheckZero(Hproc_handle proc_id, double *d, INT num);
                                               

#if defined(__cplusplus)
}
#endif


#endif  /* #ifndef CIPXLDCONT_H */
