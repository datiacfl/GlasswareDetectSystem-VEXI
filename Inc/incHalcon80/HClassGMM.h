/*****************************************************************************
 * HClassGMM.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HClassGmm
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.1 $
 * $Date: 2007/04/03 15:06:16 $
 *
 */

#ifndef H_CLASS_GMM_H
#define H_CLASS_GMM_H


namespace Halcon {


class LIntExport HClassGmm: public HRootObject {
public:
  HClassGmm(void) {id = -1;}
  HClassGmm(const HTuple &NumDim, const HTuple &NumClasses,
            const HTuple &NumCenters, const HTuple &CovarType,
            const HTuple &Preprocessing, const HTuple &NumComponents,
            const HTuple &RandSeed);

  ~HClassGmm(void);
private:
  // Copying and Assignment not allowed
  HClassGmm(const HClassGmm &inst);
  HClassGmm &operator= (const HClassGmm &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HClassGmm";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Read a Gaussian Mixture Model from a file.
  virtual void ReadClassGmm(const Halcon::HTuple &FileName);
  virtual void ReadClassGmm(const char *FileName);
  // Write a Gaussian Mixture Model to a file.
  virtual void WriteClassGmm(const Halcon::HTuple &FileName) const;
  virtual void WriteClassGmm(const char *FileName) const;
  // Read the training data of a Gaussian Mixture Model from a file.
  virtual void ReadSamplesClassGmm(const Halcon::HTuple &FileName) const;
  virtual void ReadSamplesClassGmm(const char *FileName) const;
  // Write the training data of a Gaussian Mixture Model to a file.
  virtual void WriteSamplesClassGmm(const Halcon::HTuple &FileName) const;
  virtual void WriteSamplesClassGmm(const char *FileName) const;
  // Calculate the class of a feature vector by a Gaussian Mixture
  // Model.
  virtual HTuple ClassifyClassGmm(const Halcon::HTuple &Features, const Halcon::HTuple &Num, Halcon::HTuple *ClassProb, Halcon::HTuple *Density, Halcon::HTuple *KSigmaProb) const;
  // Evaluate a feature vector by a Gaussian Mixture Model.
  virtual HTuple EvaluateClassGmm(const Halcon::HTuple &Features, Halcon::HTuple *Density, Halcon::HTuple *KSigmaProb) const;
  virtual HTuple EvaluateClassGmm(const Halcon::HTuple &Features, double *Density, double *KSigmaProb) const;
  // Train a Gaussian Mixture Model.
  virtual HTuple TrainClassGmm(const Halcon::HTuple &MaxIter, const Halcon::HTuple &Threshold, const Halcon::HTuple &ClassPriors, const Halcon::HTuple &Regularize, Halcon::HTuple *Iter) const;
  virtual HTuple TrainClassGmm(Hlong MaxIter, double Threshold, const char *ClassPriors, double Regularize, Halcon::HTuple *Iter) const;
  // Compute the information content of the preprocessed feature vectors
  // of a GMM.
  virtual HTuple GetPrepInfoClassGmm(const Halcon::HTuple &Preprocessing, Halcon::HTuple *CumInformationCont) const;
  virtual HTuple GetPrepInfoClassGmm(const char *Preprocessing, Halcon::HTuple *CumInformationCont) const;
  // Return the number of training samples stored in the training data of
  // a Gaussian Mixture Model (GMM).
  virtual Hlong GetSampleNumClassGmm() const;
  // Return a training sample from the training data of a Gaussian
  // Mixture Models (GMM).
  virtual HTuple GetSampleClassGmm(const Halcon::HTuple &NumSample, Halcon::HTuple *ClassID) const;
  virtual HTuple GetSampleClassGmm(const Halcon::HTuple &NumSample, Hlong *ClassID) const;
  // Add a training sample to the training data of a Gaussian Mixture
  // Model.
  virtual void AddSampleClassGmm(const Halcon::HTuple &Features, const Halcon::HTuple &ClassID, const Halcon::HTuple &Randomize) const;
  // Return the parameters of a Gaussian Mixture Model.
  virtual Hlong GetParamsClassGmm(Halcon::HTuple *NumClasses, Halcon::HTuple *MinCenters, Halcon::HTuple *MaxCenters, Halcon::HTuple *CovarType) const;
  virtual Hlong GetParamsClassGmm(Hlong *NumClasses, Halcon::HTuple *MinCenters, Halcon::HTuple *MaxCenters, char *CovarType) const;
  // Create a Gaussian Mixture Model for classification
  virtual void CreateClassGmm(const Halcon::HTuple &NumDim, const Halcon::HTuple &NumClasses, const Halcon::HTuple &NumCenters, const Halcon::HTuple &CovarType, const Halcon::HTuple &Preprocessing, const Halcon::HTuple &NumComponents, const Halcon::HTuple &RandSeed);
  virtual void CreateClassGmm(Hlong NumDim, Hlong NumClasses, Hlong NumCenters, const char *CovarType, const char *Preprocessing, Hlong NumComponents, Hlong RandSeed);
  // Classify an image with a Gaussian Mixture Model.
  virtual HRegionArray ClassifyImageClassGmm(const HImage &Image, const Halcon::HTuple &RejectionThreshold) const;
  virtual HRegionArray ClassifyImageClassGmm(const HImage &Image, double RejectionThreshold) const;
  // Add training samples from an image to the training data of a
  // Gaussian Mixture Model.
  virtual void AddSamplesImageClassGmm(const HImage &Image, const HRegionArray &ClassRegions, const Halcon::HTuple &Randomize) const;
  virtual void AddSamplesImageClassGmm(const HImage &Image, const HRegionArray &ClassRegions, double Randomize) const;
};

}

#endif
