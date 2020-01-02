/*****************************************************************************
 * HRegion.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for regions
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.17 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */


#ifndef H_REGION_H
#define H_REGION_H

#include "Hconst.h"
#include "IPtype.h"


namespace Halcon {


/****************************************************************************/
/*                               HRegion                                    */
/****************************************************************************/

// <summary>
// Klasse zur Bearbeitung von Regionen.
// </summary>

// <prerequisite>
//    <li> HAbstractRegion
// </prerequisite>

// <etymology>
// HRegion ist die Kurzform fÅr Halcon-Region.
// </etymology>

// <reviewed reviewer="" date="" tests="">

// <synopsis>
// Als Basistyp fÅr Bildobjekte verwendet Halcon die virtuelle Klasse 
// HObject. Von dieser Klasse werden drei weitere Klassen abgeleitet:
//    <li> Bilder   (HImage)
//    <li> Polygone (HXLD)
//    <li> Regionen (HRegion)<BR>
// Eine Region besteht aus einer Menge von Koordinaten in der Bildebene.
// Eine solche Region muò durchaus nicht zusammenhÑngend sein und kann
// ohne weiteres auch "L˜cher" enthalten. Regionen k˜nnen auch gr˜òer als
// das aktuelle Bildformat sein. Intern werden Regionen durch 
// LauflÑngenkodierung realisiert. Die zugeh˜rige Klasse HRegion enthÑlt
// alle wichtigen Operationen zur Bearbeitung von Regionen.
// </synopsis>

// <motivation>
// HRegion bietet eine Zusammenfassung aller Operationen, die der Bearbeitung
// von Regionen dienen.
// </motivation>

// <use visibility=export>

class HRegionArray;
class LIntExport HRegion: public HAbstractRegion, public HObject {
  friend class HRegionArray;
public:
  // Default-Konstruktor. Er erzeugt eine leere Region, d.h. die FlÑche 
  // ist Null. Nicht alle Prozeduren (z.B. manche Formmerkmale) lassen 
  // sich auf diese Region anwenden.
  HRegion(void): HObject(), rl(0) {num_regions++;}
  //
  HRegion(Hkey key): HObject(key), rl(0) {num_regions++;}
  //
  HRegion(const Hobject &obj);
  // Erzeugung einer Region aus einer Sehne.
  // Eine Sehne ist eine horizontale Linie. 
  HRegion(const HDChord &line);
  // Erzeugung einer Region aus einem diskreten 2-dimensionalen Punkt.
  HRegion(const HDPoint2D &point);
  // Erzeugung einer Region aus einem Rechteck parallel zu den 
  // Koordinatenachsen mit kontinuierlichen Koordinaten.
  HRegion(const HRectangle1 &obj);
  // Erzeugung einer Region aus einem beliebig orientierten Rechteck mit
  // kontinuierlichen Koordinaten.
  HRegion(const HRectangle2 &obj);
  // Erzeugung einer Region aus einem Kreis mit kontinuierlichen Koordinaten.
  HRegion(const HCircle &obj);
  // Erzeugung einer Region aus einer beiliebig orientierten Ellipse mit
  // kontinuierlichen Koordinaten.
  HRegion(const HEllipse &obj);
  // Erzeugung einer Region durch Einlesen einer Datei. Die Datei kann mit
  // der Member-Funktion WriteRegion erzeugt werden.
  HRegion(const char *file);
  //
  HRegion(const HAbstractRegion *base);
  // Copy-Konstruktor.
  HRegion(const HRegion &reg);
  HRegion(const HRegionArray &arr);
  // Destruktor. Im Gegensatz zu den primitiven Halcon-Objekten (Hkey) 
  // braucht man sich bei dieser Klasse nicht um die Freigabe des
  // Speichers kÅmmern.
  ~HRegion(void)       {num_regions--;}
  // Zuweisungsoperator.
  HRegion &operator = (const HRegion &reg);
  HRegion &operator = (const HRegionArray &arr);

  /*----------------------- Tools ------------------------------------------*/
  //
  void          Transform(const HAffineTrans &transform, int mode);
  // Ausgabe der Region in dem angegebenen Fenster.
  virtual       void Display(const HWindow &w) const;
  // Name der Halcon-Klasse -> get_obj_class
  virtual const char *HClassName(void) const;
  //
  virtual const char *ClassName(void) const;
  //
  virtual const char *InstClassName(void) const;
  //
  virtual       INT4 ClassDBID(void) const {return REGION_ID;}
  //
  virtual       void CheckMyObjClass(void) const;
  //
  HBool          Shared(void) const;

  Hrlregion      *GetRL(void) const;

  /*----------------------- Infixoperationen -------------------------------*/ 
  // Gr˜òenskalierung der Region um den angegebenen Faktor. Das Zentrum der
  // Skalierung ist der Ursprung (0,0).
  HRegion  operator * (double scale) const;

  // Minkowsky-Subtraktion der Region mit einem Kreis mit Radius 'radius'.
  // <group>
  HRegion  operator >> (double radius) const;
  HRegion &operator >>= (double radius);
  //</group>

  // Minkowsky-Addition der Region mit einem Kreis mit Radius 'radius'.
  // <group>
  HRegion  operator << (double radius) const;
  HRegion &operator <<= (double radius);
  //</group>

  // Translation der Region mit einem diskreten Punkt.
  // <group>
  HRegion  operator + (const HDPoint2D &point) const;
  HRegion &operator += (const HDPoint2D &point);
  //</group>

  // Minkowsky-Addition der Region mit einem Kreuz, das aus insgesamt
  // 5 Punkten besteht.
  HRegion &operator ++ (void);

  // Minkowsky-Addition der Region mit einer anderen Region.
  // <group>
  HRegion  operator + (const HRegion &reg) const;
  HRegion &operator += (const HRegion &reg);
  //</group>

  // Minkowsky-Subtraktion der Region mit einer anderen Region.
  // <group>
  HRegion  operator - (const HRegion &reg) const;
  HRegion &operator -= (const HRegion &reg);
  //</group>

  // Minkowsky-Subtraktion der Region mit einem Kreuz, das aus insgesamt
  // 5 Punkten besteht.
  HRegion &operator -- (void);
  // Komplement der Region.
  HRegion  operator ~ (void) const;
  // Punktespiegelung der Region am Ursprung.
  HRegion  operator ! (void) const;

