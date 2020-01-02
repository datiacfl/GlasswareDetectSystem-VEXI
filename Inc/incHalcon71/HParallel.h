/*****************************************************************************
 * HParallel.h
 *****************************************************************************
 *
 * Project:      Halcon (libhalcon)
 * Author:       M. Lueckenhaus
 * Description:  Basic constants for controlling the automatic 
 *               parallelization of HALCON operators and 
 *               programs (operator sequences)
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *               Neherstr. 1, D-81675 Muenchen, Germany
 *
 *****************************************************************************
 *
 *
 * $Source: /halcon/CVSROOT/include/HParallel.h,v $
 * $Revision: 1.6 $
 * $Date: 2001/05/11 09:16:36 $
 * $Author: lueckenhaus $
 * $State: Exp $
 *
 */

#ifndef HCPAR_H
#define HCPAR_H

#if defined(__cplusplus)
extern "C" {
#endif

/*===========================================================================*/
/*                                Constants                                  */
/*===========================================================================*/
/* -------- (knowledge default values and control weights) ----------------- */
/* constants for describing the overall processing context:                  */
#define HAG_PAR_SEQ           0            /* all operators are called       */
                                           /* sequentially => no need of     */
                                           /* synchronization; no automatic  */
                                           /* parallelization                */
/* remark: all following "TRUE" values (!=0) mean in any case that HALCON    */
/* works in a parallel manner and needs synchronization mechanisms           */
#define HAG_PAR_MT            1            /* "multithreading" context;      */
                                           /* operators may called in        */
                                           /* parallel use synchronization   */
                                           /* mechanisms for reentrancy,     */
                                           /* but don't use automatic par.   */
#define HAG_PAR_DPAR_MT       2            /* "multithreading" context (see  */
                                           /* above) AND use automatic       */
                                           /* data parallelization for       */
                                           /* processing operators (default) */

/* constants for describing how to process an operator:                      */
#define HAG_PAR_NO_RESTRICT   0            /* no restriction                 */
#define HAG_PAR_LOCAL         1            /* force local processing         */
                                           /* by main thread/process         */
#define HAG_PAR_MUTUAL        2            /* force processing under mutual  */
                                           /* exclusion, i.e. the same       */
                                           /* operator may only run once at  */
                                           /* a time                         */
#define HAG_PAR_EXCLUSIVE     3            /* force exclusive processing,    */
                                           /* i.e. no other operator may run */
                                           /* while this operator works      */

/* default control values:                                                   */
#define HAG_KW_CHORD_NUM      30           /* minimal num. of chords for par.*/
#define HAG_KW_MIN_COSTS      16300        /* minimal costs for which to par.*/
#define HAG_KW_PAR_COSTS      308          /* weight of ctrl. par. costs     */
#define HAG_KW_CPU_RATING     10           /* threshold for assigning a cpu  */


/* -------- (postprocessing of control parameters) ------------------------- */
#define HAG_PAR_NOCT          1            /* no need of ctrl. par. postproc.*/
                                           /* =>adopt par. of 1. H. thread   */
#define HAG_PAR_TUCT_ADD      2            /* add ctrl. par.s ;       tuple  */
#define HAG_PAR_CHCT_ADD      4            /* add ctrl. par.s ;       channel*/
                                           /* (must be 2*HAG_PAR_TUCT_ADD)   */
#define HAG_PAR_RECT_ADD      8            /* add ctrl. par.s ;       res.de.*/
                                           /* (must be 4*HAG_PAR_TUCT_ADD)   */
#define HAG_PAR_TUCT_MIN      16           /* minimum of ctrl. par.s; tuple  */
#define HAG_PAR_CHCT_MIN      32           /* minimum of ctrl. par.s; channel*/
#define HAG_PAR_RECT_MIN      64           /* minimum of ctrl. par.s; res.de.*/
#define HAG_PAR_TUCT_MAX      128          /* maximum of ctrl. par.s; tuple  */
#define HAG_PAR_CHCT_MAX      256          /* maximum of ctrl. par.s; channel*/
#define HAG_PAR_RECT_MAX      512          /* maximum of ctrl. par.s; res.de.*/
#define HAG_PAR_TUCT_CON      1024         /* concatenate ctrl. par.s;tuple  */
#define HAG_PAR_CHCT_CON      2048         /* concatenate ctrl. par.s;channel*/
#define HAG_PAR_RECT_CON      4096         /* concatenate ctrl. par.s;res.de.*/
                                           /* ATTENTION: the difference in   */
                                           /* the codes for tuples/channels/ */
                                           /* resources must always show the */
                                           /* above scheme of *2 and *4!     */
                                           /* Because this is used in the    */
                                           /* HAgent-source code; e.g.:      */
                                           /* HAG_PAR_CHCT_MIN is assumed to */
                                           /* be HAG_PAR_TUCT_MIN*2          */
#define HAG_PAR_TUCT          1170         /* postprocess ctrl. par.; tuple  */
/* remark: this is a shortcut for: HAG_PAR_TUCT_ADD | HAG_PAR_TUCT_MIN |     */
/*                                 HAG_PAR_TUCT_MAX | HAG_PAR_TUCT_CON       */
#define HAG_PAR_CHCT          2340         /* postprocess ctrl. par.; channel*/
                                           /* (must be 2*HAG_PAR_TUCT)       */
#define HAG_PAR_RECT          4680         /* postprocess ctrl. par.; res.de.*/
                                           /* (must be 4*HAG_PAR_TUCT)       */

/* -------- (postprocessing of domains/region components of output objects)  */
#define HAG_PAR_REG_NONE      0            /* no post processing             */
#define HAG_PAR_REG_CONSI     1            /* concatenation of (disjuntive)  */
                                           /* result regions for single      */
                                           /* input iconic parameter         */
#define HAG_PAR_REG_CONMU     2            /* concatenation of (disjuntive)  */
                                           /* result regions for multiple    */
                                           /* input iconic parameters        */

/* -------- (task-/operator-/thread-parallelization; chances and states) --- */
/* -------- (and postprocessing of control parameters) --------------------- */
/* The following constants symbolize different methods of parallelization.   */
/* Their values are built up according to the following rules:               */
/*     Bits 1-7 signal which method of parallelization can be used:          */
#define HAG_PAR_TUPL          1            /* tuple parallelization possible */
#define HAG_PAR_CHNL          2            /* channel paralleli. is possible */
#define HAG_PAR_RESC          4            /* resource decomposition possible*/
#define HAG_PAR_REIF          8            /* res. dec. at image filtering   */
/*                            16            *                                */
/*                            32            *                                */
#define HAG_PAR_NONE          64           /* no parallelization 'lucrative' */
/* the latter is set explicitely, if the hardware/operator training showed,  */
/* that the processing does not speed up by parallelization                  */
#define HAG_PAR_TUCH          3            /* tuple & channel par. possible  */
#define HAG_PAR_TURS          5            /* tuple par. & res. dec. possible*/
#define HAG_PAR_ALL           15           /* tuple & channel p. & res. dec. */
/*     Bits 8-23 currently not used                                          */
/* #define                    128           *                                */
/* #define                    256           *                                */
/* #define                    512           *                                */
/* #define                    1024          *                                */
/* #define                    2048          *                                */
/* #define                    4096          *                                */
/* #define                    8192          *                                */
/* #define                    16384         *                                */
/* #define                    32768         *                                */
/* #define                    65536         *                                */
/* #define                    131072        *                                */
/* #define                    262144        *                                */
/* #define                    524288        *                                */
/* #define                    1048576       *                                */
/* #define                    2097152       *                                */
/* #define                    4194304       *                                */
/*     Bits 24-31 signal which parallelization steps have already been       */
/*     done for the actual task/operator/thread:                             */
#define HAG_PAR_TUPLED        8388608      /* tuple parallelized             */
#define HAG_PAR_CHNLED        16777216     /* channel parallelized           */
#define HAG_PAR_RESCED        33554432     /* resources already decomposed   */
#define HAG_PAR_REIFED        67108864     /* res. decom. at image filtering */

#if defined(__cplusplus)
}
#endif

#endif
