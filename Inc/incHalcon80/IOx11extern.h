/*****************************************************************************
 * IOx11extern.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: X11 specific external variables
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *                  Neherstr. 1, 81675 Muenchen, Germany
 * 
 *****************************************************************************
 *
 * $Revision: 1.7 $
 * $Date: 2000/02/24 15:36:45 $
 *
 */


#ifndef IOX11EXTERN_H
#define IOX11EXTERN_H

extern DCurs          Cur[MAX_WINDOW];    /* which Cursor for which */
					  /* Window                 */
extern WDescr         *W[MAX_WINDOW];     /* window description   */
extern DDescr         *D[MAX_WINDOW];     /* display description   */
extern HBYTE          XGreyTab[256];

#endif
