/*****************************************************************************
 * HXLDPoly.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDPoly
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.17 $
 * $Date: 2006/07/27 14:02:38 $
 *
 */

#ifndef XLD_POLY_H
#define XLD_POLY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDPoly                                   */
/****************************************************************************/

class HXLDPolyArray;
class LIntExport HXLDPoly: public HXLD {
  friend class HXLDPolyArray;
public:
  HXLDPoly(void): HXLD() {}
  HXLDPoly(Hkey key);
  HXLDPoly(const Hobject &obj);
  HXLDPoly(const HXLDPoly &poly);
  HXLDPoly(const HXLDPolyArray &arr);
  HXLDPoly(const HXLD &xld);
  ~HXLDPoly(void) {}

  HXLDPoly &operator= (const HXLDPoly &poly);
  HXLDPoly &operator= (const HXLDPolyArray &arr);
  HXLDPoly &operator= (const HXLD &xld);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual INT4        ClassDBID(void) const;
          HBool       Shared(void) const;

  // Class Functions

public:
  // Read XLD polygons from a DXF file.
  static HXLDPoly ReadPolygonXldDxf(const Halcon::HTuple &FileName, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, char *DxfStatus);
  static HXLDPoly ReadPolygonXldDxf(const char *FileName, const char *GenParamNames, double GenParamValues, char *DxfStatus);
  // Write XLD polygons to a file in DXF format.
  virtual void WritePolygonXldDxf(const Halcon::HTuple &FileName) const;
  virtual void WritePolygonXldDxf(const char *FileName) const;
  // Create a region from an XLD polygon.
  virtual HRegion GenRegionPolygonXld(const Halcon::HTuple &Mode) const;
  virtual HRegion GenRegionPolygonXld(const char *Mode) const;
  // Union of closed polygons.
  virtual HXLDPoly Union2ClosedPolygonsXld(const HXLDPoly &Polygons2) const;
  virtual HXLDPoly Union2ClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  // Symmetric difference of closed polygons.
  virtual HXLDPoly SymmDifferenceClosedPolygonsXld(const HXLDPoly &Polygons2) const;
  virtual HXLDPoly SymmDifferenceClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  // Difference of closed polygons.
  virtual HXLDPoly DifferenceClosedPolygonsXld(const HXLDPoly &Sub) const;
  virtual HXLDPoly DifferenceClosedPolygonsXld(const HXLDPolyArray &Sub) const;
  // Intersection of closed polygons.
  virtual HXLDPoly IntersectionClosedPolygonsXld(const HXLDPoly &Polygons2) const;
  virtual HXLDPoly IntersectionClosedPolygonsXld(const HXLDPolyArray &Polygons2) const;
  // Read XLD polygons from a file in ARC/INFO generate format.
  static HXLDPoly ReadPolygonXldArcInfo(const Halcon::HTuple &FileName);
  static HXLDPoly ReadPolygonXldArcInfo(const char *FileName);
  // Write XLD polygons to a file in ARC/INFO generate format.
  virtual void WritePolygonXldArcInfo(const Halcon::HTuple &FileName) const;
  virtual void WritePolygonXldArcInfo(const char *FileName) const;
  // Return an XLD polygon's data (as lines).
  virtual HTuple GetLinesXld(Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol, Halcon::HTuple *Length, Halcon::HTuple *Phi) const;
  // Return an XLD polygon's data.
  virtual HTuple GetPolygonXld(Halcon::HTuple *Col, Halcon::HTuple *Length, Halcon::HTuple *Phi) const;
  // Split XLD contours at dominant points.
  virtual HXLDCont SplitContoursXld(const Halcon::HTuple &Mode, const Halcon::HTuple &Weight, const Halcon::HTuple &Smooth) const;
  virtual HXLDCont SplitContoursXld(const char *Mode, Hlong Weight, Hlong Smooth) const;
  // Apply an arbitrary affine transformation to XLD polygons.
  virtual HXLDPoly AffineTransPolygonXld(const Halcon::HTuple &HomMat2D) const;
};

}

#endif
