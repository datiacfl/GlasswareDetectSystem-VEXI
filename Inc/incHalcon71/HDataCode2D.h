/*****************************************************************************
 * HDataCode2D.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HDataCode2D
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

#ifndef H_DATA_CODE_2D_H
#define H_DATA_CODE_2D_H


namespace Halcon {


class LIntExport HDataCode2D: public HRootObject {
public:
  HDataCode2D(void) {id = -1;} 
  HDataCode2D(const HTuple &SymbolType, 
              const HTuple &GenParamNames, 
              const HTuple &GenParamValues);

  virtual ~HDataCode2D(void);

private:
  // Internal Cleanup
  void Cleanup(void);

public:
  // Tools
  const char *ClassName(void) const {return "HDataCode2D";}

  // Cast Operator
  operator HTuple () const {return GetHandle();}

  // Access and Manipulation
  HTuple GetHandle(void) const {return HCtrlVal(id);}
  void   SetHandle(Hlong ID) {id = ID;}

private:
  Hlong  id;
public:
  // Get the alphanumerical results that were accumulated during the
  // search for 2D data code symbols.
  virtual HTuple GetDataCode2dResults(const Halcon::HTuple &CandidateHandle, const Halcon::HTuple &ResultNames) const;
  // Detect and read 2D data code symbols in an image or
  // train the 2D data code model.
  virtual HXLDContArray FindDataCode2d(const HImage &Image, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, Halcon::HTuple *ResultHandles, Halcon::HTuple *DecodedDataStrings) const;
  virtual HXLDContArray FindDataCode2d(const HImage &Image, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues, Hlong *ResultHandles, char *DecodedDataStrings) const;
  virtual HXLDContArray FindDataCode2d(const HImage &Image, const char *GenParamNames, Hlong GenParamValues, Halcon::HTuple *ResultHandles, Halcon::HTuple *DecodedDataStrings) const;
  virtual HXLDContArray FindDataCode2d(const HImage &Image, const char *GenParamNames, Hlong GenParamValues, Hlong *ResultHandles, char *DecodedDataStrings) const;
  // Set selected parameters of the 2D data code model.
  virtual void SetDataCode2dParam(const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues) const;
  // Get one or several parameters that describe the 2D data code model.
  virtual HTuple GetDataCode2dParam(const Halcon::HTuple &GenParamNames) const;
  virtual HTuple GetDataCode2dParam(const char *GenParamNames) const;
  // Get for a given 2D data code model the names of the generic
  // parameters or objects that can be used in the other 2D data code
  // operators.
  virtual HTuple QueryDataCode2dParams(const Halcon::HTuple &QueryName) const;
  virtual HTuple QueryDataCode2dParams(const char *QueryName) const;
  // Read a 2D data code model from a file and create a new model.
  virtual void ReadDataCode2dModel(const Halcon::HTuple &FileName);
  virtual void ReadDataCode2dModel(const char *FileName);
  // Writes a 2D data code model into a file.
  virtual void WriteDataCode2dModel(const Halcon::HTuple &FileName) const;
  virtual void WriteDataCode2dModel(const char *FileName) const;
  // Create a model of a 2D data code class.
  virtual void CreateDataCode2dModel(const Halcon::HTuple &SymbolType, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues);
};

}

#endif
