/*****************************************************************************
 * HImageArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Types for Halcon-images arrays
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

#ifndef H_IMAGE_ARRAY_H
#define H_IMAGE_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                             HImageArray                                  */
/****************************************************************************/
class LIntExport HImageArray: public HObjectArray {
public:
  HImageArray(void) : array(NULL) {}
  HImageArray(Hkey *key, Hlong num);
  HImageArray(const Hobject &obj);
  HImageArray(const HImage &image);
  HImageArray(const HImageArray &arr);
  ~HImageArray(void);
  HImageArray &operator = (const HImageArray &arr);
  
  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual       INT4  ClassDBID(void) const {return IMAGE_ID;}
  virtual       Hkey  Key(Hlong i) const {return array[i].Key();}
  virtual    Hobject  ElemId(Hlong i) const {return array[i].Id();}
  virtual       void  CopyHImageArray(const HImageArray &in);
  virtual       void  Display(const HWindow &w) const;

  // Access und Manipulation
  HImage       &operator [] (Hlong index);
  HImage const &operator [] (Hlong index) const;
  HImageArray  operator () (Hlong min, Hlong max);
  HImageArray  &Append(const HImage &image);
  HImageArray  &Append(const HImageArray &images);
  virtual void SetKeys(Hkey *key, Hlong num);
  virtual void SetKeys(Hkey *key, Hlong num, Herror *err);
  virtual void DeleteArray(void);

private:
  HImage  *array;
  void    NewLength(Hlong new_num, Hlong old_num);
public:
  static HImageArray GrabDataAsync(HRegionArray *Region, HXLDContArray *Contours, const Halcon::HTuple &AcqHandle, const Halcon::HTuple &MaxDelay, Halcon::HTuple *Data);
  static HImageArray GrabDataAsync(HRegionArray *Region, HXLDContArray *Contours, Hlong AcqHandle, double MaxDelay, Halcon::HTuple *Data);
  static HImageArray GrabData(HRegionArray *Region, HXLDContArray *Contours, const Halcon::HTuple &AcqHandle, Halcon::HTuple *Data);
  static HImageArray GrabData(HRegionArray *Region, HXLDContArray *Contours, Hlong AcqHandle, Halcon::HTuple *Data);
  // Convert one-channel images into a multichannel image
  virtual HImage ChannelsToImage(void) const;
  virtual HImageArray Compose7(const HImageArray &Image2, const HImageArray &Image3, const HImageArray &Image4, const HImageArray &Image5, const HImageArray &Image6, const HImageArray &Image7) const;
  virtual HImageArray Compose6(const HImageArray &Image2, const HImageArray &Image3, const HImageArray &Image4, const HImageArray &Image5, const HImageArray &Image6) const;
  virtual HImageArray Compose5(const HImageArray &Image2, const HImageArray &Image3, const HImageArray &Image4, const HImageArray &Image5) const;
  virtual HImageArray Compose4(const HImageArray &Image2, const HImageArray &Image3, const HImageArray &Image4) const;
  virtual HImageArray Compose3(const HImageArray &Image2, const HImageArray &Image3) const;
  virtual HImageArray Compose2(const HImageArray &Image2) const;
  virtual HImageArray Decompose7(HImageArray *Image2, HImageArray *Image3, HImageArray *Image4, HImageArray *Image5, HImageArray *Image6, HImageArray *Image7) const;
  virtual HImageArray Decompose6(HImageArray *Image2, HImageArray *Image3, HImageArray *Image4, HImageArray *Image5, HImageArray *Image6) const;
  virtual HImageArray Decompose5(HImageArray *Image2, HImageArray *Image3, HImageArray *Image4, HImageArray *Image5) const;
  virtual HImageArray Decompose4(HImageArray *Image2, HImageArray *Image3, HImageArray *Image4) const;
  virtual HImageArray Decompose3(HImageArray *Image2, HImageArray *Image3) const;
  virtual HImageArray Decompose2(HImageArray *Image2) const;
  virtual HTuple CountChannels(void) const;
  virtual HImage TileImagesOffset(const Halcon::HTuple &OffsetRow, const Halcon::HTuple &OffsetCol, const Halcon::HTuple &Row1, const Halcon::HTuple &Col1, const Halcon::HTuple &Row2, const Halcon::HTuple &Col2, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImage TileImagesOffset(Hlong OffsetRow, Hlong OffsetCol, Hlong Row1, Hlong Col1, Hlong Row2, Hlong Col2, Hlong Width, Hlong Height) const;
  // Tile multiple image objects into a large image.
  virtual HImage TileImages(const Halcon::HTuple &NumColumns, const Halcon::HTuple &TileOrder) const;
  virtual HImage TileImages(Hlong NumColumns, const char *TileOrder) const;
  virtual HImageArray TileChannels(const Halcon::HTuple &NumColumns, const Halcon::HTuple &TileOrder) const;
  virtual HImageArray TileChannels(Hlong NumColumns, const char *TileOrder) const;
  virtual HImageArray CropDomain(void) const;
  virtual HImageArray CropRectangle1(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2) const;
  virtual HImageArray CropRectangle1(Hlong Row1, Hlong Column1, Hlong Row2, Hlong Column2) const;
  virtual HImageArray CropPart(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray CropPart(Hlong Row, Hlong Column, Hlong Width, Hlong Height) const;
  virtual HImageArray ChangeFormat(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray ChangeFormat(Hlong Width, Hlong Height) const;
  virtual HImageArray ChangeDomain(const HRegion &NewDomain) const;
  virtual HImageArray Rectangle1Domain(const Halcon::HTuple &Row1, const Halcon::HTuple &Column1, const Halcon::HTuple &Row2, const Halcon::HTuple &Column2) const;
  virtual HImageArray Rectangle1Domain(Hlong Row1, Hlong Column1, Hlong Row2, Hlong Column2) const;
  virtual HImageArray ReduceDomain(const HRegion &Region) const;
  virtual HImageArray FullDomain(void) const;
  virtual HRegionArray GetDomain(void) const;
  virtual void WriteImage(const Halcon::HTuple &Format, const Halcon::HTuple &FillColor, const Halcon::HTuple &FileName) const;
  virtual void WriteImage(const char *Format, Hlong FillColor, const char *FileName) const;
  static HImageArray ReadImage(const Halcon::HTuple &FileName);
  static HImageArray ReadImage(const char *FileName);
  // Automatic color correction of panorama images.
  virtual HImageArray AdjustMosaicImages(const Halcon::HTuple &From, const Halcon::HTuple &To, const Halcon::HTuple &ReferenceImage, const Halcon::HTuple &HomMatrices2D, const Halcon::HTuple &EstimationMethod, const Halcon::HTuple &EstimateParameters, const Halcon::HTuple &OECFModel) const;
  // Create 6 cube map images of a spherical mosaic.
  virtual HImage GenCubeMapMosaic(HImage *Rear, HImage *Left, HImage *Right, HImage *Top, HImage *Bottom, const Halcon::HTuple &CameraMatrices, const Halcon::HTuple &RotationMatrices, const Halcon::HTuple &CubeMapDimension, const Halcon::HTuple &StackingOrder, const Halcon::HTuple &Interpolation) const;
  // Create a spherical mosaic image.
  virtual HImage GenSphericalMosaic(const Halcon::HTuple &CameraMatrices, const Halcon::HTuple &RotationMatrices, const Halcon::HTuple &LatMin, const Halcon::HTuple &LatMax, const Halcon::HTuple &LongMin, const Halcon::HTuple &LongMax, const Halcon::HTuple &LatLongStep, const Halcon::HTuple &StackingOrder, const Halcon::HTuple &Interpolation) const;
  // Combine multiple images into a mosaic image.
  virtual HImage GenBundleAdjustedMosaic(const Halcon::HTuple &HomMatrices2D, const Halcon::HTuple &StackingOrder, const Halcon::HTuple &TransformRegion, Halcon::HTuple *TransMat2D) const;
  // Combine multiple images into a mosaic image.
  virtual HImage GenProjectiveMosaic(const Halcon::HTuple &StartImage, const Halcon::HTuple &MappingSource, const Halcon::HTuple &MappingDest, const Halcon::HTuple &HomMatrices2D, const Halcon::HTuple &StackingOrder, const Halcon::HTuple &TransformRegion, Halcon::HTuple *MosaicMatrices2D) const;
  virtual HImageArray ProjectiveTransImageSize(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &TransformRegion) const;
  virtual HImageArray ProjectiveTransImage(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation, const Halcon::HTuple &AdaptImageSize, const Halcon::HTuple &TransformRegion) const;
  virtual HImageArray AffineTransImageSize(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray AffineTransImage(const Halcon::HTuple &HomMat2D, const Halcon::HTuple &Interpolation, const Halcon::HTuple &AdaptImageSize) const;
  virtual HImageArray ZoomImageFactor(const Halcon::HTuple &ScaleWidth, const Halcon::HTuple &ScaleHeight, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray ZoomImageFactor(double ScaleWidth, double ScaleHeight, const char *Interpolation) const;
  virtual HImageArray ZoomImageSize(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray ZoomImageSize(Hlong Width, Hlong Height, const char *Interpolation) const;
  virtual HImageArray MirrorImage(const Halcon::HTuple &Mode) const;
  virtual HImageArray MirrorImage(const char *Mode) const;
  virtual HImageArray RotateImage(const Halcon::HTuple &Phi, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray RotateImage(double Phi, const char *Interpolation) const;
  virtual HImageArray PolarTransImageInv(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleEnd, const Halcon::HTuple &RadiusStart, const Halcon::HTuple &RadiusEnd, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray PolarTransImageInv(double Row, double Column, double AngleStart, double AngleEnd, double RadiusStart, double RadiusEnd, Hlong Width, Hlong Height, const char *Interpolation) const;
  virtual HImageArray PolarTransImageExt(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleEnd, const Halcon::HTuple &RadiusStart, const Halcon::HTuple &RadiusEnd, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray PolarTransImageExt(double Row, double Column, double AngleStart, double AngleEnd, double RadiusStart, double RadiusEnd, Hlong Width, Hlong Height, const char *Interpolation) const;
  virtual HImageArray PolarTransImage(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray PolarTransImage(Hlong Row, Hlong Column, Hlong Width, Hlong Height) const;
  virtual HImageArray SqrtImage(void) const;
  virtual HImageArray SubImage(const HImageArray &ImageSubtrahend, const Halcon::HTuple &Mult, const Halcon::HTuple &Add) const;
  virtual HImageArray SubImage(const HImageArray &ImageSubtrahend, double Mult, double Add) const;
  virtual HImageArray ScaleImage(const Halcon::HTuple &Mult, const Halcon::HTuple &Add) const;
  virtual HImageArray ScaleImage(double Mult, double Add) const;
  virtual HImageArray DivImage(const HImageArray &Image2, const Halcon::HTuple &Mult, const Halcon::HTuple &Add) const;
  virtual HImageArray DivImage(const HImageArray &Image2, double Mult, double Add) const;
  virtual HImageArray MultImage(const HImageArray &Image2, const Halcon::HTuple &Mult, const Halcon::HTuple &Add) const;
  virtual HImageArray MultImage(const HImageArray &Image2, double Mult, double Add) const;
  virtual HImageArray AddImage(const HImageArray &Image2, const Halcon::HTuple &Mult, const Halcon::HTuple &Add) const;
  virtual HImageArray AddImage(const HImageArray &Image2, double Mult, double Add) const;
  virtual HImageArray AbsImage(void) const;
  virtual HImageArray MinImage(const HImageArray &Image2) const;
  virtual HImageArray MaxImage(const HImageArray &Image2) const;
  virtual HImageArray InvertImage(void) const;
  virtual HImageArray BitMask(const Halcon::HTuple &BitMask) const;
  virtual HImageArray BitMask(Hlong BitMask) const;
  virtual HImageArray BitSlice(const Halcon::HTuple &Bit) const;
  virtual HImageArray BitSlice(Hlong Bit) const;
  virtual HImageArray BitRshift(const Halcon::HTuple &Shift) const;
  virtual HImageArray BitRshift(Hlong Shift) const;
  virtual HImageArray BitLshift(const Halcon::HTuple &Shift) const;
  virtual HImageArray BitLshift(Hlong Shift) const;
  virtual HImageArray BitNot(void) const;
  virtual HImageArray BitXor(const HImageArray &Image2) const;
  virtual HImageArray BitOr(const HImageArray &Image2) const;
  virtual HImageArray BitAnd(const HImageArray &Image2) const;
  virtual HImageArray Rgb1ToGray(void) const;
  virtual HImageArray Rgb3ToGray(const HImageArray &ImageGreen, const HImageArray &ImageBlue) const;
  virtual HImageArray TransFromRgb(const HImageArray &ImageGreen, const HImageArray &ImageBlue, HImageArray *ImageResult2, HImageArray *ImageResult3, const Halcon::HTuple &ColorSpace) const;
  virtual HImageArray TransFromRgb(const HImageArray &ImageGreen, const HImageArray &ImageBlue, HImageArray *ImageResult2, HImageArray *ImageResult3, const char *ColorSpace) const;
  virtual HImageArray TransToRgb(const HImageArray &ImageInput2, const HImageArray &ImageInput3, HImageArray *ImageGreen, HImageArray *ImageBlue, const Halcon::HTuple &ColorSpace) const;
  virtual HImageArray TransToRgb(const HImageArray &ImageInput2, const HImageArray &ImageInput3, HImageArray *ImageGreen, HImageArray *ImageBlue, const char *ColorSpace) const;
  virtual HImageArray PowerLn(void) const;
  virtual HImageArray PowerReal(void) const;
  virtual HImageArray PowerByte(void) const;
  virtual HImageArray PhaseDeg(void) const;
  virtual HImageArray PhaseRad(void) const;
  virtual HImageArray EnergyGabor(const HImageArray &ImageHilbert) const;
  virtual HImageArray ConvolGabor(const HImage &GaborFilter, HImageArray *ImageResultHilbert) const;
  virtual HImageArray CorrelationFft(const HImageArray &ImageFFT2) const;
  virtual HImageArray ConvolFft(const HImage &ImageFilter) const;
  virtual HImageArray RftGeneric(const Halcon::HTuple &Direction, const Halcon::HTuple &Norm, const Halcon::HTuple &ResultType, const Halcon::HTuple &Width) const;
  virtual HImageArray RftGeneric(const char *Direction, const char *Norm, const char *ResultType, Hlong Width) const;
  virtual HImageArray FftImageInv(void) const;
  virtual HImageArray FftImage(void) const;
  virtual HImageArray FftGeneric(const Halcon::HTuple &Direction, const Halcon::HTuple &Exponent, const Halcon::HTuple &Norm, const Halcon::HTuple &Mode, const Halcon::HTuple &ResultType) const;
  virtual HImageArray FftGeneric(const char *Direction, Hlong Exponent, const char *Norm, const char *Mode, const char *ResultType) const;
  virtual HImageArray IsotropicDiffusion(const Halcon::HTuple &Sigma, const Halcon::HTuple &Iterations) const;
  virtual HImageArray IsotropicDiffusion(double Sigma, Hlong Iterations) const;
  virtual HImageArray AnisotropicDiffusion(const Halcon::HTuple &Mode, const Halcon::HTuple &Contrast, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations) const;
  virtual HImageArray AnisotropicDiffusion(const char *Mode, double Contrast, double Theta, Hlong Iterations) const;
  virtual HImageArray SmoothImage(const Halcon::HTuple &Filter, const Halcon::HTuple &Alpha) const;
  virtual HImageArray SmoothImage(const char *Filter, double Alpha) const;
  virtual HImageArray SigmaImage(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth, const Halcon::HTuple &Sigma) const;
  virtual HImageArray SigmaImage(Hlong MaskHeight, Hlong MaskWidth, Hlong Sigma) const;
  virtual HImageArray MidrangeImage(const HRegion &Mask, const Halcon::HTuple &Margin) const;
  virtual HImageArray TrimmedMean(const HRegion &Mask, const Halcon::HTuple &Number, const Halcon::HTuple &Margin) const;
  virtual HImageArray MedianSeparate(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &Margin) const;
  virtual HImageArray MedianImage(const Halcon::HTuple &MaskType, const Halcon::HTuple &Radius, const Halcon::HTuple &Margin) const;
  virtual HImageArray MedianWeighted(const Halcon::HTuple &MaskType, const Halcon::HTuple &MaskSize) const;
  virtual HImageArray MedianWeighted(const char *MaskType, Hlong MaskSize) const;
  virtual HImageArray RankImage(const HRegion &Mask, const Halcon::HTuple &Rank, const Halcon::HTuple &Margin) const;
  virtual HImageArray DualRank(const Halcon::HTuple &MaskType, const Halcon::HTuple &Radius, const Halcon::HTuple &ModePercent, const Halcon::HTuple &Margin) const;
  virtual HImageArray MeanImage(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight) const;
  virtual HImageArray MeanImage(Hlong MaskWidth, Hlong MaskHeight) const;
  virtual HImageArray BinomialFilter(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight) const;
  virtual HImageArray BinomialFilter(Hlong MaskWidth, Hlong MaskHeight) const;
  virtual HImageArray GaussImage(const Halcon::HTuple &Size) const;
  virtual HImageArray GaussImage(Hlong Size) const;
  virtual HImageArray AnisotropeDiff(const Halcon::HTuple &Percent, const Halcon::HTuple &Mode, const Halcon::HTuple &Iteration, const Halcon::HTuple &NeighborhoodType) const;
  virtual HImageArray AnisotropeDiff(Hlong Percent, Hlong Mode, Hlong Iteration, Hlong NeighborhoodType) const;
  virtual HImageArray FillInterlace(const Halcon::HTuple &Mode) const;
  virtual HImageArray FillInterlace(const char *Mode) const;
  virtual HImageArray MeanN(void) const;
  virtual HImageArray EliminateSp(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MinThresh, const Halcon::HTuple &MaxThresh) const;
  virtual HImageArray EliminateSp(Hlong MaskWidth, Hlong MaskHeight, Hlong MinThresh, Hlong MaxThresh) const;
  virtual HImageArray MeanSp(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MinThresh, const Halcon::HTuple &MaxThresh) const;
  virtual HImageArray MeanSp(Hlong MaskWidth, Hlong MaskHeight, Hlong MinThresh, Hlong MaxThresh) const;
  virtual HImageArray SobelAmp(const Halcon::HTuple &FilterType, const Halcon::HTuple &Size) const;
  virtual HImageArray SobelAmp(const char *FilterType, Hlong Size) const;
  virtual HImageArray SobelDir(HImageArray *EdgeDirection, const Halcon::HTuple &FilterType, const Halcon::HTuple &Size) const;
  virtual HImageArray SobelDir(HImageArray *EdgeDirection, const char *FilterType, Hlong Size) const;
  virtual HImageArray Roberts(const Halcon::HTuple &FilterType) const;
  virtual HImageArray Roberts(const char *FilterType) const;
  virtual HImageArray Laplace(const Halcon::HTuple &ResultType, const Halcon::HTuple &MaskSize, const Halcon::HTuple &FilterMask) const;
  virtual HImageArray Laplace(const char *ResultType, Hlong MaskSize, const char *FilterMask) const;
  virtual HImageArray HighpassImage(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray HighpassImage(Hlong Width, Hlong Height) const;
  virtual HImageArray EdgesColor(HImageArray *ImaDir, const Halcon::HTuple &Filter, const Halcon::HTuple &Alpha, const Halcon::HTuple &NMS, const Halcon::HTuple &Low, const Halcon::HTuple &High) const;
  virtual HImageArray EdgesColor(HImageArray *ImaDir, const char *Filter, double Alpha, const char *NMS, Hlong Low, Hlong High) const;
  virtual HImageArray EdgesImage(HImageArray *ImaDir, const Halcon::HTuple &Filter, const Halcon::HTuple &Alpha, const Halcon::HTuple &NMS, const Halcon::HTuple &Low, const Halcon::HTuple &High) const;
  virtual HImageArray EdgesImage(HImageArray *ImaDir, const char *Filter, double Alpha, const char *NMS, Hlong Low, Hlong High) const;
  virtual HImageArray DerivateGauss(const Halcon::HTuple &Sigma, const Halcon::HTuple &Component) const;
  virtual HImageArray DerivateGauss(double Sigma, const char *Component) const;
  virtual HImageArray LaplaceOfGauss(const Halcon::HTuple &Sigma) const;
  virtual HImageArray LaplaceOfGauss(double Sigma) const;
  virtual HImageArray DiffOfGauss(const Halcon::HTuple &Sigma, const Halcon::HTuple &SigFactor) const;
  virtual HImageArray DiffOfGauss(double Sigma, double SigFactor) const;
  virtual HTuple DetectEdgeSegments(const Halcon::HTuple &SobelSize, const Halcon::HTuple &MinAmplitude, const Halcon::HTuple &MaxDistance, const Halcon::HTuple &MinLength, Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol) const;
  virtual HTuple DetectEdgeSegments(Hlong SobelSize, Hlong MinAmplitude, Hlong MaxDistance, Hlong MinLength, Halcon::HTuple *BeginCol, Halcon::HTuple *EndRow, Halcon::HTuple *EndCol) const;
  virtual HImageArray RobinsonDir(HImageArray *ImageEdgeDir) const;
  virtual HImageArray RobinsonAmp(void) const;
  virtual HImageArray KirschDir(HImageArray *ImageEdgeDir) const;
  virtual HImageArray KirschAmp(void) const;
  virtual HImageArray FreiDir(HImageArray *ImageEdgeDir) const;
  virtual HImageArray FreiAmp(void) const;
  virtual HImageArray PrewittDir(HImageArray *ImageEdgeDir) const;
  virtual HImageArray PrewittAmp(void) const;
  virtual HImageArray BandpassImage(const Halcon::HTuple &FilterType) const;
  virtual HImageArray BandpassImage(const char *FilterType) const;
  virtual HImageArray UnwarpImageVectorField(const HImageArray &VectorField) const;
  virtual HImageArray VectorFieldLength(const Halcon::HTuple &Mode) const;
  virtual HImageArray VectorFieldLength(const char *Mode) const;
  virtual HImageArray OpticalFlowMg(const HImageArray &Image2, const Halcon::HTuple &Algorithm, const Halcon::HTuple &SmoothingSigma, const Halcon::HTuple &IntegrationSigma, const Halcon::HTuple &FlowSmoothness, const Halcon::HTuple &GradientConstancy, const Halcon::HTuple &MGParamName, const Halcon::HTuple &MGParamValue) const;
  virtual HImageArray ExhaustiveMatchMg(const HImage &ImageTemplate, const Halcon::HTuple &Mode, const Halcon::HTuple &Level, const Halcon::HTuple &Threshold) const;
  virtual HImageArray ExhaustiveMatchMg(const HImage &ImageTemplate, const char *Mode, Hlong Level, Hlong Threshold) const;
  virtual void AdaptTemplate(const Halcon::HTuple &TemplateID) const;
  virtual void AdaptTemplate(Hlong TemplateID) const;
  virtual HRegionArray FastMatchMg(const Halcon::HTuple &TemplateID, const Halcon::HTuple &MaxError, const Halcon::HTuple &NumLevel) const;
  virtual HRegionArray FastMatchMg(Hlong TemplateID, double MaxError, Hlong NumLevel) const;
  // Searching the best grayvalue matches in a pre generated pyramid.
  virtual double BestMatchPreMg(const Halcon::HTuple &TemplateID, const Halcon::HTuple &MaxError, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &WhichLevels, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual double BestMatchPreMg(Hlong TemplateID, double MaxError, const char *SubPixel, Hlong NumLevels, Hlong WhichLevels, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual double BestMatchMg(const Halcon::HTuple &TemplateID, const Halcon::HTuple &MaxError, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &WhichLevels, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual double BestMatchMg(Hlong TemplateID, double MaxError, const char *SubPixel, Hlong NumLevels, Hlong WhichLevels, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual HRegionArray FastMatch(const Halcon::HTuple &TemplateID, const Halcon::HTuple &MaxError) const;
  virtual HRegionArray FastMatch(Hlong TemplateID, double MaxError) const;
  virtual HTuple BestMatchRotMg(const Halcon::HTuple &TemplateID, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtend, const Halcon::HTuple &MaxError, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Error) const;
  virtual HTuple BestMatchRotMg(Hlong TemplateID, double AngleStart, double AngleExtend, double MaxError, const char *SubPixel, Hlong NumLevels, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Error) const;
  virtual HTuple BestMatchRot(const Halcon::HTuple &TemplateID, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtend, const Halcon::HTuple &MaxError, const Halcon::HTuple &SubPixel, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Error) const;
  virtual HTuple BestMatchRot(Hlong TemplateID, double AngleStart, double AngleExtend, double MaxError, const char *SubPixel, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Error) const;
  virtual HTuple BestMatch(const Halcon::HTuple &TemplateID, const Halcon::HTuple &MaxError, const Halcon::HTuple &SubPixel, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual HTuple BestMatch(Hlong TemplateID, double MaxError, const char *SubPixel, Halcon::HTuple *Column, Halcon::HTuple *Error) const;
  virtual HImageArray CornerResponse(const Halcon::HTuple &Size, const Halcon::HTuple &Weight) const;
  virtual HImageArray CornerResponse(Hlong Size, double Weight) const;
  virtual HImageArray Monotony(void) const;
  virtual HTuple EstimateNoise(const Halcon::HTuple &Method, const Halcon::HTuple &Percent) const;
  virtual HTuple EstimateNoise(const char *Method, double Percent) const;
  virtual HImageArray AddNoiseWhite(const Halcon::HTuple &Amp) const;
  virtual HImageArray AddNoiseWhite(double Amp) const;
  virtual HImageArray AddNoiseDistribution(const Halcon::HTuple &Distribution) const;
  virtual HImageArray DotsImage(const Halcon::HTuple &Diameter, const Halcon::HTuple &FilterType, const Halcon::HTuple &PixelShift) const;
  virtual HImageArray DotsImage(Hlong Diameter, const char *FilterType, Hlong PixelShift) const;
  virtual HImageArray InpaintingTexture(const HRegion &Region, const Halcon::HTuple &MaskSize, const Halcon::HTuple &SearchSize, const Halcon::HTuple &Anisotropy, const Halcon::HTuple &PostIteration, const Halcon::HTuple &Smoothness) const;
  virtual HImageArray InpaintingTexture(const HRegion &Region, Hlong MaskSize, Hlong SearchSize, double Anisotropy, const char *PostIteration, double Smoothness) const;
  virtual HImageArray InpaintingCt(const HRegion &Region, const Halcon::HTuple &Epsilon, const Halcon::HTuple &Kappa, const Halcon::HTuple &Sigma, const Halcon::HTuple &Rho, const Halcon::HTuple &ChannelCoefficients) const;
  virtual HImageArray InpaintingCt(const HRegion &Region, double Epsilon, double Kappa, double Sigma, double Rho, double ChannelCoefficients) const;
  virtual HImageArray InpaintingMcf(const HRegion &Region, const Halcon::HTuple &Sigma, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations) const;
  virtual HImageArray InpaintingMcf(const HRegion &Region, double Sigma, double Theta, Hlong Iterations) const;
  virtual HImageArray InpaintingCed(const HRegion &Region, const Halcon::HTuple &Sigma, const Halcon::HTuple &Rho, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations) const;
  virtual HImageArray InpaintingCed(const HRegion &Region, double Sigma, double Rho, double Theta, Hlong Iterations) const;
  virtual HImageArray InpaintingAniso(const HRegion &Region, const Halcon::HTuple &Mode, const Halcon::HTuple &Contrast, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations, const Halcon::HTuple &Rho) const;
  virtual HImageArray InpaintingAniso(const HRegion &Region, const char *Mode, double Contrast, double Theta, Hlong Iterations, double Rho) const;
  virtual HImageArray HarmonicInterpolation(const HRegion &Region, const Halcon::HTuple &Precision) const;
  virtual HImageArray HarmonicInterpolation(const HRegion &Region, double Precision) const;
  virtual HImageArray ExpandDomainGray(const Halcon::HTuple &ExpansionRange) const;
  virtual HImageArray ExpandDomainGray(Hlong ExpansionRange) const;
  virtual HImageArray TopographicSketch(void) const;
  virtual HImageArray LinearTransColor(const Halcon::HTuple &TransMat) const;
  virtual HTuple GenPrincipalCompTrans(Halcon::HTuple *TransInv, Halcon::HTuple *Mean, Halcon::HTuple *Cov, Halcon::HTuple *InfoPerComp) const;
  virtual HImageArray GrayClosingShape(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskShape) const;
  virtual HImageArray GrayClosingShape(double MaskHeight, double MaskWidth, const char *MaskShape) const;
  virtual HImageArray GrayOpeningShape(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskShape) const;
  virtual HImageArray GrayOpeningShape(double MaskHeight, double MaskWidth, const char *MaskShape) const;
  virtual HImageArray GrayErosionShape(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskShape) const;
  virtual HImageArray GrayErosionShape(double MaskHeight, double MaskWidth, const char *MaskShape) const;
  virtual HImageArray GrayDilationShape(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskShape) const;
  virtual HImageArray GrayDilationShape(double MaskHeight, double MaskWidth, const char *MaskShape) const;
  virtual HImageArray GrayRangeRect(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth) const;
  virtual HImageArray GrayRangeRect(Hlong MaskHeight, Hlong MaskWidth) const;
  virtual HImageArray GrayClosingRect(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth) const;
  virtual HImageArray GrayClosingRect(Hlong MaskHeight, Hlong MaskWidth) const;
  virtual HImageArray GrayOpeningRect(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth) const;
  virtual HImageArray GrayOpeningRect(Hlong MaskHeight, Hlong MaskWidth) const;
  virtual HImageArray GrayErosionRect(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth) const;
  virtual HImageArray GrayErosionRect(Hlong MaskHeight, Hlong MaskWidth) const;
  virtual HImageArray GrayDilationRect(const Halcon::HTuple &MaskHeight, const Halcon::HTuple &MaskWidth) const;
  virtual HImageArray GrayDilationRect(Hlong MaskHeight, Hlong MaskWidth) const;
  virtual HImageArray GraySkeleton(void) const;
  virtual HImageArray LutTrans(const Halcon::HTuple &Lut) const;
  virtual HImageArray ConvolImage(const Halcon::HTuple &FilterMask, const Halcon::HTuple &Margin) const;
  virtual HImageArray ConvertImageType(const Halcon::HTuple &NewType) const;
  virtual HImageArray ConvertImageType(const char *NewType) const;
  virtual HImageArray RealToVectorField(const HImageArray &Col) const;
  virtual HImageArray VectorFieldToReal(HImageArray *Col) const;
  virtual HImageArray RealToComplex(const HImageArray &ImageImaginary) const;
  virtual HImageArray ComplexToReal(HImageArray *ImageImaginary) const;
  virtual HImageArray GrayInside(void) const;
  virtual HImageArray Symmetry(const Halcon::HTuple &MaskSize, const Halcon::HTuple &Direction, const Halcon::HTuple &Exponent) const;
  virtual HImageArray Symmetry(Hlong MaskSize, double Direction, double Exponent) const;
  virtual HImageArray SelectGrayvaluesFromChannels(const HImageArray &IndexImage) const;
  virtual HImageArray DepthFromFocus(HImageArray *Confidence, const Halcon::HTuple &Filter, const Halcon::HTuple &Selection) const;
  virtual HImageArray DepthFromFocus(HImageArray *Confidence, const char *Filter, const char *Selection) const;
  virtual HImageArray TextureLaws(const Halcon::HTuple &FilterTypes, const Halcon::HTuple &Shift, const Halcon::HTuple &FilterSize) const;
  virtual HImageArray TextureLaws(const char *FilterTypes, Hlong Shift, Hlong FilterSize) const;
  virtual HImageArray DeviationImage(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray DeviationImage(Hlong Width, Hlong Height) const;
  virtual HImageArray EntropyImage(const Halcon::HTuple &Width, const Halcon::HTuple &Height) const;
  virtual HImageArray EntropyImage(Hlong Width, Hlong Height) const;
  virtual HImageArray ShockFilter(const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations, const Halcon::HTuple &Mode, const Halcon::HTuple &Sigma) const;
  virtual HImageArray ShockFilter(double Theta, Hlong Iterations, const char *Mode, double Sigma) const;
  virtual HImageArray MeanCurvatureFlow(const Halcon::HTuple &Sigma, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations) const;
  virtual HImageArray MeanCurvatureFlow(double Sigma, double Theta, Hlong Iterations) const;
  virtual HImageArray CoherenceEnhancingDiff(const Halcon::HTuple &Sigma, const Halcon::HTuple &Rho, const Halcon::HTuple &Theta, const Halcon::HTuple &Iterations) const;
  virtual HImageArray CoherenceEnhancingDiff(double Sigma, double Rho, double Theta, Hlong Iterations) const;
  virtual HImageArray EquHistoImage(void) const;
  virtual HImageArray Illuminate(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &Factor) const;
  virtual HImageArray Illuminate(Hlong MaskWidth, Hlong MaskHeight, double Factor) const;
  virtual HImageArray Emphasize(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &Factor) const;
  virtual HImageArray Emphasize(Hlong MaskWidth, Hlong MaskHeight, double Factor) const;
  virtual HImageArray ScaleImageMax(void) const;
  virtual void DispChannel(const Halcon::HTuple &WindowHandle, const Halcon::HTuple &Channel) const;
  virtual void DispChannel(Hlong WindowHandle, Hlong Channel) const;
  // Perform a radiometric self-calibration of a camera.
  virtual HTuple RadiometricSelfCalibration(const Halcon::HTuple &ExposureRatios, const Halcon::HTuple &Features, const Halcon::HTuple &FunctionType, const Halcon::HTuple &Smoothness, const Halcon::HTuple &PolynomialDegree) const;
  virtual HTuple RadiometricSelfCalibration(double ExposureRatios, const char *Features, const char *FunctionType, double Smoothness, Hlong PolynomialDegree) const;
  virtual HImageArray MapImage(const HImage &Map) const;
  virtual HImageArray ImageToWorldPlane(const Halcon::HTuple &CamParam, const Halcon::HTuple &WorldPose, const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Scale, const Halcon::HTuple &Interpolation) const;
  virtual HImageArray ChangeRadialDistortionImage(const HRegion &Region, const Halcon::HTuple &CamParIn, const Halcon::HTuple &CamParOut) const;
  virtual HRegionArray ClusterModelComponents(const Halcon::HTuple &ComponentTrainingID, const Halcon::HTuple &AmbiguityCriterion, const Halcon::HTuple &MaxContourOverlap, const Halcon::HTuple &ClusterThreshold) const;
  virtual HRegionArray ClusterModelComponents(Hlong ComponentTrainingID, const char *AmbiguityCriterion, double MaxContourOverlap, double ClusterThreshold) const;
  virtual HRegionArray GenInitialComponents(const Halcon::HTuple &ContrastLow, const Halcon::HTuple &ContrastHigh, const Halcon::HTuple &MinSize, const Halcon::HTuple &Mode, const Halcon::HTuple &GenericName, const Halcon::HTuple &GenericValue) const;
  virtual HRegionArray GenInitialComponents(Hlong ContrastLow, Hlong ContrastHigh, Hlong MinSize, const char *Mode, const char *GenericName, double GenericValue) const;
  virtual HImageArray GrayBothat(const HImage &SE) const;
  virtual HImageArray GrayTophat(const HImage &SE) const;
  virtual HImageArray GrayClosing(const HImage &SE) const;
  virtual HImageArray GrayOpening(const HImage &SE) const;
  virtual HImageArray GrayDilation(const HImage &SE) const;
  virtual HImageArray GrayErosion(const HImage &SE) const;
  virtual HImageArray CropDomainRel(const Halcon::HTuple &Top, const Halcon::HTuple &Left, const Halcon::HTuple &Bottom, const Halcon::HTuple &Right) const;
  virtual HImageArray CropDomainRel(Hlong Top, Hlong Left, Hlong Bottom, Hlong Right) const;
  virtual void WriteOcrTrainfImage(const Halcon::HTuple &Class, const Halcon::HTuple &FileName) const;
  virtual void WriteOcrTrainfImage(const char *Class, const char *FileName) const;
  // Read training specific characters from files and convert to images.
  static HImageArray ReadOcrTrainfSelect(const Halcon::HTuple &TrainFileNames, const Halcon::HTuple &SearchNames, Halcon::HTuple *FoundNames);
  static HImageArray ReadOcrTrainfSelect(const char *TrainFileNames, const char *SearchNames, Halcon::HTuple *FoundNames);
  // Read training characters from files and convert to images.
  static HImageArray ReadOcrTrainf(const Halcon::HTuple &TrainFileNames, Halcon::HTuple *CharacterNames);
  static HImageArray ReadOcrTrainf(const char *TrainFileNames, Halcon::HTuple *CharacterNames);
  virtual HTuple DoOcvSimple(const Halcon::HTuple &OCVHandle, const Halcon::HTuple &PatternName, const Halcon::HTuple &AdaptPos, const Halcon::HTuple &AdaptSize, const Halcon::HTuple &AdaptAngle, const Halcon::HTuple &AdaptGray, const Halcon::HTuple &Threshold) const;
  virtual HTuple DoOcvSimple(Hlong OCVHandle, const char *PatternName, const char *AdaptPos, const char *AdaptSize, const char *AdaptAngle, const char *AdaptGray, double Threshold) const;
  virtual void TraindOcvProj(const Halcon::HTuple &OCVHandle, const Halcon::HTuple &Name, const Halcon::HTuple &Mode) const;
  virtual void TraindOcvProj(Hlong OCVHandle, const char *Name, const char *Mode) const;
  virtual HRegionArray ClassNdimBox(const Halcon::HTuple &ClassifHandle) const;
  virtual HRegionArray ClassNdimBox(Hlong ClassifHandle) const;
  virtual HRegionArray ClassNdimNorm(const Halcon::HTuple &Metric, const Halcon::HTuple &SingleMultiple, const Halcon::HTuple &Radius, const Halcon::HTuple &Center) const;
  virtual HRegionArray ClassNdimNorm(const char *Metric, const char *SingleMultiple, double Radius, double Center) const;
  virtual HRegionArray Class2dimSup(const HImageArray &ImageRow, const HRegionArray &FeatureSpace) const;
  virtual HRegionArray CheckDifference(const HImageArray &Pattern, const Halcon::HTuple &Mode, const Halcon::HTuple &DiffLowerBound, const Halcon::HTuple &DiffUpperBound, const Halcon::HTuple &GrayOffset, const Halcon::HTuple &AddRow, const Halcon::HTuple &AddCol) const;
  virtual HRegionArray CheckDifference(const HImageArray &Pattern, const char *Mode, Hlong DiffLowerBound, Hlong DiffUpperBound, Hlong GrayOffset, Hlong AddRow, Hlong AddCol) const;
  virtual HRegionArray CharThreshold(const HRegion &HistoRegion, const Halcon::HTuple &Sigma, const Halcon::HTuple &Percent, Halcon::HTuple *Threshold) const;
  virtual HRegionArray CharThreshold(const HRegion &HistoRegion, double Sigma, double Percent, Halcon::HTuple *Threshold) const;
  virtual HRegionArray LabelToRegion(void) const;
  virtual HImageArray NonmaxSuppressionAmp(const Halcon::HTuple &Mode) const;
  virtual HImageArray NonmaxSuppressionAmp(const char *Mode) const;
  virtual HImageArray NonmaxSuppressionDir(const HImageArray &ImgDir, const Halcon::HTuple &Mode) const;
  virtual HImageArray NonmaxSuppressionDir(const HImageArray &ImgDir, const char *Mode) const;
  virtual HRegionArray HysteresisThreshold(const Halcon::HTuple &Low, const Halcon::HTuple &High, const Halcon::HTuple &MaxLength) const;
  virtual HRegionArray HysteresisThreshold(Hlong Low, Hlong High, Hlong MaxLength) const;
  virtual HRegionArray VarThreshold(const Halcon::HTuple &MaskWidth, const Halcon::HTuple &MaskHeight, const Halcon::HTuple &StdDevScale, const Halcon::HTuple &AbsThreshold, const Halcon::HTuple &LightDark) const;
  virtual HRegionArray VarThreshold(Hlong MaskWidth, Hlong MaskHeight, double StdDevScale, double AbsThreshold, const char *LightDark) const;
  virtual HRegionArray DynThreshold(const HImageArray &ThresholdImage, const Halcon::HTuple &Offset, const Halcon::HTuple &LightDark) const;
  virtual HRegionArray DynThreshold(const HImageArray &ThresholdImage, double Offset, const char *LightDark) const;
  virtual HRegionArray Threshold(const Halcon::HTuple &MinGray, const Halcon::HTuple &MaxGray) const;
  virtual HRegionArray Threshold(double MinGray, double MaxGray) const;
  virtual HRegionArray RegiongrowingN(const Halcon::HTuple &Metric, const Halcon::HTuple &MinTolerance, const Halcon::HTuple &MaxTolerance, const Halcon::HTuple &MinSize) const;
  virtual HRegionArray RegiongrowingN(const char *Metric, double MinTolerance, double MaxTolerance, Hlong MinSize) const;
  virtual HRegionArray Regiongrowing(const Halcon::HTuple &Row, const Halcon::HTuple &Column, const Halcon::HTuple &Tolerance, const Halcon::HTuple &MinSize) const;
  virtual HRegionArray Regiongrowing(Hlong Row, Hlong Column, double Tolerance, Hlong MinSize) const;
  virtual HRegionArray RegiongrowingMean(const Halcon::HTuple &StartRows, const Halcon::HTuple &StartColumns, const Halcon::HTuple &Tolerance, const Halcon::HTuple &MinSize) const;
  virtual HRegionArray RegiongrowingMean(Hlong StartRows, Hlong StartColumns, double Tolerance, Hlong MinSize) const;
  virtual HRegionArray Watersheds(HRegionArray *Watersheds) const;
  virtual HRegionArray ZeroCrossing(void) const;
  virtual HRegionArray DualThreshold(const Halcon::HTuple &MinSize, const Halcon::HTuple &MinGray, const Halcon::HTuple &Threshold) const;
  virtual HRegionArray DualThreshold(Hlong MinSize, double MinGray, double Threshold) const;
  virtual HRegionArray ExpandLine(const Halcon::HTuple &Coordinate, const Halcon::HTuple &ExpandType, const Halcon::HTuple &RowColumn, const Halcon::HTuple &Threshold) const;
  virtual HRegionArray ExpandLine(Hlong Coordinate, const char *ExpandType, const char *RowColumn, double Threshold) const;
  virtual HRegionArray LocalMin(void) const;
  virtual HRegionArray Lowlands(void) const;
  virtual HRegionArray LowlandsCenter(void) const;
  virtual HRegionArray LocalMax(void) const;
  virtual HRegionArray Plateaus(void) const;
  virtual HRegionArray PlateausCenter(void) const;
  virtual HRegionArray AutoThreshold(const Halcon::HTuple &Sigma) const;
  virtual HRegionArray AutoThreshold(double Sigma) const;
  virtual HRegionArray BinThreshold(void) const;
  virtual HRegionArray FastThreshold(const Halcon::HTuple &MinGray, const Halcon::HTuple &MaxGray, const Halcon::HTuple &MinSize) const;
  virtual HRegionArray FastThreshold(double MinGray, double MaxGray, Hlong MinSize) const;
  virtual HImageArray ShadeHeightField(const Halcon::HTuple &Slant, const Halcon::HTuple &Tilt, const Halcon::HTuple &Albedo, const Halcon::HTuple &Ambient, const Halcon::HTuple &Shadows) const;
  virtual HImageArray ShadeHeightField(double Slant, double Tilt, double Albedo, double Ambient, const char *Shadows) const;
  virtual HTuple EstimateAlAm(Halcon::HTuple *Ambient) const;
  virtual HTuple EstimateSlAlZc(Halcon::HTuple *Albedo) const;
  virtual HTuple EstimateSlAlLr(Halcon::HTuple *Albedo) const;
  virtual HTuple EstimateTiltZc(void) const;
  virtual HTuple EstimateTiltLr(void) const;
  virtual HImageArray SfsPentland(const Halcon::HTuple &Slant, const Halcon::HTuple &Tilt, const Halcon::HTuple &Albedo, const Halcon::HTuple &Ambient) const;
  virtual HImageArray SfsPentland(double Slant, double Tilt, double Albedo, double Ambient) const;
  virtual HImageArray SfsOrigLr(const Halcon::HTuple &Slant, const Halcon::HTuple &Tilt, const Halcon::HTuple &Albedo, const Halcon::HTuple &Ambient) const;
  virtual HImageArray SfsOrigLr(double Slant, double Tilt, double Albedo, double Ambient) const;
  virtual HImageArray SfsModLr(const Halcon::HTuple &Slant, const Halcon::HTuple &Tilt, const Halcon::HTuple &Albedo, const Halcon::HTuple &Ambient) const;
  virtual HImageArray SfsModLr(double Slant, double Tilt, double Albedo, double Ambient) const;
  static HImageArray GenBinocularProjRectification(HImageArray *Map2, const Halcon::HTuple &FMatrix, const Halcon::HTuple &CovFMat, const Halcon::HTuple &Width1, const Halcon::HTuple &Height1, const Halcon::HTuple &Width2, const Halcon::HTuple &Height2, const Halcon::HTuple &SubSampling, const Halcon::HTuple &Mapping, Halcon::HTuple *CovFMatRect, Halcon::HTuple *H1, Halcon::HTuple *H2);
  static HImageArray ReceiveImage(const Halcon::HTuple &Socket);
  static HImageArray ReceiveImage(Hlong Socket);
  virtual void SendImage(const Halcon::HTuple &Socket) const;
  virtual void SendImage(Hlong Socket) const;
  virtual HTuple FindAnisoShapeModels(const Halcon::HTuple &ModelIDs, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleRMin, const Halcon::HTuple &ScaleRMax, const Halcon::HTuple &ScaleCMin, const Halcon::HTuple &ScaleCMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindAnisoShapeModels(Hlong ModelIDs, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindScaledShapeModels(const Halcon::HTuple &ModelIDs, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleMin, const Halcon::HTuple &ScaleMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindScaledShapeModels(Hlong ModelIDs, double AngleStart, double AngleExtent, double ScaleMin, double ScaleMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindShapeModels(const Halcon::HTuple &ModelIDs, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindShapeModels(Hlong ModelIDs, double AngleStart, double AngleExtent, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HRegionArray CompareExtVariationModel(const Halcon::HTuple &ModelID, const Halcon::HTuple &Mode) const;
  virtual HRegionArray CompareExtVariationModel(Hlong ModelID, const char *Mode) const;
  virtual HRegionArray CompareVariationModel(const Halcon::HTuple &ModelID) const;
  virtual HRegionArray CompareVariationModel(Hlong ModelID) const;
  virtual void TrainVariationModel(const Halcon::HTuple &ModelID) const;
  virtual void TrainVariationModel(Hlong ModelID) const;
};

}

#endif
