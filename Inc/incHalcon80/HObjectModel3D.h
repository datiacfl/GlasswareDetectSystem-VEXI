/*****************************************************************************
 * HObjectModel3D.h
 ***************************************************************************** 
 *
 * Project:     Halcon/C++
 * Description: Class HObjectModel3D
 *
 * (c) 2007-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $
 * $
 *
 */

#ifndef H_OBJECT_MODEL_3D_H
#define H_OBJECT_MODEL_3D_H


namespace Halcon {


class LIntExport HObjectModel3D: public HRootObject {
public:
  HObjectModel3D(void) {id = -1;}

  ~HObjectModel3D(void);
private:
  // Copying and Assignment not allowed
  HObjectModel3D(const HObjectModel3D &inst);
  HObjectModel3D &operator= (const HObjectModel3D &inst);
  // Internal Cleanup
  void Cleanup(void);

public: 
  // Tools
  const char *ClassName(void) const {return "HObjectModel3D";}

  // Cast Operator
  operator HTuple () const {return HTuple(GetHandle());}

  // Access and Manipulation
  Hlong GetHandle(void) const {return id;}
  void SetHandle(Hlong ID) {id = ID;}

private:
  //Handle
  Hlong  id;
public:
  // Return the parameters of a 3D object model.
  virtual HTuple GetObjectModel3dParams(const Halcon::HTuple &GenParamNames) const;
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
