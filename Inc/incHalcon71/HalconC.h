/*****************************************************************************
 * HalconC.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Defines, types, and declarations for HALCON/C
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.25 $
 * $Date: 2005/06/20 09:28:00 $
 * 
 */

#ifndef HALCON_C_H
#define HALCON_C_H

#ifdef _WIN32
#include <windows.h>
#endif
#include "HIntDef.h"
#include "HCVersion.h"
#include "HBase.h"
#include "HDeclSpec.h"
#include "Hconst.h"
#include "IPtype.h"
#include "HCtype.h"
#include "Hextern.h"

#define     HALCON_C_VERS             "7.0"
#define     HALCON_C_LAST_UPDATE      "01.08.2005"

#define     UNDEF_TYPE  (-1)  /* Type after deleting a tuple               */
                              /* instead of STRING_PAR, INT_PAR, etc       */

/* 
 * Data of type Hobject is a pointer into the HALCON object data base.
 * Thus it has to be treated as a magic number and must not not changed
 * by the user.
 */
typedef Hkey     Hobject;      /* Pointer to HALCON iconic data            */



/*
 * The data structure Htuple is used to pass control data to the
 * HALCON operators and get various kinds to non iconic data back
 * the the application.
 * Creating, access and deletion must only be done with the
 * supplied procedures.
 */
typedef struct {
        Hcpar    *tuple;       /* values (array von long/float/string)     */
        Hlong    length;       /* length of array                          */
        } Htuple;

#include "HInterfaceC.h"


/* 
 * Constants
 */ 
#define _                 (Hlong*)0      /* anonyme Variable               */
#ifndef NO_ANONYM_PAR
#define _i                (Hlong*)0      /* anonyme Variable (long)        */
#define _d                (double*)0     /* anonyme Variable (double)      */
#define _s                (char*)0       /* anonyme Variable (string)      */
#define _t                (Htuple*)0     /* anonyme Variable (Tupel)       */
#endif
#define NO_OBJECTS        (Hobject)(1)   /* leere Objektliste          */
#define EMPTY_REGION      (Hobject)(2)   /* Objekt mit leerer Region   */
#if 0
#define FULL_REGION       (Hobject)(3)   /* Objekt mit maximaler Region*/
#endif

/* 
 * Short versions for the tuple operators
 */
#define create_tuple(Tupel,Length) CT(Tupel,Length)
#define copy_tuple(Tupel,Out)      CPT(Tupel,Out)
#define resize_tuple(Tupel,Length) RT(Tupel,Length)
#define destroy_tuple(Tupel)       DT(Tupel)
#define length_tuple(Tupel)        LT(Tupel)
#define set_s(Tupel,Val,Index)     SS(Tupel,Val,Index)
#define set_i(Tupel,Val,Index)     SI(Tupel,Val,Index)
#define set_d(Tupel,Val,Index)     SD(Tupel,Val,Index)
#define get_s(Tupel,Index)         GS(Tupel,Index)
#define get_i(Tupel,Index)         GI(Tupel,Index)
#define get_d(Tupel,Index)         GD(Tupel,Index)
#define get_type(Tupel,Index)      GT(Tupel,Index)

#define RT(Tupel,Length)           Mresize_tuple(Tupel,Length,__FILE__,__LINE__)
#define CT(Tupel,Length)           Mcreate_tuple(Tupel,Length,__FILE__,__LINE__)
#define CPT(Tupel,Out)             Mcopy_tuple(Tupel,Out,__FILE__,__LINE__)
#define DT(Tupel)                  Mdestroy_tuple(Tupel,__FILE__,__LINE__)	
#define SS(Tupel,Val,Index)        Mset_s(Tupel,Val,Index,__FILE__,__LINE__)
	
#ifdef FAST /* Compiler option for tested programs */
#define LT(Tupel)                  ((Tupel).length)
#define SI(Tupel,Val,Index)        { Hlong I = Index; \
                                     (Tupel).tuple[I].par.l = (Hlong)(Val); \
                                     (Tupel).tuple[I].type = INT_PAR; }
#define SD(Tupel,Val,Index)        { Hlong I = Index; \
                                     (Tupel).tuple[I].par.f = (double)(Val); \
                                     (Tupel).tuple[I].type = DOUBLE_PAR; }
#define GS(Tupel,Index)            ((Tupel).tuple[Index].par.s)
#define GI(Tupel,Index)            Mget_i(Tupel,Index,__FILE__,__LINE__)
#define GD(Tupel,Index)            Mget_d(Tupel,Index,__FILE__,__LINE__)
#define GT(Tupel,Index)            ((Tupel).tuple[Index].type)
#else
#define LT(Tupel)                  Mlength_tuple(Tupel,__FILE__,__LINE__)
#define SI(Tupel,Val,Index)        Mset_i(Tupel,Val,Index,__FILE__,__LINE__)
#define SD(Tupel,Val,Index)        Mset_d(Tupel,Val,Index,__FILE__,__LINE__)
#define GS(Tupel,Index)            Mget_s(Tupel,Index,__FILE__,__LINE__)
#define GI(Tupel,Index)            Mget_i(Tupel,Index,__FILE__,__LINE__)
#define GD(Tupel,Index)            Mget_d(Tupel,Index,__FILE__,__LINE__)
#define GT(Tupel,Index)            Mget_type(Tupel,Index,__FILE__,__LINE__)
#endif
	
#define TC(ProcName)               T_call_halcon(ProcName)
#define IT(Tupel,ParNum)           set_in_tpar(Tupel,ParNum)
#define OT(Tupel,ParNum)           set_out_tpar(Tupel,ParNum)
#define IO(Obj,ParNum)             set_in_opar(Obj,ParNum)
#define OO(Obj,ParNum)             set_out_opar(Obj,ParNum)

	
/*
 * Prototypes for all HALCON operators
 */
#include "HProto.h"


#endif
