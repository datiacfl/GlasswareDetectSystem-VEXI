/*****************************************************************************
 * HBarCode.i
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HBarCode
 *
 * (c) 2007-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.1 $
 * $Date: 2007/03/27 13:29:32 $
 * $Author: rahmann $
 * $Log: HBarCode.i,v $
 * Revision 1.1  2007/03/27 13:29:32  rahmann
 * Added class HBarCode
 *
 *
 */


#ifndef H_BAR_CODE_H
#define H_BAR_CODE_H


namespace Halcon {


class LIntExport HBarCode: public HRootObject {
public:
  HBarCode(void) {id = -1;} 
  HBarCode(const HTuple &GenParamNames, 
           const HTuple &GenParamValues);
  HBarCode(const char *GenParamNames, 
           const char *GenParamValues);

  virtual ~HBarCode(void);

private:
  // Internal Cleanup
  void Cleanup(void);

public:
  // Tools
  const char *ClassName(void) const {return "HBarCode";}

  // Cast Operator
  operator HTuple () const {return GetHandle();}

  // Access and Manipulation
  HTuple GetHandle(void) const {return HCtrlVal(id);}
  void   SetHandle(Hlong ID) {id = ID;}

private:
  Hlong  id;
public:
  // Get the alphanumerical results that were accumulated during the
  // decoding of bar code symbols.
  virtual HTuple GetBarCodeResult(const Halcon::HTuple &CandidateHandle, const Halcon::HTuple &ResultName) const;
  // Detect and read bar code symbols in an image.
  virtual HRegionArray FindBarCode(const HImage &Image, const Halcon::HTuple &CodeType, Halcon::HTuple *DecodedDataStrings) const;
  virtual HRegionArray FindBarCode(const HImage &Image, const Halcon::HTuple &CodeType, char *DecodedDataStrings) const;
  virtual HRegionArray FindBarCode(const HImage &Image, const char *CodeType, Halcon::HTuple *DecodedDataStrings) const;
  virtual HRegionArray FindBarCode(const HImage &Image, const char *CodeType, char *DecodedDataStrings) const;
  // Get one or several parameters that describe the bar code model.
  virtual HTuple GetBarCodeParam(const Halcon::HTuple &GenParamNames) const;
  virtual HTuple GetBarCodeParam(const char *GenParamNames) const;
  // Set selected parameters of the bar code model.
  virtual void SetBarCodeParam(const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues) const;
  virtual void SetBarCodeParam(const char *GenParamNames, Hlong GenParamValues) const;
  // Create a model of a bar code reader.
  virtual void CreateBarCodeModel(const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues);
};

}

#endif
