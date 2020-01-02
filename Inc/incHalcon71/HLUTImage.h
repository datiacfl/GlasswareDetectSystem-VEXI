/*****************************************************************************
 * LUTImage.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for char-images with color table
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.9 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */


#ifndef H_LUT_IMAGE_H
#define H_LUT_IMAGE_H


namespace Halcon {


class LIntExport HLUTImage: public HSemAbstractImage {
public:
  HLUTImage(void);
  HLUTImage(const char *file);
  HLUTImage(const HByteImage &image);
  HLUTImage(const HByteImage &image, const HByteLUT &lut);
  HLUTImage(const HLUTImage &image);
  virtual ~HLUTImage(void);
  
  // Tools
  char *ClassName(void) const { return "HLUTImage"; }
  operator HRGBImage(void) const;
  HRGBLUT GetLUT(void) const;
  HRGBLUT SetLUT(void);

  // Klassenoperationen
  static Hlong NumInst(void) { return num_images; }
protected:
private:
  HByteImage  image;
  HByteLUT     lut;
  static Hlong num_images;
};


}


#endif
