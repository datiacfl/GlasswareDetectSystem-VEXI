/*****************************************************************************
 * CIPPyramid.h
 *****************************************************************************
 * 
 * Projekt:  Halcon (libhalcon)
 * Description:  Gauss / Laplace Pyramide
 *
 * (c) 1996-2002 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.16 $
 * $Date: 2002/07/03 15:49:00 $
 *
 */


#ifndef CIPPYRAMID_H
#define CIPPYRAMID_H


#if defined(__cplusplus)
extern "C" {
#endif

   
extern HLibExport Herror IPBGridmin(HBYTE *image_in,
                                    INT width_in, INT height_in,
                                    HBYTE *image_out,
                                    INT width_out,
                                    INT height_out);

extern HLibExport Herror IPU2Gridmin(UINT2 *image_in,
                                     INT width_in, INT height_in,
                                     UINT2 *image_out,
                                     INT width_out,
                                     INT height_out);

extern HLibExport Herror IPFGridmin(float *image_in,
                                    INT width_in, INT height_in,
                                    float *image_out,
                                    INT width_out,
                                    INT height_out);

extern HLibExport Herror IPBGridmax(HBYTE *image_in,
                                    INT width_in, INT height_in,
                                    HBYTE *image_out,
                                    INT width_out,
                                    INT height_out);

extern HLibExport Herror IPU2Gridmax(UINT2 *image_in,
                                     INT width_in, INT height_in,
                                     UINT2 *image_out,
                                     INT width_out,
                                     INT height_out);

extern HLibExport Herror IPFGridmax(float *image_in,
                                    INT width_in, INT height_in,
                                    float *image_out,
                                    INT width_out,
                                    INT height_out);

extern HLibExport Herror IPBGridreduce(HBYTE *image_in,
                                       INT width_in, INT height_in,
                                       HBYTE *image_out,
                                       INT width_out,
                                       INT height_out);

extern HLibExport Herror IPI2Gridreduce(INT2 *image_in,
                                        INT width_in, INT height_in,
                                        INT2 *image_out,
                                        INT width_out,
                                        INT height_out);

extern HLibExport Herror IPU2Gridreduce(UINT2 *image_in,
                                        INT width_in, INT height_in,
                                        UINT2 *image_out,
                                        INT width_out,
                                        INT height_out);

extern HLibExport Herror IPFGridreduce(float *image_in,
                                       INT width_in, INT height_in,
                                       float *image_out,
                                       INT width_out,
                                       INT height_out);

extern HLibExport Herror IPBGridgauss(HBYTE *image_in,
                                      INT width_in, INT height_in,
                                      HBYTE *image_out,
                                      INT width_out,
                                      INT height_out);

extern HLibExport Herror IPI2Gridgauss(INT2 *image_in,
                                       INT width_in, INT height_in,
                                       INT2 *image_out,
                                       INT width_out,
                                       INT height_out);

extern HLibExport Herror IPI2Gridgauss(INT2 *image_in,
                                       INT width_in, INT height_in,
                                       INT2 *image_out,
                                       INT width_out,
                                       INT height_out);

extern HLibExport Herror IPU2Gridgauss(UINT2 *image_in,
                                       INT width_in, INT height_in,
                                       UINT2 *image_out,
                                       INT width_out,
                                       INT height_out);

extern HLibExport Herror IPFGridgauss(float *image_in,
                                      INT width_in, INT height_in,
                                      float *image_out,
                                      INT width_out,
                                      INT height_out);

extern HLibExport Herror IPBGridaverage(HBYTE *image_in,
                                        INT width_in, INT height_in,
                                        HBYTE *image_out, 
                                        INT width_out,
                                        INT height_out);

extern HLibExport Herror IPI2Gridaverage(INT2 *image_in,
                                         INT width_in, INT height_in,
                                         INT2 *image_out,
                                         INT width_out,
                                         INT height_out);

extern HLibExport Herror IPU2Gridaverage(UINT2 *image_in,
                                         INT width_in, INT height_in,
                                         UINT2 *image_out,
                                         INT width_out,
                                         INT height_out);

extern HLibExport Herror IPFGridaverage(float *image_in,
                                        INT width_in, INT height_in,
                                        float *image_out,
                                        INT width_out,
                                        INT height_out);


#if defined(__cplusplus)
}
#endif

#endif
