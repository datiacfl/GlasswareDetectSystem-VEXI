/*****************************************************************************
 * HXLDContArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDContArray
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.15 $
 * $Date: 2005/05/06 07:36:06 $
 *
 */

#ifndef XLD_CONT_ARRAY_H
#define XLD_CONT_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDContArray                              */
/****************************************************************************/

class LIntExport HXLDContArray: public HXLDArray {
public:
  HXLDContArray(void) : HXLDArray() {num_xld_cont_arrays++;}
  HXLDContArray(Hkey *key, Hlong num);
  HXLDContArray(const Hobject &obj);
  HXLDContArray(const HXLDCont &cont);
  HXLDContArray(const HXLD &xld);
  HXLDContArray(const HXLDContArray &arr);
  HXLDContArray(const HXLDArray &arr);
  ~HXLDContArray(void) {num_xld_cont_arrays--;}

  HXLDContArray &operator= (const HXLDContArray &arr);
  HXLDContArray &operator= (const HXLDArray &arr);

  // Tools
  virtual const char *HClassName(void)    const;
  virtual const char *ClassName(void)     const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void)     const {return XLD_CONTOUR_ID;}
  virtual       Hkey  Key(Hlong i)         const {return array[i].Key();}
  virtual    Hobject  ElemId(Hlong i)      const {return array[i].Id();}

  // Access and Manipulation
  HXLDCont  const   &operator[] (Hlong index) const;
  HXLDCont          &operator[] (Hlong index);
  HXLDContArray      operator() (Hlong min, Hlong max) const;
  HXLDContArray     &Append(const HXLDCont &cont);
  HXLDContArray     &Append(const HXLD &xld);
  HXLDContArray     &Append(const HXLDContArray &conts);
  HXLDContArray     &Append(const HXLDArray &xlds);
  virtual void       SetKeys(Hkey *key, Hlong num);
  void               CopyHXLDContArray(const HXLDContArray &in);
  void               CopyHXLDArray(const HXLDArray &in);

  // Class Functions
  static Hlong NumInst(void) {return num_xld_cont_arrays;}

private:
  static Hlong   num_xld_cont_arrays; 
  void          NewLength(Hlong new_num, Hlong old_num);

