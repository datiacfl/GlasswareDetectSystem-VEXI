/*****************************************************************************
 * HInt2Image.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for short-images
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.11 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */


#ifndef H_INT2_IMAGE_H
#define H_INT2_IMAGE_H


namespace Halcon {


class LIntExport HInt2Image: public HImage {
public:
  HInt2Image(void);
  HInt2Image(const char *file);
  HInt2Image(const HImage &image);
  HInt2Image(const HInt2Image &image);
  HInt2Image(const HInt1Image &image);
  HInt2Image(const HUInt2Image &image);
  HInt2Image(const HInt4Image &image);
  HInt2Image(const HFloatImage &image);
  HInt2Image(const HComplexImage &image);
  HInt2Image(const HByteImage &image);
  HInt2Image(int width, int height);
  HInt2Image(HInt2 *ptr, int width, int height);
  virtual ~HInt2Image(void);
  
  // Tools
  const char *ClassName(void) const { return "HInt2Image"; }

  // Pixelzugriff
  int operator[] (Hlong k) const
  { if (!privat) ((HInt2Image*)this)->Private(); return ((INT2*)ptr)[k]; }
  INT2 &operator[] (Hlong k)
  { if (!init) Init(); return ((INT2*)ptr)[k]; }
  INT2 &operator()(int x, int y) 
  { if (!init) Init(); return ((INT2*)ptr)[HLinearCoord(x,y,width)]; }
  INT2 &operator()(Hlong k) 
  { if (!init) Init(); return ((INT2*)ptr)[k]; }
  void SetPixVal(Hlong k, const HPixVal &val); 
    //{ if (!init) Init(); ((int*)ptr)[k] = HClipInt2(val); }
  void SetPixVal(int x, int y, const HPixVal &val); 
    //{ if (!init) Init(); ((int*)ptr)[HLinearCoord(x,y,width)] = HClipInt2(val); }

  // Klassenoperationen
  static Hlong NumInst(void) { return num_images; }
protected:
private:
  static Hlong num_images;
};


}


#endif
