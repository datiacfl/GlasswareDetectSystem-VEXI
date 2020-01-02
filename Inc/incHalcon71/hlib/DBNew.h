/*****************************************************************************
 * DBNew.h
 ***************************************************************************** 
 *
 * Project:     Halcon/libhalcon
 * Description: Object handling and storing in memory
 *
 * (c) 1996-2000 by MVTec Software GmbH
 *                  Neherstr. 1, 81675 Muenchen, Germany
 * 
 *****************************************************************************
 *
 * $Revision: 1.19 $
 * $Date: 2001/03/01 10:27:39 $
 *
 */

#ifndef HDBNEW_H
#define HDBNEW_H


#if defined(__cplusplus)
extern "C" {
#endif
   


/*===========================================================================*/
/*                                 Defines                                   */
/*===========================================================================*/

#define REGION_ID               1
#define IMAGE_ID                2
#define OBJECT_ID               3
#define TUPLE_ID                4
#define XLD_CONTOUR_ID          5
#define XLD_POLYGON_ID          6
#define XLD_PARALLEL_ID         7
#define XLD_MOD_PARALLEL_ID     8
#define XLD_EXT_PARALLEL_ID     9
#define MIN_XLD_ID              XLD_CONTOUR_ID
#define MAX_XLD_ID              XLD_EXT_PARALLEL_ID
#define STD_FREE                HFree

#define DB_MAGIC_OK             1234567890
#define DB_MAGIC_REGION         (DB_MAGIC_OK+REGION_ID)
#define DB_MAGIC_IMAGE          (DB_MAGIC_OK+IMAGE_ID) 
#define DB_MAGIC_OBJECT         (DB_MAGIC_OK+OBJECT_ID)
#define DB_MAGIC_OBJECT_TUPLE   (DB_MAGIC_OK+TUPLE_ID)

#define DB_MAGIC_CLEARED        1987654320
#define DB_CLEARED_REGION       (DB_MAGIC_CLEARED+REGION_ID)
#define DB_CLEARED_IMAGE        (DB_MAGIC_CLEARED+IMAGE_ID)
#define DB_CLEARED_OBJECT       (DB_MAGIC_CLEARED+OBJECT_ID)
#define DB_CLEARED_OBJECT_TUPLE (DB_MAGIC_CLEARED+TUPLE_ID)
#define DB_MIN_CLEARED          (DB_MAGIC_CLEARED+1)
#define DB_MAX_CLEARED          (DB_MAGIC_CLEARED+MAX_XLD_ID)

/*===========================================================================*/
/*                            'Global' Makros                                */
/*===========================================================================*/
/* -------- work on data identifiers --------------------------------------- */
#define DB_ID(PTR) ((INT4)(((DBImage*)PTR)->magic) - DB_MAGIC_OK)
#define DB_ERROR_ID(PTR) ((INT4)(((DBImage*)PTR)->magic) - DB_MAGIC_CLEARED)

#define DB_IS_XLD(PTR) ((DB_ID(PTR) >= MIN_XLD_ID) && \
			(DB_ID(PTR) <= MAX_XLD_ID))

/*****************************************************************************/
/* DB_INCREMENT - increase counter of image/region by 1                      */
/*****************************************************************************/
#define DB_INCREMENT(PTR)   (PTR)->counter++

/* -------- work on doubly linked lists ------------------------------------ */
/*****************************************************************************/
/* DB_INSERT - insert element in doubly linked list                          */
/*****************************************************************************/
#define DB_INSERT(ROOT,PTR,H) \
  H = (ROOT)->succ; \
  if (H != NULL) (H)->pred = PTR; \
  (ROOT)->succ = PTR; \
  (PTR)->succ = H; \
  (PTR)->pred = ROOT

/*****************************************************************************/
/* DB_REMOVE - remove element from doubly linked list                        */
/*****************************************************************************/
#define DB_REMOVE(PTR) \
  (PTR)->pred->succ = (PTR)->succ; \
  if ((PTR)->succ != NULL) \
    (PTR)->succ->pred = (PTR)->pred

/*===========================================================================*/
/*                                Data Types                                 */
/*===========================================================================*/

typedef Herror (*DBFreeProc)(Hproc_handle proc_handle, void *mem);

/*****************************************************************************/
/*                                   Images                                  */
/*****************************************************************************/

typedef struct DB_IMAGE {
  UINT4             magic;
  Himage            image;         /* image data                             */
  UINT2             creator;       /* operator index (see HProcInfo)         */
  UINT2             counter;       /* references > 0; if == 0 delete it      */
  struct DB_IMAGE   *pred;
  struct DB_IMAGE   *succ;
  VOIDP             list;          /* associated management list             */
} DBImage;

typedef DBImage  *DBImagePtr;


/*****************************************************************************/
/*                                  Regions                                  */
/*****************************************************************************/

