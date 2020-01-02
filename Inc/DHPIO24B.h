/************************************************************************/
/* Copyright (c) 2009, �������ͼ���Ӿ��������޹�˾�Ӿ�ϵͳ��    
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHPIO24B.h
/* ժҪ�� 
/*
/* ��ǰ�汾�� 3.1
/* �޸��ߣ� ����
/* ������ڣ� 2009��9��24��
/* ˵���� �ӿڿ��Ĵ���˵���ĵ�
/*�����дϵͳ�Ĵ���
/************************************************************************/

#if !defined(PIO24B_h_)
#define PIO24B_h_


//////////////////////////////////////////////////////////////////////////
//

// ��ƽ״̬
enum e_PIOLevelVal
{
	LevelLow = 0,
	LevelHigh
};

// �ӿڿ���λģʽ
enum e_PIOResetMode
{
	FPGAProgramReset = 0x5a5a, // ��λPIO24B�ӿڿ���FPGA���򣬵�����λ���е�parameter�Ĵ���
		PramRegisterReset = 0x12ab // ��λ���е�parameter�Ĵ�����������λPIO24B�ӿڿ���FPGA����
};

// �жϵȴ�����ֵ
enum e_InterruptReturnVal
{
	WaitSuccess = 0,
		WaitTimeout,
		WaitCanceled,
		WaitFailed
};

//  ϵͳ�Ĵ���[9/24/2009 gZ]
enum e_PIOSystemRegister
{
	SystemRegister0	 = 0,	//	{"�汾��λ�Ĵ���", 0},
	SystemRegister1	,		//	{"��Ŀ�żĴ���0", 1},
	SystemRegister2	 ,		//	{"��Ŀ�żĴ���1", 2},
	SystemRegister3			//	{"���ϵͳ����״̬", 3},

};
// �����̶ȱ����ַ
enum e_PIOTriggerTable
{
	TriggerTable0 = 0,
	TriggerTable1,
	TriggerTable2,
	TriggerTable3
};

// ������
enum e_PIOCounter
{
	Counter0 = 0, //	{"�����źż�����0", 0},     
	Counter1,     //	{"�����źż�����1", 1},     
	Counter2,     //	{"�����źż�����2", 2},     
	Counter3,     //	{"�����źż�����3", 3},     
	Counter4,     //	{"����źż�����0", 4},     
	Counter5,     //	{"����źż�����1", 5},     
	Counter6,     //	{"����źż�����2", 6},     
	Counter7,     //	{"����źż�����3", 7},     
	Counter8,     //	{"����źż�����4", 8},     
	Counter9,     //	{"����źż�����5", 9},     
	Counter10,    //	{"����źż�����6", 10},     
	Counter11,    //	{"����źż�����7", 11},     
	Counter12,    //	{"��֡������", 12},     
	Counter13,    //	{"���ź�A�������", 13},     
	Counter14,    //	{"���ź�B�������", 14},     
    Counter15,    //	{"֡�źż�����", 15},     
	Counter16,    //	{"A����Ƶ�ʼĴ���", 16},     
	Counter17,    //	{"B����Ƶ�ʼĴ���", 17},     
	Counter18,    //	{"A��ÿ����������Ĵ���", 18},     
	Counter19,    //	{"B��ÿ����������Ĵ���", 19},     
	Counter20,    //	{"�����������ź�ʱ�������", 20},     
    Counter21,    //	{"��ѹ֡����", 21},     
	Counter22,    //	{"��ѹ֡����", 22},     
	Counter23,    //	{"���������������ʱ���м���", 23},     
	Counter24,    //	{"���� ", 24},     
	Counter25,    //	{"����", 25},     
	Counter26,    //	{"������x�Ĵ����ź�Դ ", 26},     
	Counter27,    //	{"����", 27},     
	Counter28,		//	{"ͼ��ż�����0", 28},
	Counter29,		//	{"ͼ��ż�����1", 29},
	Counter30,	//	{"ͼ��ż�����2", 30},
	Counter31		//	{"ͼ��ż�����3", 31},

};

