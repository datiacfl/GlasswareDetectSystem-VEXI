/*****************************************************************************
 * HRegionArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for regions arrays
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


#ifndef H_REGION_ARRAY_H
#define H_REGION_ARRAY_H

//#include "Hconst.h"
//#include "IPtype.h"


namespace Halcon {


/****************************************************************************/
/*                            HRegionArray                                  */
/****************************************************************************/
class LIntExport HRegionArray: public HObjectArray {
public:
  HRegionArray(void) : array(NULL) {}
  HRegionArray(Hkey *key, Hlong num);
  HRegionArray(const Hobject &obj);
  HRegionArray(const HRegion &reg);
  HRegionArray(const HRegionArray &arr);
  ~HRegionArray(void);
  HRegionArray &operator = (const HRegionArray &arr);
  
  // Tools
  virtual const char *HClassName(void)    const;
  virtual const char *ClassName(void)     const;
  virtual       INT4  ClassDBID(void)     const {return REGION_ID;}
  virtual       Hkey  Key(Hlong i)         const {return array[i].Key();}
  virtual    Hobject  ElemId(Hlong i)      const {return array[i].Id();}
  
  // Access und Manipulation
  HRegion      const &operator [] (Hlong index) const;
  HRegion            &operator [] (Hlong index);
  HRegionArray        operator () (Hlong min, Hlong max) const;
  HRegionArray       &Append(const HRegion &reg);
  HRegionArray       &Append(const HRegionArray &reg);
  virtual void        SetKeys(Hkey *key, Hlong num);
  virtual void        SetKeys(Hkey *key, Hlong num, Herror *err);
  virtual void        Display(const HWindow &w) const;
  virtual void        DeleteArray(void);
  
