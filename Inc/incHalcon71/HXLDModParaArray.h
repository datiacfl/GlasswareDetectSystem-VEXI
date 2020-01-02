/*****************************************************************************
 * HXLDModParaArray.h
 ***************************************************************************** 
 *
 * Projekt:     Halcon/libhalcon
 * Description: Class HXLDModParaArray
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.14 $
 * $Date: 2005/05/06 07:36:06 $
 */

#ifndef XLD_MOD_PARA_ARRAY_H
#define XLD_MOD_PARA_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDModParaArray                           */
/****************************************************************************/

class LIntExport HXLDModParaArray: public HXLDArray {
public:
  HXLDModParaArray(void) : HXLDArray() {num_xld_mod_para_arrays++;}
  HXLDModParaArray(Hkey *key, Hlong num);
  HXLDModParaArray(const Hobject &obj);
  HXLDModParaArray(const HXLDModPara &mod_para);
  HXLDModParaArray(const HXLD &xld);
  HXLDModParaArray(const HXLDModParaArray &arr);
  HXLDModParaArray(const HXLDArray &arr);
  ~HXLDModParaArray(void) {num_xld_mod_para_arrays--;}

  HXLDModParaArray &operator= (const HXLDModParaArray &arr);
  HXLDModParaArray &operator= (const HXLDArray &arr);

  // Tools
  virtual const char *HClassName(void)    const;
  virtual const char *ClassName(void)     const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void)     const {return XLD_MOD_PARALLEL_ID;}
  virtual       Hkey  Key(Hlong i)         const {return array[i].Key();}
  virtual    Hobject  ElemId(Hlong i)      const {return array[i].Id();}

  // Access and Manipulation
  HXLDModPara  const   &operator[] (Hlong index) const;
  HXLDModPara          &operator[] (Hlong index);
  HXLDModParaArray      operator() (Hlong min, Hlong max) const;
  HXLDModParaArray     &Append(const HXLDModPara &mod_para);
  HXLDModParaArray     &Append(const HXLD &xld);
  HXLDModParaArray     &Append(const HXLDModParaArray &mod_para);
  HXLDModParaArray     &Append(const HXLDArray &xlds);
  virtual void          SetKeys(Hkey *key, Hlong num);
  void                  CopyHXLDModParaArray(const HXLDModParaArray &in);
  void                  CopyHXLDArray(const HXLDArray &in);

  // Class Functions
  static Hlong NumInst(void) {return num_xld_mod_para_arrays;}

private:
  static Hlong   num_xld_mod_para_arrays; 
  void          NewLength(Hlong new_num, Hlong old_num);

public:
};

}

#endif