// �������ƼĴ���
enum e_PIOParamRegister
{
	Parameter0 = 0,    //	{"�����������˲����������", 0},
	Parameter1,        //	{"�����������˲������", 1},
	Parameter2,        //	{"��������0�˲����������", 2},
	Parameter3,        //	{"���������źŷ�Ƶ", 3},
	Parameter4,        //	{"��������1�˲����������", 4},
	Parameter5,        //	{"����", 5},
	Parameter6,        //	{"��������2�˲����������", 6},
	Parameter7,        //	{"����", 7},
	Parameter8,        //	{"��������3�˲����������", 8},
	Parameter9,        //	{"����", 9},
	Parameter10,       //	{"��������0��С���", 10},
	Parameter11,       //	{"��������1��С���", 11},
	Parameter12,       //	{"��������2��С���", 12},
	Parameter13,       //	{"��������3��С���", 13},
	Parameter14,       //	{"����������������", 14},
	Parameter15,       //	{"PIO24B����˿ڿ���", 15},
	Parameter16,       //	{"��������˿�����ѡ��", 16},
	Parameter17,       //	{"����������������", 17},
	Parameter18,       //	{"��������˿�����ѡ��-��λ", 18},
	Parameter19,       //	{"��������˿�����ѡ��-��λ", 19},
	Parameter20,       //	{"��λ��������˿�", 20},
	Parameter21,       //	{"RS422����˿�����ѡ��", 21},
	Parameter22,       //	{"LVDS����˿�����ѡ��", 22},
	Parameter23,       //	{"��λLVDS/RS422����˿�", 23},
	Parameter24,       //	{"������֡�ź����޲���", 24},
	Parameter25,       //	{"������֡�ź����޲���", 25},
	Parameter26,       //	{"������֡�źŲ�֡����", 26},
	Parameter27,       //	{"���������ź���С����", 27},
	Parameter28,       //	{"����֡�ź����������", 28},
	Parameter29,       //	{"��Ч��ʹ��������", 29},
	Parameter30,       //	{"�����Чλ����", 30},
	Parameter31,       //	{"���ӳٶ���x��ģʽ�Ĵ���", 31},
	Parameter32,       //	{"���ӳٶ���x���ӳٲ���-��λ", 32},
	Parameter33,       //	{"���ӳٶ���x���ӳٲ���-��λ", 33},
	Parameter34,       //	{"��������x��ģʽ�Ĵ���", 34},
	Parameter35,       //	{"��������x�����ƼĴ���", 35},
	Parameter36,       //	{"��������x����ͼ���", 36},
	Parameter37,       //	{"��������x��ͼ���", 37},
	Parameter38,       //	{"��������x�����ƫ��λ��", 38},
	Parameter39,       //	{"�̶����0��������", 39},
	Parameter40,       //	{"Ƶ���������ʱ", 40},
	Parameter41,       //	{"����", 41},
	Parameter42,       //	{"����", 42},
	Parameter43,       //	{"�ӳٶ�������Ĵ������", 43},
	Parameter44,       //	{"�ӳٶ�������Ĵ�������", 44},
	Parameter45,       //	{"�ӳٶ���x�������������", 45},
	Parameter46,       //	{"������x�������������", 46},
	Parameter47,       //	{"�������������", 47},
	Parameter48,       //	{"����", 48},
	Parameter49,       //	{"������x���ӳٲ�����λ", 49},
	Parameter50,       //	{"������x���ӳٲ�����λ", 50},
	Parameter51,       //	{"��⵽�ڵ����ӳٴ���ʱ��", 51},
	Parameter52,       //	{"��⵽�ڵ��Ĵ�������", 52},
	Parameter53,       //	{"Ԥ�������ڵ�ļ��", 53},
	Parameter54,		   //	{"Qpick0���ƼĴ���", 54},
	Parameter55,			//	{"Qpick1���ƼĴ���", 55},
	Parameter56,		//	{"Qpick2���ƼĴ���", 56},
	Parameter57,		//	{"���ӳٶ���0���ӳٲ���-��λ", 57},
	Parameter58,		//	{"���ӳٶ���0���ӳٲ���-��λ", 58},
	Parameter59,		//	{"���ӳٶ���1���ӳٲ���-��λ", 59},
	Parameter60,		//	{"���ӳٶ���1���ӳٲ���-��λ", 60},
	Parameter61,		//	{"���ӳٶ���2���ӳٲ���-��λ", 61},
	Parameter62,		//	{"���ӳٶ���2���ӳٲ���-��λ", 62},
	Parameter63,		//	{"ͼ����ӳٸ��²���A", 63},
	Parameter64,			//	{"ͼ����ӳٸ��²���B", 64},
	Parameter65,
	Parameter66,
	Parameter67,
	Parameter68,
	Parameter69,
	Parameter70,
	Parameter71,
	Parameter72,
	Parameter73,
	Parameter74,
	Parameter75

};

