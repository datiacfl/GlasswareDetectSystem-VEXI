/*****************************************************************************
 * HDevEngine.h
 *****************************************************************************
 *
 * Description: Classes for Execution of HDevelop programs and procedures
 *
 * (c) 1996-2005 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 */

#include "HalconC.h"

class HDevEngine;
class HDevProcedureCall;
class HDevEngineException;
class HDevOperatorImpl;


// Class for Execution of HDevelop programs and procedures
class LIntExport HDevEngine
{
  public:

    HDevEngine(void);
    HDevEngine(const HDevEngine &hdev_eng);
    HDevEngine &operator = (const HDevEngine &hdev_eng);
    virtual ~HDevEngine(void);

    // Clear program and reset callstack
    void Reset(void); 
    // Load program <file_name>
    void LoadProgram(const char *file_name);
    // Set path for external procedures
    void SetProcedurePath(const char *path);
    // Load external procedure <proc_name> und all needed procedures
    void LoadExternalProcedure(const char *proc_name);
    // Get names of all (local and external) procedures
    void GetProcedureNames(Htuple *proc_names);
    // Delete procedure <proc_name>
    void DeleteProcedure(const char *proc_name);

    // Execute program
    void ExecuteProgram(void);
    // Execute procedure call
    void ExecuteProcedure(HDevProcedureCall *proc_call);

    // Set implementation for HDevelop internal operators
    void SetHDevOperatorImpl(HDevOperatorImpl *hdev_op_impl);
};


// Class for Execution of HDevelop procedure calls
class  LIntExport HDevProcedureCall
{
  public:

    // Create HDevelop procedure call instance
    HDevProcedureCall(const char *proc_name);
    HDevProcedureCall(const HDevProcedureCall &proc_call);
    HDevProcedureCall &operator = (const HDevProcedureCall &proc_call);
    ~HDevProcedureCall(void);
  
    const char* GetProcedureName(void) const {return _ProcName;}
    const char* GetShortDescription(void) const;

    // Get number/name of input/output object/control parameters
    int GetInpObjNumber(void) const {return _InpObjNum;}
    int GetOutpObjNumber(void) const {return _OutpObjNum;}
    int GetInpCtrlNumber(void) const {return _InpCtrlNum;}
    int GetOutpCtrlNumber(void) const {return _OutpCtrlNum;}
    const char *GetInpObjParamName(int param_num) const;
    const char *GetOutpObjParamName(int param_num) const;
    const char *GetInpCtrlParamName(int param_num) const;
    const char *GetOutpCtrlParamName(int param_num) const;

    // Set input object/control parameter
    void SetInputObject(int param_num, const Hobject &obj);
    void SetInputObject(const char *param_name, const Hobject &obj);
    void SetInputCtrl(int param_num, const Htuple &val);
    void SetInputCtrl(const char *param_name, const Htuple &val);

    // Get output object/control parameter
    void GetOutputObject(int param_num, Hobject *obj) const;
    void GetOutputObject(const char *param_name, Hobject *obj) const;
    void GetOutputCtrl(int param_num, Htuple *val) const;
    void GetOutputCtrl(const char *param_name, Htuple *val) const;

    // internal usage
    Hobject GetInputObject(int param_num) const;
    void SetOutputObject(int param_num, const Hobject &obj); 
    Htuple GetInputCtrl(int param_num) const;
    void SetOutputCtrl(int param_num, const Htuple &val);

  private:

    Hobject _InpObj[MAX_INP_OBJ_PAR];
    Hobject _OutpObj[MAX_OUTP_OBJ_PAR];
    Htuple  _InpCtrl[MAX_INP_CTRL_PAR];
    Htuple  _OutpCtrl[MAX_OUTP_CTRL_PAR];
    int     _InpObjNum, _OutpObjNum, _InpCtrlNum, _OutpCtrlNum;
    char   *_ProcName;
    void    Clear(void);
    void    Copy(const HDevProcedureCall &proc_call);
};


// Class for HDevelop engine exceptions
class  LIntExport HDevEngineException
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
    HDevEngineException(const char *message, 
                        ExceptionCategory category = Exception,
                        int prog_line_nr = -1, const char *prog_line_name = "",
                        Herror h_err_nr = H_MSG_VOID);
    virtual ~HDevEngineException(void) {}
  
    // Error text
    const char *Message(void) {return _Message;}
    // Category of exception
    ExceptionCategory Category(void) {return _Category;}
    // Name of executed procedure
    const char *ExecProcedureName(void) {return _ExecProcedureName;}
    // Number of executed procedure or operator program line
    int ProgLineNr(void) {return _ProgLineNr;}
    // Name of executed procedure or operator program line 
    const char *ProgLineName(void) {return _ProgLineName;}
    // HALCON error number
    Herror HalconErrNr(void) {return _HalconErrNr;}

  private:

    const char         *_Message;
    ExceptionCategory   _Category;
    const char         *_ExecProcedureName;
    int                 _ProgLineNr;
    const char         *_ProgLineName;
    Herror              _HalconErrNr;
};


// Class for Implemention of HDevelop internal operators
class LIntExport HDevOperatorImpl
{
  public:

    HDevOperatorImpl(void) {}
    virtual ~HDevOperatorImpl(void) {}

    virtual int DevUpdateWindow(Htuple mode);
    virtual int DevUpdateVar(Htuple mode);
    virtual int DevUpdatePC(Htuple mode);
    virtual int DevClearWindow(void);			 
    virtual int DevCloseWindow(void);
    virtual int DevSetWindow(Htuple win_id);
    virtual int DevCloseInspectCtrl(const char *var_name);	
    virtual int DevInspectCtrl(const char *var_name);	
    virtual int DevDisplay(Hobject obj);
    virtual int DevSetWindowExtents(Htuple row,Htuple col,
                                    Htuple width,Htuple height);
    virtual int DevClearObj(Hobject obj);
    virtual int DevSetDraw(Htuple draw);
    virtual int DevUnmapProg(void);
    virtual int DevMapProg(void);
    virtual int DevUnmapVar(void);
    virtual int DevMapVar(void);
    virtual int DevUnmapPar(void);
    virtual int DevMapPar(void);
    virtual int DevSetShape(Htuple shape);
    virtual int DevSetColored(Htuple colored);
    virtual int DevSetColor(Htuple color);
    virtual int DevSetLut(Htuple lut);
    virtual int DevSetPaint(Htuple paint);
    virtual int DevSetPart(Htuple row,Htuple col,
                           Htuple width,Htuple height);
    virtual int DevSetLineWidth(Htuple width);
    virtual int DevOpenWindow(Htuple row,Htuple col,Htuple width,Htuple height,
                              Htuple background, Htuple *win_id);
};