  // Durchschnitt der Region mit einer anderen Region.
  // <group>
  HRegion  operator & (const HRegion &reg) const;
  HRegion &operator &= (const HRegion &reg);
  //</group>

  // Vereinigung einer Region mit einer anderen Region.
  // <group>
  HRegion  operator | (const HRegion &reg) const;
  HRegion &operator |= (const HRegion &reg);
  //</group>

  // Von der Region eine andere Region abziehen.
  // <group>
  HRegion  operator / (const HRegion &reg) const;
  HRegion &operator /= (const HRegion &reg);
  // </group>

  // Vergleich zweier Regionen auf IdentitÑt.
  HBool     operator == (const HRegion &reg) const;

  // Test auf Enthaltensein (Teilmengenbeziehung der beinhalteten Koordinaten).
  // <group>
  HBool     operator >= (const HRegion &reg) const;
  HBool     operator > (const HRegion &reg) const;
  HBool     operator <= (const HRegion &reg) const;
  HBool     operator < (const HRegion &reg) const;
  // </group>

  // new und delete
  // <group>
#ifdef WIN32EXTRA
  void*    operator new(size_t nSize);
  void     operator delete (void* p);
#endif
  // </group>
  /*----------------------- Merkmale, die in Halcon keine Funktionen sind ---*/
  // Orientierung der Region (Winkel der Ñquivalenten Ellipse im Bogenmaò).
  double Phi(void) const;
  // LÑnge des Hauptradius der Ñquivalenten Ellipse.
  double Ra(void) const;
  // LÑnge des Nebenradius der Ñquivalenten Ellipse.
  double Rb(void) const;

  // Formfaktoren.
  // <group>
  double Anisometry(void) const;
  double Bulkiness(void) const;
  double StructureFactor(void) const;
  // </group>
  // FlÑche der Kontur.
  Hlong   Area(void) const;

  // Schwerpunkt der Region.
  // <group>
  double X(void) const {return Col();}
  double Y(void) const {return Row();}
  // </group>

  //
  double Row(void) const;
  //
  double Col(void) const;

  // Momente der Region (siehe Halcon-Referenzhandbuch).
  // <group>
  double M11(void) const;
  double M20(void) const;
  double M02(void) const;
  double Ia(void) const;
  double Ib(void) const;
  // </group>
  
  // Klassen-Operationen.
  // <group>
  static Hlong NumInst(void) { return num_regions; }
  static Hlong NumData(void);
  // </group>

  /*----------------------- Funktionen fÅr HAbstractRegion ------------------*/
  // Erzeugen einer Kopie.
  HAbstractRegion *CopyAbstractRegion(void) const;
  // Erzeugen einer analogen leeren Kopie.
  HAbstractRegion *NewEmpty(void) const;
  //
  HRectangle1 BoundingBox(void) const;
  //
  HRectangle1 SmallestRectangle1(void) const;
  // öberprÅfung, ob ein Punkt enthalten ist.
  HBool           In(const HDPoint2D &p) const;
  // EinfÅgen eines Punktes.
  void           Insert(const HDPoint2D &p);
  // L˜schen eines Punktes.
  void           Delete(const HDPoint2D &p);
  //
  HBool           IsEmpty(void) const;
  //
  HAbstractRegion *ToRLRegion(void) const;
  //
  HAbstractRegion *ToHRegion(void) const;


private:
  static Hlong num_regions;
  //	 
  Hrlregion  *rl;

