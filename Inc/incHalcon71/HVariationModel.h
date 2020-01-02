/*****************************************************************************
 * HVariationModel.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HVariationModel
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.6 $
 * $Date: 2005/05/06 07:36:06 $
 *
 */

#ifndef H_VARIATION_MODEL_H
#define H_VARIATION_MODEL_H


namespace Halcon {


class LIntExport HVariationModel: public HRootObject {
public:
  HVariationModel(void) {id = -1;}
  HVariationModel(const HTuple &Width, const HTuple &Height, 
                  const HTuple &Type = "byte", 
                  const HTuple &Mode = "standard");
  HVariationModel(Hlong Width, Hlong Height, 
                  const char *Type = "byte", 
                  const char *Mode = "standard");

  ~HVariationModel(void);
private:
  // Copying and Assignment not allowed
  HVariationModel(const HVariationModel &inst);
  HVariationModel &operator= (const HVariationModel &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HVariationModel";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  //Handle
  Hlong  id;
public:
  // Read a variation model from a file.
  virtual void ReadVariationModel(const Halcon::HTuple &FileName);
  virtual void ReadVariationModel(const char *FileName);
  // Write a variation model to a file.
  virtual void WriteVariationModel(const Halcon::HTuple &FileName) const;
  virtual void WriteVariationModel(const char *FileName) const;
  // Return the images used for image comparison by a variation model.
  virtual HImage GetVariationModel(HImage *VarImage) const;
  // Compare an image to a variation model.
  virtual HRegionArray CompareVariationModel(const HImageArray &Image) const;
  // Prepare a variation model for comparison with an image.
  virtual void PrepareVariationModel(const Halcon::HTuple &AbsThreshold, const Halcon::HTuple &VarThreshold) const;
  virtual void PrepareVariationModel(double AbsThreshold, double VarThreshold) const;
  // Train a variation model.
  virtual void TrainVariationModel(const HImageArray &Images) const;
  // Create a variation model for image comparison.
  virtual void CreateVariationModel(const Halcon::HTuple &Width, const Halcon::HTuple &Height, const Halcon::HTuple &Type, const Halcon::HTuple &Mode);
  virtual void CreateVariationModel(Hlong Width, Hlong Height, const char *Type, const char *Mode);
};

}

#endif
