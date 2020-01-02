/*****************************************************************************
 * HXLDPolyArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDPolyArray
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.16 $
 * $Date: 2007/05/03 14:21:51 $
 *
 */

#ifndef XLD_POLY_ARRAY_H
#define XLD_POLY_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDPolyArray                              */
/****************************************************************************/

class LIntExport HXLDPolyArray: public HXLDArray {
public:
  HXLDPolyArray(void) : HXLDArray() {}
  HXLDPolyArray(Hkey *key, Hlong num);
  HXLDPolyArray(const Hobject &obj);
  HXLDPolyArray(const HXLDPoly &poly);
  HXLDPolyArray(const HXLD &xld);
  HXLDPolyArray(const HXLDPolyArray &arr);
  HXLDPolyArray(const HXLDArray &arr);
  ~HXLDPolyArray(void) {}

  HXLDPolyArray &operator= (const HXLDPolyArray &arr);
  HXLDPolyArray &operator= (const HXLDArray &arr);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual INT4        ClassDBID(void) const {return XLD_POLYGON_ID;}
  virtual Hkey        Key(Hlong i) const {return array[i].Key();}
  virtual Hobject     ElemId(Hlong i) const {return array[i].Id();}

  // Access and Manipulation
  HXLDPoly  const  &operator[] (Hlong index) const;
  HXLDPoly         &operator[] (Hlong index);
  HXLDPolyArray     operator() (Hlong min, Hlong max) const;
  HXLDPolyArray    &Append(const HXLDPoly &poly);
  HXLDPolyArray    &Append(const HXLD &xld);
  HXLDPolyArray    &Append(const HXLDPolyArray &polys);
  HXLDPolyArray    &Append(const HXLDArray &xlds);
  virtual void      SetKeys(Hkey *key, Hlong num);
  virtual void      SetKeys(Hkey *key, Hlong num, Herror *err);
  void              CopyHXLDPolyArray(const HXLDPolyArray &in);
  void              CopyHXLDArray(const HXLDArray &in);

private:
  void NewLength(Hlong new_num, Hlong old_num);

  // Class Functions

public:
  static HXLDPolyArray ReadPolygonXldDxf(const Halcon::HTuple &FileName, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, Halcon::HTuple *DxfStatus);
  static HXLDPolyArray ReadPolygonXldDxf(const char *FileName, const char *GenParamNames, double GenParamValues, Halcon::HTuple *DxfStatus);
  virtual void WritePolygonXldDxf(const Halcon::HTuple &FileName) const;
  virtual void WritePolygonXldDxf(const char *FileName) const;
  virtual HXLDPolyArray Union2ClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  virtual HXLDPolyArray SymmDifferenceClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  virtual HXLDPolyArray DifferenceClosedPolygonsXld(const HXLDPolyArray &Sub) const;
  virtual HXLDPolyArray IntersectionClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  static HXLDPolyArray ReadPolygonXldArcInfo(const Halcon::HTuple &FileName);
  static HXLDPolyArray ReadPolygonXldArcInfo(const char *FileName);
  virtual void WritePolygonXldArcInfo(const Halcon::HTuple &FileName) const;
  virtual void WritePolygonXldArcInfo(const char *FileName) const;
  // Combine road hypotheses from two resolution levels.
  virtual HXLDPolyArray CombineRoadsXld(const HXLDModParaArray &ModParallels, const HXLDExtParaArray &ExtParallels, const HXLDPolyArray &CenterLines, const Halcon::HTuple &MaxAngleParallel, const Halcon::HTuple &MaxAngleColinear, const Halcon::HTuple &MaxDistanceParallel, const Halcon::HTuple &MaxDistanceColinear) const;
  virtual HXLDPolyArray CombineRoadsXld(const HXLDModParaArray &ModParallels, const HXLDExtParaArray &ExtParallels, const HXLDPolyArray &CenterLines, double MaxAngleParallel, double MaxAngleColinear, double MaxDistanceParallel, double MaxDistanceColinear) const;
  // Extract parallel XLD polygons.
  virtual HXLDParaArray GenParallelsXld(const Halcon::HTuple &Len, const Halcon::HTuple &Dist, const Halcon::HTuple &Alpha, const Halcon::HTuple &Merge) const;
  virtual HXLDParaArray GenParallelsXld(double Len, double Dist, double Alpha, const char *Merge) const;
  virtual HTuple GetLinesXld(Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol, Halcon::HTuple *Length, Halcon::HTuple *Phi) const;
  virtual HXLDContArray SplitContoursXld(const Halcon::HTuple &Mode, const Halcon::HTuple &Weight, const Halcon::HTuple &Smooth) const;
  virtual HXLDContArray SplitContoursXld(const char *Mode, Hlong Weight, Hlong Smooth) const;
  virtual HXLDPolyArray AffineTransPolygonXld(const Halcon::HTuple &HomMat2D) const;
};

}

#endif