  void  setRLptr(void) const;

public:
  // Extract the data values of the elements (in ECC 200: ``modules'') inside a
  // bar code region (``Data Matrix symbol'') and their positions in the image.
  virtual HTuple Get2dBarCodePos(const HImage &Image, const Halcon::HTuple &BarCodeDescr, const Halcon::HTuple &CodeRegDescr, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, Halcon::HTuple *BarCodeData, Halcon::HTuple *DataElementRow, Halcon::HTuple *DataElementCol) const;
  // Extract the values of the data elements (in ECC 200: ``modules'') inside a
  // bar code region (``Data Matrix symbol'').
  virtual HTuple Get2dBarCode(const HImage &Image, const Halcon::HTuple &BarCodeDescr, const Halcon::HTuple &CodeRegDescr, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, Halcon::HTuple *BarCodeData) const;
  // Grab and segment an image from the specified frame grabber and
  // start the asynchronous grab of the next image.
  static HRegion GrabRegionAsync(const Halcon::HTuple &FGHandle, const Halcon::HTuple &MaxDelay);
  static HRegion GrabRegionAsync(Hlong FGHandle, double MaxDelay);
  // Grab and segment an image from the specified frame grabber.
  static HRegion GrabRegion(const Halcon::HTuple &FGHandle);
  static HRegion GrabRegion(Hlong FGHandle);
  // Add gray values to regions.
  virtual HImage AddChannels(const HImage &Image) const;
  // Write regions on file.
  virtual void WriteRegion(const Halcon::HTuple &FileName) const;
  virtual void WriteRegion(const char *FileName) const;
  // Read binary images or Halcon regions.
  static HRegion ReadRegion(const Halcon::HTuple &FileName);
  static HRegion ReadRegion(const char *FileName);
  // Close edge gaps using the edge amplitude image.
  virtual HRegion CloseEdgesLength(const HImage &Gradient, const Halcon::HTuple &MinAmplitude, const Halcon::HTuple &MaxGapLength) const;
  virtual HRegion CloseEdgesLength(const HImage &Gradient, Hlong MinAmplitude, Hlong MaxGapLength) const;
  // Close edge gaps using the edge amplitude image.
  virtual HRegion CloseEdges(const HImage &EdgeImage, const Halcon::HTuple &MinAmplitude) const;
  virtual HRegion CloseEdges(const HImage &EdgeImage, Hlong MinAmplitude) const;
  // Determine the noise distribution of an image.
  virtual HTuple NoiseDistributionMean(const HImage &Image, const Halcon::HTuple &FilterSize) const;
  virtual HTuple NoiseDistributionMean(const HImage &Image, Hlong FilterSize) const;
  // Determine the fuzzy entropy of regions.
  virtual double FuzzyEntropy(const HImage &Image, const Halcon::HTuple &Apar, const Halcon::HTuple &Cpar) const;
  virtual double FuzzyEntropy(const HImage &Image, Hlong Apar, Hlong Cpar) const;
  // Calculate the fuzzy perimeter of a region.
  virtual double FuzzyPerimeter(const HImage &Image, const Halcon::HTuple &Apar, const Halcon::HTuple &Cpar) const;
  virtual double FuzzyPerimeter(const HImage &Image, Hlong Apar, Hlong Cpar) const;
  // Paint regions with their average gray value.
  virtual HImage RegionToMean(const HImage &Image) const;
  // Displays regions in a window.
  virtual void DispRegion(const Halcon::HTuple &WindowHandle) const;
  virtual void DispRegion(Hlong WindowHandle) const;
  // Query the icon for region output
  static HRegion GetIcon(const Halcon::HTuple &WindowHandle);
  static HRegion GetIcon(Hlong WindowHandle);
  // Icon definition for region output.
  virtual void SetIcon(const Halcon::HTuple &WindowHandle) const;
  virtual void SetIcon(Hlong WindowHandle) const;
  // Calculate the distance between one line segment and one region.
  virtual HTuple DistanceSr(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2, Halcon::HTuple *DistanceMax) const;
  virtual HTuple DistanceSr(double Row1, double Column1, double Row2, double Column2, Halcon::HTuple *DistanceMax) const;
  // Calculate the distance between one line and one region.
  virtual HTuple DistanceLr(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2, Halcon::HTuple *DistanceMax) const;
  virtual HTuple DistanceLr(double Row1, double Column1, double Row2, double Column2, Halcon::HTuple *DistanceMax) const;
  // Calculate the distance between one point and one region.
  virtual HTuple DistancePr(const Halcon::HTuple &Row, const Halcon::HTuple &Column, Halcon::HTuple *DistanceMax) const;
  virtual HTuple DistancePr(double Row, double Column, Halcon::HTuple *DistanceMax) const;
  // Centres of circles for a specific radius.
  virtual HRegionArray HoughCircles(const Halcon::HTuple &Radius, const Halcon::HTuple &Percent, const Halcon::HTuple &Mode) const;
  virtual HRegionArray HoughCircles(Hlong Radius, Hlong Percent, Hlong Mode) const;
  // Return the Hough-Transform for circles with a given radius.
  virtual HImageArray HoughCircleTrans(const Halcon::HTuple &Radius) const;
  virtual HImageArray HoughCircleTrans(Hlong Radius) const;
  // Detect lines in edge images with the help of the Hough transform and
  // returns it in HNF.
  virtual HTuple HoughLines(const Halcon::HTuple &AngleResolution, const Halcon::HTuple &Threshold, const Halcon::HTuple &AngleGap, const Halcon::HTuple &DistGap, Halcon::HTuple *Dist) const;
  virtual HTuple HoughLines(Hlong AngleResolution, Hlong Threshold, Hlong AngleGap, Hlong DistGap, Halcon::HTuple *Dist) const;
  // Produce the Hough transform for lines within regions.
  virtual HImage HoughLineTrans(const Halcon::HTuple &AngleResolution) const;
  virtual HImage HoughLineTrans(Hlong AngleResolution) const;
  // Select those lines from a set of lines (in HNF) which
  // fit best into a region.
  virtual HRegionArray SelectMatchingLines(const Halcon::HTuple &AngleIn, const Halcon::HTuple &DistIn, const Halcon::HTuple &LineWidth, const Halcon::HTuple &Thresh, Halcon::HTuple *AngleOut, Halcon::HTuple *DistOut) const;
  virtual HRegionArray SelectMatchingLines(double AngleIn, double DistIn, Hlong LineWidth, Hlong Thresh, Halcon::HTuple *AngleOut, Halcon::HTuple *DistOut) const;
  // Calculate gray value moments and approximation by a first order surface
  // (plane).
  virtual double FitSurfaceFirstOrder(const HImage &Image, const Halcon::HTuple &Algorithm, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, double *Beta, double *Gamma) const;
  virtual double FitSurfaceFirstOrder(const HImage &Image, const char *Algorithm, Hlong Iterations, double ClippingFactor, double *Beta, double *Gamma) const;
  // Calculate gray value moments and approximation by a second order surface.
  virtual double FitSurfaceSecondOrder(const HImage &Image, const Halcon::HTuple &Algorithm, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, double *Beta, double *Gamma, double *Delta, double *Epsilon, double *Zeta) const;
  virtual double FitSurfaceSecondOrder(const HImage &Image, const char *Algorithm, Hlong Iterations, double ClippingFactor, double *Beta, double *Gamma, double *Delta, double *Epsilon, double *Zeta) const;
  // Determine a histogram of features along all threshold values.
  virtual HTuple ShapeHistoPoint(const HImage &Image, const Halcon::HTuple &Feature, const Halcon::HTuple &Row, const Halcon::HTuple &Column, Halcon::HTuple *RelativeHisto) const;
  virtual HTuple ShapeHistoPoint(const HImage &Image, const char *Feature, Hlong Row, Hlong Column, Halcon::HTuple *RelativeHisto) const;
  // Determine a histogram of features along all threshold values.
  virtual HTuple ShapeHistoAll(const HImage &Image, const Halcon::HTuple &Feature, Halcon::HTuple *RelativeHisto) const;
  virtual HTuple ShapeHistoAll(const HImage &Image, const char *Feature, Halcon::HTuple *RelativeHisto) const;
  // Determine the minimum and maximum gray values within regions.
  virtual double MinMaxGray(const HImage &Image, const Halcon::HTuple &Percent, double *Max, double *Range) const;
  virtual double MinMaxGray(const HImage &Image, double Percent, double *Max, double *Range) const;
  // Calculate the mean and deviation of gray values.
  virtual double Intensity(const HImage &Image, double *Deviation) const;
  // Calculate the histogram of two-channel gray value images.
  virtual HImage Histo2dim(const HImage &ImageCol, const HImage &ImageRow) const;
  // Calculate the gray value distribution.
  virtual HTuple GrayHistoAbs(const HImage &Image, const Halcon::HTuple &Quantization) const;
  virtual HTuple GrayHistoAbs(const HImage &Image, double Quantization) const;
  // Calculate the gray value distribution.
  virtual HTuple GrayHisto(const HImage &Image, Halcon::HTuple *RelativeHisto) const;
  // Determine the entropy and anisotropy of images.
  virtual double EntropyGray(const HImage &Image, double *Anisotropy) const;
  // Calculate a co-occurrence matrix and derive gray value features thereof.
  virtual double CoocFeatureImage(const HImage &Image, const Halcon::HTuple &LdGray, const Halcon::HTuple &Direction, double *Correlation, double *Homogeneity, double *Contrast) const;
  virtual double CoocFeatureImage(const HImage &Image, Hlong LdGray, Hlong Direction, double *Correlation, double *Homogeneity, double *Contrast) const;
  // Calculate the co-occurrence matrix of a region in an image.
  virtual HImage GenCoocMatrix(const HImage &Image, const Halcon::HTuple &LdGray, const Halcon::HTuple &Direction) const;
  virtual HImage GenCoocMatrix(const HImage &Image, Hlong LdGray, Hlong Direction) const;
  // Calculate gray value moments and approximation by a plane.
  virtual double MomentsGrayPlane(const HImage &Image, double *MCol, double *Alpha, double *Beta, double *Mean) const;
  // Calculate the deviation of the gray values from the approximating
  // image plane.
  virtual double PlaneDeviation(const HImage &Image) const;
  // Compute the orientation and major axes of a region in a gray value
  // image.
  virtual double EllipticAxisGray(const HImage &Image, double *Rb, double *Phi) const;
  // Compute the area and center of gravity of a region in a gray value
  // image.
  virtual double AreaCenterGray(const HImage &Image, double *Row, double *Column) const;
  // Calculate horizontal and vertical gray-value projections.
  virtual HTuple GrayProjections(const HImage &Image, const Halcon::HTuple &Mode, Halcon::HTuple *VertProjection) const;
  virtual HTuple GrayProjections(const HImage &Image, const char *Mode, Halcon::HTuple *VertProjection) const;
  // Geometric moments of regions.
  virtual double MomentsRegionCentralInvar(double *PSI2, double *PSI3, double *PSI4) const;
  // Geometric moments of regions.
  virtual double MomentsRegionCentral(double *I2, double *I3, double *I4) const;
  // Geometric moments of regions.
  virtual double MomentsRegion3rdInvar(double *M12, double *M03, double *M30) const;
  // Geometric moments of regions.
  virtual double MomentsRegion3rd(double *M12, double *M03, double *M30) const;
  // Smallest surrounding rectangle with any orientation.
  virtual double SmallestRectangle2(double *Column, double *Phi, double *Length1, double *Length2) const;
  // Surrounding rectangle parallel to the coordinate axes.
  virtual Hlong SmallestRectangle1(Hlong *Column1, Hlong *Row2, Hlong *Column2) const;
  // Smallest surrounding circle of a region.
  virtual double SmallestCircle(double *Column, double *Radius) const;
  // Choose regions having a certain relation to each other.
  virtual HRegion SelectShapeProto(const HRegion &Pattern, const Halcon::HTuple &Feature, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegion SelectShapeProto(const HRegion &Pattern, const char *Feature, double Min, double Max) const;
  virtual HRegion SelectShapeProto(const HRegionArray &Pattern, const Halcon::HTuple &Feature, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegion SelectShapeProto(const HRegionArray &Pattern, const char *Feature, double Min, double Max) const;
  // Characteristic values for runlength coding of regions.
  virtual Hlong RunlengthFeatures(double *KFactor, double *LFactor, double *MeanLength, Hlong *Bytes) const;
  // Search direct neighbors.
  virtual HTuple FindNeighbors(const HRegion &Regions2, const Halcon::HTuple &MaxDistance, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple FindNeighbors(const HRegion &Regions2, Hlong MaxDistance, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple FindNeighbors(const HRegionArray &Regions2, const Halcon::HTuple &MaxDistance, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple FindNeighbors(const HRegionArray &Regions2, Hlong MaxDistance, Halcon::HTuple *RegionIndex2) const;
  // Geometric moments of regions.
  virtual double MomentsRegion2ndRelInvar(double *PHI2) const;
  // Geometric moments of regions.
  virtual double MomentsRegion2ndInvar(double *M20, double *M02) const;
  // Geometric moments of regions.
  virtual double MomentsRegion2nd(double *M20, double *M02, double *Ia, double *Ib) const;
  // Minimum distance between the contour pixels of two regions each.
  virtual double DistanceRrMin(const HRegion &Regions2, Hlong *Row1, Hlong *Column1, Hlong *Row2, Hlong *Column2) const;
  virtual double DistanceRrMin(const HRegionArray &Regions2, Hlong *Row1, Hlong *Column1, Hlong *Row2, Hlong *Column2) const;
  // Minimum distance between two regions with the help of dilatation.
  virtual Hlong DistanceRrMinDil(const HRegion &Regions2) const;
  virtual Hlong DistanceRrMinDil(const HRegionArray &Regions2) const;
  // Maximal distance between two boundary points of a region.
  virtual Hlong DiameterRegion(Hlong *Column1, Hlong *Row2, Hlong *Column2, double *Diameter) const;
  // Test if the region consists of the given point.
  virtual HBool TestRegionPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HBool TestRegionPoint(Hlong Row, Hlong Column) const;
  // Select regions of a given shape.
  virtual HRegion SelectShapeStd(const Halcon::HTuple &Shape, const Halcon::HTuple &Percent) const;
  virtual HRegion SelectShapeStd(const char *Shape, double Percent) const;
  // Hamming distance between two regions using normalization.
  virtual Hlong HammingDistanceNorm(const HRegion &Regions2, const Halcon::HTuple &Norm, double *Similarity) const;
  virtual Hlong HammingDistanceNorm(const HRegion &Regions2, const char *Norm, double *Similarity) const;
  virtual Hlong HammingDistanceNorm(const HRegionArray &Regions2, const Halcon::HTuple &Norm, double *Similarity) const;
  virtual Hlong HammingDistanceNorm(const HRegionArray &Regions2, const char *Norm, double *Similarity) const;
  // Hamming distance between two regions.
  virtual Hlong HammingDistance(const HRegion &Regions2, double *Similarity) const;
  virtual Hlong HammingDistance(const HRegionArray &Regions2, double *Similarity) const;
  // Shape features derived from the ellipse parameters.
  virtual double Eccentricity(double *Bulkiness, double *StructureFactor) const;
  // Calculate the Euler number.
  virtual Hlong EulerNumber(void) const;
  // Orientation of a region.
  virtual double OrientationRegion(void) const;
  // Parameters of the equivalent ellipse.
  virtual double EllipticAxis(double *Rb, double *Phi) const;
  // Pose relation of regions.
  virtual HTuple SelectRegionSpatial(const HRegion &Regions2, const Halcon::HTuple &Direction, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple SelectRegionSpatial(const HRegion &Regions2, const char *Direction, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple SelectRegionSpatial(const HRegionArray &Regions2, const Halcon::HTuple &Direction, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple SelectRegionSpatial(const HRegionArray &Regions2, const char *Direction, Halcon::HTuple *RegionIndex2) const;
  // Pose relation of regions with regard to  the coordinate axes.
  virtual HTuple SpatialRelation(const HRegion &Regions2, const Halcon::HTuple &Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  virtual HTuple SpatialRelation(const HRegion &Regions2, Hlong Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  virtual HTuple SpatialRelation(const HRegionArray &Regions2, const Halcon::HTuple &Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  virtual HTuple SpatialRelation(const HRegionArray &Regions2, Hlong Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  // Shape factor for the convexity of a region.
  virtual double Convexity(void) const;
  // Contour length of a region.
  virtual double Contlength(void) const;
  // Number of connection components and holes
  virtual Hlong ConnectAndHoles(Hlong *NumHoles) const;
  // Shape factor for the rectangularity of a region.
  virtual double Rectangularity(void) const;
  // Shape factor for the compactness of a region.
  virtual double Compactness(void) const;
  // Shape factor for the circularity (similarity to a circle) of a region.
  virtual double Circularity(void) const;
  // Area and center of regions.
  virtual Hlong AreaCenter(double *Row, double *Column) const;
  // Distribution of runs needed for runlength encoding of a region.
  virtual HTuple RunlengthDistribution(Halcon::HTuple *Background) const;
  // Shape factors from contour.
  virtual double Roundness(double *Sigma, double *Roundness, double *Sides) const;
  // Largest inner circle of a region.
  virtual double InnerCircle(double *Column, double *Radius) const;
  // Prune the branches of a region.
  virtual HRegion Pruning(const Halcon::HTuple &Length) const;
  virtual HRegion Pruning(Hlong Length) const;
  // Reduce a region to its boundary.
  virtual HRegion Boundary(const Halcon::HTuple &BoundaryType) const;
  virtual HRegion Boundary(const char *BoundaryType) const;
  // Perform a closing after an opening with multiple structuring elements.
  virtual HRegion Fitting(const HRegion &StructElements) const;
  virtual HRegion Fitting(const HRegionArray &StructElements) const;
  // Generate standard structuring elements.
  static HRegion GenStructElements(const Halcon::HTuple &Type, const Halcon::HTuple &Row, const Halcon::HTuple &Column);
  static HRegion GenStructElements(const char *Type, Hlong Row, Hlong Column);
  // Reflect a region about a point.
  virtual HRegion TransposeRegion(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegion TransposeRegion(Hlong Row, Hlong Column) const;
  // Remove the result of a hit-or-miss operation from a region (sequential).
  virtual HRegion ThinningSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion ThinningSeq(const char *GolayElement, Hlong Iterations) const;
  // Remove the result of a hit-or-miss operation from a region (using a
  // Golay structuring element).
  virtual HRegion ThinningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegion ThinningGolay(const char *GolayElement, Hlong Rotation) const;
  // Remove the result of a hit-or-miss operation from a region.
  virtual HRegion Thinning(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion Thinning(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Add the result of a hit-or-miss operation to a region (sequential).
  virtual HRegion ThickeningSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion ThickeningSeq(const char *GolayElement, Hlong Iterations) const;
  // Add the result of a hit-or-miss operation to a region (using a Golay
  // structuring element).
  virtual HRegion ThickeningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegion ThickeningGolay(const char *GolayElement, Hlong Rotation) const;
  // Add the result of a hit-or-miss operation to a region.
  virtual HRegion Thickening(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion Thickening(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Hit-or-miss operation for regions using the Golay alphabet (sequential).
  virtual HRegion HitOrMissSeq(const Halcon::HTuple &GolayElement) const;
  virtual HRegion HitOrMissSeq(const char *GolayElement) const;
  // Hit-or-miss operation for regions using the Golay alphabet.
  virtual HRegion HitOrMissGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegion HitOrMissGolay(const char *GolayElement, Hlong Rotation) const;
  // Hit-or-miss operation for regions.
  virtual HRegion HitOrMiss(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegion HitOrMiss(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column) const;
  // Generate the structuring elements of the Golay alphabet.
  static HRegion GolayElements(HRegion *StructElement2, const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation, const Halcon::HTuple &Row, const Halcon::HTuple &Column);
  static HRegion GolayElements(HRegion *StructElement2, const char *GolayElement, Hlong Rotation, Hlong Row, Hlong Column);
  // Thinning of a region.
  virtual HRegion MorphSkiz(const Halcon::HTuple &Iterations1, const Halcon::HTuple &Iterations2) const;
  virtual HRegion MorphSkiz(Hlong Iterations1, Hlong Iterations2) const;
  // Compute the morphological skeleton of a region.
  virtual HRegion MorphSkeleton(void) const;
  // Compute the union of bottom_hat and top_hat.
  virtual HRegion MorphHat(const HRegion &StructElement) const;
  // Compute the bottom hat of regions.
  virtual HRegion BottomHat(const HRegion &StructElement) const;
  // Compute the top hat of regions.
  virtual HRegion TopHat(const HRegion &StructElement) const;
  // Erode a region (using a reference point).
  virtual HRegion MinkowskiSub2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion MinkowskiSub2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Erode a region.
  virtual HRegion MinkowskiSub1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion MinkowskiSub1(const HRegion &StructElement, Hlong Iterations) const;
  // Dilate a region (using a reference point).
  virtual HRegion MinkowskiAdd2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion MinkowskiAdd2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Perform a Minkowski addition on a region.
  virtual HRegion MinkowskiAdd1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion MinkowskiAdd1(const HRegion &StructElement, Hlong Iterations) const;
  // Close a region with a rectangular structuring element.
  virtual HRegion ClosingRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegion ClosingRectangle1(Hlong Width, Hlong Height) const;
  // Close a region with an element from the Golay alphabet.
  virtual HRegion ClosingGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegion ClosingGolay(const char *GolayElement, Hlong Rotation) const;
  // Close a region with a circular structuring element.
  virtual HRegion ClosingCircle(const Halcon::HTuple &Radius) const;
  virtual HRegion ClosingCircle(double Radius) const;
  // Close a region.
  virtual HRegion Closing(const HRegion &StructElement) const;
  // Separate overlapping regions.
  virtual HRegionArray OpeningSeg(const HRegion &StructElement) const;
  // Open a region with an element from the Golay alphabet.
  virtual HRegion OpeningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegion OpeningGolay(const char *GolayElement, Hlong Rotation) const;
  // Open a region with a rectangular structuring element.
  virtual HRegion OpeningRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegion OpeningRectangle1(Hlong Width, Hlong Height) const;
  // Open a region with a circular structuring element.
  virtual HRegion OpeningCircle(const Halcon::HTuple &Radius) const;
  virtual HRegion OpeningCircle(double Radius) const;
  // Open a region.
  virtual HRegion Opening(const HRegion &StructElement) const;
  // Erode a region sequentially.
  virtual HRegion ErosionSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion ErosionSeq(const char *GolayElement, Hlong Iterations) const;
  // Erode a region with an element from the Golay alphabet.
  virtual HRegion ErosionGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations, const Halcon::HTuple &Rotation) const;
  virtual HRegion ErosionGolay(const char *GolayElement, Hlong Iterations, Hlong Rotation) const;
  // Erode a region with a rectangular structuring element.
  virtual HRegion ErosionRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegion ErosionRectangle1(Hlong Width, Hlong Height) const;
  // Erode a region with a circular structuring element.
  virtual HRegion ErosionCircle(const Halcon::HTuple &Radius) const;
  virtual HRegion ErosionCircle(double Radius) const;
  // Erode a region (using a reference point).
  virtual HRegion Erosion2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion Erosion2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Erode a region.
  virtual HRegion Erosion1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion Erosion1(const HRegion &StructElement, Hlong Iterations) const;
  // Dilate a region sequentially.
  virtual HRegion DilationSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion DilationSeq(const char *GolayElement, Hlong Iterations) const;
  // Dilate a region with an element from the Golay alphabet.
  virtual HRegion DilationGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations, const Halcon::HTuple &Rotation) const;
  virtual HRegion DilationGolay(const char *GolayElement, Hlong Iterations, Hlong Rotation) const;
  // Dilate a region with a rectangular structuring element.
  virtual HRegion DilationRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegion DilationRectangle1(Hlong Width, Hlong Height) const;
  // Dilate a region with a circular structuring element.
  virtual HRegion DilationCircle(const Halcon::HTuple &Radius) const;
  virtual HRegion DilationCircle(double Radius) const;
  // Dilate a region (using a reference point).
  virtual HRegion Dilation2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegion Dilation2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  // Dilate a region.
  virtual HRegion Dilation1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegion Dilation1(const HRegion &StructElement, Hlong Iterations) const;
  // Classify one character.
  virtual HTuple DoOcrSingle(const HImage &Image, const Halcon::HTuple &OcrHandle, Halcon::HTuple *Confidences) const;
  virtual HTuple DoOcrSingle(const HImage &Image, Hlong OcrHandle, Halcon::HTuple *Confidences) const;
  // Classify characters.
  virtual HTuple DoOcrMulti(const HImage &Image, const Halcon::HTuple &OcrHandle, double *Confidence) const;
  virtual HTuple DoOcrMulti(const HImage &Image, Hlong OcrHandle, double *Confidence) const;
  // Train an OCR classifier by the input of regions.
  virtual double TraindOcrClassBox(const HImage &Image, const Halcon::HTuple &OcrHandle, const Halcon::HTuple &Class) const;
  virtual double TraindOcrClassBox(const HImage &Image, Hlong OcrHandle, const char *Class) const;
  // Storing of trained characters into a file.
  virtual void WriteOcrTrainf(const HImage &Image, const Halcon::HTuple &Class, const Halcon::HTuple &FileName) const;
  virtual void WriteOcrTrainf(const HImage &Image, const char *Class, const char *FileName) const;
  // Train an OCR classifier by the input of regions.
  virtual double TestdOcrClassBox(const HImage &Image, const Halcon::HTuple &OcrHandle, const Halcon::HTuple &Class) const;
  virtual double TestdOcrClassBox(const HImage &Image, Hlong OcrHandle, const char *Class) const;
  // Add characters to a training file.
  virtual void AppendOcrTrainf(const HImage &Image, const Halcon::HTuple &Class, const Halcon::HTuple &FileName) const;
  virtual void AppendOcrTrainf(const HImage &Image, const char *Class, const char *FileName) const;
  // Store a polygon as a ``filled'' region.
  static HRegion GenRegionPolygonFilled(const Halcon::HTuple &Rows, const Halcon::HTuple &Columns);
  static HRegion GenRegionPolygonFilled(Hlong Rows, Hlong Columns);
  // Store a polygon as an image object.
  static HRegion GenRegionPolygon(const Halcon::HTuple &Rows, const Halcon::HTuple &Columns);
  static HRegion GenRegionPolygon(Hlong Rows, Hlong Columns);
  // Store individual pixels as image region.
  static HRegion GenRegionPoints(const Halcon::HTuple &Rows, const Halcon::HTuple &Columns);
  static HRegion GenRegionPoints(Hlong Rows, Hlong Columns);
  // Create an image region from a runlength coding.
  static HRegion GenRegionRuns(const Halcon::HTuple &Row, const Halcon::HTuple &ColumnBegin, const Halcon::HTuple &ColumnEnd);
  static HRegion GenRegionRuns(Hlong Row, Hlong ColumnBegin, Hlong ColumnEnd);
  // Create a rectangle of any orientation.
  static HRegion GenRectangle2(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Length1, const Halcon::HTuple &Length2);
  static HRegion GenRectangle2(double Row, double Column, double Phi, double Length1, double Length2);
  // Create a rectangle parallel to the coordinate axes.
  static HRegion GenRectangle1(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2);
  static HRegion GenRectangle1(double Row1, double Column1, double Row2, double Column2);
  // Create a random region.
  static HRegion GenRandomRegion(const Halcon::HTuple &Width, const Halcon::HTuple &Height);
  static HRegion GenRandomRegion(Hlong Width, Hlong Height);
  // Create an ellipse.
  static HRegion GenEllipse(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Radius1, const Halcon::HTuple &Radius2);
  static HRegion GenEllipse(double Row, double Column, double Phi, double Radius1, double Radius2);
  // Create a circle.
  static HRegion GenCircle(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Radius);
  static HRegion GenCircle(double Row, double Column, double Radius);
  // Create a checkered region.
  static HRegion GenCheckerRegion(const Halcon::HTuple &WidthRegion, const Halcon::HTuple &HeightRegion, const Halcon::HTuple &WidthPattern, const Halcon::HTuple &HeightPattern);
  static HRegion GenCheckerRegion(Hlong WidthRegion, Hlong HeightRegion, Hlong WidthPattern, Hlong HeightPattern);
  // Create a region from lines or pixels.
  static HRegion GenGridRegion(const Halcon::HTuple &RowSteps, const Halcon::HTuple &ColumnSteps, const Halcon::HTuple &Type, const Halcon::HTuple &Width, const Halcon::HTuple &Height);
  static HRegion GenGridRegion(Hlong RowSteps, Hlong ColumnSteps, const char *Type, Hlong Width, Hlong Height);
  // Store input lines described in Hesse normal shape as regions.
  static HRegion GenRegionHline(const Halcon::HTuple &Orientation, const Halcon::HTuple &Distance);
  static HRegion GenRegionHline(double Orientation, double Distance);
  // Store input lines as regions.
  static HRegion GenRegionLine(const Halcon::HTuple &BeginRow, const Halcon::HTuple &BeginCol, const Halcon::HTuple &EndRow, const Halcon::HTuple &EndCol);
  static HRegion GenRegionLine(Hlong BeginRow, Hlong BeginCol, Hlong EndRow, Hlong EndCol);
  // Create an empty region.
  static HRegion GenEmptyRegion();
  // Test whether the regions of two objects are identical.
  virtual HBool TestEqualRegion(const HRegion &Regions2) const;
  virtual HBool TestEqualRegion(const HRegionArray &Regions2) const;
  // Paint regions into an image.
  virtual HImage PaintRegion(const HImage &Image, const Halcon::HTuple &Grayval, const Halcon::HTuple &Type) const;
  virtual HImage PaintRegion(const HImage &Image, double Grayval, const char *Type) const;
  // Access the thickness of a region along the main axis.
  virtual HTuple GetRegionThickness(Halcon::HTuple *Histogramm) const;
  // Polygon approximation of a region.
  virtual HTuple GetRegionPolygon(const Halcon::HTuple &Tolerance, Halcon::HTuple *Columns) const;
  virtual HTuple GetRegionPolygon(double Tolerance, Halcon::HTuple *Columns) const;
  // Access the pixels of a region.
  virtual HTuple GetRegionPoints(Halcon::HTuple *Columns) const;
  // Access the contour of an object.
  virtual HTuple GetRegionContour(Halcon::HTuple *Columns) const;
  // Access the runlength coding of a region.
  virtual HTuple GetRegionRuns(Halcon::HTuple *ColumnBegin, Halcon::HTuple *ColumnEnd) const;
  // Contour of an object as chain code.
  virtual Hlong GetRegionChain(Halcon::HTuple *Column, Halcon::HTuple *Chain) const;
  // Access convex hull as contour.
  virtual HTuple GetRegionConvex(Halcon::HTuple *Columns) const;
  // Merge regions from line scan images.
  virtual HRegion MergeRegionsLineScan(const HRegion &PrevRegions, HRegion *PrevMergedRegions, const Halcon::HTuple &ImageHeight, const Halcon::HTuple &MergeBorder, const Halcon::HTuple &MaxImagesRegion) const;
  virtual HRegion MergeRegionsLineScan(const HRegion &PrevRegions, HRegion *PrevMergedRegions, Hlong ImageHeight, const char *MergeBorder, Hlong MaxImagesRegion) const;
  virtual HRegion MergeRegionsLineScan(const HRegionArray &PrevRegions, HRegion *PrevMergedRegions, const Halcon::HTuple &ImageHeight, const Halcon::HTuple &MergeBorder, const Halcon::HTuple &MaxImagesRegion) const;
  virtual HRegion MergeRegionsLineScan(const HRegionArray &PrevRegions, HRegion *PrevMergedRegions, Hlong ImageHeight, const char *MergeBorder, Hlong MaxImagesRegion) const;
  // Partition a region into rectangles of equal size.
  virtual HRegion PartitionRectangle(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegion PartitionRectangle(double Width, double Height) const;
  // Partition a region horizontally into rectangles.
  virtual HRegionArray PartitionDynamic(const Halcon::HTuple &Distance, const Halcon::HTuple &Percent) const;
  virtual HRegionArray PartitionDynamic(double Distance, double Percent) const;
  // Convert regions to a label image.
  virtual HImage RegionToLabel(const Halcon::HTuple &Type, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage RegionToLabel(const char *Type, Hlong Width, Hlong Height) const;
  // Convert a region into a binary byte-image.
  virtual HImage RegionToBin(const Halcon::HTuple &ForegroundGray, const Halcon::HTuple &BackgroundGray, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage RegionToBin(Hlong ForegroundGray, Hlong BackgroundGray, Hlong Width, Hlong Height) const;
  // Return the union of two regions.
  virtual HRegion Union2(const HRegion &Region2) const;
  virtual HRegion Union2(const HRegionArray &Region2) const;
  // Compute the distance transformation of a region.
  virtual HImage DistanceTransform(const Halcon::HTuple &Metric, const Halcon::HTuple &Foreground, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage DistanceTransform(const char *Metric, const char *Foreground, Hlong Width, Hlong Height) const;
  // Compute the skeleton of a region.
  virtual HRegion Skeleton(void) const;
  // Apply a projective transformation to a region.
  virtual HRegion ProjectiveTransRegion(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation) const;
  virtual HRegion ProjectiveTransRegion(double HomMat2D, const char *Interpolation) const;
  // Apply an arbitrary affine 2D transformation to regions.
  virtual HRegion AffineTransRegion(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolate) const;
  virtual HRegion AffineTransRegion(double HomMat2D, const char *Interpolate) const;
  // Reflect a region about the x- or y-axis.
  virtual HRegion MirrorRegion(const Halcon::HTuple &RowColumn, const Halcon::HTuple &WidthHeight) const;
  virtual HRegion MirrorRegion(const char *RowColumn, Hlong WidthHeight) const;
  // Zoom a region.
  virtual HRegion ZoomRegion(const Halcon::HTuple &ScaleWidth, const Halcon::HTuple &ScaleHeight) const;
  virtual HRegion ZoomRegion(double ScaleWidth, double ScaleHeight) const;
  // Translate a region.
  virtual HRegion MoveRegion(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegion MoveRegion(Hlong Row, Hlong Column) const;
  // Find junctions and end points in a skeleton.
  virtual HRegion JunctionsSkeleton(HRegion *JuncPoints) const;
  // Calculate the intersection of two regions.
  virtual HRegion Intersection(const HRegion &Region2) const;
  virtual HRegion Intersection(const HRegionArray &Region2) const;
  // Partition the image plane using given regions.
  virtual HRegion Interjacent(const Halcon::HTuple &Mode) const;
  virtual HRegion Interjacent(const char *Mode) const;
  // Fill up holes in regions.
  virtual HRegion FillUp(void) const;
  // Fill up holes in regions having given shape features.
  virtual HRegion FillUpShape(const Halcon::HTuple &Feature, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegion FillUpShape(const char *Feature, double Min, double Max) const;
  // Fill gaps between regions or split overlapping regions.
  virtual HRegion ExpandRegion(const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode) const;
  virtual HRegion ExpandRegion(const HRegion &ForbiddenArea, Hlong Iterations, const char *Mode) const;
  // Clip a region relative to its size.
  virtual HRegion ClipRegionRel(const Halcon::HTuple &Top, const Halcon::HTuple &Bottom, const Halcon::HTuple &Left, const Halcon::HTuple &Right) const;
  virtual HRegion ClipRegionRel(Hlong Top, Hlong Bottom, Hlong Left, Hlong Right) const;
  // Clip a region to a rectangle.
  virtual HRegion ClipRegion(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2) const;
  virtual HRegion ClipRegion(Hlong Row1, Hlong Column1, Hlong Row2, Hlong Column2) const;
  // Rank operator for regions.
  virtual HRegion RankRegion(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Number) const;
  virtual HRegion RankRegion(Hlong Width, Hlong Height, Hlong Number) const;
  // Compute connected components of a region.
  virtual HRegionArray Connection(void) const;
  // Calculate the symmetric difference of two regions.
  virtual HRegion SymmDifference(const HRegion &Region2) const;
  virtual HRegion SymmDifference(const HRegionArray &Region2) const;
  // Calculate the difference of two regions.
  virtual HRegion Difference(const HRegion &Sub) const;
  virtual HRegion Difference(const HRegionArray &Sub) const;
  // Return the complement of a region.
  virtual HRegion Complement(void) const;
  // Determine the connected components of the background of given regions.
  virtual HRegionArray BackgroundSeg(void) const;
  // Generate a region having a given Hamming distance.
  virtual HRegion HammingChangeRegion(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Distance) const;
  virtual HRegion HammingChangeRegion(Hlong Width, Hlong Height, Hlong Distance) const;
  // Remove noise from a region.
  virtual HRegion RemoveNoiseRegion(const Halcon::HTuple &Type) const;
  virtual HRegion RemoveNoiseRegion(const char *Type) const;
  // Transform the shape of a region.
  virtual HRegion ShapeTrans(const Halcon::HTuple &Type) const;
  virtual HRegion ShapeTrans(const char *Type) const;
  // Fill gaps between regions (depending on gray value or color) or split
  // overlapping regions.
  virtual HRegion ExpandGray(const HImage &Image, const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode, const Halcon::HTuple &Threshold) const;
  // Fill gaps between regions (depending on gray value or color) or split
  // overlapping regions.
  virtual HRegion ExpandGrayRef(const HImage &Image, const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode, const Halcon::HTuple &RefGray, const Halcon::HTuple &Threshold) const;
  // Split lines represented by one pixel wide, non-branching regions.
  virtual HRegionArray SplitSkeletonRegion(const Halcon::HTuple &MaxDistance) const;
  virtual HRegionArray SplitSkeletonRegion(Hlong MaxDistance) const;
  // Convert a histogram into a region.
  static HRegion GenRegionHisto(const Halcon::HTuple &Histogram, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Scale);
  static HRegion GenRegionHisto(Hlong Histogram, Hlong Row, Hlong Column, Hlong Scale);
  // Eliminate runs of a given length.
  virtual HRegion EliminateRuns(const Halcon::HTuple &ElimShorter, const Halcon::HTuple &ElimLonger) const;
  virtual HRegion EliminateRuns(Hlong ElimShorter, Hlong ElimLonger) const;
  // Construct classes for class_ndim_norm.
  virtual HTuple LearnNdimNorm(const HRegion &Background, const HImage &Image, const Halcon::HTuple &Metric, const Halcon::HTuple &Distance, const Halcon::HTuple &MinNumberPercent, Halcon::HTuple *Center, double *Quality) const;
  virtual HTuple LearnNdimNorm(const HRegion &Background, const HImage &Image, const char *Metric, double Distance, double MinNumberPercent, Halcon::HTuple *Center, double *Quality) const;
  virtual HTuple LearnNdimNorm(const HRegionArray &Background, const HImageArray &Image, const Halcon::HTuple &Metric, const Halcon::HTuple &Distance, const Halcon::HTuple &MinNumberPercent, Halcon::HTuple *Center, double *Quality) const;
  virtual HTuple LearnNdimNorm(const HRegionArray &Background, const HImageArray &Image, const char *Metric, double Distance, double MinNumberPercent, Halcon::HTuple *Center, double *Quality) const;
  // Train a classificator using a multi-channel image.
  virtual void LearnNdimBox(const HRegion &Background, const HImage &MultiChannelImage, const Halcon::HTuple &ClassifHandle) const;
  virtual void LearnNdimBox(const HRegion &Background, const HImage &MultiChannelImage, Hlong ClassifHandle) const;
  virtual void LearnNdimBox(const HRegionArray &Background, const HImageArray &MultiChannelImage, const Halcon::HTuple &ClassifHandle) const;
  virtual void LearnNdimBox(const HRegionArray &Background, const HImageArray &MultiChannelImage, Hlong ClassifHandle) const;
  // Receive regions over a socket connection.
  static HRegion ReceiveRegion(const Halcon::HTuple &Socket);
  static HRegion ReceiveRegion(Hlong Socket);
  // Send regions over a socket connection.
  virtual void SendRegion(const Halcon::HTuple &Socket) const;
  virtual void SendRegion(Hlong Socket) const;
  // Generate XLD contours from regions.
  virtual HXLDCont GenContourRegionXld(const Halcon::HTuple &Mode) const;
  virtual HXLDCont GenContourRegionXld(const char *Mode) const;
  // Convert a skeleton into XLD contours.
  virtual HXLDContArray GenContoursSkeletonXld(const Halcon::HTuple &Length, const Halcon::HTuple &Mode) const;
  virtual HXLDContArray GenContoursSkeletonXld(Hlong Length, const char *Mode) const;
};

}

#endif
