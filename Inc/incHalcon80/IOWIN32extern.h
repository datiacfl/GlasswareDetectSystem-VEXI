/*****************************************************************************
 * IOWIN32extern.h
 *****************************************************************************
 *
 * Project:     Halcon/libhalcon
 * Description: Windows NT specific external variables
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *               Neherstr. 1, 81675 Muenchen, Germany
 * 
 *****************************************************************************
 *
 * $Revision: 1.7 $
 * $Date: 2000/02/24 15:32:54 $
 *
 */


#ifndef IOWIN32EXTERN_H
#define IOWIN32EXTERN_H

extern DCurs          Cur[MAX_WINDOW];    /* which Cursor for which Window */
extern WDescr         *W[MAX_WINDOW];     /* window description   */
extern DDescr         *D[MAX_WINDOW];     /* display description   */
extern HBYTE          XGreyTab[256];
extern DFont          loaded_font[MAX_LOADED_FONT]; /* table of loaded fonts */
extern INT            nWinOS;             /* operationsystem newer ore equal 4.0 */ 

#endif
