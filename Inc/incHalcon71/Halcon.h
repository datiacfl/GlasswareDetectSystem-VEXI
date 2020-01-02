/*****************************************************************************
 * Halcon.h
 ***************************************************************************** 
 *
 * Project:      Halcon/libhalcon
 * Author:       W. Eckstein
 * Description:  Includes all header files for HALCON/library (C-Interface)
 *               This include file is used for user extensions (packages)
 *
 * (c) 1996-2004 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.28 $
 * $Date: 2004/06/24 14:34:33 $
 *
 */

#ifndef HALCON_H
#define HALCON_H

#include "HVersNum.h"
#include "HCVersion.h"
#include "HIntDef.h"
#include "Hconfig.h"
#include "HDeclSpec.h"
#include "Hconst.h"
#include "HBase.h"
#include "IPtype.h"
#include "HParallel.h"
#include "hlib/DBNew.h"
#include "hlib/HAlloc.h"
#include "HCtype.h"
#include "Hmakro.h"
#include "Hextern.h"
#include "hlib/CORE1.h"
#include "hlib/HBaseGP.h"
#include "hlib/HCLib.h"
#include "hlib/IOSpy.h"
#include "hlib/HInstance.h"
#include "hlib/CIPXLDCont.h"
#include "hlib/CIPXLDPara.h"
#include "hlib/CIPXLDPoly.h"
#if defined(_WIN32) && (defined(_HLibDLL) || defined(_LIntDLL))
#include "hlib/CoreInterface.h"
#endif

#endif
