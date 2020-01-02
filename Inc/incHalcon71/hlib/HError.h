/*****************************************************************************
 * HError.h
 ***************************************************************************** 
 *
 * Projekt:     Halcon/libhalcon
 * Description: error messages
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *                  Neherstr. 1, 81675 Muenchen, Germany
 * 
 *****************************************************************************
 * 
 * $Revision: 1.12 $
 * $Date: 2000/06/08 15:54:38 $
 *
 */


#ifndef HERROR_H
#define HERROR_H


#if defined(__cplusplus)
extern "C" {
#endif

extern HLibExport Herror HSetErrText(char *text);

extern HLibExport Herror HErrText(Herror message,char *err_text);

extern HLibExport Herror HMessage(Herror message,char *msg_text);



#if defined(__cplusplus)
}
#endif


#endif
