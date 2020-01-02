/*****************************************************************************
 * HXLDModPara.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDModPara
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.16 $
 * $Date: 2005/05/06 07:36:06 $
 *
 */

#ifndef XLD_MOD_PARA_H
#define XLD_MOD_PARA_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDModPara                                */
/****************************************************************************/

class HXLDModParaArray;
class LIntExport HXLDModPara: public HXLD {
  friend class HXLDModParaArray;
public:
  HXLDModPara(void): HXLD() {num_mod_para++;}
  HXLDModPara(Hkey key);
  HXLDModPara(const Hobject &obj);
  HXLDModPara(const HXLDModPara &mod_para);
  HXLDModPara(const HXLDModParaArray &arr);
  HXLDModPara(const HXLD &xld);
  ~HXLDModPara(void) {num_mod_para--;}

  HXLDModPara &operator= (const HXLDModPara &mod_para);
  HXLDModPara &operator= (const HXLDModParaArray &arr);
  HXLDModPara &operator= (const HXLD &xld);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void) const;
  HBool         Shared(void) const;

  // Class Functions
  static Hlong NumInst(void) {return num_mod_para;}

private:
  static Hlong num_mod_para;

public: 
};

}

#endif
