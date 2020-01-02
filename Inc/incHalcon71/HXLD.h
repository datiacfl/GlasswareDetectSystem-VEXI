/*****************************************************************************
 * HXLD.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLD
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 */

#ifndef XLD_H
#define XLD_H


namespace Halcon {


/****************************************************************************/
/*                               HXLD                                       */
/****************************************************************************/

class HXLDArray;
class LIntExport HXLD: public HObject {
  friend class HXLDArray;
public:
  HXLD(void): HObject() {num_xld++;}
  HXLD(Hkey key, HBool checktype = H_TRUE);
  HXLD(const Hobject &obj, HBool checktype = H_TRUE);
  HXLD(const HXLD &xld);
  HXLD(const HXLDArray &arr);
  ~HXLD(void) {num_xld--;}

  HXLD &operator= (const HXLD &xld);
  HXLD &operator= (const HXLDArray &arr);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual HBool       Shared(void) const;
  virtual void        Display(const HWindow &w) const;

  // Class Functions
  static Hlong NumInst(void) {return num_xld;}

private:
  static Hlong num_xld;

public:
  // Determine the 3D pose of a circle from its perspective 2D projection.
  // 
  virtual HTuple GetCirclePose(const Halcon::HTuple &CamParam, const Halcon::HTuple &Radius, const Halcon::HTuple &OutputType, Halcon::HTuple *Pose2) const;
  virtual HTuple GetCirclePose(double CamParam, double Radius, const char *OutputType, Halcon::HTuple *Pose2) const;
  // Choose all contours or polygons containing a given pixel.
  virtual HXLD SelectXldPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HXLD SelectXldPoint(double Row, double Column) const;
  // Test whether one or more contours or polygons enclose the given point(s).
  virtual Hlong TestXldPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual Hlong TestXldPoint(double Row, double Column) const;
  // Orientation of a contour.
  virtual double OrientationXld(void) const;
  // Shape features derived from the ellipse parameters.
  virtual double EccentricityXld(double *Bulkiness, double *StructureFactor) const;
  // Shape factor for the compactness of a contour.
  virtual double CompactnessXld(void) const;
  // Maximum distance between two contour points.
  virtual double DiameterXld(double *Column1, double *Row2, double *Column2, double *Diameter) const;
  // Shape factor for the convexity of a contour.
  virtual double ConvexityXld(void) const;
  // Shape factor for the circularity (similarity to a circle) of a contour.
  virtual double CircularityXld(void) const;
  // Parameters of the equivalent ellipse.
  virtual double EllipticAxisXld(double *Rb, double *Phi) const;
  // Smallest enclosing rectangle with arbitrary orientation.
  virtual double SmallestRectangle2Xld(double *Column, double *Phi, double *Length1, double *Length2) const;
  // Enclosing rectangle parallel to the coordinate axes.
  virtual double SmallestRectangle1Xld(double *Column1, double *Row2, double *Column2) const;
  // Smallest enclosing circle of a contour.
  virtual double SmallestCircleXld(double *Column, double *Radius) const;
  // Transform the shape of a contour.
  virtual HXLD ShapeTransXld(const Halcon::HTuple &Type) const;
  virtual HXLD ShapeTransXld(const char *Type) const;
  // Length of contours or polygons.
  virtual double LengthXld(void) const;
  // Arbitrary geometric moments of contours or polygons.
  virtual double MomentsAnyXld(const Halcon::HTuple &Mode, const Halcon::HTuple &PointOrder, const Halcon::HTuple &Area, const Halcon::HTuple &CenterRow, const Halcon::HTuple &CenterCol, const Halcon::HTuple &P, const Halcon::HTuple &Q) const;
  virtual double MomentsAnyXld(const char *Mode, const char *PointOrder, double Area, double CenterRow, double CenterCol, Hlong P, Hlong Q) const;
  // Geometric moments M20, M02, and M11 of contours or polygons.
  virtual double MomentsXld(double *M20, double *M02) const;
  // Area and center of gravity (centroid) of contours and polygons.
  virtual double AreaCenterXld(double *Row, double *Column, char *PointOrder) const;
  // Paint XLD objects into an image.
  virtual HImage PaintXld(const HImage &Image, const Halcon::HTuple &Grayval) const;
  virtual HImage PaintXld(const HImage &Image, double Grayval) const;
  // Receive an XLD object over a socket connection.
  static HXLD ReceiveXld(const Halcon::HTuple &Socket);
  static HXLD ReceiveXld(Hlong Socket);
  // Send an XLD object over a socket connection.
  virtual void SendXld(const Halcon::HTuple &Socket) const;
  virtual void SendXld(Hlong Socket) const;
  // Return an XLD parallel's data (as lines).
  virtual HTuple GetParallelsXld(Halcon::HTuple *Col1, Halcon::HTuple *Length1, Halcon::HTuple *Phi1, Halcon::HTuple *Row2, Halcon::HTuple *Col2, Halcon::HTuple *Length2, Halcon::HTuple *Phi2) const;
};

}

#endif
