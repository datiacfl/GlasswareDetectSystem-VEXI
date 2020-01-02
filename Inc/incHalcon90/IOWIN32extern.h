/*****************************************************************************
 * IOWIN32extern.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Windows-specific external variables
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


#ifndef IOWIN32EXTERN_H
#define IOWIN32EXTERN_H

extern DCurs          Cur[MAX_WINDOW];    /* which cursor for which Windows */
extern WDescr         *W[MAX_WINDOW];     /* window description   */
extern DDescr         *D[MAX_WINDOW];     /* display description   */
extern HBYTE          XGreyTab[256];
extern DFont          loaded_font[MAX_LOADED_FONT]; /* table of loaded fonts */
extern INT            nWinOS;             /* operationsystem newer ore equal 4.0 */ 

#endif
