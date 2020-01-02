/*****************************************************************************
 * HOCRSVM.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HOCRSvm
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision $
 * $Date: 2006/01/16 16:26:31 $
 *
 */

#ifndef H_OCRSVM_H
#define H_OCRSVM_H


namespace Halcon {


class LIntExport HOCRSvm: public HRootObject {
public:
  HOCRSvm(void) {id = -1;}
  HOCRSvm(const HTuple &WidthCharacter, const HTuple &HeightCharacter, 
          const HTuple &Interpolation, const HTuple &Features, 
          const HTuple &Characters, const HTuple &KernelType,
          const HTuple &KernelParam, const HTuple &Nu, const HTuple &Mode,
          const HTuple &Preprocessing, const HTuple &NumComponents);

  ~HOCRSvm(void);
private:
  // Copying and Assignment not allowed
  HOCRSvm(const HOCRSvm &inst);
  HOCRSvm &operator= (const HOCRSvm &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HOCRSvm";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Read an SVM-based OCR classifier from a file.
  virtual void ReadOcrClassSvm(const Halcon::HTuple &FileName);
  virtual void ReadOcrClassSvm(const char *FileName);
  // Write an OCR classifier to a file.
  virtual void WriteOcrClassSvm(const Halcon::HTuple &FileName) const;
  virtual void WriteOcrClassSvm(const char *FileName) const;
  // Compute the features of a character.
  virtual HTuple GetFeaturesOcrClassSvm(const HImage &Character, const Halcon::HTuple &Transform) const;
  virtual HTuple GetFeaturesOcrClassSvm(const HImage &Character, const char *Transform) const;
  // Classify a related group of characters with an OCR classifier.
  virtual HTuple DoOcrWordSvm(const HRegionArray &Character, const HImage &Image, const Halcon::HTuple &Expression, const Halcon::HTuple &NumAlternatives, const Halcon::HTuple &NumCorrections, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrWordSvm(const HRegionArray &Character, const HImage &Image, const Halcon::HTuple &Expression, const Halcon::HTuple &NumAlternatives, const Halcon::HTuple &NumCorrections, char *Word, double *Score) const;
  virtual HTuple DoOcrWordSvm(const HRegionArray &Character, const HImage &Image, const char *Expression, Hlong NumAlternatives, Hlong NumCorrections, Halcon::HTuple *Word, Halcon::HTuple *Score) const;
  virtual HTuple DoOcrWordSvm(const HRegionArray &Character, const HImage &Image, const char *Expression, Hlong NumAlternatives, Hlong NumCorrections, char *Word, double *Score) const;
  // Classify multiple characters with an SVM-based OCR classifier.
  virtual HTuple DoOcrMultiClassSvm(const HRegionArray &Character, const HImage &Image) const;
  // Classify a single character with an SVM-based OCR classifier.
  virtual HTuple DoOcrSingleClassSvm(const HRegion &Character, const HImage &Image, const Halcon::HTuple &Num) const;
  // Approximate a trained SVM-based OCR classifier by a reduced SVM.
  virtual Hlong ReduceOcrClassSvm(const Halcon::HTuple &Method, const Halcon::HTuple &MinRemainingSV, const Halcon::HTuple &MaxError);
  virtual Hlong ReduceOcrClassSvm(const char *Method, Hlong MinRemainingSV, double MaxError);
  // Train an OCR classifier.
  virtual void TrainfOcrClassSvm(const Halcon::HTuple &TrainingFile, const Halcon::HTuple &Epsilon, const Halcon::HTuple &TrainMode) const;
  // Compute the information content of the preprocessed feature vectors
  // of an SVM-based OCR classifier.
  virtual HTuple GetPrepInfoOcrClassSvm(const Halcon::HTuple &TrainingFile, const Halcon::HTuple &Preprocessing, Halcon::HTuple *CumInformationCont) const;
  virtual HTuple GetPrepInfoOcrClassSvm(const char *TrainingFile, const char *Preprocessing, Halcon::HTuple *CumInformationCont) const;
  // Return the number of support vectors of an OCR classificator.
  virtual Hlong GetSupportVectorNumOcrClassSvm(Halcon::HTuple *NumSVPerSVM) const;
  // Return the index of a support vector from a trained OCR classifier that is
  // based on support vector machines.
  virtual double GetSupportVectorOcrClassSvm(const Halcon::HTuple &IndexSupportVector) const;
  // Return the parameters of an OCR classifier.
  virtual Hlong GetParamsOcrClassSvm(Halcon::HTuple *HeightCharacter, Halcon::HTuple *Interpolation, Halcon::HTuple *Features, Halcon::HTuple *Characters, Halcon::HTuple *KernelType, Halcon::HTuple *KernelParam, Halcon::HTuple *Nu, Halcon::HTuple *Mode, Halcon::HTuple *Preprocessing, Halcon::HTuple *NumComponents) const;
  virtual Hlong GetParamsOcrClassSvm(Hlong *HeightCharacter, char *Interpolation, char *Features, Halcon::HTuple *Characters, char *KernelType, double *KernelParam, double *Nu, char *Mode, char *Preprocessing, Hlong *NumComponents) const;
  // Create an OCR classifier using a support vector machine.
  virtual void CreateOcrClassSvm(const Halcon::HTuple &WidthCharacter, const Halcon::HTuple &HeightCharacter, const Halcon::HTuple &Interpolation, const Halcon::HTuple &Features, const Halcon::HTuple &Characters, const Halcon::HTuple &KernelType, const Halcon::HTuple &KernelParam, const Halcon::HTuple &Nu, const Halcon::HTuple &Mode, const Halcon::HTuple &Preprocessing, const Halcon::HTuple &NumComponents);
};

}

#endif