// ϵͳ״̬�Ĵ���Satus0-IO�����״̬  address = 0x800
enum e_PIOInputState
{
	In0 = 0,           //	{"PIO24B����˿�״̬�Ĵ���", 0},
	In1,               //	{"PIO24B����˿�״̬�Ĵ���", 1},
	In2,               //	{"������״̬", 2},
	In3,               //	{"���ӳٶ���x��״̬", 3},
	In4,               //	{"��������x��״̬", 4},
	In5,               //	{"��������x���ӳٶӵ�״̬", 5},
	In6,               //	{"��������0����״̬", 6},
	In7,               //	{"��������1����״̬", 7},
	In8,               //	{"��������2����״̬", 8},
	In9,               //	{"���ӳٶ���0��״̬", 9},
	In10,              //	{"���ӳٶ���1��״̬", 10},
	In11,              //	{"���ӳٶ���2��״̬", 11}
	In12,              // ����
	In13,              // ����
	In14,              // ����
	In15               // ����

};


// ϵͳ״̬�Ĵ���Satus1-IO�����״̬ address = 0x802
enum e_PIOOutputState
{
	Out0 = 0,          // ��0·��PIO24B��������˿ڡ�
	Out1,              // ��1·��PIO24B��������˿ڡ�
	Out2,              // ��2·��PIO24B��������˿ڡ�
	Out3,              // ��3·��PIO24B��������˿ڡ�
	Out4,              // ��4·��PIO24B��������˿ڡ�
	Out5,              // ��5·��PIO24B��������˿ڡ�
	Out6,              // ��6·��PIO24B��������˿ڡ�
	Out7,              // ��7·��PIO24B��������˿ڡ�
	Out8,              // ����
	Out9,              // ����
	Out10,             // ����
	Out11,             // ����
	Out12,             // ����
	Out13,             // ����
	Out14,             // ����
	Out15              // ����
};

enum e_PIOSystemStateBit
{
	SysState0 = 0,          // ��0λ
	SysState1,              // ��1λ
	SysState2,              // ��2λ
	SysState3,              // ��3λ
	SysState4,              // ��4λ
	SysState5,              // ��5λ
	SysState6,              // ��6λ
	SysState7,              // ��7λ
	SysState8,              // ��8λ
	SysState9,              // ��9λ
	SysState10,             // ��10λ
	SysState11,             // ��11λ
	SysState12,             // ��12λ
	SysState13,             // ��13λ
	SysState14,             // ��14λ
	SysState15              // ��15λ
};

// ϵͳ״̬�Ĵ���
enum e_PIOSystemStatus
{
	SystemStatus2 = 0,       //   ����������״̬  address = 0x804
    SystemStatus3,           // ���ӳٶ���x��״̬ address = 0x806
	SystemStatus4,            // ��������x��״̬ address = 0x808
	SystemStatus5            // ��������x���ӳٶӵ�״̬ address = 0x80a
};


