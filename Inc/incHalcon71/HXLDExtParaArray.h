/*****************************************************************************
 * HXLDExtParaArray.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDExtParaArray
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.15 $
 * $Date: 2005/05/06 07:36:06 $
 *
 */

#ifndef XLD_EXT_PARA_ARRAY_H
#define XLD_EXT_PARA_ARRAY_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDExtParaArray                           */
/****************************************************************************/

class LIntExport HXLDExtParaArray: public HXLDArray {
public:
  HXLDExtParaArray(void) : HXLDArray() {num_xld_ext_para_arrays++;}
  HXLDExtParaArray(Hkey *key, Hlong num);
  HXLDExtParaArray(const Hobject &obj);
  HXLDExtParaArray(const HXLDExtPara &ext_para);
  HXLDExtParaArray(const HXLD &xld);
  HXLDExtParaArray(const HXLDExtParaArray &arr);
  HXLDExtParaArray(const HXLDArray &arr);
  ~HXLDExtParaArray(void) {num_xld_ext_para_arrays--;}

  HXLDExtParaArray &operator= (const HXLDExtParaArray &arr);
  HXLDExtParaArray &operator= (const HXLDArray &arr);

  // Tools
  virtual const char *HClassName(void)    const;
  virtual const char *ClassName(void)     const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void)     const {return XLD_EXT_PARALLEL_ID;}
  virtual       Hkey  Key(Hlong i)         const {return array[i].Key();}
  virtual    Hobject  ElemId(Hlong i)      const {return array[i].Id();}

  // Access and Manipulation
  HXLDExtPara  const   &operator[] (Hlong index) const;
  HXLDExtPara          &operator[] (Hlong index);
  HXLDExtParaArray      operator() (Hlong min, Hlong max) const;
  HXLDExtParaArray     &Append(const HXLDExtPara &ext_para);
  HXLDExtParaArray     &Append(const HXLD &xld);
  HXLDExtParaArray     &Append(const HXLDExtParaArray &ext_paras);
  HXLDExtParaArray     &Append(const HXLDArray &xlds);
  virtual void          SetKeys(Hkey *key, Hlong num);
  void                  CopyHXLDExtParaArray(const HXLDExtParaArray &in);
  void                  CopyHXLDArray(const HXLDArray &in);

  // Class Functions
  static Hlong NumInst(void) {return num_xld_ext_para_arrays;}

private:
  static Hlong   num_xld_ext_para_arrays; 
  void          NewLength(Hlong new_num, Hlong old_num);

public:
  // Join modified XLD parallels lying on the same polygon.
  virtual HXLDPolyArray MaxParallelsXld(void) const;
};

}

#endif
