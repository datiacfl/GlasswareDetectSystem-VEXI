/*****************************************************************************
 * HClassBox.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HClassBox
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.6 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */

#ifndef H_CLASS_BOX_H
#define H_CLASS_BOX_H


namespace Halcon {


class LIntExport HClassBox: public HRootObject {
public:
  HClassBox(void);

  ~HClassBox(void);
private:
  // Copying and Assignment not allowed
  HClassBox(const HClassBox &inst);
  HClassBox &operator= (const HClassBox &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HClassBox";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Save the classificator in a file.
  virtual void WriteClassBox(const Halcon::HTuple &FileName) const;
  virtual void WriteClassBox(const char *FileName) const;
  // Set system parameters for classification.
  virtual void SetClassBoxParam(const Halcon::HTuple &Flag, const Halcon::HTuple &Value) const;
  virtual void SetClassBoxParam(const char *Flag, double Value) const;
  // Read the classificator from a file.
  virtual void ReadClassBox(const Halcon::HTuple &FileName) const;
  virtual void ReadClassBox(const char *FileName) const;
  // Train the classificator with one data set.
  virtual void LearnSampsetBox(const Halcon::HTuple &SampKey, const Halcon::HTuple &Outfile, const Halcon::HTuple &NSamples, const Halcon::HTuple &StopError, const Halcon::HTuple &ErrorN) const;
  virtual void LearnSampsetBox(Hlong SampKey, const char *Outfile, Hlong NSamples, double StopError, Hlong ErrorN) const;
  // Train the classificator.
  virtual void LearnClassBox(const Halcon::HTuple &Features, const Halcon::HTuple &Class) const;
  // Get information about the current parameter.
  virtual double GetClassBoxParam(const Halcon::HTuple &Flag) const;
  virtual double GetClassBoxParam(const char *Flag) const;
  // Create a new classificator.
  virtual void CreateClassBox(void);
  // Description of the classificator.
  virtual void DescriptClassBox(const Halcon::HTuple &Dimensions) const;
  virtual void DescriptClassBox(Hlong Dimensions) const;
  // Classify a set of arrays.
  virtual double TestSampsetBox(const Halcon::HTuple &SampKey) const;
  virtual double TestSampsetBox(Hlong SampKey) const;
  // Classify a tuple of attributes with rejection class.
  virtual Hlong EnquireRejectClassBox(const Halcon::HTuple &FeatureList) const;
  // Classify a tuple of attributes.
  virtual Hlong EnquireClassBox(const Halcon::HTuple &FeatureList) const;
  // Train a classificator using a multi-channel image.
  virtual void LearnNdimBox(const HRegionArray &Foreground, const HRegionArray &Background, const HImageArray &MultiChannelImage) const;
  // Classify pixels using hyper-cuboids.
  virtual HRegionArray ClassNdimBox(const HImageArray &MultiChannelImage) const;
};

}

#endif
