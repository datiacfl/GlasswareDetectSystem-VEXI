/*****************************************************************************
 * HFloatImage.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for float-images
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

#ifndef H_FLOAT_IMAGE_H
#define H_FLOAT_IMAGE_H


namespace Halcon {


class LIntExport HFloatImage: public HImage {
public:
  HFloatImage(void);
  HFloatImage(const char *file);
  HFloatImage(const HImage &image);
  HFloatImage(const HFloatImage &image);
  HFloatImage(int width, int height);
  HFloatImage(float *ptr, int width, int height);
  virtual ~HFloatImage(void);
  
  // Tools
  const char *ClassName(void) const { return "HFloatImage"; }

  // Pixelzugriff
  double operator[] (Hlong k) const
  { if (!privat) ((HFloatImage*)this)->Private(); return ((float*)ptr)[k]; }
  float &operator[] (Hlong k)
  { if (!init) Init(); return ((float*)ptr)[k]; }
  float &operator()(int x, int y) 
  { if (!init) Init(); return ((float*)ptr)[HLinearCoord(x,y,width)]; }
  float &operator()(Hlong k) 
  { if (!init) Init(); return ((float*)ptr)[k]; }
  void SetPixVal(Hlong k, const HPixVal &val);
    //{ if (!init) Init(); ((float*)ptr)[k] = val; }
  void SetPixVal(int x, int y, const HPixVal &val); 
    //{ if (!init) Init(); ((float*)ptr)[HLinearCoord(x,y,width)] = val; }

  // Klassenoperationen
  static Hlong NumInst(void) { return num_images; }
protected:
private:
  static Hlong num_images;
};


}


#endif
