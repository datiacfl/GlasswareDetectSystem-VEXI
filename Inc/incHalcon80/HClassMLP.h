/*****************************************************************************
 * HClassMLP.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HClassMlp
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.4 $
 * $Date: 2005/05/06 07:36:05 $
 *
 */

#ifndef H_CLASS_MLP_H
#define H_CLASS_MLP_H


namespace Halcon {


class LIntExport HClassMlp: public HRootObject {
public:
  HClassMlp(void) {id = -1;}
  HClassMlp(const HTuple &NumInput, const HTuple &NumHidden,
            const HTuple &NumOutput, const HTuple &OutputFunction,
            const HTuple &Preprocessing, const HTuple &NumComponents,
            const HTuple &RandSeed);

  ~HClassMlp(void);
private:
  // Copying and Assignment not allowed
  HClassMlp(const HClassMlp &inst);
  HClassMlp &operator= (const HClassMlp &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HClassMlp";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Read a multilayer perceptron from a file.
  virtual void ReadClassMlp(const Halcon::HTuple &FileName);
  virtual void ReadClassMlp(const char *FileName);
  // Write a multilayer perceptron to a file.
  virtual void WriteClassMlp(const Halcon::HTuple &FileName) const;
  virtual void WriteClassMlp(const char *FileName) const;
  // Read the training data of a multilayer perceptron from a file.
  virtual void ReadSamplesClassMlp(const Halcon::HTuple &FileName) const;
  virtual void ReadSamplesClassMlp(const char *FileName) const;
  // Write the training data of a multilayer perceptron to a file.
  virtual void WriteSamplesClassMlp(const Halcon::HTuple &FileName) const;
  virtual void WriteSamplesClassMlp(const char *FileName) const;
  // Calculate the class of a feature vector by a multilayer perceptron.
  virtual HTuple ClassifyClassMlp(const Halcon::HTuple &Features, const Halcon::HTuple &Num, Halcon::HTuple *Confidence) const;
  virtual Hlong ClassifyClassMlp(const Halcon::HTuple &Features, const Halcon::HTuple &Num, double *Confidence) const;
  // Calculate the evaluation of a feature vector by a multilayer
  // perceptron.
  virtual HTuple EvaluateClassMlp(const Halcon::HTuple &Features) const;
  // Train a multilayer perceptron.
  virtual double TrainClassMlp(const Halcon::HTuple &MaxIterations, const Halcon::HTuple &WeightTolerance, const Halcon::HTuple &ErrorTolerance, Halcon::HTuple *ErrorLog) const;
  virtual double TrainClassMlp(Hlong MaxIterations, double WeightTolerance, double ErrorTolerance, Halcon::HTuple *ErrorLog) const;
  // Compute the information content of the preprocessed feature vectors
  // of a multilayer perceptron.
  virtual HTuple GetPrepInfoClassMlp(const Halcon::HTuple &Preprocessing, Halcon::HTuple *CumInformationCont) const;
  virtual HTuple GetPrepInfoClassMlp(const char *Preprocessing, Halcon::HTuple *CumInformationCont) const;
  // Return the number of training samples stored in the training data of
  // a multilayer perceptron.
  virtual Hlong GetSampleNumClassMlp() const;
  // Return a training sample from the training data of a multilayer
  // perceptron.
  virtual HTuple GetSampleClassMlp(const Halcon::HTuple &IndexSample, Halcon::HTuple *Target) const;
  // Add a training sample to the training data of a multilayer
  // perceptron.
  virtual void AddSampleClassMlp(const Halcon::HTuple &Features, const Halcon::HTuple &Target) const;
  // Return the parameters of a multilayer perceptron.
  virtual Hlong GetParamsClassMlp(Halcon::HTuple *NumHidden, Halcon::HTuple *NumOutput, Halcon::HTuple *OutputFunction, Halcon::HTuple *Preprocessing, Halcon::HTuple *NumComponents) const;
  virtual Hlong GetParamsClassMlp(Hlong *NumHidden, Hlong *NumOutput, char *OutputFunction, char *Preprocessing, Hlong *NumComponents) const;
  // Create a multilayer perceptron for classification or regression.
  virtual void CreateClassMlp(const Halcon::HTuple &NumInput, const Halcon::HTuple &NumHidden, const Halcon::HTuple &NumOutput, const Halcon::HTuple &OutputFunction, const Halcon::HTuple &Preprocessing, const Halcon::HTuple &NumComponents, const Halcon::HTuple &RandSeed);
  virtual void CreateClassMlp(Hlong NumInput, Hlong NumHidden, Hlong NumOutput, const char *OutputFunction, const char *Preprocessing, Hlong NumComponents, Hlong RandSeed);
  // Classify an image with a multilayer perceptron.
  virtual HRegionArray ClassifyImageClassMlp(const HImage &Image, const Halcon::HTuple &RejectionThreshold) const;
  virtual HRegionArray ClassifyImageClassMlp(const HImage &Image, double RejectionThreshold) const;
  // Add training samples from an image to the training data of a
  // multilayer perceptron.
  virtual void AddSamplesImageClassMlp(const HImage &Image, const HRegionArray &ClassRegions) const;
};

}

#endif