// �������ƼĴ���
enum e_PIOTriggerPosition
{
	TriggerPosition0 = 0,
	TriggerPosition1,
	TriggerPosition2,
	TriggerPosition3,
	TriggerPosition4,
	TriggerPosition5,
	TriggerPosition6,
	TriggerPosition7,
	TriggerPosition8,
	TriggerPosition9,	
	TriggerPosition10,
	TriggerPosition11,
	TriggerPosition12,
	TriggerPosition13,
	TriggerPosition14,
	TriggerPosition15,
	TriggerPosition16,
	TriggerPosition17,
	TriggerPosition18,
	TriggerPosition19,
	TriggerPosition20,
	TriggerPosition21,
	TriggerPosition22,
	TriggerPosition23,
	TriggerPosition24,
	TriggerPosition25,	
	TriggerPosition26,
	TriggerPosition27,
	TriggerPosition28,
	TriggerPosition29,
	TriggerPosition30,
	TriggerPosition31,
	TriggerPosition32,
	TriggerPosition33,
	TriggerPosition34,
	TriggerPosition35,
	TriggerPosition36,
	TriggerPosition37,
	TriggerPosition38,
	TriggerPosition39,
	TriggerPosition40,
	TriggerPosition41,	
	TriggerPosition42,
	TriggerPosition43,
	TriggerPosition44,
	TriggerPosition45,
	TriggerPosition46,
	TriggerPosition47,
	TriggerPosition48,
	TriggerPosition49,
	TriggerPosition50,
	TriggerPosition51,
	TriggerPosition52,
	TriggerPosition53,
	TriggerPosition54,
	TriggerPosition55,
	TriggerPosition56,
	TriggerPosition57,	
	TriggerPosition58,
	TriggerPosition59,
	TriggerPosition60,
	TriggerPosition61,
	TriggerPosition62,
	TriggerPosition63    
};
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �쳣

class AFX_EXT_CLASS CPIO24BException
{
//����
public:	
	int m_iCode;				// �쳣����
	CString m_strDescription;	// �쳣����
	CString m_strContext;		// �쳣������Ϣ
	
//����
public:
	
	CPIO24BException(int iCode, const CString &strDescription, const CString &strContext);
	~CPIO24BException();

	//�Ի�����ʾ
	void ShowMessageBox();
};
//
//////////////////////////////////////////////////////////////////////////

class CPIO24B;

class AFX_EXT_CLASS CDHPIO24B
{
public:

	
	CDHPIO24B();
	virtual ~CDHPIO24B();
	
	// ��	
	void Open();
	
	// �ر�
	void Close();	
	
	// ����
	void SetZero();
	
	// ��λ�ӿڿ�
	void ResetPortCard(e_PIOResetMode ResetMode);
	
	// ��ȡ�ӿڿ��汾��
	CString GetPortCardVersion();
	
	// ��ȡ�ӿڿ��������õ���Ŀ���
	CString GetProjectVersion();
	
	// �õ�������ֵ
	int GetCounterVal(e_PIOCounter eCounter);
	
	// �õ�����ֵ
	int GetParameterVal(e_PIOParamRegister eParameter);
	
	// ���ò���ֵ
	void SetParameterVal(e_PIOParamRegister eParameter, int iParameterVal);
	
	// �õ�IO�����״̬
	e_PIOLevelVal GetOutputState(e_PIOOutputState eOutputState);
	
	// ����IO�����״̬
	void SetOutputState(e_PIOOutputState eOutputState, e_PIOLevelVal eLevelVal);
	
	// �õ�IO�����״̬
	e_PIOLevelVal GetInputState(e_PIOInputState eInputState);
	
	// �õ�ϵͳ����״̬
	e_PIOLevelVal GetSystemStatus(e_PIOSystemStatus eSystemStatus,e_PIOSystemStateBit eStateBit);
	
	// �õ�������������
	int GetTriggerLines(e_PIOTriggerTable eTriggerTable,e_PIOTriggerPosition eTriggerPosition);
	
	// ���ô�����������
	void SetTriggerLines(e_PIOTriggerTable eTriggerTable,e_PIOTriggerPosition eTriggerPosition, int iTriggerLines);
	
	// ʹ���ж�
	void EnableInterrupt();
	
	// ��ֹ�ж�
	void DisableInterrupt();
	
	// �����ж��¼�����
	void SetInterruptEvent();
	
	// �ȴ��ն��¼�����
	e_InterruptReturnVal WaitInterruptEvent(int iWaitOutTime);	
	
	// ���ò����Ի���
	void CallParamDialog();

	BOOL SetSystemParam0Val(int iParam0);

	//��дϵͳ�Ĵ���
	BOOL SetSystemRegisterVal(e_PIOSystemRegister eSystemRegister,int iparamval);
	int GetSystemRegisterVal(e_PIOSystemRegister eSystempRegister);
	
private:
	CPIO24B* m_pIOCard;
};


#endif// !defined(DHPIO24B_h_)