/*****************************************************************************
 * Hmakro.h
 ***************************************************************************** 
 *
 * Project:      Halcon/libhalcon
 * Description:  Definition of macros
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *               www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.80 $
 * $Date: 2005/06/14 09:55:57 $
 *
 */

#ifndef HMAKRO_H
#define HMAKRO_H



#define HDFImage(VAR,IMAGE_IN,KOOR) { VAR = 0.0; \
  switch ((IMAGE_IN)->kind) {\
    case BYTE_IMAGE: VAR = (double)(IMAGE_IN)->pixel.b[KOOR]; break;\
    case INT1_IMAGE: VAR = (double)(IMAGE_IN)->pixel.i[KOOR]; break;\
    case INT2_IMAGE: VAR = (double)(IMAGE_IN)->pixel.s.p[KOOR]; break;\
    case UINT2_IMAGE: VAR = (double)(IMAGE_IN)->pixel.u.p[KOOR]; break;\
    case DIR_IMAGE: VAR = (double)(IMAGE_IN)->pixel.d[KOOR]; break;\
    case CYCLIC_IMAGE: VAR = (double)(IMAGE_IN)->pixel.z[KOOR]; break;\
    case INT4_IMAGE: VAR = (double)(IMAGE_IN)->pixel.l[KOOR]; break;\
    case FLOAT_IMAGE: VAR = (double)(IMAGE_IN)->pixel.f[KOOR]; break;\
    case COMPLEX_IMAGE: return(H_ERR_WITFO); /* wrong image type for oparation*/ \
    case XY_IMAGE: return(H_ERR_WITFO);      /* wrong image type for oparation*/ \
    default: return(H_ERR_NIIT);             /* not implemented image type */\
  }} 



#define HAbsImage(VAR,IMAGE_IN,KOOR) \
  switch ((IMAGE_IN)->kind) {\
    case BYTE_IMAGE: VAR = ABS((double)(IMAGE_IN)->pixel.b[KOOR]); break; \
    default: ; \
  }



#define HImageFD(IMAGE_OUT,VAR,KOOR) \
  switch ((IMAGE_OUT)->kind) {\
    case BYTE_IMAGE: { \
      INT HHH; \
      HHH = HIRound(VAR); \
      if (HHH > 255) HHH = 255; else if (HHH < 0) HHH = 0;\
      (IMAGE_OUT)->pixel.b[KOOR] = (HBYTE)HHH; \
      break; } \
    case CYCLIC_IMAGE: \
      (IMAGE_OUT)->pixel.z[KOOR] = HMOD(HLRound(VAR),(INT)(UCHAR_MAX+1)); \
      break; \
    case INT1_IMAGE: { \
      INT HHH; \
      HHH = HIRound(VAR); \
      if (HHH > INT1_MAX) HHH = INT1_MAX; \
      else if (HHH < INT1_MIN) HHH = INT1_MIN;\
      (IMAGE_OUT)->pixel.i[KOOR] = (INT1)HHH; \
      break; } \
    case INT2_IMAGE: { \
      double DDD = (VAR);\
      if (DDD > (double)INT2_MAX) DDD = INT2_MAX; \
      else if (DDD < INT2_MIN) DDD = INT2_MIN;\
     (IMAGE_OUT)->pixel.s.p[KOOR] = (INT2)HLRound(DDD); \
      break; } \
    case UINT2_IMAGE: { \
      double DDD = (VAR);\
      if (DDD > (double)UINT2_MAX) DDD = UINT2_MAX; \
      else if (DDD < 0) DDD = 0;\
     (IMAGE_OUT)->pixel.s.p[KOOR] = (UINT2)HLRound(DDD); \
      break; } \
    case LONG_IMAGE: { \
      double DDD = (VAR);\
      if (DDD > (double)INT4_MAX) DDD = INT4_MAX; \
      else if (DDD < INT4_MIN) DDD = INT4_MIN;\
     (IMAGE_OUT)->pixel.l[KOOR] = (INT4)HLRound(DDD); \
      break; } \
    case FLOAT_IMAGE: { \
      double DDD = (VAR);\
      if (DDD > (double)FLT_MAX) DDD = FLT_MAX; \
      else if (DDD < -(double)FLT_MAX) DDD = -(double)FLT_MAX;\
      (IMAGE_OUT)->pixel.f[KOOR] = (float)DDD; \
      break; } \
    case COMPLEX_IMAGE: { \
      double DDD = (VAR);\
      if (DDD > (double)FLT_MAX) DDD = FLT_MAX; \
      else if (DDD < -(double)FLT_MAX) DDD = -(double)FLT_MAX;\
      (IMAGE_OUT)->pixel.c[KOOR].re = (float)DDD; \
      (IMAGE_OUT)->pixel.c[KOOR].im = (float)0.0; \
      break; }\
    case DIR_IMAGE: return(H_ERR_WITFO); \
    case XY_IMAGE: return(H_ERR_WITFO); /* wrong image type for operation*/ \
    default: return(H_ERR_NIIT); /* not implemented image type */\
  } 


#define HCkFilterSize(IMAGE_WIDTH,IMAGE_HEIGHT,FILTER_WIDTH,FILTER_HEIGHT) \
  if(((IMAGE_WIDTH) < ((FILTER_WIDTH)>>1)+1) || ((IMAGE_HEIGHT) < ((FILTER_HEIGHT)>>1)+1)) \
     return(H_ERR_FSEIS); 
     
#define HCkFilterSize_2(IMAGE_WIDTH,IMAGE_HEIGHT,FILTER_WIDTH_2,FILTER_HEIGHT_2) \
  if(((IMAGE_WIDTH) < (FILTER_WIDTH_2)+1)  || ((IMAGE_HEIGHT) < (FILTER_HEIGHT_2)+1)) \
     return(H_ERR_FSEIS); 
     

#define DIST(PIX,PIX2,ABSDIF,IMAGE_IN_KIND) \
  switch (IMAGE_IN_KIND) { \
    case BYTE_IMAGE: \
    case LONG_IMAGE: \
    case INT1_IMAGE: \
    case INT2_IMAGE: \
    case UINT2_IMAGE: \
    case FLOAT_IMAGE: \
      ABSDIF = ABS((PIX)-(PIX2)); \
      break; \
    case CYCLIC_IMAGE: \
      { double dmax,dmaxh; \
	dmax = (double)UCHAR_MAX + 1.;\
	dmaxh = (double)(int)(dmax/2.); \
	ABSDIF = ABS((PIX)-(PIX2)); \
	if ((ABSDIF) > dmaxh) ABSDIF = dmax - (ABSDIF); \
      } \
      break; \
    case DIR_IMAGE: \
      if ((PIX) > 200. || (PIX2) > 200.) ABSDIF = (double)UCHAR_MAX; \
      else \
      { ABSDIF = ABS((PIX)-(PIX2)); \
	if ((ABSDIF) > 90.) ABSDIF = 181. - (ABSDIF); \
      } \
      break; \
    default: return(H_ERR_NIIT); \
  }  


#define HMOD(VAL,VALMAX) (((VAL) < 0) ? \
  ((unsigned char)(((VALMAX) - (-(VAL) % (VALMAX))) % (VALMAX))) :\
  ((unsigned char)((VAL) % (VALMAX)))) 



#ifdef FAST
#define TestRegIma(REG,WIDTH,HEIGHT)
#else
#define TestRegIma(REG,WIDTH,HEIGHT) \
if (REG->num > 0) { \
if (REG->rl[REG->num-1].ce >= WIDTH) \
  return(H_ERR_LLTB);   /* letzte Zeile zu gross */\
if (REG->rl[0].l < 0) \
  return(H_ERR_FLTS);   /* erste Zeile zu klein */\
if (REG->rl[REG->num-1].l >= HEIGHT) { \
  printf("file %s, in line %d:\n",__FILE__,__LINE__); \
  printf("image width/height = (%d,%d)\n",WIDTH,HEIGHT); \
  printf("region min/max row = %d, %d\n", \
	 REG->rl[0].l,REG->rl[REG->num-1].l); \
  return(H_ERR_LLTB);  } } /* letzte Zeile zu gross */
#endif



/* Grauwertkomponente eines Graubildes */
#define IMAGE_INDEX  1

#define HBitImageSize(WIDTH,HEIGHT) (size_t)(WIDTH*HEIGHT/8+1)

#define WarningCompl(Proc) \
    (void)printf("warning: is_compl not yet full implemented (%s)\n",Proc)


/*****************************************************************************
 * Routines for allocating "permanent" memory from the heap.  This memory is
 * _not_ freed automatically after each call to a Halcon operator.
 *****************************************************************************/

#ifdef SMALL
#define HAlloc(PROC_HANDLE,SIZE,VOID_PTR) \
   HXAlloc(PROC_HANDLE,SIZE,"",(INT4_8)-1,H_GLOBAL_ALLOC,(VOIDP*)(VOID_PTR))
#else
#define HAlloc(PROC_HANDLE,SIZE,VOID_PTR) \
   HXAlloc(PROC_HANDLE,SIZE,__FILE__,(INT4_8)__LINE__,H_GLOBAL_ALLOC, \
           (VOIDP*)(VOID_PTR))
#endif

#ifdef SMALL
#define HRealloc(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR) \
    HXRealloc(PROC_HANDLE,VOID_PTR,SIZE,(VOIDP*)(NEW_PTR),"",(INT4_8)-1)
