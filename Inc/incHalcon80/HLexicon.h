/*****************************************************************************
 * HLexicon.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HLexicon
 *
 * (c) 1996-2006 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision $
 * $Date: 2007/01/17 12:44:47 $
 *
 */

#ifndef H_LEXICON_H
#define H_LEXICON_H


namespace Halcon {


class LIntExport HLexicon: public HRootObject {
public:
  HLexicon(void) {id = -1;}
  HLexicon(const HTuple &Name, const HTuple &Words);
  HLexicon(const char   *Name, const HTuple &Words);

  ~HLexicon(void);
private:
  // Copying and Assignment not allowed
  HLexicon(const HLexicon &inst);
  HLexicon &operator= (const HLexicon &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HLexicon";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  // Handle
  Hlong  id;
public:
  // Find a similar word in a lexicon.
  virtual HTuple SuggestLexicon(const Halcon::HTuple &Word, Halcon::HTuple *NumCorrections) const;
  virtual HTuple SuggestLexicon(const Halcon::HTuple &Word, Hlong *NumCorrections) const;
  virtual HTuple SuggestLexicon(const char *Word, Halcon::HTuple *NumCorrections) const;
  virtual HTuple SuggestLexicon(const char *Word, Hlong *NumCorrections) const;
  // Check if a word is contained in a lexicon.
  virtual Hlong LookupLexicon(const Halcon::HTuple &Word) const;
  virtual Hlong LookupLexicon(const char *Word) const;
  // Query all words from a lexicon.
  virtual HTuple InspectLexicon() const;
  // Create a lexicon from a text file.
  virtual void ImportLexicon(const Halcon::HTuple &Name, const Halcon::HTuple &FileName);
  virtual void ImportLexicon(const char *Name, const char *FileName);
  // Create a lexicon from a tuple of words.
  virtual void CreateLexicon(const Halcon::HTuple &Name, const Halcon::HTuple &Words);
};

}

#endif
