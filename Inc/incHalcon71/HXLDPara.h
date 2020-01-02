/*****************************************************************************
 * HXLDPara.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Class HXLDPara
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

#ifndef XLD_PARA_H
#define XLD_PARA_H


namespace Halcon {


/****************************************************************************/
/*                               HXLDPara                                   */
/****************************************************************************/

class HXLDParaArray;
class LIntExport HXLDPara: public HXLD {
  friend class HXLDParaArray;
public:
  HXLDPara(void): HXLD() {num_para++;}
  HXLDPara(Hkey key);
  HXLDPara(const Hobject &obj);
  HXLDPara(const HXLDPara &para);
  HXLDPara(const HXLDParaArray &arr);
  HXLDPara(const HXLD &xld);
  ~HXLDPara(void) {num_para--;}

  HXLDPara &operator= (const HXLDPara &para);
  HXLDPara &operator= (const HXLDParaArray &arr);
  HXLDPara &operator= (const HXLD &xld);

  // Tools
  virtual const char *HClassName(void) const;
  virtual const char *ClassName(void) const;
  virtual const char *InstClassName(void) const;
  virtual       INT4  ClassDBID(void) const;
  HBool         Shared(void) const;

  // Class Functions
  static Hlong NumInst(void) {return num_para;}

private:
  static Hlong num_para;

public:

};

}

#endif
