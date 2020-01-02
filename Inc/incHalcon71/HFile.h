/*****************************************************************************
 * HFile.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HFile
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

#ifndef H_FILE_H
#define H_FILE_H


namespace Halcon {


class LIntExport HFile: public HRootObject {
public:
  HFile(void) {id = -1;}
  HFile(const HTuple &FileName, const HTuple &FileType);
  HFile(const char   *FileName, const char   *FileType);

  ~HFile(void);
private:
  // Copying and Assignment not allowed
  HFile(const HFile &inst);
  HFile &operator= (const HFile &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HFile";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Open text file.
  virtual void OpenFile(const Halcon::HTuple &FileName, const Halcon::HTuple &FileType);
  virtual void OpenFile(const char *FileName, const char *FileType);
  // Write values in a text file.
  virtual void FwriteString(const Halcon::HTuple &String) const;
  // Read a line from a text file.
  virtual HTuple FreadLine(Halcon::HTuple *IsEOF) const;
  virtual HTuple FreadLine(Hlong *IsEOF) const;
  // Read strings from a text file.
  virtual HTuple FreadString(Halcon::HTuple *IsEOF) const;
  virtual HTuple FreadString(Hlong *IsEOF) const;
  // Read a character from a text file.
  virtual HTuple FreadChar() const;
  // Create a line feed.
  virtual void FnewLine() const;
};

}

#endif
