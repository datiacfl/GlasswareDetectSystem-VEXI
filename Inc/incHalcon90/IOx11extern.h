/*****************************************************************************
 * IOx11extern.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: X11-specific external variables
 *
 * (c) 1996-2008 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.8 $
 * $Date: 2008/12/06 13:36:26 $
 *
 */


#ifndef IOX11EXTERN_H
#define IOX11EXTERN_H

extern DCurs          Cur[MAX_WINDOW];    /* which cursor for which window */
extern WDescr         *W[MAX_WINDOW];     /* window description */
extern DDescr         *D[MAX_WINDOW];     /* display description */
extern HBYTE          XGreyTab[256];

#endif
