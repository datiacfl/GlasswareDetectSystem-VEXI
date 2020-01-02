/*****************************************************************************
 * HDevEngine.h
 *****************************************************************************
 *
 * Description: Classes for Execution of HDevelop programs and procedures
 *
 * (c) 1996-2007 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 */

#ifndef H_DEV_ENGINE_H
#define H_DEV_ENGINE_H

#include "HalconC.h"

// Maximum number of HDevelop procedure parameters per parameter class
#define MAX_HDEV_PROC_PAR 100


#ifndef HDEV_PD
#define HDEV_PD private: class Data; Data* mData
#endif

// forward declarations
class HDevEngine;
class HDevProcedureCall;
class HDevEngineException;
class HDevOperatorImpl;


/*****************************************************************************
 *****************************************************************************
 ** class HDevEngine
 **===========================================================================
 ** Class for Execution of HDevelop programs and procedures
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevEngine
{
public:

  HDevEngine();
  HDevEngine(const HDevEngine &hdev_eng);
  HDevEngine &operator = (const HDevEngine &hdev_eng);
  virtual ~HDevEngine();

  // Clear program and reset callstack
  void Reset(); 
  // Load program <file_name>
  void LoadProgram(const char* file_name);
  // Set path for external procedures
  // Attention:
  //   this settings are global for all HDevEngine instances
  void SetProcedurePath(const char* path);
  // Get names of all (local and external) procedures
  void GetProcedureNames(Htuple* proc_names);
  // Delete procedure <proc_name>
  void DeleteProcedure(const char* proc_name);

  // Execute program
  void ExecuteProgram();
  // Execute procedure call
  void ExecuteProcedure(HDevProcedureCall* proc_call);

  // Set implementation for HDevelop internal operators
  // Attention:
  //   this settings are global for all HDevEngine instances
  void SetHDevOperatorImpl(HDevOperatorImpl* hdev_op_impl, 
                           int mem_free_intern=TRUE);

  //
  // New methods for accessing the variables of the main program
  //

  // get the number of iconic and control variables
  size_t      GetIconicVarCount() const;
  size_t      GetCtrlVarCount() const;

  // get the names of the variables
  //   (indices of the variables run from 1 to count)
  const char* GetIconicVarName(size_t idx);
  const char* GetCtrlVarName(size_t idx);

  // get the objects / values of the variables by name or by index
  //   (indices of the variables run from 1 to count)
  void        GetIconicVarObject(const char* var_name, Hobject* obj);
  void        GetCtrlVarValue(const char* var_name, Htuple* tuple);
  void        GetIconicVarObject(size_t idx, Hobject* obj);
  void        GetCtrlVarValue(size_t idx, Htuple* tuple);



  // !!! obsolete !!!
  //   the procedures are loaded automatically, if they are used
  void LoadExternalProcedure(const char* proc_name);

  HDEV_PD;
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevEngineException
 **===========================================================================
 ** Class for Execution of HDevelop procedure calls
 *****************************************************************************
 *****************************************************************************/
class  LIntExport HDevProcedureCall
{
public:

  // Create HDevelop procedure call instance
  HDevProcedureCall(const char* proc_name);
  HDevProcedureCall(const HDevProcedureCall& pcall);
  HDevProcedureCall& operator=(const HDevProcedureCall& pcall);
  ~HDevProcedureCall();

  const char* GetProcedureName() const;
  const char* GetShortDescription(void) const;

  // Get number of input/output object/control parameters
  int GetInpObjNumber() const;
  int GetOutpObjNumber() const;
  int GetInpCtrlNumber() const;
  int GetOutpCtrlNumber() const;

  // Get name of input/output object/control parameters
  const char* GetInpObjParamName(int par_idx) const;
  const char* GetOutpObjParamName(int par_idx) const;
  const char* GetInpCtrlParamName(int par_idx) const;
  const char* GetOutpCtrlParamName(int par_idx) const;

  // Set input object/control parameter
  void SetInputObject(int par_idx, const Hobject &obj);
  void SetInputObject(const char* par_name, const Hobject &obj);
  void SetInputCtrl(int par_idx, const Htuple &val);
  void SetInputCtrl(const char* par_name, const Htuple &val);

  // Get output object/control parameter
  void GetOutputObject(int par_idx, Hobject* obj) const;
  void GetOutputObject(const char* par_name, Hobject* obj) const;
  void GetOutputCtrl(int par_idx, Htuple* val) const;
  void GetOutputCtrl(const char* par_name, Htuple* val) const;

  HDEV_PD;
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevEngineException
 **===========================================================================
 ** Class for HDevelop engine exceptions
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevEngineException
{
public:

  // Exception categories
  enum  ExceptionCategory
  {
    Exception,            // Generic
    ExceptionInpNotInit,  // Error input parameters not initialized
    ExceptionCall,        // Error HALCON or HDevelop operator call
    ExceptionFile         // Error opening or reading HDevelop file
  };

  // Create HDevelop engine exception
  HDevEngineException(const char* message,
                      ExceptionCategory category,
                      int prog_line_num,
                      const char* prog_line_name="",
                      Herror h_err_nr=H_MSG_VOID); 
  HDevEngineException(const char* message,
                      ExceptionCategory category=Exception,
                      const char* exec_proc_name="",
                      int prog_line_num=-1,
                      const char* prog_line_name="",
                      Herror h_err_nr=H_MSG_VOID); 
  HDevEngineException(const HDevEngineException& exc);
  HDevEngineException& operator = (const HDevEngineException& exc);
  virtual ~HDevEngineException();

  // Error text
  const char* Message() const;
  // Category of exception
  ExceptionCategory Category() const;
  // Name of executed procedure
  const char* ExecProcedureName() const;
  // Number of executed procedure or operator program line
  int ProgLineNum() const;
  int ProgLineNr() const {
    return ProgLineNum();
  }
  // Name of executed procedure or operator program line 
  const char* ProgLineName() const;
  // HALCON error number
  Herror HalconErrNum() const;
  Herror HalconErrNr() const {
    return HalconErrNum();
  }

  HDEV_PD;
};



/*****************************************************************************
 *****************************************************************************
 ** class HDevOperatorImpl
 **===========================================================================
 ** Class for the implemention of HDevelop internal operators
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevOperatorImpl
{
  public:

    HDevOperatorImpl() {
    }
    virtual ~HDevOperatorImpl() {
    }
    virtual int DevClearWindow();
    virtual int DevCloseWindow();
    virtual int DevSetWindow(Htuple win_id);
    virtual int DevDisplay(Hobject obj);
    virtual int DevSetWindowExtents(Htuple row, Htuple col,
                                    Htuple width, Htuple height);
    virtual int DevSetDraw(Htuple draw);
    virtual int DevSetShape(Htuple shape);
    virtual int DevSetColored(Htuple colored);
    virtual int DevSetColor(Htuple color);
    virtual int DevSetLut(Htuple lut);
    virtual int DevSetPaint(Htuple paint);
    virtual int DevSetPart(Htuple row1, Htuple col1,
                           Htuple row2, Htuple col2);
    virtual int DevSetLineWidth(Htuple width);
    virtual int DevOpenWindow(Htuple row,Htuple col,Htuple width,Htuple height,
                              Htuple background, Htuple* win_id);
};

#endif
