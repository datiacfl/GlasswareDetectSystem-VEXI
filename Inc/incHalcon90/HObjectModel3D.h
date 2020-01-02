/*****************************************************************************
 * HObjectModel3D.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Class HObjectModel3D
 *
 * (c) 2007-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.6 $
 * $Date: 2008/12/06 13:35:12 $
 *
 */

#ifndef H_OBJECT_MODEL_3D_H
#define H_OBJECT_MODEL_3D_H


#include "HCPPToolRef.h"


namespace Halcon {


class LIntExport HObjectModel3D: public HToolBase
{
public:

  // Tool-specific functional class constructors

  HObjectModel3D(const HTuple &FileName, 
                 const HTuple &Scale,
                 const HTuple &GenParamNames, 
                 const HTuple &GenParamValues,
                 HTuple *DxfStatus);

  // Common tool class management functionality

  HObjectModel3D();
  HObjectModel3D(Hlong ID);
  const char *ClassName(void) const;
  Hlong GetHandle(void) const;
  void  SetHandle(Hlong ID);

  // Tool-specific member functions

  // Return the parameters of a 3D object model.
  virtual HTuple GetObjectModel3dParams(const Halcon::HTuple &GenParamNames) const;
  // Return the parameters of a 3D object model.
  virtual HTuple GetObjectModel3dParams(const char *GenParamNames) const;
  // Project the edges of a 3D object model into image coordinates.
  virtual HXLDContArray ProjectObjectModel3d(const Halcon::HTuple &CamParam, const Halcon::HTuple &Pose, const Halcon::HTuple &HiddenSurfaceRemoval, const Halcon::HTuple &MinFaceAngle) const;
  // Apply an arbitrary affine 3D transformation to a 3D object model.
  virtual Hlong AffineTransObjectModel3d(const Halcon::HTuple &HomMat3D) const;
  // Read a 3D object model from a DXF file.
  virtual HTuple ReadObjectModel3dDxf(const Halcon::HTuple &FileName, const Halcon::HTuple &Scale, const Halcon::HTuple &GenParamNames, const Halcon::HTuple &GenParamValues);
};

}

#endif
