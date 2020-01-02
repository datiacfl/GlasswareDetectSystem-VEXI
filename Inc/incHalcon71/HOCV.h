/*****************************************************************************
 * HOCV.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HOCV
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

#ifndef H_OCV_H
#define H_OCV_H


namespace Halcon {


class LIntExport HOCV: public HRootObject {
public:
  HOCV(void) {id = -1;}
  HOCV(const HTuple &PatternName);
  HOCV(const char *PatternName);

  ~HOCV(void);
private:
  // Copying and Assignment not allowed
  HOCV(const HOCV &inst);
  HOCV &operator= (const HOCV &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HOCV";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Verification of a pattern using an OCV tool.
  virtual HTuple DoOcvSimple(const HImageArray &Pattern, const Halcon::HTuple &PatternName, const Halcon::HTuple &AdaptPos, const Halcon::HTuple &AdaptSize, const Halcon::HTuple &AdaptAngle, const Halcon::HTuple &AdaptGray, const Halcon::HTuple &Threshold) const;
  virtual HTuple DoOcvSimple(const HImageArray &Pattern, const char *PatternName, const char *AdaptPos, const char *AdaptSize, const char *AdaptAngle, const char *AdaptGray, double Threshold) const;
  // Training of an OCV tool.
  virtual void TraindOcvProj(const HImageArray &Pattern, const Halcon::HTuple &Name, const Halcon::HTuple &Mode) const;
  virtual void TraindOcvProj(const HImageArray &Pattern, const char *Name, const char *Mode) const;
  // Reading an OCV tool from file.
  virtual void ReadOcv(const Halcon::HTuple &FileName);
  virtual void ReadOcv(const char *FileName);
  // Saving an OCV tool to file.
  virtual void WriteOcv(const Halcon::HTuple &FileName) const;
  virtual void WriteOcv(const char *FileName) const;
  // Create a new OCV tool based on gray value projections.
  virtual void CreateOcvProj(const Halcon::HTuple &PatternNames);
  virtual void CreateOcvProj(const char *PatternNames);
};

}

#endif
