/*****************************************************************************
 * CIPPyramid.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Gauss and Laplace pyramid
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.20 $
 * $Date: 2008/12/06 13:13:00 $
 *
 */


#ifndef CIPPYRAMID_H
#define CIPPYRAMID_H


#if defined(__cplusplus)
extern "C" {
#endif


extern HLibExport Herror IPBGridmin(HBYTE *image_in,
                                    HIMGDIM width_in, HIMGDIM height_in,
                                    HBYTE *image_out,
                                    HIMGDIM width_out,
                                    HIMGDIM height_out);

extern HLibExport Herror IPU2Gridmin(UINT2 *image_in,
                                     HIMGDIM width_in, HIMGDIM height_in,
                                     UINT2 *image_out,
                                     HIMGDIM width_out,
                                     HIMGDIM height_out);

extern HLibExport Herror IPFGridmin(float *image_in,
                                    HIMGDIM width_in, HIMGDIM height_in,
                                    float *image_out,
                                    HIMGDIM width_out,
                                    HIMGDIM height_out);

extern HLibExport Herror IPBGridmax(HBYTE *image_in,
                                    HIMGDIM width_in, HIMGDIM height_in,
                                    HBYTE *image_out,
                                    HIMGDIM width_out,
                                    HIMGDIM height_out);

extern HLibExport Herror IPU2Gridmax(UINT2 *image_in,
                                     HIMGDIM width_in, HIMGDIM height_in,
                                     UINT2 *image_out,
                                     HIMGDIM width_out,
                                     HIMGDIM height_out);

extern HLibExport Herror IPFGridmax(float *image_in,
                                    HIMGDIM width_in, HIMGDIM height_in,
                                    float *image_out,
                                    HIMGDIM width_out,
                                    HIMGDIM height_out);

extern HLibExport Herror IPBGridreduce(HBYTE *image_in,
                                       HIMGDIM width_in, HIMGDIM height_in,
                                       HBYTE *image_out,
                                       HIMGDIM width_out,
                                       HIMGDIM height_out);

extern HLibExport Herror IPI2Gridreduce(INT2 *image_in,
                                        HIMGDIM width_in, HIMGDIM height_in,
                                        INT2 *image_out,
                                        HIMGDIM width_out,
                                        HIMGDIM height_out);

extern HLibExport Herror IPU2Gridreduce(UINT2 *image_in,
                                        HIMGDIM width_in, HIMGDIM height_in,
                                        UINT2 *image_out,
                                        HIMGDIM width_out,
                                        HIMGDIM height_out);

extern HLibExport Herror IPFGridreduce(float *image_in,
                                       HIMGDIM width_in, HIMGDIM height_in,
                                       float *image_out,
                                       HIMGDIM width_out,
                                       HIMGDIM height_out);

extern HLibExport Herror IPBGridgauss(HBYTE *image_in,
                                      HIMGDIM width_in, HIMGDIM height_in,
                                      HBYTE *image_out,
                                      HIMGDIM width_out,
                                      HIMGDIM height_out);

extern HLibExport Herror IPI2Gridgauss(INT2 *image_in,
                                       HIMGDIM width_in, HIMGDIM height_in,
                                       INT2 *image_out,
                                       HIMGDIM width_out,
                                       HIMGDIM height_out);

extern HLibExport Herror IPI2Gridgauss(INT2 *image_in,
                                       HIMGDIM width_in, HIMGDIM height_in,
                                       INT2 *image_out,
                                       HIMGDIM width_out,
                                       HIMGDIM height_out);

extern HLibExport Herror IPU2Gridgauss(UINT2 *image_in,
                                       HIMGDIM width_in, HIMGDIM height_in,
                                       UINT2 *image_out,
                                       HIMGDIM width_out,
                                       HIMGDIM height_out);

extern HLibExport Herror IPFGridgauss(float *image_in,
                                      HIMGDIM width_in, HIMGDIM height_in,
                                      float *image_out,
                                      HIMGDIM width_out,
                                      HIMGDIM height_out);

extern HLibExport Herror IPBGridaverage(HBYTE *image_in,
                                        HIMGDIM width_in, HIMGDIM height_in,
                                        HBYTE *image_out,
                                        HIMGDIM width_out,
                                        HIMGDIM height_out);

extern HLibExport Herror IPI2Gridaverage(INT2 *image_in,
                                         HIMGDIM width_in, HIMGDIM height_in,
                                         INT2 *image_out,
                                         HIMGDIM width_out,
                                         HIMGDIM height_out);

extern HLibExport Herror IPI4Gridaverage(Hproc_handle proc_id, 
                                         INT4 *image_in,
                                         HIMGDIM width_in, HIMGDIM height_in,
                                         INT4 *image_out,
                                         HIMGDIM width_out, HIMGDIM height_out);

extern HLibExport Herror IPU2Gridaverage(UINT2 *image_in,
                                         HIMGDIM width_in, HIMGDIM height_in,
                                         UINT2 *image_out,
                                         HIMGDIM width_out,
                                         HIMGDIM height_out);

extern HLibExport Herror IPFGridaverage(float *image_in,
                                        HIMGDIM width_in, HIMGDIM height_in,
                                        float *image_out,
                                        HIMGDIM width_out,
                                        HIMGDIM height_out);


#if defined(__cplusplus)
}
#endif

#endif