typedef struct DB_REGION {
  UINT4             magic;
  Hrlregion         *region;       /* region data inn runlength encoding     */
  UINT2             creator;       /* operator index (see HProcInfo)         */
  UINT2             counter;       /* references > 0; if == 0 delete it      */
  struct DB_REGION  *pred;
  struct DB_REGION  *succ;
  DBFreeProc        clear;
  VOIDP             list;          /* associated management list             */
} DBRegion;

typedef DBRegion  *DBRegionPtr;

/*****************************************************************************/
/*                                 Objects                                   */
/*****************************************************************************/

typedef struct DB_OBJECT {
  UINT4             magic;         /* specific magic number for tests        */
  DBRegion          *region;       /* pointer to region                      */
  DBImagePtr        *image;        /* pointer to array of image matrices     */
                                   /* (undefined components are set to NULL) */
  UINT2             num;           /* num. of gray value matrices; not fixed!*/
  UINT2             creator;       /* operator index (see HProcInfo)         */
  struct DB_OBJECT  *pred;
  struct DB_OBJECT  *succ;
  VOIDP             list;          /* associated management list             */
} DBObject;

typedef DBObject  *DBObjectPtr;


/*****************************************************************************/
/*                                 XLD                                       */
/*****************************************************************************/


typedef struct DB_XLD {
  UINT4             magic;
  void              *xld;          /* pointer to data                        */
  Hkey              *uses;         /* XLD objects that are used              */
  UINT2             num_uses;
  UINT2             creator;       /* operator index (see HProcInfo)         */
  INT4              counter;
  struct DB_XLD     *pred;
  struct DB_XLD     *succ;
  DBFreeProc        clear;
  VOIDP             list;          /* associated management list             */
} DBXLD;

typedef DBXLD  *DBXLDPtr;


/*****************************************************************************/
/*                             Object Tuple                                  */
/*****************************************************************************/

typedef struct DB_TUPLE {
  UINT4            magic;          /* specific magic number for tests        */
  DBObjectPtr      *object;        /* array of pointers to DBObjects         */
  UINT4            num;            /* length of object                       */
  UINT2            creator;        /* operator index (see HProcInfo)         */
  struct DB_TUPLE  *pred;
  struct DB_TUPLE  *succ;
  VOIDP            list;           /* associated management list             */
} DBObjectTuple;

/*****************************************************************************/
/*                Data Structure for Management Lists and Counters           */
/*****************************************************************************/
typedef struct DB_HANDLE {
  DBObjectTuple     *DBObjectTupleRoot;          /* entry of obj. tuple list */
  DBObjectTuple     *DBObjectTupleSave;          /* memory to recycle        */
  H_pthread_mutex_t mutex_ObjectTupleRoot;       /* to lock obj. tuple list  */
  H_pthread_mutex_t mutex_ObjectTupleSave;       /* to lock recycle-list     */

  DBObject          *DBObjectRoot;               /* entry of object list     */
  DBObject          *DBObjectSave;               /* memory to recycle        */
  H_pthread_mutex_t mutex_ObjectRoot;            /* to lock object list      */
  H_pthread_mutex_t mutex_ObjectSave;            /* to lock recycle-list     */

  DBRegion          *DBRegionRoot;               /* entry of region list     */
  DBRegion          *DBRegionSave;               /* memory to recycle        */
  H_pthread_mutex_t mutex_RegionRoot;            /* to lock region list      */
  H_pthread_mutex_t mutex_RegionSave;            /* to lock recycle-list     */

  DBImage           *DBImageRoot;                /* Bildobjekt-Liste-Anker   */
  DBImage           *DBImageSave;                /* memory to recycle        */
  H_pthread_mutex_t mutex_ImageRoot;             /* to lock image list       */
  H_pthread_mutex_t mutex_ImageSave;             /* to lock recycle-list     */

  DBXLD             *DBXLDRoot;                  /* XLD-Objekt-Liste-Anker   */
  DBXLD             *DBXLDSave;                  /* memory to recycle        */
  H_pthread_mutex_t mutex_XLDRoot;               /* to lock XLD object list  */
  H_pthread_mutex_t mutex_XLDSave;               /* to lock recycle-list     */

  /* counters for managed objects (remark: those counters may also contain   */
  /* negative values - at least the thread-specific ones)                    */
  INT4              CountObjectTuple;            /* number of object tuples  */
  H_pthread_mutex_t mutex_cObjectTuple;          /* lock writing to counter  */
  INT4              CountObject;                 /* number of objects        */
  H_pthread_mutex_t mutex_cObject;               /* lock writing to counter  */
  INT4              CountRegion;                 /* number of regions        */
  H_pthread_mutex_t mutex_cRegion;               /* lock writing to counter  */
  INT4              CountImage;                  /* number of image objects  */
  H_pthread_mutex_t mutex_cImage;                /* lock writing to counter  */
  INT4              CountXLD;                    /* number of XLD objects    */
  H_pthread_mutex_t mutex_cXLD;                  /* lock writing to counter  */

  /* mutex variables for changing an object reference pointer                */
  H_pthread_mutex_t mutex_RegionCount;           /* lock writing to counter  */
  H_pthread_mutex_t mutex_ImageCount;            /* lock writing to counter  */
  H_pthread_mutex_t mutex_XLDCount;              /* lock writing to counter  */

} DBHandle;

