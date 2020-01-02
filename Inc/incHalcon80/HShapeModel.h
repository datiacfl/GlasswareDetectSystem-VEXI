/*****************************************************************************
 * HShapeModel.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HShapeModel
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.7 $
 * $Date: 2007/01/02 08:48:45 $
 *
 */

#ifndef H_SHAPE_MODEL_H
#define H_SHAPE_MODEL_H


namespace Halcon {


class LIntExport HShapeModel: public HRootObject {
public:
  HShapeModel(void) {id = -1;}
  HShapeModel(
          const HImage &Template, 
          const HTuple &NumLevels, 
          const HTuple &AngleStart, 
          const HTuple &AngleExtent, 
          const HTuple &AngleStep, 
          const HTuple &Optimization, 
          const HTuple &Metric, 
          const HTuple &Contrast, 
          const HTuple &MinContrast);
  HShapeModel(
          const HImage &Template, 
          Hlong         NumLevels, 
          double        AngleStart, 
          double        AngleExtent, 
          double        AngleStep, 
          const char   *Optimization = "none", 
          const char   *Metric = "use_polarity", 
          Hlong         Contrast = 30, 
          Hlong         MinContrast = 10);
  HShapeModel(
          const HImage &Template, 
          const HTuple &NumLevels, 
          const HTuple &AngleStart, 
          const HTuple &AngleExtent, 
          const HTuple &AngleStep, 
          const HTuple &ScaleMin, 
          const HTuple &ScaleMax, 
          const HTuple &ScaleStep, 
          const HTuple &Optimization, 
          const HTuple &Metric, 
          const HTuple &Contrast, 
          const HTuple &MinContrast);
  HShapeModel(
          const HImage &Template, 
          Hlong         NumLevels, 
          double        AngleStart, 
          double        AngleExtent, 
          double        AngleStep, 
          double        ScaleMin, 
          double        ScaleMax, 
          double        ScaleStep, 
          const char   *Optimization = "none", 
          const char   *Metric = "use_polarity", 
          Hlong         Contrast = 30, 
          Hlong         MinContrast = 10);
  HShapeModel(
          const HImage &Template, 
          const HTuple &NumLevels, 
          const HTuple &AngleStart, 
          const HTuple &AngleExtent, 
          const HTuple &AngleStep, 
          const HTuple &ScaleRMin, 
          const HTuple &ScaleRMax, 
          const HTuple &ScaleRStep, 
          const HTuple &ScaleCMin, 
          const HTuple &ScaleCMax, 
          const HTuple &ScaleCStep, 
          const HTuple &Optimization, 
          const HTuple &Metric, 
          const HTuple &Contrast, 
          const HTuple &MinContrast);
  HShapeModel(
          const HImage &Template, 
          Hlong         NumLevels, 
          double        AngleStart, 
          double        AngleExtent, 
          double        AngleStep, 
          double        ScaleRMin, 
          double        ScaleRMax, 
          double        ScaleRStep, 
          double        ScaleCMin, 
          double        ScaleCMax, 
          double        ScaleCStep, 
          const char   *Optimization = "none", 
          const char   *Metric = "use_polarity", 
          Hlong         Contrast = 30, 
          Hlong         MinContrast = 10);

