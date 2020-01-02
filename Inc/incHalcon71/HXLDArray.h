/*****************************************************************************
 * HXLDArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDArray
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 */

#ifndef XLD_ARRAY_H
#define XLD_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDArray                                  */
/****************************************************************************/

class LIntExport HXLDArray: public HObjectArray {
public:
  HXLDArray(void) : HObjectArray(), array(NULL) {num_xld_arrays++;}
  HXLDArray(Hlong n) : HObjectArray(n), array(NULL) {num_xld_arrays++;}
  HXLDArray(HBaseArrayMode m) : HObjectArray(m), 
                                array(NULL) {num_xld_arrays++;}
  HXLDArray(Hkey *key, Hlong num);
  HXLDArray(const Hobject &obj);
  HXLDArray(const HXLD &xld);
  HXLDArray(const HXLDArray &arr);
  ~HXLDArray(void);

  HXLDArray &operator= (const HXLDArray &arr);

  // Tools
  virtual const char  *HClassName(void)     const;
  virtual const char  *ClassName(void)      const;
  virtual const char  *InstClassName(void)  const;
  virtual       Hkey   Key(Hlong i)          const {return array[i].Key();}
  virtual    Hobject   ElemId(Hlong i)       const {return array[i].Id();}

  virtual void         Display(const HWindow &w) const;

  // Access and Manipulation
  HXLD  const     &operator[] (Hlong index) const;
  HXLD            &operator[] (Hlong index);
  HXLDArray       operator() (Hlong min, Hlong max) const;
  HXLDArray       &Append(const HXLD &xld);
  HXLDArray       &Append(const HXLDArray &xlds);
  virtual void    SetKeys(Hkey *key, Hlong num);
  void            CopyHXLDArray(const HXLDArray &in);
  virtual void    DeleteArray(void);
  // Accessing array elements without index checking -> fast AND risky
  HXLD            Elem(Hlong index) const {return array[index];}

  // Class Functions
  static Hlong NumInst(void) {return num_xld_arrays;}

protected:
  HXLD          *array;
private:
  static Hlong   num_xld_arrays; 
  void          NewLength(Hlong new_num, Hlong old_num);

public:
  virtual HTuple GetCirclePose(const Halcon::HTuple &CamParam, const Halcon::HTuple &Radius, const Halcon::HTuple &OutputType, Halcon::HTuple *Pose2) const;
  virtual HTuple GetCirclePose(double CamParam, double Radius, const char *OutputType, Halcon::HTuple *Pose2) const;
  virtual HXLDArray SelectXldPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HXLDArray SelectXldPoint(double Row, double Column) const;
  virtual HTuple TestXldPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HTuple TestXldPoint(double Row, double Column) const;
  // Select contours using shape features.
  virtual HXLDArray SelectShapeXld(const Halcon::HTuple &Features, const Halcon::HTuple &Operation, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HXLDArray SelectShapeXld(const char *Features, const char *Operation, double Min, double Max) const;
  virtual HTuple OrientationXld(void) const;
  virtual HTuple EccentricityXld(Halcon::HTuple *Bulkiness, Halcon::HTuple *StructureFactor) const;
  virtual HTuple CompactnessXld(void) const;
  virtual HTuple DiameterXld(Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2, Halcon::HTuple *Diameter) const;
  virtual HTuple ConvexityXld(void) const;
  virtual HTuple CircularityXld(void) const;
  virtual HTuple EllipticAxisXld(Halcon::HTuple *Rb, Halcon::HTuple *Phi) const;
  virtual HTuple SmallestRectangle2Xld(Halcon::HTuple *Column, Halcon::HTuple *Phi, Halcon::HTuple *Length1, Halcon::HTuple *Length2) const;
  virtual HTuple SmallestRectangle1Xld(Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2) const;
  virtual HTuple SmallestCircleXld(Halcon::HTuple *Column, Halcon::HTuple *Radius) const;
  virtual HXLDArray ShapeTransXld(const Halcon::HTuple &Type) const;
  virtual HXLDArray ShapeTransXld(const char *Type) const;
  virtual HTuple LengthXld(void) const;
  virtual HTuple MomentsAnyXld(const Halcon::HTuple &Mode, const Halcon::HTuple &PointOrder, const Halcon::HTuple &Area, const Halcon::HTuple &CenterRow, const Halcon::HTuple &CenterCol, const Halcon::HTuple &P, const Halcon::HTuple &Q) const;
  virtual HTuple MomentsAnyXld(const char *Mode, const char *PointOrder, double Area, double CenterRow, double CenterCol, Hlong P, Hlong Q) const;
  virtual HTuple MomentsXld(Halcon::HTuple *M20, Halcon::HTuple *M02) const;
  virtual HTuple AreaCenterXld(Halcon::HTuple *Row, Halcon::HTuple *Column, Halcon::HTuple *PointOrder) const;
  virtual HImage PaintXld(const HImage &Image, const Halcon::HTuple &Grayval) const;
  virtual HImage PaintXld(const HImage &Image, double Grayval) const;
  static HXLDArray ReceiveXld(const Halcon::HTuple &Socket);
  static HXLDArray ReceiveXld(Hlong Socket);
  virtual void SendXld(const Halcon::HTuple &Socket) const;
  virtual void SendXld(Hlong Socket) const;
  // Display an XLD object.
  virtual void DispXld(const Halcon::HTuple &WindowHandle) const;
  virtual void DispXld(Hlong WindowHandle) const;
};

}

#endif
