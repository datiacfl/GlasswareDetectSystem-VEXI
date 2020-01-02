/*****************************************************************************
 * HClassSVM.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HClassSvm
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.1 $
 * $Date: 2006/01/16 16:26:20 $
 *
 */

#ifndef H_CLASS_SVM_H
#define H_CLASS_SVM_H


namespace Halcon {


class LIntExport HClassSvm: public HRootObject {
public:
  HClassSvm(void) {id = -1;}
  HClassSvm(const HTuple &NumFeatures, const HTuple &KernelType,
            const HTuple &KernelParam, const HTuple &Nu,
            const HTuple &NumClasses, const HTuple &Mode,
            const HTuple &Preprocessing, const HTuple &NumComponents);

  ~HClassSvm(void);
private:
  // Copying and Assignment not allowed
  HClassSvm(const HClassSvm &inst);
  HClassSvm &operator= (const HClassSvm &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HClassSvm";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Read a support vector machine from a file.
  virtual void ReadClassSvm(const Halcon::HTuple &FileName);
  virtual void ReadClassSvm(const char *FileName);
  // Write a support vector machine to a file.
  virtual void WriteClassSvm(const Halcon::HTuple &FileName) const;
  virtual void WriteClassSvm(const char *FileName) const;
  // Read the training data of a support vector machine from a file.
  virtual void ReadSamplesClassSvm(const Halcon::HTuple &FileName) const;
  virtual void ReadSamplesClassSvm(const char *FileName) const;
  // Write the training data of a support vector machine to a file.
  virtual void WriteSamplesClassSvm(const Halcon::HTuple &FileName) const;
  virtual void WriteSamplesClassSvm(const char *FileName) const;
  // Classify a feature vector by a support vector machine.
  virtual HTuple ClassifyClassSvm(const Halcon::HTuple &Features, const Halcon::HTuple &Num) const;
  // Approximate a trained support vector machine by a reduced support
  // vector machine for faster classification.
  virtual Hlong ReduceClassSvm(const Halcon::HTuple &Method, const Halcon::HTuple &MinRemainingSV, const Halcon::HTuple &MaxError);
  virtual Hlong ReduceClassSvm(const char *Method, Hlong MinRemainingSV, double MaxError);
  // Train a support vector machine.
  virtual void TrainClassSvm(const Halcon::HTuple &Epsilon, const Halcon::HTuple &TrainMode) const;
  // Compute the information content of the preprocessed feature vectors
  // of a support vector machine
  virtual HTuple GetPrepInfoClassSvm(const Halcon::HTuple &Preprocessing, Halcon::HTuple *CumInformationCont) const;
  virtual HTuple GetPrepInfoClassSvm(const char *Preprocessing, Halcon::HTuple *CumInformationCont) const;
  // Return the number of support vectors of a support vector machine.
  virtual Hlong GetSupportVectorNumClassSvm(Halcon::HTuple *NumSVPerSVM) const;
  // Return the index of a support vector from a trained support vector
  // machine.
  virtual double GetSupportVectorClassSvm(const Halcon::HTuple &IndexSupportVector) const;
  // Return the number of training samples stored in the training data of
  // a support vector machine.
  virtual Hlong GetSampleNumClassSvm() const;
  // Return a training sample from the training data of a support vector
  // machine.
  virtual HTuple GetSampleClassSvm(const Halcon::HTuple &IndexSample, Halcon::HTuple *Target) const;
  virtual HTuple GetSampleClassSvm(const Halcon::HTuple &IndexSample, Hlong *Target) const;
  // Add a training sample to the training data of a support vector
  // machine.
  virtual void AddSampleClassSvm(const Halcon::HTuple &Features, const Halcon::HTuple &Class) const;
  // Return the parameters of a support vector machine.
  virtual Hlong GetParamsClassSvm(Halcon::HTuple *KernelType, Halcon::HTuple *KernelParam, Halcon::HTuple *Nu, Halcon::HTuple *NumClasses, Halcon::HTuple *Mode, Halcon::HTuple *Preprocessing, Halcon::HTuple *NumComponents) const;
  virtual Hlong GetParamsClassSvm(char *KernelType, double *KernelParam, double *Nu, Hlong *NumClasses, char *Mode, char *Preprocessing, Hlong *NumComponents) const;
  // Create a support vector machine for pattern classification.
  virtual void CreateClassSvm(const Halcon::HTuple &NumFeatures, const Halcon::HTuple &KernelType, const Halcon::HTuple &KernelParam, const Halcon::HTuple &Nu, const Halcon::HTuple &NumClasses, const Halcon::HTuple &Mode, const Halcon::HTuple &Preprocessing, const Halcon::HTuple &NumComponents);
  virtual void CreateClassSvm(Hlong NumFeatures, const char *KernelType, double KernelParam, double Nu, Hlong NumClasses, const char *Mode, const char *Preprocessing, Hlong NumComponents);
  // Classify an image with a support vector machine.
  virtual HRegionArray ClassifyImageClassSvm(const HImage &Image) const;
  // Add training samples from an image to the training data of a support
  // vector machine.
  virtual void AddSamplesImageClassSvm(const HImage &Image, const HRegionArray &ClassRegions) const;
};

}

#endif