public:
  virtual HTuple DistanceCcMin(const HXLDContArray &Contour2, const Halcon::HTuple &Mode) const;
  virtual HTuple DistanceCcMin(const HXLDContArray &Contour2, const char *Mode) const;
  virtual HTuple DistanceCc(const HXLDContArray &Contour2, const Halcon::HTuple &Mode, Halcon::HTuple *DistanceMax) const;
  virtual HTuple DistanceCc(const HXLDContArray &Contour2, const char *Mode, Halcon::HTuple *DistanceMax) const;
  virtual HXLDContArray ChangeRadialDistortionContoursXld(const Halcon::HTuple &CamParIn, const Halcon::HTuple &CamParOut) const;
  virtual HXLDContArray ChangeRadialDistortionContoursXld(double CamParIn, double CamParOut) const;
  virtual HTuple TestSelfIntersectionXld(const Halcon::HTuple &CloseContours) const;
  virtual HTuple TestSelfIntersectionXld(const char *CloseContours) const;
  // Merge contours that belong to the same circle.
  virtual HXLDContArray UnionCocircularContoursXld(const Halcon::HTuple &MaxArcAngleDiff, const Halcon::HTuple &MaxArcOverlap, const Halcon::HTuple &MaxTangentAngle, const Halcon::HTuple &MaxDist, const Halcon::HTuple &MaxRadiusDiff, const Halcon::HTuple &MaxCenterDist, const Halcon::HTuple &MergeSmallContours, const Halcon::HTuple &Iterations) const;
  virtual HXLDContArray UnionCocircularContoursXld(double MaxArcAngleDiff, double MaxArcOverlap, double MaxTangentAngle, double MaxDist, double MaxRadiusDiff, double MaxCenterDist, const char *MergeSmallContours, Hlong Iterations) const;
  virtual HXLDContArray CropContoursXld(const Halcon::HTuple &Row1, const Halcon::HTuple &Col1, const Halcon::HTuple &Row2, const Halcon::HTuple &Col2, const Halcon::HTuple &CloseContours) const;
  virtual HXLDContArray CropContoursXld(double Row1, double Col1, double Row2, double Col2, const char *CloseContours) const;
  // Generate one XLD contour in the shape of a cross for each input point.
  static HXLDContArray GenCrossContourXld(const Halcon::HTuple &Row, const Halcon::HTuple &Col, const Halcon::HTuple &Size, const Halcon::HTuple &Angle);
  static HXLDContArray GenCrossContourXld(double Row, double Col, double Size, double Angle);
  // Sorting of contours with respect to their relative position.
  virtual HXLDContArray SortContoursXld(const Halcon::HTuple &SortMode, const Halcon::HTuple &Order, const Halcon::HTuple &RowOrCol) const;
  virtual HXLDContArray SortContoursXld(const char *SortMode, const char *Order, const char *RowOrCol) const;
  virtual HXLDContArray MergeContLineScanXld(const HXLDContArray &PrevConts, HXLDContArray *PrevMergedConts, const Halcon::HTuple &ImageHeight, const Halcon::HTuple &Margin, const Halcon::HTuple &MergeBorder, const Halcon::HTuple &MaxImagesCont) const;
  virtual HXLDContArray MergeContLineScanXld(const HXLDContArray &PrevConts, HXLDContArray *PrevMergedConts, Hlong ImageHeight, double Margin, const char *MergeBorder, Hlong MaxImagesCont) const;
  static HXLDContArray ReadContourXldArcInfo(const Halcon::HTuple &FileName);
  static HXLDContArray ReadContourXldArcInfo(const char *FileName);
  virtual void WriteContourXldArcInfo(const Halcon::HTuple &FileName) const;
  virtual void WriteContourXldArcInfo(const char *FileName) const;
  // Compute the parallel contour of an XLD contour.
  virtual HXLDContArray GenParallelContourXld(const Halcon::HTuple &Mode, const Halcon::HTuple &Distance) const;
  virtual HXLDContArray GenParallelContourXld(const char *Mode, double Distance) const;
  virtual HXLDContArray SegmentContoursXld(const Halcon::HTuple &Mode, const Halcon::HTuple &SmoothCont, const Halcon::HTuple &MaxLineDist1, const Halcon::HTuple &MaxLineDist2) const;
  virtual HXLDContArray SegmentContoursXld(const char *Mode, Hlong SmoothCont, double MaxLineDist1, double MaxLineDist2) const;
  virtual HTuple FitCircleContourXld(const Halcon::HTuple &Algorithm, const Halcon::HTuple &MaxNumPoints, const Halcon::HTuple &MaxClosureDist, const Halcon::HTuple &ClippingEndPoints, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, Halcon::HTuple *Column, Halcon::HTuple *Radius, Halcon::HTuple *StartPhi, Halcon::HTuple *EndPhi, Halcon::HTuple *PointOrder) const;
  virtual HTuple FitCircleContourXld(const char *Algorithm, Hlong MaxNumPoints, double MaxClosureDist, Hlong ClippingEndPoints, Hlong Iterations, double ClippingFactor, Halcon::HTuple *Column, Halcon::HTuple *Radius, Halcon::HTuple *StartPhi, Halcon::HTuple *EndPhi, Halcon::HTuple *PointOrder) const;
  virtual HTuple FitLineContourXld(const Halcon::HTuple &Algorithm, const Halcon::HTuple &MaxNumPoints, const Halcon::HTuple &ClippingEndPoints, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, Halcon::HTuple *ColBegin, Halcon::HTuple *RowEnd, Halcon::HTuple *ColEnd, Halcon::HTuple *Nr, Halcon::HTuple *Nc, Halcon::HTuple *Dist) const;
  virtual HTuple FitLineContourXld(const char *Algorithm, Hlong MaxNumPoints, Hlong ClippingEndPoints, Hlong Iterations, double ClippingFactor, Halcon::HTuple *ColBegin, Halcon::HTuple *RowEnd, Halcon::HTuple *ColEnd, Halcon::HTuple *Nr, Halcon::HTuple *Nc, Halcon::HTuple *Dist) const;
  virtual HTuple DistEllipseContourXld(const Halcon::HTuple &Mode, const Halcon::HTuple &MaxNumPoints, const Halcon::HTuple &ClippingEndPoints, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Radius1, const Halcon::HTuple &Radius2, Halcon::HTuple *MaxDist, Halcon::HTuple *AvgDist, Halcon::HTuple *SigmaDist) const;
  virtual HTuple DistEllipseContourXld(const char *Mode, Hlong MaxNumPoints, Hlong ClippingEndPoints, double Row, double Column, double Phi, double Radius1, double Radius2, Halcon::HTuple *MaxDist, Halcon::HTuple *AvgDist, Halcon::HTuple *SigmaDist) const;
  virtual HTuple FitEllipseContourXld(const Halcon::HTuple &Algorithm, const Halcon::HTuple &MaxNumPoints, const Halcon::HTuple &MaxClosureDist, const Halcon::HTuple &ClippingEndPoints, const Halcon::HTuple &VossTabSize, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, Halcon::HTuple *Column, Halcon::HTuple *Phi, Halcon::HTuple *Radius1, Halcon::HTuple *Radius2, Halcon::HTuple *StartPhi, Halcon::HTuple *EndPhi, Halcon::HTuple *PointOrder) const;
  virtual HTuple FitEllipseContourXld(const char *Algorithm, Hlong MaxNumPoints, double MaxClosureDist, Hlong ClippingEndPoints, Hlong VossTabSize, Hlong Iterations, double ClippingFactor, Halcon::HTuple *Column, Halcon::HTuple *Phi, Halcon::HTuple *Radius1, Halcon::HTuple *Radius2, Halcon::HTuple *StartPhi, Halcon::HTuple *EndPhi, Halcon::HTuple *PointOrder) const;
  static HXLDContArray GenEllipseContourXld(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Radius1, const Halcon::HTuple &Radius2, const Halcon::HTuple &StartPhi, const Halcon::HTuple &EndPhi, const Halcon::HTuple &PointOrder, const Halcon::HTuple &Resolution);
  static HXLDContArray GenEllipseContourXld(double Row, double Column, double Phi, double Radius1, double Radius2, double StartPhi, double EndPhi, const char *PointOrder, double Resolution);
  virtual HXLDContArray AddNoiseWhiteContourXld(const Halcon::HTuple &NumRegrPoints, const Halcon::HTuple &Amp) const;
  virtual HXLDContArray AddNoiseWhiteContourXld(Hlong NumRegrPoints, double Amp) const;
  // Approximate XLD contours by polygons.
  virtual HXLDPolyArray GenPolygonsXld(const Halcon::HTuple &Type, const Halcon::HTuple &Alpha) const;
  virtual HXLDPolyArray GenPolygonsXld(const char *Type, double Alpha) const;
  virtual HXLDContArray ProjectiveTransContourXld(const Halcon::HTuple &HomMat2D) const;
  virtual HXLDContArray ProjectiveTransContourXld(double HomMat2D) const;
  virtual HXLDContArray AffineTransContourXld(const Halcon::HTuple &HomMat2D) const;
  virtual HXLDContArray AffineTransContourXld(double HomMat2D) const;
  // Close an XLD contour.
  virtual HXLDContArray CloseContoursXld(void) const;
  // Clip an XLD contour.
  virtual HXLDContArray ClipContoursXld(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2) const;
  virtual HXLDContArray ClipContoursXld(Hlong Row1, Hlong Column1, Hlong Row2, Hlong Column2) const;
  // Select XLD contours with a local maximum of gray values.
  virtual HXLDContArray LocalMaxContoursXld(const HImage &Image, const Halcon::HTuple &MinPercent, const Halcon::HTuple &MinDiff, const Halcon::HTuple &Distance) const;
  virtual HXLDContArray LocalMaxContoursXld(const HImage &Image, Hlong MinPercent, Hlong MinDiff, Hlong Distance) const;
  // Merge neighboring straight contours having a similar distance from a 
  // given line.
  virtual HXLDContArray UnionStraightContoursHistoXld(HXLDContArray *SelectedContours, const Halcon::HTuple &RefLineStartRow, const Halcon::HTuple &RefLineStartColumn, const Halcon::HTuple &RefLineEndRow, const Halcon::HTuple &RefLineEndColumn, const Halcon::HTuple &Width, const Halcon::HTuple &MaxWidth, const Halcon::HTuple &FilterSize, Halcon::HTuple *HistoValues) const;
  virtual HXLDContArray UnionStraightContoursHistoXld(HXLDContArray *SelectedContours, Hlong RefLineStartRow, Hlong RefLineStartColumn, Hlong RefLineEndRow, Hlong RefLineEndColumn, Hlong Width, Hlong MaxWidth, Hlong FilterSize, Halcon::HTuple *HistoValues) const;
  // Merge neighboring straight contours having a similar direction.
  virtual HXLDContArray UnionStraightContoursXld(const Halcon::HTuple &MaxDist, const Halcon::HTuple &MaxDiff, const Halcon::HTuple &Percent, const Halcon::HTuple &Mode, const Halcon::HTuple &Iterations) const;
  // Union of collinear contours (operator with extended functionality).
  virtual HXLDContArray UnionCollinearContoursExtXld(const Halcon::HTuple &MaxDistAbs, const Halcon::HTuple &MaxDistRel, const Halcon::HTuple &MaxShift, const Halcon::HTuple &MaxAngle, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &MaxRegrError, const Halcon::HTuple &MaxCosts, const Halcon::HTuple &WeightDist, const Halcon::HTuple &WeightShift, const Halcon::HTuple &WeightAngle, const Halcon::HTuple &WeightLink, const Halcon::HTuple &WeightRegr, const Halcon::HTuple &Mode) const;
  virtual HXLDContArray UnionCollinearContoursExtXld(double MaxDistAbs, double MaxDistRel, double MaxShift, double MaxAngle, double MaxOverlap, double MaxRegrError, double MaxCosts, double WeightDist, double WeightShift, double WeightAngle, double WeightLink, double WeightRegr, const char *Mode) const;
  // Union of collinear contours.
  virtual HXLDContArray UnionCollinearContoursXld(const Halcon::HTuple &MaxDistAbs, const Halcon::HTuple &MaxDistRel, const Halcon::HTuple &MaxShift, const Halcon::HTuple &MaxAngle, const Halcon::HTuple &Mode) const;
  virtual HXLDContArray UnionCollinearContoursXld(double MaxDistAbs, double MaxDistRel, double MaxShift, double MaxAngle, const char *Mode) const;
  // Union of contours of which the end points are close together.
  virtual HXLDContArray UnionAdjacentContoursXld(const Halcon::HTuple &MaxDistAbs, const Halcon::HTuple &MaxDistRel, const Halcon::HTuple &Mode) const;
  virtual HXLDContArray UnionAdjacentContoursXld(double MaxDistAbs, double MaxDistRel, const char *Mode) const;
  // Select XLD contours according to several features.
  virtual HXLDContArray SelectContoursXld(const Halcon::HTuple &Feature, const Halcon::HTuple &Min1, const Halcon::HTuple &Max1, const Halcon::HTuple &Min2, const Halcon::HTuple &Max2) const;
  virtual HXLDContArray SelectContoursXld(const char *Feature, double Min1, double Max1, double Min2, double Max2) const;
  // Return XLD contour parameters.
  virtual HTuple GetRegressParamsXld(Halcon::HTuple *Nx, Halcon::HTuple *Ny, Halcon::HTuple *Dist, Halcon::HTuple *Fpx, Halcon::HTuple *Fpy, Halcon::HTuple *Lpx, Halcon::HTuple *Lpy, Halcon::HTuple *Mean, Halcon::HTuple *Deviation) const;
  // Calculate the parameters of a regression line to an XLD contour.
  virtual HXLDContArray RegressContoursXld(const Halcon::HTuple &Mode, const Halcon::HTuple &Iterations) const;
  virtual HXLDContArray RegressContoursXld(const char *Mode, Hlong Iterations) const;
  // Smooth an XLD contour.
  virtual HXLDContArray SmoothContoursXld(const Halcon::HTuple &NumRegrPoints) const;
  virtual HXLDContArray SmoothContoursXld(Hlong NumRegrPoints) const;
};

}

#endif