  // Infix Operations
  HRegionArray operator >> (double radius) const;
  HRegionArray operator << (double radius) const;
  HRegionArray operator + (const HRegion &reg) const;
  HRegionArray operator - (const HRegion &reg) const;
  HRegionArray operator ~ (void) const;
  HRegionArray operator & (const HRegionArray &reg) const;
  HRegionArray operator | (const HRegionArray &reg) const;
  HRegionArray operator / (const HRegionArray &reg) const;
  
private:
  HRegion  *array;
  void     NewLength(Hlong new_num, Hlong old_num);
  void     CopyHRegionArray(const HRegionArray &in);

public:
  virtual HImageArray AddChannels(const HImage &Image) const;
  virtual void WriteRegion(const Halcon::HTuple &FileName) const;
  virtual void WriteRegion(const char *FileName) const;
  static HRegionArray ReadRegion(const Halcon::HTuple &FileName);
  static HRegionArray ReadRegion(const char *FileName);
  virtual HRegionArray CloseEdgesLength(const HImage &Gradient, const Halcon::HTuple &MinAmplitude, const Halcon::HTuple &MaxGapLength) const;
  virtual HRegionArray CloseEdgesLength(const HImage &Gradient, Hlong MinAmplitude, Hlong MaxGapLength) const;
  virtual HRegionArray CloseEdges(const HImage &EdgeImage, const Halcon::HTuple &MinAmplitude) const;
  virtual HRegionArray CloseEdges(const HImage &EdgeImage, Hlong MinAmplitude) const;
  virtual HTuple NoiseDistributionMean(const HImage &Image, const Halcon::HTuple &FilterSize) const;
  virtual HTuple NoiseDistributionMean(const HImage &Image, Hlong FilterSize) const;
  virtual HTuple FuzzyEntropy(const HImage &Image, const Halcon::HTuple &Apar, const Halcon::HTuple &Cpar) const;
  virtual HTuple FuzzyEntropy(const HImage &Image, Hlong Apar, Hlong Cpar) const;
  virtual HTuple FuzzyPerimeter(const HImage &Image, const Halcon::HTuple &Apar, const Halcon::HTuple &Cpar) const;
  virtual HTuple FuzzyPerimeter(const HImage &Image, Hlong Apar, Hlong Cpar) const;
  virtual HImage RegionToMean(const HImage &Image) const;
  virtual void DispRegion(const Halcon::HTuple &WindowHandle) const;
  virtual void DispRegion(Hlong WindowHandle) const;
  // Interactive movement of a region with restriction of positions.
  virtual HRegionArray DragRegion3(const HRegionArray &MaskRegion, const Halcon::HTuple &WindowHandle, const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray DragRegion3(const HRegionArray &MaskRegion, Hlong WindowHandle, Hlong Row, Hlong Column) const;
  // Interactive movement of a region with fixpoint specification.
  virtual HRegionArray DragRegion2(const Halcon::HTuple &WindowHandle, const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray DragRegion2(Hlong WindowHandle, Hlong Row, Hlong Column) const;
  // Interactive moving of a region.
  virtual HRegionArray DragRegion1(const Halcon::HTuple &WindowHandle) const;
  virtual HRegionArray DragRegion1(Hlong WindowHandle) const;
  virtual HTuple FitSurfaceFirstOrder(const HImage &Image, const Halcon::HTuple &Algorithm, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, Halcon::HTuple *Beta, Halcon::HTuple *Gamma) const;
  virtual HTuple FitSurfaceFirstOrder(const HImage &Image, const char *Algorithm, Hlong Iterations, double ClippingFactor, Halcon::HTuple *Beta, Halcon::HTuple *Gamma) const;
  virtual HTuple FitSurfaceSecondOrder(const HImage &Image, const Halcon::HTuple &Algorithm, const Halcon::HTuple &Iterations, const Halcon::HTuple &ClippingFactor, Halcon::HTuple *Beta, Halcon::HTuple *Gamma, Halcon::HTuple *Delta, Halcon::HTuple *Epsilon, Halcon::HTuple *Zeta) const;
  virtual HTuple FitSurfaceSecondOrder(const HImage &Image, const char *Algorithm, Hlong Iterations, double ClippingFactor, Halcon::HTuple *Beta, Halcon::HTuple *Gamma, Halcon::HTuple *Delta, Halcon::HTuple *Epsilon, Halcon::HTuple *Zeta) const;
  // Select regions based on gray value features.
  virtual HRegionArray SelectGray(const HImage &Image, const Halcon::HTuple &Features, const Halcon::HTuple &Operation, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegionArray SelectGray(const HImage &Image, const char *Features, const char *Operation, double Min, double Max) const;
  virtual HTuple MinMaxGray(const HImage &Image, const Halcon::HTuple &Percent, Halcon::HTuple *Max, Halcon::HTuple *Range) const;
  virtual HTuple MinMaxGray(const HImage &Image, double Percent, Halcon::HTuple *Max, Halcon::HTuple *Range) const;
  virtual HTuple Intensity(const HImage &Image, Halcon::HTuple *Deviation) const;
  virtual HImage Histo2dim(const HImage &ImageCol, const HImage &ImageRow) const;
  virtual HTuple GrayHistoAbs(const HImage &Image, const Halcon::HTuple &Quantization) const;
  virtual HTuple GrayHistoAbs(const HImage &Image, double Quantization) const;
  virtual HTuple GrayHisto(const HImage &Image, Halcon::HTuple *RelativeHisto) const;
  virtual HTuple EntropyGray(const HImage &Image, Halcon::HTuple *Anisotropy) const;
  virtual HTuple CoocFeatureImage(const HImage &Image, const Halcon::HTuple &LdGray, const Halcon::HTuple &Direction, Halcon::HTuple *Correlation, Halcon::HTuple *Homogeneity, Halcon::HTuple *Contrast) const;
  virtual HTuple CoocFeatureImage(const HImage &Image, Hlong LdGray, Hlong Direction, Halcon::HTuple *Correlation, Halcon::HTuple *Homogeneity, Halcon::HTuple *Contrast) const;
  virtual HImageArray GenCoocMatrix(const HImage &Image, const Halcon::HTuple &LdGray, const Halcon::HTuple &Direction) const;
  virtual HImageArray GenCoocMatrix(const HImage &Image, Hlong LdGray, Hlong Direction) const;
  virtual HTuple MomentsGrayPlane(const HImage &Image, Halcon::HTuple *MCol, Halcon::HTuple *Alpha, Halcon::HTuple *Beta, Halcon::HTuple *Mean) const;
  virtual HTuple PlaneDeviation(const HImage &Image) const;
  virtual HTuple EllipticAxisGray(const HImage &Image, Halcon::HTuple *Rb, Halcon::HTuple *Phi) const;
  virtual HTuple AreaCenterGray(const HImage &Image, Halcon::HTuple *Row, Halcon::HTuple *Column) const;
  virtual HTuple MomentsRegionCentralInvar(Halcon::HTuple *PSI2, Halcon::HTuple *PSI3, Halcon::HTuple *PSI4) const;
  virtual HTuple MomentsRegionCentral(Halcon::HTuple *I2, Halcon::HTuple *I3, Halcon::HTuple *I4) const;
  virtual HTuple MomentsRegion3rdInvar(Halcon::HTuple *M12, Halcon::HTuple *M03, Halcon::HTuple *M30) const;
  virtual HTuple MomentsRegion3rd(Halcon::HTuple *M12, Halcon::HTuple *M03, Halcon::HTuple *M30) const;
  virtual HTuple SmallestRectangle2(Halcon::HTuple *Column, Halcon::HTuple *Phi, Halcon::HTuple *Length1, Halcon::HTuple *Length2) const;
  virtual HTuple SmallestRectangle1(Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2) const;
  virtual HTuple SmallestCircle(Halcon::HTuple *Column, Halcon::HTuple *Radius) const;
  virtual HRegionArray SelectShapeProto(const HRegionArray &Pattern, const Halcon::HTuple &Feature, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegionArray SelectShapeProto(const HRegionArray &Pattern, const char *Feature, double Min, double Max) const;
  // Choose regions with the aid of shape features.
  virtual HRegionArray SelectShape(const Halcon::HTuple &Features, const Halcon::HTuple &Operation, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegionArray SelectShape(const char *Features, const char *Operation, double Min, double Max) const;
  virtual HTuple RunlengthFeatures(Halcon::HTuple *KFactor, Halcon::HTuple *LFactor, Halcon::HTuple *MeanLength, Halcon::HTuple *Bytes) const;
  virtual HTuple FindNeighbors(const HRegionArray &Regions2, const Halcon::HTuple &MaxDistance, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple FindNeighbors(const HRegionArray &Regions2, Hlong MaxDistance, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple MomentsRegion2ndRelInvar(Halcon::HTuple *PHI2) const;
  virtual HTuple MomentsRegion2ndInvar(Halcon::HTuple *M20, Halcon::HTuple *M02) const;
  virtual HTuple MomentsRegion2nd(Halcon::HTuple *M20, Halcon::HTuple *M02, Halcon::HTuple *Ia, Halcon::HTuple *Ib) const;
  virtual HTuple DistanceRrMin(const HRegionArray &Regions2, Halcon::HTuple *Row1, Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2) const;
  virtual HTuple DistanceRrMinDil(const HRegionArray &Regions2) const;
  virtual HTuple DiameterRegion(Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2, Halcon::HTuple *Diameter) const;
  virtual Hlong TestRegionPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual Hlong TestRegionPoint(Hlong Row, Hlong Column) const;
  // Index of all regions containing a given pixel.
  virtual HTuple GetRegionIndex(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HTuple GetRegionIndex(Hlong Row, Hlong Column) const;
  // Choose all regions containing a given pixel.
  virtual HRegionArray SelectRegionPoint(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray SelectRegionPoint(Hlong Row, Hlong Column) const;
  virtual HRegionArray SelectShapeStd(const Halcon::HTuple &Shape, const Halcon::HTuple &Percent) const;
  virtual HRegionArray SelectShapeStd(const char *Shape, double Percent) const;
  virtual HTuple HammingDistanceNorm(const HRegionArray &Regions2, const Halcon::HTuple &Norm, Halcon::HTuple *Similarity) const;
  virtual HTuple HammingDistanceNorm(const HRegionArray &Regions2, const char *Norm, Halcon::HTuple *Similarity) const;
  virtual HTuple HammingDistance(const HRegionArray &Regions2, Halcon::HTuple *Similarity) const;
  virtual HTuple Eccentricity(Halcon::HTuple *Bulkiness, Halcon::HTuple *StructureFactor) const;
  virtual HTuple EulerNumber(void) const;
  virtual HTuple OrientationRegion(void) const;
  virtual HTuple EllipticAxis(Halcon::HTuple *Rb, Halcon::HTuple *Phi) const;
  virtual HTuple SelectRegionSpatial(const HRegionArray &Regions2, const Halcon::HTuple &Direction, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple SelectRegionSpatial(const HRegionArray &Regions2, const char *Direction, Halcon::HTuple *RegionIndex2) const;
  virtual HTuple SpatialRelation(const HRegionArray &Regions2, const Halcon::HTuple &Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  virtual HTuple SpatialRelation(const HRegionArray &Regions2, Hlong Percent, Halcon::HTuple *RegionIndex2, Halcon::HTuple *Relation1, Halcon::HTuple *Relation2) const;
  virtual HTuple Convexity(void) const;
  virtual HTuple Contlength(void) const;
  virtual HTuple ConnectAndHoles(Halcon::HTuple *NumHoles) const;
  virtual HTuple Rectangularity(void) const;
  virtual HTuple Compactness(void) const;
  virtual HTuple Circularity(void) const;
  virtual HTuple AreaCenter(Halcon::HTuple *Row, Halcon::HTuple *Column) const;
  virtual HTuple Roundness(Halcon::HTuple *Sigma, Halcon::HTuple *Roundness, Halcon::HTuple *Sides) const;
  virtual HTuple InnerRectangle1(Halcon::HTuple *Column1, Halcon::HTuple *Row2, Halcon::HTuple *Column2) const;
  virtual HTuple InnerCircle(Halcon::HTuple *Column, Halcon::HTuple *Radius) const;
  virtual HRegionArray Pruning(const Halcon::HTuple &Length) const;
  virtual HRegionArray Pruning(Hlong Length) const;
  virtual HRegionArray Boundary(const Halcon::HTuple &BoundaryType) const;
  virtual HRegionArray Boundary(const char *BoundaryType) const;
  virtual HRegionArray Fitting(const HRegionArray &StructElements) const;
  static HRegionArray GenStructElements(const Halcon::HTuple &Type, const Halcon::HTuple &Row, const Halcon::HTuple &Column);
  static HRegionArray GenStructElements(const char *Type, Hlong Row, Hlong Column);
  virtual HRegionArray TransposeRegion(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray TransposeRegion(Hlong Row, Hlong Column) const;
  virtual HRegionArray ThinningSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray ThinningSeq(const char *GolayElement, Hlong Iterations) const;
  virtual HRegionArray ThinningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray ThinningGolay(const char *GolayElement, Hlong Rotation) const;
  virtual HRegionArray Thinning(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Thinning(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray ThickeningSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray ThickeningSeq(const char *GolayElement, Hlong Iterations) const;
  virtual HRegionArray ThickeningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray ThickeningGolay(const char *GolayElement, Hlong Rotation) const;
  virtual HRegionArray Thickening(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Thickening(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray HitOrMissSeq(const Halcon::HTuple &GolayElement) const;
  virtual HRegionArray HitOrMissSeq(const char *GolayElement) const;
  virtual HRegionArray HitOrMissGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray HitOrMissGolay(const char *GolayElement, Hlong Rotation) const;
  virtual HRegionArray HitOrMiss(const HRegion &StructElement1, const HRegion &StructElement2, const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray HitOrMiss(const HRegion &StructElement1, const HRegion &StructElement2, Hlong Row, Hlong Column) const;
  virtual HRegionArray MorphSkiz(const Halcon::HTuple &Iterations1, const Halcon::HTuple &Iterations2) const;
  virtual HRegionArray MorphSkiz(Hlong Iterations1, Hlong Iterations2) const;
  virtual HRegionArray MorphSkeleton(void) const;
  virtual HRegionArray MorphHat(const HRegion &StructElement) const;
  virtual HRegionArray BottomHat(const HRegion &StructElement) const;
  virtual HRegionArray TopHat(const HRegion &StructElement) const;
  virtual HRegionArray MinkowskiSub2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray MinkowskiSub2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray MinkowskiSub1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray MinkowskiSub1(const HRegion &StructElement, Hlong Iterations) const;
  virtual HRegionArray MinkowskiAdd2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray MinkowskiAdd2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray MinkowskiAdd1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray MinkowskiAdd1(const HRegion &StructElement, Hlong Iterations) const;
  virtual HRegionArray ClosingRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegionArray ClosingRectangle1(Hlong Width, Hlong Height) const;
  virtual HRegionArray ClosingGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray ClosingGolay(const char *GolayElement, Hlong Rotation) const;
  virtual HRegionArray ClosingCircle(const Halcon::HTuple &Radius) const;
  virtual HRegionArray ClosingCircle(double Radius) const;
  virtual HRegionArray Closing(const HRegion &StructElement) const;
  virtual HRegionArray OpeningSeg(const HRegion &StructElement) const;
  virtual HRegionArray OpeningGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray OpeningGolay(const char *GolayElement, Hlong Rotation) const;
  virtual HRegionArray OpeningRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegionArray OpeningRectangle1(Hlong Width, Hlong Height) const;
  virtual HRegionArray OpeningCircle(const Halcon::HTuple &Radius) const;
  virtual HRegionArray OpeningCircle(double Radius) const;
  virtual HRegionArray Opening(const HRegion &StructElement) const;
  virtual HRegionArray ErosionSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray ErosionSeq(const char *GolayElement, Hlong Iterations) const;
  virtual HRegionArray ErosionGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray ErosionGolay(const char *GolayElement, Hlong Iterations, Hlong Rotation) const;
  virtual HRegionArray ErosionRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegionArray ErosionRectangle1(Hlong Width, Hlong Height) const;
  virtual HRegionArray ErosionCircle(const Halcon::HTuple &Radius) const;
  virtual HRegionArray ErosionCircle(double Radius) const;
  virtual HRegionArray Erosion2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Erosion2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray Erosion1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Erosion1(const HRegion &StructElement, Hlong Iterations) const;
  virtual HRegionArray DilationSeq(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray DilationSeq(const char *GolayElement, Hlong Iterations) const;
  virtual HRegionArray DilationGolay(const Halcon::HTuple &GolayElement, const Halcon::HTuple &Iterations, const Halcon::HTuple &Rotation) const;
  virtual HRegionArray DilationGolay(const char *GolayElement, Hlong Iterations, Hlong Rotation) const;
  virtual HRegionArray DilationRectangle1(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegionArray DilationRectangle1(Hlong Width, Hlong Height) const;
  virtual HRegionArray DilationCircle(const Halcon::HTuple &Radius) const;
  virtual HRegionArray DilationCircle(double Radius) const;
  virtual HRegionArray Dilation2(const HRegion &StructElement, const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Dilation2(const HRegion &StructElement, Hlong Row, Hlong Column, Hlong Iterations) const;
  virtual HRegionArray Dilation1(const HRegion &StructElement, const Halcon::HTuple &Iterations) const;
  virtual HRegionArray Dilation1(const HRegion &StructElement, Hlong Iterations) const;
  virtual HTuple DoOcrWordSvm(const HImage &Image, const Halcon::HTuple &OCRHandle, const Halcon::HTuple &Expression, const Halcon::HTuple &NumAlternatives, const Halcon::HTuple &NumCorrections, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrWordSvm(const HImage &Image, Hlong OCRHandle, const char *Expression, Hlong NumAlternatives, Hlong NumCorrections, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrMultiClassSvm(const HImage &Image, const Halcon::HTuple &OCRHandle) const;
  virtual HTuple DoOcrMultiClassSvm(const HImage &Image, Hlong OCRHandle) const;
  virtual HTuple DoOcrWordMlp(const HImage &Image, const Halcon::HTuple &OCRHandle, const Halcon::HTuple &Expression, const Halcon::HTuple &NumAlternatives, const Halcon::HTuple &NumCorrections, Halcon::HTuple *Confidence, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrWordMlp(const HImage &Image, Hlong OCRHandle, const char *Expression, Hlong NumAlternatives, Hlong NumCorrections, Halcon::HTuple *Confidence, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrMultiClassMlp(const HImage &Image, const Halcon::HTuple &OCRHandle, Halcon::HTuple *Confidence) const;
  virtual HTuple DoOcrMultiClassMlp(const HImage &Image, Hlong OCRHandle, Halcon::HTuple *Confidence) const;
  virtual HTuple DoOcrMulti(const HImage &Image, const Halcon::HTuple &OcrHandle, Halcon::HTuple *Confidence) const;
  virtual HTuple DoOcrMulti(const HImage &Image, Hlong OcrHandle, Halcon::HTuple *Confidence) const;
  virtual double TraindOcrClassBox(const HImage &Image, const Halcon::HTuple &OcrHandle, const Halcon::HTuple &Class) const;
  virtual double TraindOcrClassBox(const HImage &Image, Hlong OcrHandle, const char *Class) const;
  virtual void WriteOcrTrainf(const HImage &Image, const Halcon::HTuple &Class, const Halcon::HTuple &FileName) const;
  virtual void WriteOcrTrainf(const HImage &Image, const char *Class, const char *FileName) const;
  // Sorting of regions with respect to their relative position.
  virtual HRegionArray SortRegion(const Halcon::HTuple &SortMode, const Halcon::HTuple &Order, const Halcon::HTuple &RowOrCol) const;
  virtual HRegionArray SortRegion(const char *SortMode, const char *Order, const char *RowOrCol) const;
  virtual HTuple TestdOcrClassBox(const HImage &Image, const Halcon::HTuple &OcrHandle, const Halcon::HTuple &Class) const;
  virtual HTuple TestdOcrClassBox(const HImage &Image, Hlong OcrHandle, const char *Class) const;
  virtual void AppendOcrTrainf(const HImage &Image, const Halcon::HTuple &Class, const Halcon::HTuple &FileName) const;
  virtual void AppendOcrTrainf(const HImage &Image, const char *Class, const char *FileName) const;
  static HRegionArray GenRectangle2(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Length1, const Halcon::HTuple &Length2);
  static HRegionArray GenRectangle2(double Row, double Column, double Phi, double Length1, double Length2);
  static HRegionArray GenRectangle1(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2);
  static HRegionArray GenRectangle1(double Row1, double Column1, double Row2, double Column2);
  static HRegionArray GenEllipse(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Phi, const Halcon::HTuple &Radius1, const Halcon::HTuple &Radius2);
  static HRegionArray GenEllipse(double Row, double Column, double Phi, double Radius1, double Radius2);
  static HRegionArray GenCircle(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Radius);
  static HRegionArray GenCircle(double Row, double Column, double Radius);
  // Create random regions like circles, rectangles and ellipses.
  static HRegionArray GenRandomRegions(const Halcon::HTuple &Type, const Halcon::HTuple &WidthMin, const Halcon::HTuple &WidthMax, const Halcon::HTuple &HeightMin, const Halcon::HTuple &HeightMax, const Halcon::HTuple &PhiMin, const Halcon::HTuple &PhiMax, const Halcon::HTuple &NumRegions, const Halcon::HTuple &Width, const Halcon::HTuple &Height);
  static HRegionArray GenRandomRegions(const char *Type, double WidthMin, double WidthMax, double HeightMin, double HeightMax, double PhiMin, double PhiMax, Hlong NumRegions, Hlong Width, Hlong Height);
  static HRegionArray GenRegionHline(const Halcon::HTuple &Orientation, const Halcon::HTuple &Distance);
  static HRegionArray GenRegionHline(double Orientation, double Distance);
  static HRegionArray GenRegionLine(const Halcon::HTuple &BeginRow, const Halcon::HTuple &BeginCol, const Halcon::HTuple &EndRow, const Halcon::HTuple &EndCol);
  static HRegionArray GenRegionLine(Hlong BeginRow, Hlong BeginCol, Hlong EndRow, Hlong EndCol);
  virtual HTuple TestSubsetRegion(const HRegionArray &Region2) const;
  virtual Hlong TestEqualRegion(const HRegionArray &Regions2) const;
  virtual HImage PaintRegion(const HImage &Image, const Halcon::HTuple &Grayval, const Halcon::HTuple &Type) const;
  virtual HImage PaintRegion(const HImage &Image, double Grayval, const char *Type) const;
  virtual HRegionArray PolarTransRegionInv(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleEnd, const Halcon::HTuple &RadiusStart, const Halcon::HTuple &RadiusEnd, const Halcon::HTuple &WidthIn, const Halcon::HTuple &HeightIn, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Interpolation) const;
  virtual HRegionArray PolarTransRegionInv(double Row, double Column, double AngleStart, double AngleEnd, double RadiusStart, double RadiusEnd, Hlong WidthIn, Hlong HeightIn, Hlong Width, Hlong Height, const char *Interpolation) const;
  virtual HRegionArray PolarTransRegion(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleEnd, const Halcon::HTuple &RadiusStart, const Halcon::HTuple &RadiusEnd, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Interpolation) const;
  virtual HRegionArray PolarTransRegion(double Row, double Column, double AngleStart, double AngleEnd, double RadiusStart, double RadiusEnd, Hlong Width, Hlong Height, const char *Interpolation) const;
  virtual HRegionArray MergeRegionsLineScan(const HRegionArray &PrevRegions, HRegionArray *PrevMergedRegions, const Halcon::HTuple &ImageHeight, const Halcon::HTuple &MergeBorder, const Halcon::HTuple &MaxImagesRegion) const;
  virtual HRegionArray MergeRegionsLineScan(const HRegionArray &PrevRegions, HRegionArray *PrevMergedRegions, Hlong ImageHeight, const char *MergeBorder, Hlong MaxImagesRegion) const;
  virtual HRegionArray PartitionRectangle(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HRegionArray PartitionRectangle(double Width, double Height) const;
  virtual HRegionArray PartitionDynamic(const Halcon::HTuple &Distance, const Halcon::HTuple &Percent) const;
  virtual HRegionArray PartitionDynamic(double Distance, double Percent) const;
  virtual HImage RegionToLabel(const Halcon::HTuple &Type, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage RegionToLabel(const char *Type, Hlong Width, Hlong Height) const;
  virtual HImage RegionToBin(const Halcon::HTuple &ForegroundGray, const Halcon::HTuple &BackgroundGray, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage RegionToBin(Hlong ForegroundGray, Hlong BackgroundGray, Hlong Width, Hlong Height) const;
  virtual HRegionArray Union2(const HRegionArray &Region2) const;
  // Return the union of all input regions.
  virtual HRegion Union1(void) const;
  virtual HImage DistanceTransform(const Halcon::HTuple &Metric, const Halcon::HTuple &Foreground, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage DistanceTransform(const char *Metric, const char *Foreground, Hlong Width, Hlong Height) const;
  virtual HRegionArray Skeleton(void) const;
  virtual HRegionArray ProjectiveTransRegion(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation) const;
  virtual HRegionArray AffineTransRegion(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolate) const;
  virtual HRegionArray MirrorRegion(const Halcon::HTuple &RowColumn, const Halcon::HTuple &WidthHeight) const;
  virtual HRegionArray MirrorRegion(const char *RowColumn, Hlong WidthHeight) const;
  virtual HRegionArray ZoomRegion(const Halcon::HTuple &ScaleWidth, const Halcon::HTuple &ScaleHeight) const;
  virtual HRegionArray ZoomRegion(double ScaleWidth, double ScaleHeight) const;
  virtual HRegionArray MoveRegion(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual HRegionArray MoveRegion(Hlong Row, Hlong Column) const;
  virtual HRegionArray JunctionsSkeleton(HRegionArray *JuncPoints) const;
  virtual HRegionArray Intersection(const HRegionArray &Region2) const;
  virtual HRegion Interjacent(const Halcon::HTuple &Mode) const;
  virtual HRegion Interjacent(const char *Mode) const;
  virtual HRegionArray FillUp(void) const;
  virtual HRegionArray FillUpShape(const Halcon::HTuple &Feature, const Halcon::HTuple &Min, const Halcon::HTuple &Max) const;
  virtual HRegionArray FillUpShape(const char *Feature, double Min, double Max) const;
  virtual HRegionArray ExpandRegion(const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode) const;
  virtual HRegionArray ExpandRegion(const HRegion &ForbiddenArea, Hlong Iterations, const char *Mode) const;
  virtual HRegionArray ClipRegionRel(const Halcon::HTuple &Top, const Halcon::HTuple &Bottom, const Halcon::HTuple &Left, const Halcon::HTuple &Right) const;
  virtual HRegionArray ClipRegionRel(Hlong Top, Hlong Bottom, Hlong Left, Hlong Right) const;
  virtual HRegionArray ClipRegion(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2) const;
  virtual HRegionArray ClipRegion(Hlong Row1, Hlong Column1, Hlong Row2, Hlong Column2) const;
  virtual HRegionArray RankRegion(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Number) const;
  virtual HRegionArray RankRegion(Hlong Width, Hlong Height, Hlong Number) const;
  virtual HRegionArray Connection(void) const;
  virtual HRegionArray SymmDifference(const HRegionArray &Region2) const;
  virtual HRegionArray Difference(const HRegionArray &Sub) const;
  virtual HRegionArray Complement(void) const;
  virtual HRegionArray BackgroundSeg(void) const;
  virtual HRegionArray HammingChangeRegion(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Distance) const;
  virtual HRegionArray HammingChangeRegion(Hlong Width, Hlong Height, Hlong Distance) const;
  virtual HRegionArray RemoveNoiseRegion(const Halcon::HTuple &Type) const;
  virtual HRegionArray RemoveNoiseRegion(const char *Type) const;
  virtual HRegionArray ShapeTrans(const Halcon::HTuple &Type) const;
  virtual HRegionArray ShapeTrans(const char *Type) const;
  virtual HRegionArray ExpandGray(const HImage &Image, const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode, const Halcon::HTuple &Threshold) const;
  virtual HRegionArray ExpandGrayRef(const HImage &Image, const HRegion &ForbiddenArea, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode, const Halcon::HTuple &RefGray, const Halcon::HTuple &Threshold) const;
  // Split lines represented by one pixel wide, non-branching lines.
  virtual HTuple SplitSkeletonLines(const Halcon::HTuple &MaxDistance, Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol) const;
  virtual HTuple SplitSkeletonLines(Hlong MaxDistance, Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol) const;
  virtual HRegionArray SplitSkeletonRegion(const Halcon::HTuple &MaxDistance) const;
  virtual HRegionArray SplitSkeletonRegion(Hlong MaxDistance) const;
  virtual HRegionArray EliminateRuns(const Halcon::HTuple &ElimShorter, const Halcon::HTuple &ElimLonger) const;
  virtual HRegionArray EliminateRuns(Hlong ElimShorter, Hlong ElimLonger) const;
  virtual HRegionArray SelectCharacters(const Halcon::HTuple &DotPrint, const Halcon::HTuple &StrokeWidth, const Halcon::HTuple &CharWidth, const Halcon::HTuple &CharHeight, const Halcon::HTuple &Punctuation, const Halcon::HTuple &DiacriticMarks, const Halcon::HTuple &PartitionMethod, const Halcon::HTuple &PartitionLines, const Halcon::HTuple &FragmentDistance, const Halcon::HTuple &ConnectFragments, const Halcon::HTuple &ClutterSizeMax, const Halcon::HTuple &StopAfter) const;
  virtual HTuple TextLineSlant(const HImage &Image, const Halcon::HTuple &CharHeight, const Halcon::HTuple &SlantFrom, const Halcon::HTuple &SlantTo) const;
  virtual HTuple TextLineSlant(const HImage &Image, Hlong CharHeight, double SlantFrom, double SlantTo) const;
  virtual HTuple TextLineOrientation(const HImage &Image, const Halcon::HTuple &CharHeight, const Halcon::HTuple &OrientationFrom, const Halcon::HTuple &OrientationTo) const;
  virtual HTuple TextLineOrientation(const HImage &Image, Hlong CharHeight, double OrientationFrom, double OrientationTo) const;
  virtual HTuple LearnNdimNorm(const HRegionArray &Background, const HImageArray &Image, const Halcon::HTuple &Metric, const Halcon::HTuple &Distance, const Halcon::HTuple &MinNumberPercent, Halcon::HTuple *Center, Halcon::HTuple *Quality) const;
  virtual HTuple LearnNdimNorm(const HRegionArray &Background, const HImageArray &Image, const char *Metric, double Distance, double MinNumberPercent, Halcon::HTuple *Center, Halcon::HTuple *Quality) const;
  virtual void LearnNdimBox(const HRegionArray &Background, const HImageArray &MultiChannelImage, const Halcon::HTuple &ClassifHandle) const;
  virtual void LearnNdimBox(const HRegionArray &Background, const HImageArray &MultiChannelImage, Hlong ClassifHandle) const;
  static HRegionArray ReceiveRegion(const Halcon::HTuple &Socket);
  static HRegionArray ReceiveRegion(Hlong Socket);
  virtual void SendRegion(const Halcon::HTuple &Socket) const;
  virtual void SendRegion(Hlong Socket) const;
  virtual HXLDContArray GenContourRegionXld(const Halcon::HTuple &Mode) const;
  virtual HXLDContArray GenContourRegionXld(const char *Mode) const;
};

}

#endif