#else
#define HRealloc(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR) \
    HXRealloc(PROC_HANDLE,VOID_PTR,SIZE,(VOIDP*)(NEW_PTR),__FILE__,\
              (INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFree(PROC_HANDLE,VOID_PTR) \
   HXFree(PROC_HANDLE,(VOIDP)(VOID_PTR),"",(INT4_8)-1,FALSE)
#else
#define HFree(PROC_HANDLE,VOID_PTR) \
   HXFree(PROC_HANDLE,(VOIDP)(VOID_PTR),__FILE__,(INT4_8)__LINE__,FALSE)
#endif

#ifdef SMALL
#define HAllocRLNum(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNum(PROC_HANDLE,REGION,SIZE,"",(INT4_8)-1)
#else
#define HAllocRLNum(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNum(PROC_HANDLE,REGION,SIZE,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION) \
    HXReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION,"",(INT4_8)-1)
#else
#define HReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION) \
    HXReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION,__FILE__,\
                   (INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HAllocRL(PROC_HANDLE,REGION) \
    HXAllocRL(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HAllocRL(PROC_HANDLE,REGION) \
    HXAllocRL(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeRL(PROC_HANDLE,REGION) \
   HXFreeRL(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HFreeRL(PROC_HANDLE,REGION) \
   HXFreeRL(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif


/*****************************************************************************
 * Routines for allocating temporary memory from a "stack" of memory.  This
 * memory is freed automatically after each call to a Halcon operator.
 *****************************************************************************/

#ifdef SMALL
#define HAllocTmp(PROC_HANDLE,VOID_PTR,SIZE) \
   HXAllocTmp(PROC_HANDLE,(VOIDP*)(VOID_PTR),SIZE,"",(INT4_8)-1)
#else
#define HAllocTmp(PROC_HANDLE,VOID_PTR,SIZE) \
   HXAllocTmp(PROC_HANDLE,(VOIDP*)(VOID_PTR),SIZE,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeTmp(PROC_HANDLE,VOID_PTR) \
   HXFreeTmp(PROC_HANDLE,(VOIDP)(VOID_PTR),"",(INT4_8)-1)
#else
#define HFreeTmp(PROC_HANDLE,VOID_PTR) \
   HXFreeTmp(PROC_HANDLE,(VOIDP)(VOID_PTR),__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeNTmp(PROC_HANDLE,NUM) \
   HXFreeNTmp(PROC_HANDLE,NUM,"",(INT4_8)-1)
#else
#define HFreeNTmp(PROC_HANDLE,NUM) \
   HXFreeNTmp(PROC_HANDLE,NUM,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeAllTmp(PROC_HANDLE) \
   HXFreeAllTmp(PROC_HANDLE,"",(INT4_8)-1)
#else
#define HFreeAllTmp(PROC_HANDLE) \
   HXFreeAllTmp(PROC_HANDLE,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeUpToTmp(PROC_HANDLE,VOID_PTR) \
    HXFreeUpToTmp(PROC_HANDLE,(VOIDP)(VOID_PTR),"",(INT4_8)-1)
#else
#define HFreeUpToTmp(PROC_HANDLE,VOID_PTR) \
    HXFreeUpToTmp(PROC_HANDLE,(VOIDP)(VOID_PTR),__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HAllocRLNumTmp(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNumTmp(PROC_HANDLE,REGION,SIZE,"",(INT4_8)-1)
#else
#define HAllocRLNumTmp(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNumTmp(PROC_HANDLE,REGION,SIZE,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HAllocRLTmp(PROC_HANDLE,REGION) \
    HXAllocRLTmp(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HAllocRLTmp(PROC_HANDLE,REGION) \
    HXAllocRLTmp(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeRLTmp(PROC_HANDLE,REGION) \
   HXFreeRLTmp(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HFreeRLTmp(PROC_HANDLE,REGION) \
   HXFreeRLTmp(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HTestTmp(PROC_HANDLE,VOID_PTR) \
    HXTestTmp(PROC_HANDLE,VOID_PTR,"",(INT4_8)-1,TRUE)
#else
#define HTestTmp(PROC_HANDLE,VOID_PTR) \
    HXTestTmp(PROC_HANDLE,VOID_PTR,__FILE__,(INT4_8)__LINE__,TRUE)
#endif

#ifdef SMALL
#define HTestPtr(VOID_PTR) \
    HXTestPtr(VOID_PTR,"",(INT4_8)-1)
#else
#define HTestPtr(VOID_PTR) \
    HXTestPtr(VOID_PTR,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HTestAllTmp(VOID_PTR) \
    HXTestAllTmp(VOID_PTR,"",(INT4_8)-1)
#else
#define HTestAllTmp(VOID_PTR) \
    HXTestAllTmp(VOID_PTR,__FILE__,(INT4_8)__LINE__)
#endif


/*****************************************************************************
 * Routines for allocating temporary memory from the heap.  This memory is
 * freed automatically after each call to a Halcon operator.
 *****************************************************************************/

#ifdef SMALL
#define HAllocLocal(PROC_HANDLE,SIZE,VOID_PTR) \
   HXAllocLocal(PROC_HANDLE,SIZE,"",(INT4_8)-1,(VOIDP*)(VOID_PTR))
#else
#define HAllocLocal(PROC_HANDLE,SIZE,VOID_PTR) \
   HXAllocLocal(PROC_HANDLE,SIZE,__FILE__,(INT4_8)__LINE__,(VOIDP*)(VOID_PTR))
#endif

#ifdef SMALL
#define HReallocLocal(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR) \
    HXReallocLocal(PROC_HANDLE,VOID_PTR,SIZE,(VOIDP*)(NEW_PTR),"",(INT4_8)-1)
#else
#define HReallocLocal(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR) \
    HXReallocLocal(PROC_HANDLE,VOID_PTR,SIZE,(VOIDP*)(NEW_PTR),\
                   __FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeLocal(PROC_HANDLE,VOID_PTR) \
   HXFreeLocal(PROC_HANDLE,(VOIDP)(VOID_PTR),"",(INT4_8)-1,TRUE)
#else
#define HFreeLocal(PROC_HANDLE,VOID_PTR) \
   HXFreeLocal(PROC_HANDLE,(VOIDP)(VOID_PTR),__FILE__,(INT4_8)__LINE__,TRUE)
#endif

#ifdef SMALL
#define HAllocRLNumLocal(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNumLocal(PROC_HANDLE,REGION,SIZE,"",(INT4_8)-1)
#else
#define HAllocRLNumLocal(PROC_HANDLE,REGION,SIZE) \
    HXAllocRLNumLocal(PROC_HANDLE,REGION,SIZE,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HAllocRLLocal(PROC_HANDLE,REGION) \
    HXAllocRLLocal(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HAllocRLLocal(PROC_HANDLE,REGION) \
    HXAllocRLLocal(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif

#ifdef SMALL
#define HFreeRLLocal(PROC_HANDLE,REGION) \
   HXFreeRLLocal(PROC_HANDLE,REGION,"",(INT4_8)-1)
#else
#define HFreeRLLocal(PROC_HANDLE,REGION) \
   HXFreeRLLocal(PROC_HANDLE,REGION,__FILE__,(INT4_8)__LINE__)
#endif



#ifndef ABS
#define ABS(A)  (((A) >= 0) ? (A) : (-(A)))
#endif

/* Umwandlung Bogenmass in Grad und zurueck */
#define RadToDeg(x) (double)(x) * 57.295779513082
#define DegToRad(x) (double)(x) / 57.295779513082

#define HIRound(Val) (((Val) < 0.0) ? ((INT)((Val)-0.5)):((INT)((Val)+0.5)))
#define HLRound(Val) (((Val) < 0.0) ? ((INT4_8)((Val)-0.5)):\
		     ((INT4_8)((Val)+0.5)))


/* Randbehandlung bei Bildern; Achtung 'width' wird als global angenommen */
/* Spiegeln */
#define BR(ROW)   (((ROW) < 0) ? (-(ROW)) : \
  (((ROW) >= height) ? (height-(ROW)+height-2) : \
    (ROW)))
#define BC(COL)   (((COL) < 0) ? (-(COL)) : \
  (((COL) >= width) ? (width - (COL) + width - 2) : \
    (COL)))


/* Hrlregion */
#define HRLReset(RL) \
  { (RL)->feature.def.all = 0; (RL)->is_compl = FALSE; (RL)->num = 0; }

#define HTestF(RL,FEAT) ((RL)->feature.def.single.FEAT == 1)

#define HSetF(RL,FEAT) (RL)->feature.def.single.FEAT = 1

#define HGetFVal(RL,FEAT) (RL)->feature.FEAT

#define HTestBF(RL,FEAT) (HTestF(RL,FEAT) && (HGetFVal(RL,FEAT) == TRUE))

#define HSetBF(RL,FEAT) { HSetF(RL,FEAT); HSetFVal(RL,FEAT,TRUE); }

#define HSetFVal(RL,FEAT,VAL) (RL)->feature.FEAT = VAL

#define HRLSize(NumRuns) ((size_t)((NumRuns) * sizeof(Hrun) +\
		(sizeof(Hrlregion_min))))

#define HLinesSize(NumLines) ((size_t)((NumLines) * sizeof(Hline) +\
		   (sizeof(Hlines_min))))

/* Binaerbild */
#define HTestBit(D,P) ((D)[(P)>>3] & (1<<(7-((P)&7))))

#define HDelBit(D,P) (D)[(P)>>3] &= (UINT1)(~(1<<(7-((P)&7))))

#define HSetBit(D,P) (D)[(P)>>3] |= (UINT1)(1<<(7-((P)&7)))

/* Koordinaten */
#define HLinCoor(L,C,W) (((INT4_8)(L)*(INT4_8)(W))+(INT4_8)(C))

#define HXLinCoor(L,C,W) HLinCoor(L,C,W)

#define HCol(K,W) (INT2)(((K) % (W)))

#define HRow(K,W) (INT2)(((K) / (W)))

#define CB(RL,I,W) HLinCoor((RL)[I].l,(RL)[I].cb,W)

#define CE(RL,I,W) HLinCoor((RL)[I].l,(RL)[I].ce,W)


#define FLinCoor(R,C,H) ((C)*(H)+(R))


/* misc */
#ifndef SGN
#define SGN(X) (((X)==0)?0:(((X)>0)?1:(-1)))
#endif

#ifndef ODD
#define ODD(X) ((X) % 2)
#endif

#ifndef EVEN
#define EVEN(X) (!((X)%2))
#endif

#ifndef MIN
#define MIN(X,Y) (((X)>(Y))?(Y):(X))
#endif

#ifndef MAX
#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#endif

#define HInsideImage(R,C,WIDTH,HEIGHT) \
   ((((R)>=0) && ((C)>=0) && ((R)<(HEIGHT)) && ((C)<(WIDTH)))?TRUE:FALSE)


#if !defined(NO_SPY) && !defined(FAST)
#define HCkP(Proc) {Herror ERR,H_ERR_P;\
   if (HROInfo.SpyAllProc && HROInfo.Spy) \
     IOSpyProcCall(#Proc,__LINE__,__FILE__); \
   if ((ERR = Proc) != H_MSG_OK) \
     { if( (H_ERR_P = HProcessErr(#Proc,ERR,__LINE__,__FILE__)) != H_MSG_OK)\
          return(H_ERR_P);\
       return(ERR); }}
#else
#define HCkP(Proc) {Herror ERR;\
   if ((ERR = Proc) != H_MSG_OK) \
     { return(ERR); }}
#endif

#if !defined(NO_SPY) && !defined(FAST)
#define HCkPasync(Proc,GapingFlag,ComplFlag,ErrFlag) {Herror ERR,H_ERR_P;     \
   if(HROInfo.SpyAllProc && HROInfo.Spy)                                      \
      IOSpyProcCall(#Proc,__LINE__,__FILE__);                                 \
   if( (ERR = Proc) != H_MSG_OK)                                              \
     {                                                                        \
      if( (H_ERR_P = HProcessErr(#Proc,ERR,__LINE__,__FILE__)) != H_MSG_OK)   \
        {                                                                     \
         if(GapingFlag == FALSE)                                              \
           {                                                                  \
            *ErrFlag = H_ERR_P;                                               \
            *ComplFlag = TRUE;                                                \
           }                                                                  \
         return(H_ERR_P);                                                     \
	}                                                                     \
      if(GapingFlag == FALSE)                                                 \
        {                                                                     \
         *ErrFlag = ERR;                                                      \
         *ComplFlag = TRUE;                                                   \
        }                                                                     \
      return(ERR);                                                            \
     }}
#else
#define HCkPasync(Proc,GapingFlag,ComplFlag,ErrFlag) {Herror ERR;             \
   if( (ERR = Proc) != H_MSG_OK)                                              \
     {                                                                        \
      if(GapingFlag == FALSE)                                                 \
        {                                                                     \
         *ErrFlag = ERR;                                                      \
         *ComplFlag = TRUE;                                                   \
        }                                                                     \
      return(ERR);                                                            \
     }}
#endif

#if defined(FAST) || defined (NO_SPY) 
#define HCkE(ERR) {if (ERR != H_MSG_OK) return(ERR);}
#else
#define HCkE(ERR) { \
  if (ERR != H_MSG_OK) \
  { if (HROInfo.SpyAllProc && HROInfo.Spy) \
    (void)HProcessErr("-",ERR,__LINE__,__FILE__); \
  return(ERR);}}
#endif

#define HCkNoObj(PROC_HANDLE) { HBOOL BOOL_PTR; \
  if ((HNoInpObj(PROC_HANDLE, &BOOL_PTR) != H_MSG_OK) || \
      (BOOL_PTR == TRUE)) \
    { Herror N_OBJ_RESULT;\
      HReadGV(PROC_HANDLE,HGNoObjResult,&N_OBJ_RESULT);\
      return(N_OBJ_RESULT); }}

#define HCkOnlySqr(width,height) \
  if (!HIs2Pot(width) || (!HIs2Pot(height))) return(H_ERR_NPOT)

#define HIsError(Err) ((Err>=1000)?(TRUE):(FALSE))

#define HIsMessage(Err) ((Err<1000)?(TRUE):(FALSE))

#ifdef FAST
#define HCkRL(PROC_HANDLE,RL,PROC,IN_OUT)
#else
#define HCkRL(PROC_HANDLE,RL,PROC,IN_OUT) { Herror H_ERR_RL;\
   INT4 CHECK_F;\
   HReadGV(PROC_HANDLE,HGcheck,&CHECK_F);\
   if (CHECK_F & CHECK_CHORD)\
   {\
     H_ERR_RL = HRLTest(PROC_HANDLE,RL,FALSE);\
     if (H_ERR_RL != H_MSG_OK)\
     {\
       (void)fprintf(stderr,"runlength error (%s) %s: #%d\n",\
		     IN_OUT,PROC,H_ERR_RL);\
       (void)fprintf(stderr,"runlength data dump in file: <<%s>>\n",RL_DUMP);\
       HCkP(HRLDump(PROC_HANDLE,RL,RL_DUMP));\
       return(H_ERR_RL);\
     }\
   }}
#endif



/* #define CStoreOutpObj(PROC_HANDLE,PAR,OBJ)\ */
/* { INT4   Num_obj_outp;\ */
/*   INT4   L_outplist;\ */
/*   INT    New_size;\ */
/*   HReadGV(PROC_HANDLE,HGNumObjOutp,&Num_obj_outp);\ */
/*   HWriteGVKA(PROC_HANDLE,HGOutpObjList,OBJ,Num_obj_outp);\ */
/*   HWriteGVA(PROC_HANDLE,HGOutpObjParList,PAR,Num_obj_outp);\ */
/*   if (Num_obj_outp >= MAX_OBJ_PER_PAR) return(H_ERR_OONTB);\ */
/*   Num_obj_outp++;\ */
/*   HWriteGV(PROC_HANDLE,HGNumObjOutp,Num_obj_outp);\ */
/*   HReadGV(PROC_HANDLE,HGLengthOutpObjList,&L_outplist);\ */
/*   if (Num_obj_outp >= L_outplist)\ */
/*   {\ */
/*     New_size = (INT)(2*L_outplist*sizeof(Hkey));\ */
/*     HReallocGVA(PROC_HANDLE,HGOutpObjList,New_size);\ */
/*     New_size = (INT)(2*L_outplist*sizeof(char));\ */
/*     HReallocGVA(PROC_HANDLE,HGOutpObjParList,New_size);\ */
/*     HWriteGV(PROC_HANDLE,HGLengthOutpObjList,2*L_outplist);\ */
/*   }\ */
/* } */

#define CStoreOutpObj(PH,PAR,OBJ) {                 \
  INT4   OutpObjNum = HGetGV_OutpObjNum_p(PH,PAR);  \
  INT4   OutpObjLen = HGetGV_OutpObjLen_p(PH,PAR);  \
  if (OutpObjNum >= OutpObjLen) {                   \
    size_t newSize = 2*(OutpObjLen+10);             \
    VOIDP newMem;                                   \
    HCkP(HRealloc(PH,HGetGV_OutpObjList_p(PH,PAR),  \
		  newSize*sizeof(Hkey),&newMem));   \
    HInitGV_OutpObjList_p(PH,PAR,(Hkey*)newMem);    \
    HWriteGV_OutpObjLen_p(PH,PAR,newSize);          \
  }                                                 \
  HWriteGV_OutpObjList_pi(PH,PAR,OutpObjNum,OBJ);   \
  HWriteGV_OutpObjNum_p(PH,PAR,++OutpObjNum);       \
}



#define CStoreCtrlVal(PROC_HANDLE,PAR,HCPAR)\
{INT4   Num_ctrl_outp;\
 INT4   L_outplist;\
 INT    New_size;\
  HReadGV(PROC_HANDLE,HGNumCtrlOutp,&Num_obj_outp);\
  HWriteGVKA(PROC_HANDLE,HGOutpObjList,OBJ,Num_obj_outp);\
  HWriteGVA(PROC_HANDLE,HGOutpObjParList,PAR,Num_obj_outp);\
  if (Num_obj_outp >= MAX_OBJ_PER_PAR) return(H_ERR_OONTB);\
  Num_obj_outp++;\
  HWriteGV(PROC_HANDLE,HGNumObjOutp,Num_obj_outp);\
  HReadGV(PROC_HANDLE,HGLengthOutpObjList,&L_outplist);\
  if (Num_obj_outp >= L_outplist)\
  {\
    New_size = (INT)(2*L_outplist*sizeof(Hkey));\
    HReallocGVA(PROC_HANDLE,HGOutpObjList,New_size);\
    New_size = (INT)(2*L_outplist*sizeof(char));\
    HReallocGVA(PROC_HANDLE,HGOutpObjParList,New_size);\
    HWriteGV(PROC_HANDLE,HGLengthOutpObjList,2*L_outplist);\
  }\
}




#define LongToNet(L,N) \
{ unsigned char  *HH; HH = (unsigned char*)&(N);\
  HH[0] = ((L) >> 24) & 255;\
  HH[1] = ((L) >> 16) & 255;\
  HH[2] = ((L) >> 8) & 255;\
  HH[3] = (L) & 255;\
}

#define NetToLong(N,L)\
{ unsigned char *HH; HH = (unsigned char*)&(N);\
 L = ((INT4)(HH[0]) << 24) |\
     ((INT4)(HH[1]) << 16) |\
     ((INT4)(HH[2]) << 8) |\
     ((INT4)(HH[3]));\
}

#define ShortToNet(S,N) \
{ unsigned char  *HH; HH = (unsigned char*)&(N);\
  HH[0] = ((S) >> 8) & 255;\
  HH[1] = (S) & 255;\
}

#define NetToShort(N,S)\
{ unsigned char *HH; HH = (unsigned char*)&(N);\
 S = ((short)(HH[0]) << 8) |\
     ((short)(HH[1]));\
}

#ifndef H_PARALLEL
#define HScale(PROC_HANDLE,TOscale) TOscale = ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->ZoomPixel

#define HScaleFWidth(PROC_HANDLE,L,Val) Val = ((L) / ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->PixelWidth)

#define HScaleFHeight(PROC_HANDLE,L,Val) Val = ((L) / ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->PixelHeight)

#define HRScaleLWidth(PROC_HANDLE,L,Val) Val = (((L) * ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->HeightMult) >> 20)

#define HRScaleLHeight(PROC_HANDLE,L,Val) Val = (((L) * ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->WidthMult) >> 20)

#define HRScaleFWidth(PROC_HANDLE,L,Val) Val = ((L) * ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->PixelWidth)

#define HRScaleFHeight(PROC_HANDLE,L,Val) Val = ((L) * ((Hproc_handle_)PROC_HANDLE)->sys_info_shared->PixelHeight)

#else
#define HScale(PROC_HANDLE,TOscale)\
 HReadGV(PROC_HANDLE,HGZoomPixel,&TOscale)

#define HScaleFWidth(PROC_HANDLE,L,Val)\
{float PixWid;\
 HReadGV(PROC_HANDLE,HGPixelWidth,&PixWid);\
 Val = (L) / PixWid;\
}
#define HScaleFHeight(PROC_HANDLE,L,Val)\
{float PixHei;\
 HReadGV(PROC_HANDLE,HGPixelHeight,&PixHei);\
 Val = (L) / PixHei;\
}
#define HRScaleLWidth(PROC_HANDLE,L,Val)\
{INT4 PixHeiMul;\
 HReadGV(PROC_HANDLE,HGHeightMult,&PixHeiMul);\
 Val = (((L) * PixHeiMul) >> 20);\
}
#define HRScaleLHeight(PROC_HANDLE,L,Val)\
{INT4 PixWidMul;\
 HReadGV(PROC_HANDLE,HGWidthMult,&PixWidMul);\
 Val = (((L) * PixWidMul) >> 20);\
}
#define HRScaleFWidth(PROC_HANDLE,L,Val)\
{float PixWid;\
 HReadGV(PROC_HANDLE,HGPixelWidth,&PixWid);\
 Val = (L) * PixWid;\
}
#define HRScaleFHeight(PROC_HANDLE,L,Val)\
{float PixHei;\
 HReadGV(PROC_HANDLE,HGPixelHeight,&PixHei);\
 Val = (L) * PixHei;\
}
#endif

#define HAllocStringMem(PROC_HANDLE,SIZE) \
  HCkP(HPAllocStringMem(PROC_HANDLE,(size_t)SIZE))

#if !defined(NO_SPY) && !defined(SMALL)
#define HPutPar(PROC_HANDLE,P,K,V,N) {Herror Err;\
  Err = IOSpyPar(PROC_HANDLE,P,K,V,(INT4_8)(N),FALSE); \
  if (Err != H_MSG_OK) return(Err); \
  Err = HPPutPar(PROC_HANDLE,P,K,V,(INT4_8)(N));\
  if (Err != H_MSG_OK) return(Err); }
#else
#define HPutPar(PROC_HANDLE,P,K,V,N) {Herror Err;\
  Err = HPPutPar(PROC_HANDLE,P,K,V,(INT4_8)(N));\
  if (Err != H_MSG_OK) return(Err); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HPutCPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = IOSpyCPar(PROC_HANDLE,P,V,(INT4_8)N,FALSE); \
  if (Err != H_MSG_OK) return(Err); \
  Err = HPPutCPar(PROC_HANDLE,P,V,(INT4_8)(N));\
  if (Err != H_MSG_OK) return(Err); }
#else
#define HPutCPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = HPPutCPar(PROC_HANDLE,P,V,(INT4_8)(N));\
  if (Err != H_MSG_OK) return(Err); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HPutPPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = IOSpyCPar(PROC_HANDLE,P,V,(INT4_8)N,FALSE); \
  if (Err != H_MSG_OK) return(Err); \
  Err = HPPutPPar(PROC_HANDLE,P,V,N);\
  if (Err != H_MSG_OK) return(Err); }
#else
#define HPutPPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = HPPutPPar(PROC_HANDLE,P,V,N);\
  if (Err != H_MSG_OK) return(Err); }
#endif

#define HGetCParNum(PROC_HANDLE,Par,Num) {Herror Err;\
  Err = HPGetCParNum(PROC_HANDLE,Par,Num);\
  if (Err != H_MSG_OK) return(Err); }


/* macros for accessing input parameters
 *  - without copying
 *  - with type and/or number check
 *===========================================================================*/

/* HGetPParN:
 *   specify the exact number of the read parameter (any type)
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPParN(PROC_HANDLE,PAR,NUM,VAL) {                \
  INT4_8 num;                                               \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);         \
  if (err != H_MSG_OK)            return err;               \
  if (NUM != num)                 return H_ERR_WIPN ## PAR; \
  err = IOSpyCPar(PROC_HANDLE,PAR,VAL?*VAL:NULL,num,TRUE);  \
  if (err != H_MSG_OK) return err;                          }
#else
#define HGetPParN(PROC_HANDLE,PAR,NUM,VAL) {                \
  INT4_8 num;                                               \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);         \
  if (err != H_MSG_OK)            return err;               \
  if (NUM != num)                 return H_ERR_WIPN ## PAR; }
#endif


/* HGetPParMM:
 *    the value number of the read parameter is expected to be within a
 *    certain range
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPParMM(PROC_HANDLE,PAR,MIN,MAX,VAL,NUM) {       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);          \
  if (err != H_MSG_OK)            return err;               \
  if (*NUM < MIN || *NUM > MAX)   return H_ERR_WIPN ## PAR; \
  err = IOSpyCPar(PROC_HANDLE,PAR,VAL?*VAL:NULL,num,TRUE);  \
  if (err != H_MSG_OK) return err;                          }
#else
#define HGetPParMM(PROC_HANDLE,PAR,MIN,MAX,VAL,NUM) {       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);          \
  if (err != H_MSG_OK)            return err;               \
  if (*NUM < MIN || *NUM > MAX)   return H_ERR_WIPN ## PAR; }
#endif


/* HGetPParT:
 *   specify the expected type(s) of the read parameter
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPParT(PROC_HANDLE,PAR,TYPE,VAL) {                          \
  INT4_8 i, num;                                                       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);                    \
  if (err != H_MSG_OK)                    return err;                  \
  if (*(VAL))                                                          \
    for (i=0; i<num; i++)                                              \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  \
  err = IOSpyCPar(PROC_HANDLE,PAR,(VAL) ? *(VAL) : NULL,num,TRUE);     \
  if (err != H_MSG_OK) return err;                                     }
#else
#define HGetPParT(PROC_HANDLE,PAR,TYPE,VAL) {                          \
  INT4_8 i, num;                                                       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);                    \
  if (err != H_MSG_OK)                    return err;                  \
  if (*(VAL))                                                          \
    for (i=0; i<num; i++)                                              \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  }
#endif


/* HGetPParTN:
 *   specify the exact number and the expected type(s) of the read parameter
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPParTN(PROC_HANDLE,PAR,TYPE,NUM,VAL) {                     \
  INT4_8 i, num;                                                       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);                    \
  if (err != H_MSG_OK)                    return err;                  \
  if ((NUM) != num)                       return H_ERR_WIPN ## PAR;    \
  if (*(VAL))                                                          \
    for (i=0; i<num; i++)                                              \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  \
  err = IOSpyCPar(PROC_HANDLE,PAR,(VAL) ? *(VAL) : NULL,num,TRUE);     \
  if (err != H_MSG_OK) return err;                                     }
#else
#define HGetPParTN(PROC_HANDLE,PAR,TYPE,NUM,VAL) {                     \
  INT4_8 i, num;                                                       \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,&num);                    \
  if (err != H_MSG_OK)                    return err;                  \
  if ((NUM) != num)                       return H_ERR_WIPN ## PAR;    \
  if (*(VAL))                                                          \
    for (i=0; i<num; i++)                                              \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  }
#endif


/* HGetPParTMM:
 *   specify a range for the number of the read parameters as well as
 *   the expected type(s)
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPParTMM(PROC_HANDLE,PAR,TYPE,MIN,MAX,VAL,NUM) {            \
  INT4_8 i;                                                            \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                     \
  if (err != H_MSG_OK)                    return err;                  \
  if (*(NUM) < MIN || *(NUM) > MAX)       return H_ERR_WIPN ## PAR;    \
  if (*(VAL))                                                          \
    for (i=0; i<*(NUM); i++)                                           \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  \
  err = IOSpyCPar(PROC_HANDLE,PAR,(VAL) ? *(VAL) : NULL,*(NUM),TRUE);  \
  if (err != H_MSG_OK) return err;                                     }
#else
#define HGetPParTMM(PROC_HANDLE,PAR,TYPE,MIN,MAX,VAL,NUM) {            \
  INT4_8 i;                                                            \
  Herror err = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                     \
  if (err != H_MSG_OK)                    return err;                  \
  if (*(NUM) < MIN || *(NUM) > MAX)       return H_ERR_WIPN ## PAR;    \
  if (*(VAL))                                                          \
    for (i=0; i<*(NUM); i++)                                           \
      if (((TYPE) & (*(VAL))[i].type) == 0) return H_ERR_WIPT ## PAR;  }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = HPGetPPar(PROC_HANDLE,P,V,N);\
  if (Err != H_MSG_OK) return(Err); \
  Err = IOSpyCPar(PROC_HANDLE,P,*V,*N,TRUE); \
  if (Err != H_MSG_OK) return(Err); }
#else
#define HGetPPar(PROC_HANDLE,P,V,N) {Herror Err;\
  Err = HPGetPPar(PROC_HANDLE,P,V,N);\
  if (Err != H_MSG_OK) return(Err); }
#endif



#if !defined(NO_SPY) && !defined(SMALL)
#define HGetPar(PROC_HANDLE,Par,Kind,Val,Num) {Herror ERR;\
  ERR = HPGetPar(PROC_HANDLE,Par,ANY_PAR,Kind,Val,(INT4_8)0,\
                 (INT4_8)10000000,Num);\
  if (ERR != H_MSG_OK) return(ERR);\
  ERR = IOSpyCPar(PROC_HANDLE,Index,Val,*(Num),TRUE);\
  if (ERR != H_MSG_OK) return(ERR); }
#else
#define HGetPar(Par,Kind,Val,Num) {Herror ERR;\
  ERR = HPGetPar(Par,ANY_PAR,Kind,Val,(INT4_8)0,\
                 (INT4_8)10000000,Num);\
  if (ERR != H_MSG_OK) return(ERR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HGetSPar(PROC_HANDLE,Index,Type,Val,N) {INT4_8 Hn; Herror Err;\
  Err = HPGetCPar(PROC_HANDLE,Index,Type,Val,(INT4_8)(N),(INT4_8)(N),&Hn);\
  if (Err != H_MSG_OK) return(Err); \
  Err = IOSpyCPar(PROC_HANDLE,Index,Val,Hn,TRUE); \
  if (Err != H_MSG_OK) return(Err); }
#else
#define HGetSPar(PROC_HANDLE,Index,Type,Val,N) {INT4_8 Hn; Herror Err;\
  Err = HPGetCPar(PROC_HANDLE,Index,Type,Val,(INT4_8)(N),(INT4_8)(N),&Hn);\
  if (Err != H_MSG_OK) return(Err); }
#endif


#if !defined(NO_SPY) && !defined(SMALL)
#define HGetCPar(PROC_HANDLE,Index,InpType,Val,Min,Max,ResNum) {Herror Err;\
  Err = HPGetCPar(PROC_HANDLE,Index,InpType,Val,(INT4_8)(Min),\
                              (INT4_8)(Max),ResNum);\
  if (Err != H_MSG_OK) return(Err); \
  Err = IOSpyCPar(PROC_HANDLE,Index,Val,(INT4_8)*ResNum,TRUE); \
  if (Err != H_MSG_OK) return(Err); }
#else
#define HGetCPar(PROC_HANDLE,Index,InpType,Val,Min,Max,ResNum) {Herror Err;\
  Err = HPGetCPar(PROC_HANDLE,Index,InpType,Val,(INT4_8)(Min),\
                              (INT4_8)(Max),ResNum);\
  if (Err != H_MSG_OK) return(Err); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HGetFPar(PROC_HANDLE,Index,Type,Val,Num) {int Ht; INT4_8 Hn; Herror Err;\
  Err = HPGetPar(PROC_HANDLE,Index,Type,&Ht,Val,(INT4_8)(Num),\
                 (INT4_8)(Num),&Hn);\
  if (Err != H_MSG_OK) return(Err); \
  Err = IOSpyPar(PROC_HANDLE,Index,Ht,Val,Hn,TRUE); \
  if (Err != H_MSG_OK) return(Err); }
#else
#define HGetFPar(PROC_HANDLE,Index,Type,Val,Num) {int Ht; INT4_8 Hn; Herror Err;\
  Err = HPGetPar(PROC_HANDLE,Index,Type,&Ht,Val,(INT4_8)(Num),\
                 (INT4_8)(Num),&Hn);\
  if (Err != H_MSG_OK) return(Err); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
#define HGetEPar(PROC_HANDLE,Index,InpType,ResType,Val,Min,Max,Num) {Herror Err;\
  Err = HPGetPar(PROC_HANDLE,Index,InpType,ResType,Val,(INT4_8)(Min),\
                 (INT4_8)(Max),Num);\
  if (Err != H_MSG_OK) return(Err); \
  Err = IOSpyPar(PROC_HANDLE,Index,*ResType,Val,(INT4_8)*Num,TRUE); \
  if (Err != H_MSG_OK) return(Err); }
#else
#define HGetEPar(PROC_HANDLE,Index,InpType,ResType,Val,Min,Max,Num) {Herror Err;\
  Err = HPGetPar(PROC_HANDLE,Index,InpType,ResType,Val,(INT4_8)(Min),\
                 (INT4_8)(Max),Num);\
  if (Err != H_MSG_OK) return(Err); }
#endif


#define HNumOfChannels(PROC_HANDLE,OBJ,NUM) HCkP(HPNumOfChannels(PROC_HANDLE,(INT)1,\
                                             (INT4_8)OBJ,NUM))

#define HAllObj(PROC_HANDLE,VAR,Hkey,I) I=0;\
  while ((HCheckObjNum(PROC_HANDLE,VAR,I+1) == TRUE) && \
         (HPGetObj(PROC_HANDLE,VAR,(INT4_8)++I, &Hkey) == H_MSG_OK) && \
         (Hkey != H_UNDEFINED))

#define HAllSegm(PROC_HANDLE,RL,IMAGES,MAX_CHANNELS,I) I=0; \
  while ((HCheckObjNum(PROC_HANDLE,1,I+1) == TRUE) && \
         (HPAllSegm(PROC_HANDLE,(INT4_8)++I,RL,IMAGES,MAX_CHANNELS) == H_MSG_OK))

#define HAllReg(PROC_HANDLE,RL,I) I=0; \
  while ((HCheckObjNum(PROC_HANDLE,1,I+1) == TRUE) && \
         (HPAllReg(PROC_HANDLE,(INT4_8)++I,RL) == H_MSG_OK))

#define HAllFilter(PROC_HANDLE,RL,IMA_IN,IMA_OUT,MAX_CHANNELS,I) I=0; \
  while ((HCheckObjNum(PROC_HANDLE,1,I+1) == TRUE) && \
         (HPAllFilter(PROC_HANDLE,(INT4_8)++I,RL,IMA_IN,IMA_OUT,MAX_CHANNELS) == H_MSG_OK))

#define HAllComp(PROC_HANDLE,OBJ_IN,IM_IN_KEY,IM_IN,INDEX) \
  HPGetComp(PROC_HANDLE,OBJ_IN,IMAGE_INDEX,&IM_IN_KEY); \
  if (IM_IN_KEY == H_UNDEFINED) return(H_ERR_AUDI); \
  for(INDEX = IMAGE_INDEX; \
      (HPGetComp(PROC_HANDLE,OBJ_IN,INDEX,&IM_IN_KEY) == H_MSG_OK) && \
        (IM_IN_KEY != H_UNDEFINED) && \
        HPGetImage(PROC_HANDLE,IM_IN_KEY,&IM_IN) == H_MSG_OK; \
          INDEX++)

#define HIfFirstComp(INDEX)  if(INDEX == IMAGE_INDEX)

#define HAllFilter2(PROC_HANDLE,RL,IMA_IN1,IMA_IN2,IMA_OUT,MAX_CHANNELS,I) I=0; \
  while ((HCheckObjNum(PROC_HANDLE,1,I+1) == TRUE) && \
         (HPAllFilter2(PROC_HANDLE,(INT4_8)++I,RL,IMA_IN1,IMA_IN2,IMA_OUT,MAX_CHANNELS) == H_MSG_OK))

#define HGetFRL(PROC_HANDLE,Key,region) \
  HCkP(HPGetFRL(PROC_HANDLE,Key,region))

#define HGetRL(PROC_HANDLE,Key,region) \
  HCkP(HPGetRL(PROC_HANDLE,Key,region))

#define HGetFDRL(PROC_HANDLE,Key,region) \
  HCkP(HPGetFDRL(PROC_HANDLE,Key,region))

#define HGetDRL(PROC_HANDLE,Key,region) \
  HCkP(HPGetDRL(PROC_HANDLE,Key,region))

#define HGetURL(PROC_HANDLE,Par,region) \
  HCkP(HPGetURL(PROC_HANDLE,Par,region))

#define HGetImage(PROC_HANDLE,Key,Image) \
  HCkP(HPGetImage(PROC_HANDLE,Key,Image))

#define HGetDImage(PROC_HANDLE,Key,Comp,Image) \
  HCkP(HPGetDImage(PROC_HANDLE,Key,Comp,Image))

#define HDelObj(PROC_HANDLE,Key) HCkP(HPDelObj(PROC_HANDLE,Key))

#define HNewRegion(PROC_HANDLE,RL) HCkP(HPNewRegion(PROC_HANDLE,RL))

#define HDupObj(PROC_HANDLE,INDEX) HCkP(HPDupObj(PROC_HANDLE,INDEX))

#define HPutDRL(PROC_HANDLE,Key,RL,KEY_PTR) HCkP(HPPutDRL(PROC_HANDLE,Key,RL,KEY_PTR));

#define HPutRect(PROC_HANDLE,Key,W,H) HCkP(HPPutRect(PROC_HANDLE,Key,W,H));

#define HPutImage(PROC_HANDLE,Image,Copy,KEY_PTR) \
  HCkP(HPPutImage(PROC_HANDLE,Image,Copy,KEY_PTR));

#define HPutDImage(PROC_HANDLE,Key,Comp,Image,Copy,KEY_PTR) \
  HCkP(HPPutDImage(PROC_HANDLE,Key,Comp,Image,Copy,KEY_PTR));

#define HDefObj(PROC_HANDLE,Obj,Key,Comp) \
  HCkP(HPDefObj(PROC_HANDLE,Obj,Key,Comp));

#define HCrObj(PROC_HANDLE,Par,KEY_PTR) HCkP(HPCrObj(PROC_HANDLE,Par,KEY_PTR));

#define HCopyObj(PROC_HANDLE,Key,Par,KEY_PTR) \
  HCkP(HPCopyObj(PROC_HANDLE,Key,Par,KEY_PTR));

#define HGetObj(PROC_HANDLE,Par,Num,KEY_PTR) \
  HCkP(HPGetObj(PROC_HANDLE,Par,(INT4_8)Num,KEY_PTR));

#define HGetObjNum(PROC_HANDLE,Par,Num) \
  HCkP(HPGetObjNum(PROC_HANDLE,Par,Num));

#define HGetComp(PROC_HANDLE,Obj,CompId,Id) HCkP(HPGetComp(PROC_HANDLE,Obj,CompId,Id));

#define HGetXLD(PROC_HANDLE,DBKEY,TYPE,XLD) { INT TMP_TYPE; INT NUM_USES; Hkey *USES;\
  HCkP(HPGetXLD(PROC_HANDLE,DBKEY,&TMP_TYPE,XLD,&USES,&NUM_USES)); \
  if (TYPE != TMP_TYPE) return(H_ERR_XLDWT); }

#define HGetSXLD(PROC_HANDLE,DBKEY,TYPE,XLD) { INT NUM_USES; Hkey *USES;\
  HCkP(HPGetXLD(PROC_HANDLE,DBKEY,TYPE,XLD,&USES,&NUM_USES)); }

#define HCrXLD(PROC_HANDLE,PAR,XLD,TYPE,USES,NUM_USES,FREE,KEY_PTR) \
  HCkP(HPCrXLD(PROC_HANDLE,PAR,XLD,TYPE,USES,NUM_USES,FREE,KEY_PTR)); 

#define Hisqrt(Val,Res) if (HROInfo.HSqrtTab == NULL) \
  { HCkP(HXAlloc(GLOBAL_ID,(size_t)(MAX_HSQRT * sizeof(HBYTE)),\
                __FILE__,(INT4_8)__LINE__,H_GLOBAL_ALLOC,\
                (VOIDP*)&(HROInfo.HSqrtTab))); \
    if (HROInfo.HSqrtTab != NULL) \
    { int II; for (II=0; II < MAX_HSQRT; II++) \
      HROInfo.HSqrtTab[II] = (HBYTE)(sqrt((double)II) + 0.5); \
    } \
    Res = (INT)(sqrt((double)(Val)) + 0.5); \
  } \
  else \
  { \
    INT4_8 TMP; TMP = (Val); \
    if (TMP < MAX_HSQRT) Res = (INT)HROInfo.HSqrtTab[TMP]; \
    else Res = (INT)(sqrt((double)TMP) + 0.5); \
  }
      
#define Hfsqrt(Val,Res) if (HROInfo.HSqrtTab == NULL) \
  { HCkP(HXAlloc(GLOBAL_ID,(size_t)(MAX_HSQRT * sizeof(HBYTE)),\
                __FILE__,(INT4_8)__LINE__,H_GLOBAL_ALLOC,\
                (VOIDP*)&(HROInfo.HSqrtTab))); \
    if (HROInfo.HSqrtTab != NULL) \
    { int i; for (i=0; i < MAX_HSQRT; i++) \
      HROInfo.HSqrtTab[i] = (HBYTE)(sqrt((double)i) + 0.5); \
    } \
    Res = (INT)(sqrt((double)(Val)) + 0.5); \
  } \
  else \
  { \
    double TMP = (Val);  /* double wegen moeglichem Ueberlauf */\
    if ((TMP + 0.5) < (double)MAX_HSQRT)\
      Res = (INT)HROInfo.HSqrtTab[(INT)((TMP) + 0.5)]; \
    else \
      Res = (INT)(sqrt(TMP) + 0.5); \
  }

/* -------- Makros for accessing HALCON operator context information ------- */
/* write a global context Variable ('normal' variable)                       */
#define HWriteGV(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write a global context Variable (String)                                  */
#define HWriteGVS(ProcHandle,Element,String) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,String,(Hkey)NULL,0))
/* write a global context variable (String in element of Array)              */
#define HWriteGVSA(ProcHandle,Element,String,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,String,(Hkey)NULL,Index))
/* write a global context variable (HALCON object Key in element of Array)   */
#define HWriteGVKA(ProcHandle,Element,Key,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,(char *)NULL,Key,Index))
/* write a global context variable (Pointer in element of Array)             */
#define HWriteGVPA(ProcHandle,Element,Pointer,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,Pointer,(double)0,(char *)NULL,NULL,Index))
/* write a global context variable (element of Array)                        */
#define HWriteGVA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* write a global context Variable ('normal' variable); force changement of  */
/* the corresponding reference version                                       */
#define HWriteGVF(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_FORCE,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* read a global context Variable ('normal' variable)                        */
#define HReadGV(ProcHandle,Element,Buffer) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Buffer,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read a global context Variable (element of Array)                         */
#define HReadGVA(ProcHandle,Element,Buffer,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Buffer,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize a global context Variable (Array)                              */
#define HInitGVA(ProcHandle,Element,Address) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Address,(double)0,(char *)NULL,(Hkey)NULL,0))
/* get the address of a global context Variable (Array)                      */
#define HGetAddrGVA(ProcHandle,Element,Buffer) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_GET_ADRESS,Buffer,(double)0,(char *)NULL,(Hkey)NULL,0))
/* realloc the memory of a global context Variable (Array)                   */
#define HReallocGVA(ProcHandle,Element,NewSize) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_REALLOC_A,NULL,(double)0,(char *)NULL,(Hkey)NULL,NewSize))


/*
 * direct access to the global resp. privat variables
 *===========================================================================*/


/* H_OPERATOR_INFO HProcInfo[->proc_index]
 *---------------------------------------------------------------------------*/

#define HGetGV_LogicalName(PH)   \
  HProcInfo[HGetGV_proc_index(PH)].LogicalName
#define HGetGV_Proc(PH)   \
  HProcInfo[HGetGV_proc_index(PH)].Proc
#define HGetGV_NumInpObjPar(PH)   \
  HProcInfo[HGetGV_proc_index(PH)].NumInpObjPar
#define HGetGV_NumOutpObjPar(PH)  \
  HProcInfo[HGetGV_proc_index(PH)].NumOutpObjPar
#define HGetGV_NumInpCtrlPar(PH)  \
  HProcInfo[HGetGV_proc_index(PH)].NumInpCtrlPar
#define HGetGV_NumOutpCtrlPar(PH) \
  HProcInfo[HGetGV_proc_index(PH)].NumOutpCtrlPar

/* ->HGetGV_proc_index: INT4 */
#define HGetGV_proc_index(PH)              (((Hproc_handle_)PH)->proc_index)
#define HReadGV_proc_index(PH,VAR)         (VAR=HGetGV_proc_index(PH))
#define HWriteGV_proc_index(PH,VAR)        (HGetGV_proc_index(PH)=VAR)

/* H_INSTANCE_INFO_EXCLUSIVE *info_excl
 *---------------------------------------------------------------------------*/

/* ->obj_images: INT2 */
#define HGetGV_obj_images(PH)      (((Hproc_handle_)PH)->info_excl->obj_images)
#define HReadGV_obj_images(PH,VAR)         (VAR=HGetGV_obj_images(PH))
#define HWriteGV_obj_images(PH,VAR)        (HGetGV_obj_images(PH)=VAR)

/* ->def_obj_images: INT2 */
#define HGetGV_def_obj_images(PH) \
                               (((Hproc_handle_)PH)->info_excl->def_obj_images)
#define HReadGV_def_obj_images(PH,VAR)     (VAR=HGetGV_def_obj_images(PH))
#define HWriteGV_def_obj_images(PH,VAR)    (HGetGV_def_obj_images(PH)=VAR)

/* ->ctrl_inherited: HBOOL */
#define HGetGV_ctrl_inherited(PH) \
                               (((Hproc_handle_)PH)->info_excl->ctrl_inherited)
#define HReadGV_ctrl_inherited(PH,VAR)     (VAR=HGetGV_ctrl_inherited(PH))
#define HWriteGV_ctrl_inherited(PH,VAR)    (HGetGV_ctrl_inherited(PH)=VAR)

/* ->Mem_handle: VOIDP */
#define HGetGV_Mem_handle(PH)      (((Hproc_handle_)PH)->info_excl->Mem_handle)
#define HReadGV_Mem_handle(PH,VAR)         (VAR=HGetGV_Mem_handle(PH))
#define HWriteGV_Mem_handle(PH,VAR)        (HGetGV_Mem_handle(PH)=VAR)

/* ->DB_handle: VOIDP */
#define HGetGV_DB_handle(PH)        (((Hproc_handle_)PH)->info_excl->DB_handle)
#define HReadGV_DB_handle(PH,VAR)          (VAR=HGetGV_DB_handle(PH))
#define HWriteGV_DB_handle(PH,VAR)         (HGetGV_DB_handle(PH)=VAR)

/* ->InpObjList: Hkey*[(0..)1..NumInpObjPar(..MAX_INP_OBJ_PAR+1)] */
#define HGetGV_InpObjList(PH)      (((Hproc_handle_)PH)->info_excl->InpObjList)
#define HGetGV_InpObjList_p(PH,PAR)      (HGetGV_InpObjList(PH)[PAR])
#define HGetGV_InpObjList_pi(PH,PAR,IDX) (HGetGV_InpObjList_p(PH,PAR)[IDX])
#define HReadGV_InpObjList_pi(PH,PAR,IDX,VAR) \
                                         (VAR=HGetGV_InpObjList_pi(PH,PAR,IDX))
#define HInitGV_InpObjList_p(PH,PAR,VAR) (HGetGV_InpObjList_p(PH,PAR)=VAR)

/* ->InpObjNum: INT4[(0..)1..NumInpObjPar(..MAX_INP_OBJ_PAR+1)] */
#define HGetGV_InpObjNum(PH)        (((Hproc_handle_)PH)->info_excl->InpObjNum)
#define HGetGV_InpObjNum_p(PH,PAR)         (HGetGV_InpObjNum(PH)[PAR])
#define HReadGV_InpObjNum_p(PH,PAR,VAR)    (VAR=HGetGV_InpObjNum_p(PH,PAR))
#define HWriteGV_InpObjNum_p(PH,PAR,VAR)   (HGetGV_InpObjNum_p(PH,PAR)=VAR)

/* ->InpCtrlList: Hctuple[] */
#define HGetGV_InpCtrlList(PH)    (((Hproc_handle_)PH)->info_excl->InpCtrlList)
#define HGetGV_InpCtrlList_p(PH,PAR)       (HGetGV_InpCtrlList(PH)+PAR)
#define HReadGV_InpCtrlList_p(PH,PAR,VAR)  (VAR=HGetGV_InpCtrlList_p(PH,PAR))
#define HInitGV_InpCtrlList(PH,VAR)        (HGetGV_InpCtrlList(PH)=VAR)

/* ->OutpObjList: Hkey*[(0..)1..NumOutpObjPar(..MAX_OUTP_OBJ_PAR+1)] */
#define HGetGV_OutpObjList(PH)    (((Hproc_handle_)PH)->info_excl->OutpObjList)
#define HGetGV_OutpObjList_p(PH,PAR)       (HGetGV_OutpObjList(PH)[PAR])
#define HGetGV_OutpObjList_pi(PH,PAR,IDX)  (HGetGV_OutpObjList_p(PH,PAR)[IDX])
#define HReadGV_OutpObjList_pi(PH,PAR,IDX,VAR) \
                                        (VAR=HGetGV_OutpObjList_pi(PH,PAR,IDX))
#define HWriteGV_OutpObjList_pi(PH,PAR,IDX,VAR) \
                                        (HGetGV_OutpObjList_pi(PH,PAR,IDX)=VAR)
#define HInitGV_OutpObjList_p(PH,PAR,VAR)  (HGetGV_OutpObjList_p(PH,PAR)=VAR)

/* ->OutpObjNum: INT4[(0..)1..NumOutpObjPar(..MAX_OUTP_OBJ_PAR+1)] */
#define HGetGV_OutpObjNum(PH)      (((Hproc_handle_)PH)->info_excl->OutpObjNum)
#define HGetGV_OutpObjNum_p(PH,PAR)        (HGetGV_OutpObjNum(PH)[PAR])
#define HReadGV_OutpObjNum_p(PH,PAR,VAR)   (VAR=HGetGV_OutpObjNum_p(PH,PAR))
#define HWriteGV_OutpObjNum_p(PH,PAR,VAR)  (HGetGV_OutpObjNum_p(PH,PAR)=VAR)

/* ->OutpObjLen: INT4[(0..)1..LenOutpObjPar(..MAX_OUTP_OBJ_PAR+1)] */
#define HGetGV_OutpObjLen(PH)      (((Hproc_handle_)PH)->info_excl->OutpObjLen)
#define HGetGV_OutpObjLen_p(PH,PAR)        (HGetGV_OutpObjLen(PH)[PAR])
#define HReadGV_OutpObjLen_p(PH,PAR,VAR)   (VAR=HGetGV_OutpObjLen_p(PH,PAR))
#define HWriteGV_OutpObjLen_p(PH,PAR,VAR)  (HGetGV_OutpObjLen_p(PH,PAR)=VAR)

/* ->OutpCtrlList: Hctuple[] */
#define HGetGV_OutpCtrlList(PH) (((Hproc_handle_)PH)->info_excl->OutpCtrlList)
#define HGetGV_OutpCtrlList_p(PH,PAR)      (HGetGV_OutpCtrlList(PH)+PAR)
#define HReadGV_OutpCtrlList_p(PH,PAR,VAR) (VAR=HGetGV_OutpCtrlList_p(PH,PAR))
#define HInitGV_OutpCtrlList(PH,VAR)       (HGetGV_OutpCtrlList(PH)=VAR)

/* ->usedOCP: HBOOL */
#define HGetGV_usedOCP(PH)            (((Hproc_handle_)PH)->info_excl->usedOCP)
#define HGetGV_usedOCP_p(PH,PAR)           (HGetGV_usedOCP(PH)[PAR])
#define HReadGV_usedOCP_p(PH,PAR,VAR)      (VAR=HGetGV_usedOCP_p(PH,PAR))
#define HWriteGV_usedOCP_p(PH,PAR,VAR)     (HGetGV_usedOCP_p(PH,PAR)=VAR)

/* ->StringMem: char* */
#define HGetGV_StringMem(PH)        (((Hproc_handle_)PH)->info_excl->StringMem)
#define HReadGV_StringMem(PH,VAR)          (VAR=HGetGV_StringMem(PH))
#define HWriteGV_StringMem(PH,VAR)         strcpy(HGetGV_StringMem(PH),VAR)
#define HInitGV_StringMem(PH,VAR)          (HGetGV_StringMem(PH)=VAR)

/* ->LastStringMem: char* */
#define HGetGV_LastStringMem(PH) \
                                (((Hproc_handle_)PH)->info_excl->LastStringMem)
#define HReadGV_LastStringMem(PH,VAR)      (VAR=HGetGV_LastStringMem(PH))
#define HWriteGV_LastStringMem(PH,VAR)     strcpy(HGetGV_StringMem(PH),VAR)
#define HInitGV_LastStringMem(PH,VAR)      (HGetGV_LastStringMem(PH)=VAR)

/* ->parallel_method: INT */
#define HGetGV_parallel_method(PH)         (((Hproc_handle_)PH)->info_excl->parallel_method)
#define HReadGV_parallel_method(PH,VAR)    (VAR=HGetGV_parallel_method(PH))
#define HWriteGV_parallel_method(PH,VAR)   (HGetGV_parallel_method(PH)=VAR)

/* H_INSTANCE_INFO_SHARED  *info_shared
 *---------------------------------------------------------------------------*/

/* ->CompactObj: HBOOL */
#define HGetGV_CompactObj(PH)    (((Hproc_handle_)PH)->info_shared->CompactObj)
#define HReadGV_CompactObj(PH,VAR)         (VAR=HGetGV_CompactObj(PH))
#define HWriteGV_CompactObj(PH,VAR)        (HGetGV_CompactObj(PH)=VAR)

/* ->NewFilter: HBOOL */
#define HGetGV_NewFilter(PH)      (((Hproc_handle_)PH)->info_shared->NewFilter)
#define HReadGV_NewFilter(PH,VAR)          (VAR=HGetGV_NewFilter(PH))
#define HWriteGV_NewFilter(PH,VAR)         (HGetGV_NewFilter(PH)=VAR)

/* ->nf_inp_key: Hkey* */
#define HGetGV_nf_inp_key(PH)    (((Hproc_handle_)PH)->info_shared->nf_inp_key)
#define HGetGV_nf_inp_key_i(PH,IDX)        (HGetGV_nf_inp_key(PH)[IDX])
#define HReadGV_nf_inp_key_i(PH,IDX,VAR)   (VAR=HGetGV_nf_inp_key_i(PH,IDX))
#define HWriteGV_nf_inp_key_i(PH,IDX,VAR)  (HGetGV_nf_inp_key_i(PH,IDX)=VAR)
#define HInitGV_nf_inp_key(PH,VAR)         (HGetGV_nf_inp_key(PH)=VAR)

/* ->nf_rem_inp_keys: Hkey* */
#define HGetGV_nf_rem_inp_keys(PH) (((Hproc_handle_)PH)->info_shared->\
                                      nf_rem_inp_keys)
#define HGetGV_nf_rem_inp_keys_i(PH,IDX)   (HGetGV_nf_rem_inp_keys(PH)[IDX])
#define HReadGV_nf_rem_inp_keys_i(PH,IDX,VAR) \
          (VAR=HGetGV_nf_rem_inp_keys_i(PH,IDX))
#define HWriteGV_nf_rem_inp_keys_i(PH,IDX,VAR) \
          (HGetGV_nf_rem_inp_keys_i(PH,IDX)=VAR)
#define HInitGV_nf_rem_inp_keys(PH,VAR)    (HGetGV_nf_rem_inp_keys(PH)=VAR)

/* ->nf_index: INT2* */
#define HGetGV_nf_index(PH)        (((Hproc_handle_)PH)->info_shared->nf_index)
#define HGetGV_nf_index_i(PH,IDX)          (HGetGV_nf_index(PH)[IDX])
#define HReadGV_nf_index_i(PH,IDX,VAR)     (VAR=HGetGV_nf_index_i(PH,IDX))
#define HWriteGV_nf_index_i(PH,IDX,VAR)    (HGetGV_nf_index_i(PH,IDX)=VAR)
#define HInitGV_nf_index(PH,VAR)           (HGetGV_nf_index(PH)=VAR)

/* ->nf_img_type: INT2* */
#define HGetGV_nf_img_type(PH)  (((Hproc_handle_)PH)->info_shared->nf_img_type)
#define HGetGV_nf_img_type_i(PH,IDX)       (HGetGV_nf_img_type(PH)[IDX])
#define HReadGV_nf_img_type_i(PH,IDX,VAR)  (VAR=HGetGV_nf_img_type_i(PH,IDX))
#define HWriteGV_nf_img_type_i(PH,IDX,VAR) (HGetGV_nf_img_type_i(PH,IDX)=VAR)
#define HInitGV_nf_img_type(PH,VAR)        (HGetGV_nf_img_type(PH)=VAR)

/* ->nf_out: Hkey* */
#define HGetGV_nf_out(PH)            (((Hproc_handle_)PH)->info_shared->nf_out)
#define HGetGV_nf_out_i(PH,IDX)            (HGetGV_nf_out(PH)[IDX])
#define HReadGV_nf_out_i(PH,IDX,VAR)       (VAR=HGetGV_nf_out_i(PH,IDX))
#define HWriteGV_nf_out_i(PH,IDX,VAR)      (HGetGV_nf_out_i(PH,IDX)=VAR)
#define HInitGV_nf_out(PH,VAR)             (HGetGV_nf_out(PH)=VAR)

/* ->nf_image1: float** */
#define HGetGV_nf_image1(PH)      (((Hproc_handle_)PH)->info_shared->nf_image1)
#define HGetGV_nf_image1_i(PH,IDX)         (HGetGV_nf_image1(PH)[IDX])
#define HReadGV_nf_image1_i(PH,IDX,VAR)    (VAR=HGetGV_nf_image1_i(PH,IDX))
#define HWriteGV_nf_image1_i(PH,IDX,VAR)   (HGetGV_nf_image1_i(PH,IDX)=VAR)
#define HInitGV_nf_image1(PH,VAR)          (HGetGV_nf_image1(PH)=VAR)

/* ->nf_image2: float** */
#define HGetGV_nf_image2(PH)      (((Hproc_handle_)PH)->info_shared->nf_image2)
#define HGetGV_nf_image2_i(PH,IDX)         (HGetGV_nf_image2(PH)[IDX])
#define HReadGV_nf_image2_i(PH,IDX,VAR)    (VAR=HGetGV_nf_image2_i(PH,IDX))
#define HWriteGV_nf_image2_i(PH,IDX,VAR)   (HGetGV_nf_image2_i(PH,IDX)=VAR)
#define HInitGV_nf_image2(PH,VAR)          (HGetGV_nf_image2(PH)=VAR)

/* ->nf_num: INT4 */
#define HGetGV_nf_num(PH)            (((Hproc_handle_)PH)->info_shared->nf_num)
#define HReadGV_nf_num(PH,VAR)             (VAR=HGetGV_nf_num(PH))
#define HWriteGV_nf_num(PH,VAR)            (HGetGV_nf_num(PH)=VAR)

/* ->nf_num_alloc: INT4 */
#define HGetGV_nf_num_alloc(PH) \
                               (((Hproc_handle_)PH)->info_shared->nf_num_alloc)
#define HReadGV_nf_num_alloc(PH,VAR)       (VAR=HGetGV_nf_num_alloc(PH))
#define HWriteGV_nf_num_alloc(PH,VAR)      (HGetGV_nf_num_alloc(PH)=VAR)



/* H_SYS_INFO_EXCLUSIVE  *sys_info_excl
 *---------------------------------------------------------------------------*/

/* ->imsize: INT4 */
#define HGetGV_imsize(PH)          (((Hproc_handle_)PH)->sys_info_excl->imsize)
#define HReadGV_imsize(PH,VAR)             (VAR=HGetGV_imsize(PH))
#define HWriteGV_imsize(PH,VAR)            (HGetGV_imsize(PH)=VAR)

/* ->Width: INT4 */
#define HGetGV_Width(PH)            (((Hproc_handle_)PH)->sys_info_excl->Width)
#define HReadGV_Width(PH,VAR)              (VAR=HGetGV_Width(PH))
#define HWriteGV_Width(PH,VAR)             (HGetGV_Width(PH)=VAR)

/* ->Height: INT4 */
#define HGetGV_Height(PH)          (((Hproc_handle_)PH)->sys_info_excl->Height)
#define HReadGV_Height(PH,VAR)             (VAR=HGetGV_Height(PH))
#define HWriteGV_Height(PH,VAR)            (HGetGV_Height(PH)=VAR)

/* ->CurrentRL: INT4 */
#define HGetGV_CurrentRL(PH)    (((Hproc_handle_)PH)->sys_info_excl->CurrentRL)
#define HReadGV_CurrentRL(PH,VAR)          (VAR=HGetGV_CurrentRL(PH))
#define HWriteGV_CurrentRL(PH,VAR)         (HGetGV_CurrentRL(PH)=VAR)

/* ->ClipRegion: HBOOL */
#define HGetGV_ClipRegion(PH) \
                             (((Hproc_handle_)PH)->sys_info_excl->ClipRegion)
#define HReadGV_ClipRegion(PH,VAR)            (VAR=HGetGV_ClipRegion(PH))
#define HWriteGV_ClipRegion(PH,VAR)           (HGetGV_ClipRegion(PH)=VAR)

/* ->StoreEmptyRegion: HBOOL */
#define HGetGV_StoreEmptyRegion(PH) \
                       (((Hproc_handle_)PH)->sys_info_excl->StoreEmptyRegion)
#define HReadGV_StoreEmptyRegion(PH,VAR)      (VAR=HGetGV_StoreEmptyRegion(PH))
#define HWriteGV_StoreEmptyRegion(PH,VAR)     (HGetGV_StoreEmptyRegion(PH)=VAR)

/* ->InitNewImage: HBOOL */
#define HGetGV_InitNewImageNeighbour(PH)  \
                        (((Hproc_handle_)PH)->sys_info_excl->InitNewImage)
#define HReadGV_InitNewImage(PH,VAR)             (VAR=HGetGV_InitNewImage(PH))
#define HWriteGV_InitNewImage(PH,VAR)            (HGetGV_InitNewImage(PH)=VAR)

/* ->Neighbour: UINT1 */
#define HGetGV_Neighbour(PH)  (((Hproc_handle_)PH)->sys_info_excl->Neighbour)
#define HReadGV_Neighbour(PH,VAR)             (VAR=HGetGV_Neighbour(PH))
#define HWriteGV_Neighbour(PH,VAR)            (HGetGV_Neighbour(PH)=VAR)

/* ->DoIntZoom: HBOOL */
#define HGetGV_DoIntZoom(PH)  (((Hproc_handle_)PH)->sys_info_excl->DoIntZoom)
#define HReadGV_DoIntZoom(PH,VAR)             (VAR=HGetGV_DoIntZoom(PH))
#define HWriteGV_DoIntZoom(PH,VAR)            (HGetGV_DoIntZoom(PH)=VAR)

/* H_SYS_INFO_SHARED   *sys_info_shared
 *---------------------------------------------------------------------------*/

/* ->check: INT4 */
#define HGetGV_check(PH)          (((Hproc_handle_)PH)->sys_info_shared->check)
#define HReadGV_check(PH,VAR)                 (VAR=HGetGV_check(PH))

/* ->NoObjResult: Herror */
#define HGetGV_NoObjResult(PH) \
                            (((Hproc_handle_)PH)->sys_info_shared->NoObjResult)
#define HReadGV_NoObjResult(PH,VAR)           (VAR=HGetGV_NoObjResult(PH))

/* ->EmptyObjResult: Herror */
#define HGetGV_EmptyObjResult(PH) \
                         (((Hproc_handle_)PH)->sys_info_shared->EmptyObjResult)
#define HReadGV_EmptyObjResult(PH,VAR)        (VAR=HGetGV_EmptyObjResult(PH))

/* ->UpdateLUT: HBOOL */
#define HGetGV_UpdateLUT(PH)  (((Hproc_handle_)PH)->sys_info_shared->UpdateLUT)
#define HReadGV_UpdateLUT(PH,VAR)             (VAR=HGetGV_UpdateLUT(PH))

/* ->UsedModules: UINT4 */
#define HGetGV_UsedModules(PH) \
                            (((Hproc_handle_)PH)->sys_info_shared->UsedModules)
#define HReadGV_UsedModules(PH,VAR)           (VAR=HGetGV_UsedModules(PH))






/* lock a global context mutex variable                                      */
#define HLockGVM(ProcHandle,Element) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_LOCK,NULL,(double)0,(char *)NULL,(Hkey)NULL,0))
/* lock a global context mutex variable and directly return Herror result    */
#define HLockGVMdirect(ProcHandle,Element) \
HAccessGlVar(ProcHandle,Element,GV_LOCK,NULL,(double)0,(char *)NULL,(Hkey)NULL,0)
/* unlock a global context mutex variable                                    */
#define HUnlockGVM(ProcHandle,Element) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_UNLOCK,NULL,(double)0,(char *)NULL,(Hkey)NULL,0))
/* unlock a global context mutex variable and directly return Herror result  */
#define HUnlockGVMdirect(ProcHandle,Element) \
HAccessGlVar(ProcHandle,Element,GV_UNLOCK,NULL,(double)0,(char *)NULL,(Hkey)NULL,0)

/* lock the global proc handle */
#define HLockGlobalProcHandle \
  HLockGVMdirect(HGlobalProcHandle,HGmutex_globalhandle)
/* unlock the global proc handle */
#define HUnlockGlobalProcHandle \
  HUnlockGVMdirect(HGlobalProcHandle,HGmutex_globalhandle)

/* calculate 'bitwise OR' with the content of a global context variable      */
#define HBOrGV(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_BOR_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* calculate 'bitwise AND' with the content of a global context variable     */
#define HBAndGV(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_BAND_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* - - - -  old Makros for accessing HALCON operator context information - - */
/* (all accesses using the old makros should be replaced by the new ones in  */
/* the long term                                                             */
/* write an element of the global structure HInterInfo                       */
#define HWriteInterInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HInterInfo (String)              */
#define HWriteInterInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HInterInfo (String into Array)   */
#define HWriteInterInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HInterInfo (Array element)       */
#define HWriteInterInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* read an element of the global structure HInterInfo                        */
#define HReadInterInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HInterInfo (Array element)        */
#define HReadInterInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HInterInfo (Array element)  */
#define HInitInterInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HSysComInfo                      */
#define HWriteSysComInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HSysComInfo (String)             */
#define HWriteSysComInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HSysComInfo (String into Array)  */
#define HWriteSysComInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HSysComInfo (Array element)      */
#define HWriteSysComInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* read an element of the global structure HSysComInfo                       */
#define HReadSysComInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HSysComInfo (Array element)       */
#define HReadSysComInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HSysComInfo (Array element) */
#define HInitSysComInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo                    */
#define HWriteProcCallInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo (String)           */
#define HWriteProcCallInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo (String into Array)*/
#define HWriteProcCallInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HProcCallInfo (Key into Array)   */
#define HWriteProcCallInfoKA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,(char *)NULL,Value,Index))
/* write an element of the global structure HProcCallInfo (Array element)    */
#define HWriteProcCallInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* Lesen eines Elements der globalen Struktur HProcCallInfo                  */
#define HReadProcCallInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HProcCallInfo                     */
#define HReadProcCallInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HProcCallInfo (Array)       */
#define HInitProcCallInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* get the address of an array element of the global structure HProcCallInfo */
#define HGetAdrProcCallInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_GET_ADRESS,Value,(double)0,(char *)NULL,(Hkey)NULL,0))

#endif




