/*****************************************************************************
 * HAlloc.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Memory allocation
 *
 * (c) 1996-2001 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 * 
 * $Revision: 1.29 $
 * $Date: 2001/02/22 13:19:07 $
 *
 */

#ifndef HALLOC_H
#define HALLOC_H


#if defined(__cplusplus)
extern "C" {
#endif

/*===========================================================================*/
/*                                  Defines                                  */
/*===========================================================================*/
#define H_DEF_INIT_MEM_SIZE (size_t)(1024*1024) /* default size for HInitMem */
                                                /* no more in use! see below */

/* factor for memory allocation with HNewSpace():                            
   HInitMem()          -> 2*H_NEW_SPACE_FAC*MAX_SAVE
   else (HXAlloc())    ->   H_NEW_SPACE_FAC*MAX_SAVE                         */
#define H_NEW_SPACE_FAC 1024


/* maximal size of elements (in machine words) to be put into cache:         */
#ifndef MAX_SAVE
#define MAX_SAVE        512
#endif


#define H_LOCAL_ALLOC -111                      /* AllocLevel for local. mem.*/
#define H_GLOBAL_ALLOC -112                     /* use global AllocLevel     */

/*===========================================================================*/
/*                               Data Structures                             */
/*===========================================================================*/
/* table element for stack management:                                       */
typedef struct { 
        VOIDP          data;  /* pointer to stored data of a stack element   */
        MACHINE_WORD   *next; /* pointer to next free memory area            */
        VOIDP          last;  /* pointer to last allocated area              */
        INT4           size;  /* size of memory within this stack element    */
        INT4           free;  /* free memory within stack element            */
        } MemTElt;

typedef struct MEM_TT_EL_SAVE{ 
        VOIDP                 *data;   /* memory area to manage              */
        INT4                  size;    /* size of memory                     */
        struct MEM_TT_EL_SAVE *next;   /* next element in list               */
        } MemTEltSave;

typedef struct MEM_LOCAL_EL{ 
        VOIDP               element;  /* memory element to manage            */
        struct MEM_LOCAL_EL *next;    /* next element in list                */
        } MemLElt;

/* memory management handle (with instance/thread-specific content)          */
typedef struct MEM_HANDLE {
        /*------------------------------ management of stack memory ---------*/
        MemTElt        *MemTTable;    /* management list for stack memory    */
        INT            MemTTLength;   /* current length of management list   */
        INT            MemTStack;     /* current stack depth                 */
        INT4           MemTmpCount;   /* num. of allocated stack mem. blocks */
        HBOOL          MemTmpInit;    /* must we init. the stack management? */
        /*------------------------------ management of local memory ---------*/
        MemLElt        *MemLocalList; /* management list for local memory    */
        H_pthread_mutex_t MutexLocalList; /* mutex variable for MemLocalList */
        INT4           MemLocalCount; /* num. of allocated local mem. blocks */
} MEMHANDLE;
typedef MEMHANDLE *MemHandle;

/*===========================================================================*/
/*                          Prototypes of Functions                          */
/*===========================================================================*/
/*---------------------------------------------------------------------------*/
/*                          Test Memory Allocation                           */
/*---------------------------------------------------------------------------*/
/* HXTestPtrRange - tests memory (address) allocated with HAlloc/HAllocLocal */
extern HLibExport Herror HXTestPtrRange(void *ptr, const char *file, 
					INT4_8 line,
					HBOOL do_print);

/* HXTestPtr - tests memory (address+size) allocated with HAlloc/HAllocLocal */
extern HLibExport Herror HXTestPtr(void *ptr, const char *file, INT4_8 line);

/* HTestMem - tests all the memory currently allocated by HAlloc/HAllocLocal */
extern HLibExport Herror HTestMem (void);

/*---------------------------------------------------------------------------*/
/*                 Auxiliary Functions for Memory Management                 */
/*---------------------------------------------------------------------------*/
/* HTmpStackSize - return stack size for temporary memory blocks             */
extern HLibExport Herror HTmpStackSize(Hproc_handle proc_handle, INT4 *size);

/* HSetAllocLevel - set 'level' of memory allocation                         */
extern HLibExport Herror HSetAllocLevel(INT4_8 level);

/* HGetAllocLevel - read 'level' of memory allocation                        */
extern HLibExport Herror HGetAllocLevel(INT4_8 *level);

/* HMemInfo - retrieve informationen zaboutc current memory allocation       */
extern HLibExport Herror HMemInfo(Hproc_handle proc_handle,
                                  INT4_8 *alloc_mem, INT4_8 *free_mem,
                                  INT4_8 *used_mem, INT4_8 *alloc_call,
				  INT4_8 *free_call, double *hit_rate,
				  double *small_rate, size_t *cache,
				  size_t *stack);

/* HNumMemElements - get number of currently allocated memory blocks         */
extern HLibExport Herror HNumMemElements(INT4_8  *num);

/* HAllocInfo - get line of call/size of all blocks with level >= AllocLevel */
extern HLibExport Herror HAllocInfo(INT max, char *file[], INT4 line[],
			            INT4 size[], INT4 level[], INT4_8 *num);

/* HPrepMem - prepares memory (allocates+frees memory) => more efficiency    */
extern HLibExport Herror HPrepMem (Hproc_handle proc_handle, size_t size,
                                   size_t *si_ze);

/* HFreeUnusedTmpMem - free any unused temporary memory                      */
extern HLibExport Herror HFreeUnusedTmpMem(Hproc_handle proc_handle);

/*---------------------------------------------------------------------------*/
/*                   Management of Free Usable Memory                        */
/*---------------------------------------------------------------------------*/
/* HInitMem - initialize cache-memory and free memory management             */
extern HLibExport Herror HInitMem (Hproc_handle proc_handle, size_t size);

/* HCloseMem - shut down management of cache memory and free memory          */
extern HLibExport Herror HCloseMem(void);

/* HMemInitHandle - initialize client-specific memory management handle      */
extern HLibExport Herror HMemInitHandle(Hproc_handle proc_handle);

/* HMemCloseHandle - give free client-specific memory management handle      */
extern HLibExport Herror HMemCloseHandle(Hproc_handle proc_handle);

/* HXAlloc - allocate free usable memory                                     */
extern HLibExport Herror HXAlloc (Hproc_handle proc_handle, size_t size,
                                  const char *file, INT4_8 line, INT4 level,
				  VOIDP *void_p);

/* HXFree - give free (free usable) memory (insert it into cache) and test it*/
extern HLibExport Herror HXFree(Hproc_handle proc_handle, VOIDP mem,
                                const char *file, INT4_8 line,HBOOL local_mem);

/* HXRealloc - reallocate memory and test it (memory still available?)       */
extern HLibExport Herror HXRealloc(Hproc_handle proc_handle, VOIDP ptr,
                                   size_t size, VOIDP *void_p,
			           const char *file, INT4_8 line);

/* HXAllocRLNum - allocate permanent memory for specific region              */
extern HLibExport Herror HXAllocRLNum(Hproc_handle proc_handle, 
                                      Hrlregion **region, size_t num,
                                      const char *file, INT4_8 line);

/* HXAllocRL - allocate permanent memory for new regions                     */
extern HLibExport Herror HXAllocRL(Hproc_handle proc_handle, 
                                   Hrlregion **region,
                                   const char *file, INT4_8 line);

/* HXFreeRL - give free (permanent) memory of a specific region              */
extern HLibExport Herror HXFreeRL(Hproc_handle proc_handle,Hrlregion *region, 
		                  const char *file, INT4_8 line);

/*---------------------------------------------------------------------------*/
/*                   Management of Local Free Memory                         */
/*---------------------------------------------------------------------------*/
/* HXAllocLocal - allocate local memory (AllocLevel=H_LOCAL_ALLOC)           */
extern HLibExport Herror HXAllocLocal (Hproc_handle proc_handle, size_t size,
                                       const char *file,
			               INT4_8 line, VOIDP *void_p);

/* HXFreeLocal - give free local memory (insert it in cache) and test it     */
extern HLibExport Herror HXFreeLocal(Hproc_handle proc_handle, 
                                     VOIDP mem, const char *file, 
                                     INT4_8 line,HBOOL change_list);

/* HXReallocLocal - reallocate local memory (AllocLevel=H_LOCAL_ALLOC)       */
extern HLibExport Herror HXReallocLocal(Hproc_handle proc_handle, VOIDP ptr, 
                                        size_t size, VOIDP *void_p, 
                                        const char *file, INT4_8 line);

/* HXAllocRLNumLocal - allocate local memory for specific region             */
extern HLibExport Herror HXAllocRLNumLocal(Hproc_handle proc_handle, 
                                           Hrlregion **region, size_t num, 
                                           const char *file, INT4_8 line);

/* HXAllocRLLocal -  allocate local memory for new regions                   */
extern HLibExport Herror HXAllocRLLocal(Hproc_handle proc_handle, 
                                        Hrlregion **region,
                                        const char *file, INT4_8 line);

/* HXFreeRLLocal - give free (local) memory of a specific region             */
extern HLibExport Herror HXFreeRLLocal(Hproc_handle proc_handle,
                                       Hrlregion *region, 
		                       const char *file, INT4_8 line);

/* HMemClrLocal - give free the whole local memory (alloc. by HXAllocLocal)  */
extern HLibExport Herror HMemClrLocal(Hproc_handle proc_handle);

/*---------------------------------------------------------------------------*/
/*                         Management of Stack Memory                        */
/*---------------------------------------------------------------------------*/
/* HMemResTTable - change size of table MemTTable for temporary memory       */
extern HLibExport Herror HFreeMemTTable(Hproc_handle proc_handle);

/* HXFreeAllTmp - give free all the allocated temporary memory               */
extern HLibExport Herror HXFreeAllTmp(Hproc_handle proc_handle,
			              const char *file, INT4_8 line);

/* HMemClrTTable - free (logically) all the allocated stack memory(MemTTable)*/
extern HLibExport Herror HMemClrTTable(Hproc_handle proc_handle);

/* HXAllocTmp - allocate temporary memory within a stack                     */
extern HLibExport Herror HXAllocTmp(Hproc_handle proc_handle, VOIDP *ptr,
                                    size_t size, const char *file,
				    INT4_8 line);

/* HXAllocRLNumTmp - allocate temporary memory for specific region           */
extern HLibExport Herror HXAllocRLNumTmp(Hproc_handle proc_handle,
                                         Hrlregion **region, size_t num,
                                         const char *file, INT4_8 line);

/* HXAllocRLTmp - allocate temporary memory for new regions                  */
extern HLibExport Herror HXAllocRLTmp(Hproc_handle proc_handle, 
                                      Hrlregion **region,
                                      const char *file, INT4_8 line);

/* HXTestAllTmp - test all stacks for temporary memory of consistency        */
extern HLibExport Herror HXTestAllTmp(Hproc_handle proc_handle,
                                      const char *file, INT4_8 line);

/* HXTestTmp - test the specified temporary memory block of consistency      */
extern HLibExport Herror HXTestTmp(Hproc_handle proc_handle,
			           VOIDP ptr, const char *file, INT4_8 line, 
			           HBOOL do_printf);

/* HXFreeTmp - gives free the lastly allocated (!) stack memory              */
extern HLibExport Herror HXFreeTmp(Hproc_handle proc_handle, VOIDP ptr,
                                   const char *file, INT4_8 line);

/* HXFreeRLTmp - gives free temporary memory of a specific region            */
extern HLibExport Herror HXFreeRLTmp(Hproc_handle proc_handle,
                                     Hrlregion *region,
                                     const char *file, INT4_8 line);

/* HXFreeNTmp - gives free the 'num' lastly allocated stack memory blocks    */
extern HLibExport Herror HXFreeNTmp(Hproc_handle proc_handle, INT num,
                                    const char *file, INT4_8 line);

/* HXFreeUpToTmp - give free stack memory up to a specified memory block     */
extern HLibExport Herror HXFreeUpToTmp(Hproc_handle proc_handle, void *ptr, 
			               const char *file, INT4_8 line);

/* HFreeUnusedStacks - gives free (physically) all currently unused stacks   */
extern HLibExport Herror HFreeUnusedStacks(Hproc_handle proc_handle);

/* HShrinkRL - gives free the unused memory of a specific region             */
extern HLibExport Herror HShrinkRL(Hproc_handle proc_handle, 
                                   Hrlregion **region);




#if defined(__cplusplus)
}
#endif


#endif