typedef DBHandle *DBhandle;


/*===========================================================================*/
/*                             External Interface                            */
/*===========================================================================*/
extern HLibExport Herror DBInitRoots(Hproc_handle proc_handle);
extern HLibExport Herror DBInitHandle(Hproc_handle proc_handle,HBOOL shared);
extern HLibExport Herror DBCloseRoots(Hproc_handle proc_handle);
extern HLibExport Herror DBCloseHandle(Hproc_handle proc_handle);
extern HLibExport void   HPrintPixelType(FILE *file, INT kind);
extern HLibExport Herror DBSpy(Hproc_handle proc_handle, FILE *file);
extern HLibExport void   DBInfoCleared(VOIDP ptr);
extern HLibExport Herror HIsCompact(Hproc_handle proc_handle, Hkey key, 
                                    HBOOL *res);
extern HLibExport Herror DBCountImage(Hproc_handle proc_handle,INT4_8 *num);
extern HLibExport Herror DBCountXLD(Hproc_handle proc_handle, INT4_8 *num);
extern HLibExport Herror DBStoreImage(Hproc_handle proc_handle, Himage *image,
                                      Hkey *id);
extern HLibExport Herror DBFetchImage(Hproc_handle proc_handle, Hkey id, 
                                      Himage **image);
extern HLibExport Herror DBGetImageCreator(Hproc_handle proc_handle, Hkey obj,
                                           INT comp,INT *proc_num);
extern HLibExport Herror DBCountRegion(Hproc_handle proc_handle, INT4_8 *num);
extern HLibExport Herror DBStoreRegion(Hproc_handle proc_handle, 
                                       Hrlregion *region, Hkey *id);
extern HLibExport Herror DBFetchDRegion(Hproc_handle proc_handle, Hkey id,
                             Hrlregion **region);
extern HLibExport Herror DBFetchRegion(Hproc_handle proc_handle, Hkey id,
                            Hrlregion **region);
extern HLibExport Herror DBGetRegionCreator(Hproc_handle proc_handle, Hkey obj,
                                 INT *proc_num);
extern HLibExport Herror DBGetObjectCreator(Hproc_handle proc_handle, Hkey obj,
                                 INT *proc_num);
extern HLibExport Herror DBCountObject(INT4_8 *num);
extern HLibExport Herror DBTestObjektID(Hkey id);
extern HLibExport Herror DBStoreObject(Hproc_handle proc_handle, 
                                       Hkey region_id, Hkey *image_ids, 
                                       INT num, Hkey *id);
extern HLibExport Herror DBFetchObject(Hproc_handle proc_handle, Hkey id, 
                                       Hkey *region_id,Hkey **image_ids, 
                                       INT *num);
extern HLibExport Herror DBCopyObject(Hproc_handle proc_handle, Hkey id, 
                                      Hkey *new_id);
extern HLibExport Herror DBDelObject(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBObjectNewRegion(Hproc_handle proc_handle, Hkey id, 
                                           Hkey region_id);
extern HLibExport Herror DBObjectNewImage(Hproc_handle proc_handle, Hkey id, 
                                          Hkey image_id,INT comp);
extern HLibExport Herror DBStoreXLD(Hproc_handle proc_handle, VOIDP data, 
                                    INT type,Hkey *uses, INT4 num,
                                    DBFreeProc free_proc, Hkey *id);
extern HLibExport Herror DBFetchXLD(Hproc_handle proc_handle, Hkey id, 
                                    INT *type, VOIDP *data, Hkey **uses, 
                                    INT4 *num);
extern HLibExport Herror DBCopyXLD(Hkey id, Hkey *new_id);
extern HLibExport Herror DBDelXLD(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBGetXLDCreator(Hkey obj, INT *proc_num);
extern HLibExport Herror DBCountObjectTuple(INT4_8 *num);
extern HLibExport Herror DBStoreTuple(Hproc_handle proc_handle, Hkey *ids, 
                                      INT4_8 num,Hkey *id);
extern HLibExport Herror DBFetchTuple(Hproc_handle proc_handle, 
                                      Hkey id, Hkey **ids, INT4_8 *num);
extern HLibExport Herror DBDelTuple(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBDelObjectId(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBCopyObjectId(Hproc_handle proc_handle, Hkey id,
                                        Hkey *new_id);
extern HLibExport Herror DBNumImaRefs(Hproc_handle proc_handle, Hkey id, 
                                      INT *num);
extern HLibExport Herror HGetCreator(Hproc_handle proc_handle, Hkey obj, 
                                     INT comp, INT *proc_num);
extern HLibExport Herror DBGetRLPtr(Hproc_handle proc_handle, Hkey id,
                                    Hrlregion **rl);
extern HLibExport Herror DBGetXLDPtr(Hkey id, VOIDP *xld);

#if defined(__cplusplus)
}
#endif


#endif