  ~HShapeModel(void);
private:
  // Copying and Assignment not allowed
  HShapeModel(const HShapeModel &inst);
  HShapeModel &operator= (const HShapeModel &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HShapeModel";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  //Handle
  Hlong  id;
public:
  // Read a shape model from a file.
  virtual void ReadShapeModel(const Halcon::HTuple &FileName);
  virtual void ReadShapeModel(const char *FileName);
  // Write a shape model to a file.
  virtual void WriteShapeModel(const Halcon::HTuple &FileName) const;
  virtual void WriteShapeModel(const char *FileName) const;
  // Return the contour representation of a shape model.
  virtual HXLDContArray GetShapeModelContours(const Halcon::HTuple &Level) const;
  virtual HXLDContArray GetShapeModelContours(Hlong Level) const;
  // Return the parameters of a shape model.
  virtual Hlong GetShapeModelParams(Halcon::HTuple *AngleStart, Halcon::HTuple *AngleExtent, Halcon::HTuple *AngleStep, Halcon::HTuple *ScaleMin, Halcon::HTuple *ScaleMax, Halcon::HTuple *ScaleStep, Halcon::HTuple *Metric, Halcon::HTuple *MinContrast) const;
  virtual Hlong GetShapeModelParams(double *AngleStart, double *AngleExtent, double *AngleStep, double *ScaleMin, double *ScaleMax, double *ScaleStep, char *Metric, Hlong *MinContrast) const;
  // Return the origin (reference point) of a shape model.
  virtual double GetShapeModelOrigin(Halcon::HTuple *Column) const;
  virtual double GetShapeModelOrigin(double *Column) const;
  // Set the origin (reference point) of a shape model.
  virtual void SetShapeModelOrigin(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual void SetShapeModelOrigin(double Row, double Column) const;
  // Find the best matches of multiple anisotropic scale invariant shape
  // models.
  virtual HTuple FindAnisoShapeModels(const HImageArray &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleRMin, const Halcon::HTuple &ScaleRMax, const Halcon::HTuple &ScaleCMin, const Halcon::HTuple &ScaleCMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindAnisoShapeModels(const HImageArray &Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  // Find the best matches of multiple scale invariant shape models.
  virtual HTuple FindScaledShapeModels(const HImageArray &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleMin, const Halcon::HTuple &ScaleMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindScaledShapeModels(const HImageArray &Image, double AngleStart, double AngleExtent, double ScaleMin, double ScaleMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  // Find the best matches of multiple shape models.
  virtual HTuple FindShapeModels(const HImageArray &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  virtual HTuple FindShapeModels(const HImageArray &Image, double AngleStart, double AngleExtent, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score, Halcon::HTuple *Model) const;
  // Find the best matches of an anisotropic scale invariant shape model
  // in an image.
  virtual HTuple FindAnisoShapeModel(const HImage &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleRMin, const Halcon::HTuple &ScaleRMax, const Halcon::HTuple &ScaleCMin, const Halcon::HTuple &ScaleCMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score) const;
  virtual HTuple FindAnisoShapeModel(const HImage &Image, double AngleStart, double AngleExtent, double ScaleRMin, double ScaleRMax, double ScaleCMin, double ScaleCMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *ScaleR, Halcon::HTuple *ScaleC, Halcon::HTuple *Score) const;
  // Find the best matches of a scale invariant shape model in an image.
  virtual HTuple FindScaledShapeModel(const HImage &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &ScaleMin, const Halcon::HTuple &ScaleMax, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score) const;
  virtual HTuple FindScaledShapeModel(const HImage &Image, double AngleStart, double AngleExtent, double ScaleMin, double ScaleMax, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Scale, Halcon::HTuple *Score) const;
  // Find the best matches of a shape model in an image.
  virtual HTuple FindShapeModel(const HImage &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, const Halcon::HTuple &Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score) const;
  virtual HTuple FindShapeModel(const HImage &Image, double AngleStart, double AngleExtent, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, double Greediness, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score) const;
  // Prepare a shape model for anisotropic scale invariant matching.
  virtual void CreateAnisoShapeModel(const HImage &Template, const Halcon::HTuple &NumLevels, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &AngleStep, const Halcon::HTuple &ScaleRMin, const Halcon::HTuple &ScaleRMax, const Halcon::HTuple &ScaleRStep, const Halcon::HTuple &ScaleCMin, const Halcon::HTuple &ScaleCMax, const Halcon::HTuple &ScaleCStep, const Halcon::HTuple &Optimization, const Halcon::HTuple &Metric, const Halcon::HTuple &Contrast, const Halcon::HTuple &MinContrast);
  virtual void CreateAnisoShapeModel(const HImage &Template, Hlong NumLevels, double AngleStart, double AngleExtent, double AngleStep, double ScaleRMin, double ScaleRMax, double ScaleRStep, double ScaleCMin, double ScaleCMax, double ScaleCStep, const char *Optimization, const char *Metric, Hlong Contrast, Hlong MinContrast);
  // Prepare a shape model for scale invariant matching.
  virtual void CreateScaledShapeModel(const HImage &Template, const Halcon::HTuple &NumLevels, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &AngleStep, const Halcon::HTuple &ScaleMin, const Halcon::HTuple &ScaleMax, const Halcon::HTuple &ScaleStep, const Halcon::HTuple &Optimization, const Halcon::HTuple &Metric, const Halcon::HTuple &Contrast, const Halcon::HTuple &MinContrast);
  virtual void CreateScaledShapeModel(const HImage &Template, Hlong NumLevels, double AngleStart, double AngleExtent, double AngleStep, double ScaleMin, double ScaleMax, double ScaleStep, const char *Optimization, const char *Metric, Hlong Contrast, Hlong MinContrast);
  // Prepare a shape model for matching.
  virtual void CreateShapeModel(const HImage &Template, const Halcon::HTuple &NumLevels, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &AngleStep, const Halcon::HTuple &Optimization, const Halcon::HTuple &Metric, const Halcon::HTuple &Contrast, const Halcon::HTuple &MinContrast);
  virtual void CreateShapeModel(const HImage &Template, Hlong NumLevels, double AngleStart, double AngleExtent, double AngleStep, const char *Optimization, const char *Metric, Hlong Contrast, Hlong MinContrast);
};

}

#endif
