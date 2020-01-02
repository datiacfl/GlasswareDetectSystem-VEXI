/*****************************************************************************
 * HBarCode.i
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Class HBarCode
 *
 * (c) 2007-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.4 $
 * $Date: 2008/12/06 13:35:12 $
 *
 */


#ifndef H_BAR_CODE_H
#define H_BAR_CODE_H


#include "HCPPToolRef.h"


namespace Halcon {


class LIntExport HBarCode: public HToolBase 
{
public:

  // Tool-specific functional class constructors

  HBarCode(const HTuple &GenParamNames, 
           const HTuple &GenParamValues);
           
  HBarCode(const char *GenParamNames, 
           const char *GenParamValues);

  // Common tool class management functionality

  HBarCode();
  HBarCode(Hlong ID);
  const char *ClassName(void) const;
  Hlong GetHandle(void) const;
  void  SetHandle(Hlong ID);

  // Tool-specific member functions

  // Get the alphanumerical results that were accumulated during the
  // decoding of bar code symbols.
  virtual HTuple GetBarCodeResult(const Halcon::HTuple &CandidateHandle, const Halcon::HTuple &ResultName) const;
  // Detect and read bar code symbols in an image.
  virtual HRegionArray FindBarCode(const HImage &Image, const Halcon::HTuple &CodeType, Halcon::HTuple *DecodedDataStrings) const;
  // Detect and read bar code symbols in an image.
  virtual HRegionArray FindBarCode(const HImage &Image, const Halcon::HTuple &CodeType, char *DecodedDataStrings) const;
  // Detect and read bar code symbols in an image.
  virtual HRegionArray FindBarCode(const HImage &Image, const char *CodeType, Halcon::HTuple *DecodedDataStrings) const;
  // Detect and read bar code symbols in an image.
  virtual HRegionArray FindBarCode(const HImage &Image, const char *CodeType, char *DecodedDataStrings) const;
  // Get one or several parameters that describe the bar code model.
  virtual HTuple GetBarCodeParam(const Halcon::HTuple &GenParamNames) const;
  // Get one or several parameters that describe the bar code model.
  virtual HTuple GetBarCodeParam(const char *GenParamNames) const;
  // Set selected parameters of the bar code model.
  virtual void SetBarCodeParam(const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues) const;
  // Set selected parameters of the bar code model.
  virtual void SetBarCodeParam(const char *GenParamNames, double GenParamValues) const;
  // Create a model of a bar code reader.
  virtual void CreateBarCodeModel(const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues);
  // Create a model of a bar code reader.
  virtual void CreateBarCodeModel(const char *GenParamNames, double GenParamValues);
};

}

#endif
