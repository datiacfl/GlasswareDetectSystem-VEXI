/*****************************************************************************
 * HXLDPoly.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDPoly
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.16 $
 * $Date: 2005/05/06 07:36:06 $
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
  HXLDPoly(void): HXLD() {num_poly++;}
  HXLDPoly(Hkey key);
  HXLDPoly(const Hobject &obj);
  HXLDPoly(const HXLDPoly &poly);
  HXLDPoly(const HXLDPolyArray &arr);
  HXLDPoly(const HXLD &xld);
  ~HXLDPoly(void) {num_poly--;}

  HXLDPoly &operator= (const HXLDPoly &poly);
  HXLDPoly &operator= (const HXLDPolyArray &arr);
  HXLDPoly &operator= (const HXLD &xld);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void) const;
  HBool         Shared(void) const;

  // Class Functions
  static Hlong NumInst(void) {return num_poly;}

private:
  static Hlong num_poly;

public:
  // Create a region from an XLD polygon.
  virtual HRegion GenRegionPolygonXld(const Halcon::HTuple &Mode) const;
  virtual HRegion GenRegionPolygonXld(const char *Mode) const;
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
  virtual HXLDPoly AffineTransPolygonXld(double HomMat2D) const;
};

}

#endif
