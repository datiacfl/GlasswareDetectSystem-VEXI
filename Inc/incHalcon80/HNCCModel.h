/*****************************************************************************
 * HNCCModel.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HNCCModel
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.1 $
 * $Date: 2007/01/02 11:09:36 $
 *
 */

#ifndef H_NCC_MODEL_H
#define H_NCC_MODEL_H


namespace Halcon {


class LIntExport HNCCModel: public HRootObject {
public:
  HNCCModel(void) {id = -1;}
  HNCCModel(
          const HImage &Template, 
          const HTuple &NumLevels, 
          const HTuple &AngleStart, 
          const HTuple &AngleExtent, 
          const HTuple &AngleStep, 
          const HTuple &Metric);
  HNCCModel(
          const HImage &Template, 
          Hlong         NumLevels, 
          double        AngleStart, 
          double        AngleExtent, 
          double        AngleStep, 
          const char   *Metric = "use_polarity");

  ~HNCCModel(void);
private:
  // Copying and Assignment not allowed
  HNCCModel(const HNCCModel &inst);
  HNCCModel &operator= (const HNCCModel &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HNCCModel";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  //Handle
  Hlong  id;
public:
  // Read an NCC model from a file.
  virtual void ReadNccModel(const Halcon::HTuple &FileName);
  virtual void ReadNccModel(const char *FileName);
  // Write an NCC model to a file.
  virtual void WriteNccModel(const Halcon::HTuple &FileName) const;
  virtual void WriteNccModel(const char *FileName) const;
  // Return the parameters of an NCC model.
  virtual Hlong GetNccModelParams(Halcon::HTuple *AngleStart, Halcon::HTuple *AngleExtent, Halcon::HTuple *AngleStep, Halcon::HTuple *Metric) const;
  virtual Hlong GetNccModelParams(double *AngleStart, double *AngleExtent, double *AngleStep, char *Metric) const;
  // Return the origin (reference point) of an NCC model.
  virtual double GetNccModelOrigin(Halcon::HTuple *Column) const;
  virtual double GetNccModelOrigin(double *Column) const;
  // Set the origin (reference point) of an NCC model.
  virtual void SetNccModelOrigin(const Halcon::HTuple &Row, const Halcon::HTuple &Column) const;
  virtual void SetNccModelOrigin(double Row, double Column) const;
  // Find the best matches of an NCC model in an image.
  virtual HTuple FindNccModel(const HImage &Image, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &MinScore, const Halcon::HTuple &NumMatches, const Halcon::HTuple &MaxOverlap, const Halcon::HTuple &SubPixel, const Halcon::HTuple &NumLevels, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score) const;
  virtual HTuple FindNccModel(const HImage &Image, double AngleStart, double AngleExtent, double MinScore, Hlong NumMatches, double MaxOverlap, const char *SubPixel, Hlong NumLevels, Halcon::HTuple *Column, Halcon::HTuple *Angle, Halcon::HTuple *Score) const;
  // Prepare an NCC model for matching.
  virtual void CreateNccModel(const HImage &Template, const Halcon::HTuple &NumLevels, const Halcon::HTuple &AngleStart, const Halcon::HTuple &AngleExtent, const Halcon::HTuple &AngleStep, const Halcon::HTuple &Metric);
  virtual void CreateNccModel(const HImage &Template, Hlong NumLevels, double AngleStart, double AngleExtent, double AngleStep, const char *Metric);
};

}

#endif
