/*****************************************************************************
 * HOCRBox.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HOCRBox
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.1 $
 * $Date: 2007/03/08 15:08:11 $
 *
 */

#ifndef H_OCR_BOX_H
#define H_OCR_BOX_H


namespace Halcon {


class LIntExport HOCRBox: public HRootObject {
public:
  HOCRBox(void) {id = -1;}
  HOCRBox(const HTuple &WidthPattern, const HTuple &HeightPattern, 
       const HTuple &Interpolation, 
       const HTuple &Features, 
       const HTuple &Character);

  ~HOCRBox(void);
private:
  // Copying and Assignment not allowed
  HOCRBox(const HOCRBox &inst);
  HOCRBox &operator= (const HOCRBox &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HOCRBox";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Writing an OCR classifier into a file.
  virtual void WriteOcr(const Halcon::HTuple &FileName) const;
  virtual void WriteOcr(const char *FileName) const;
  // Read an OCR classifier from a file.
  virtual void ReadOcr(const Halcon::HTuple &FileName);
  virtual void ReadOcr(const char *FileName);
  // Classify one character.
  virtual HTuple DoOcrSingle(const HRegion &Character, const HImage &Image, Halcon::HTuple *Confidences) const;
  // Classify characters.
  virtual HTuple DoOcrMulti(const HRegionArray &Character, const HImage &Image, Halcon::HTuple *Confidence) const;
  virtual HTuple DoOcrMulti(const HRegionArray &Character, const HImage &Image, double *Confidence) const;
  // Get information about an OCR classifier.
  virtual Hlong InfoOcrClassBox(Halcon::HTuple *HeightPattern, Halcon::HTuple *Interpolation, Halcon::HTuple *WidthMaxChar, Halcon::HTuple *HeightMaxChar, Halcon::HTuple *Features, Halcon::HTuple *Characters) const;
  virtual Hlong InfoOcrClassBox(Hlong *HeightPattern, Hlong *Interpolation, Hlong *WidthMaxChar, Hlong *HeightMaxChar, Halcon::HTuple *Features, Halcon::HTuple *Characters) const;
  // Create a new OCR-classifier.
  virtual void CreateOcrClassBox(const Halcon::HTuple &WidthPattern, const Halcon::HTuple &HeightPattern, const Halcon::HTuple &Interpolation, const Halcon::HTuple &Features, const Halcon::HTuple &Character);
  // Train an OCR classifier by the input of regions.
  virtual double TraindOcrClassBox(const HRegionArray &Character, const HImage &Image, const Halcon::HTuple &Class) const;
  virtual double TraindOcrClassBox(const HRegionArray &Character, const HImage &Image, const char *Class) const;
  // Train an OCR classifier with the help of a training file.
  virtual double TrainfOcrClassBox(const Halcon::HTuple &FileName) const;
  virtual double TrainfOcrClassBox(const char *FileName) const;
  // Define a new conversion table for the characters.
  virtual void OcrChangeChar(const Halcon::HTuple &Character) const;
  // Test an OCR classifier.
  virtual HTuple TestdOcrClassBox(const HRegionArray &Character, const HImage &Image, const Halcon::HTuple &Class) const;
  virtual HTuple TestdOcrClassBox(const HRegionArray &Character, const HImage &Image, const char *Class) const;
  // Access the features which correspond to a character.
  virtual HTuple OcrGetFeatures(const HImage &Character) const;
};

}

#endif
