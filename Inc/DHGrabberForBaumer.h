/************************************************************************/
/* Copyright (c) 2012, �������ͼ���Ӿ����޹�˾�Ӿ�ϵͳ��  
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForBaumer.h	
/* ժҪ�� �����ɼ�����(Baumerǧ�������)
/* �����̬�������Baumerǧ���������
/* Ŀǰ�Ѿ���������ͺţ�
/* DXG04h
/*���ù��̣�(������ù��̲ο�����)
/*
/* ��ǰ�汾�� 3.0.0.1 beta1
/* �޸��ߣ� ���ǿ
/* �޸�����ժҪ������ͷ�ļ�ע��
/* ������ڣ� 2012��6��11��
/************************************************************************/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

//�ص���Ϣ�ṹ
typedef struct _GBSignalInfoStruct
{
	PVOID Context;								//���ӵ�лص������Ķ����thisָ��
	int iGrabberTypeSN;							// �ɼ������ͱ��
	int nGrabberSN;								//�ɼ������
	int nErrorCode;								//������루0��������
	int nFrameCount;							//�Ѳɼ���֡����
	char strDescription[GBMaxTextLen];			//������Ϣ

	int iReserve1;								// �����ֶ�1
	int iReserve2;								// �����ֶ�2
	
}s_GBSIGNALINFO;//�ص���Ϣ�ṹ

//�ص�����ָ������
typedef void (WINAPI *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

//�ɼ�����ʼ���ṹ
typedef struct _GBInitStruct
{
	int iGrabberTypeSN;						// �ɼ������ͱ��
	int nGrabberSN;							//�ɼ������
    char strDeviceName[GBMaxTextLen];		//�豸����
	char strDeviceMark[GBMaxTextLen];		// �豸��ʶ
	char strGrabberFile[GBMaxFileNameLen];	//���ڳ�ʼ�����ļ�
	PGBCALLBACK CallBackFunc;				//�ص�����ָ��
	PVOID Context;							//���ӵ�лص������Ķ����thisָ��
	
	int iReserve1;							// �����ֶ�1
	int iReserve2;							// �����ֶ�2

}s_GBINITSTRUCT;//�ɼ�����ʼ���ṹ

//������Ϣ�ṹ
typedef struct _GBErrorInfoStruct
{
   	int nErrorCode;							//������루0��������
	char strErrorDescription[GBMaxTextLen];	//��������
	char strErrorRemark[GBMaxTextLen];		//������Ϣ

}s_GBERRORINFO;//������Ϣ�ṹ

//��������
enum GBParamID
{
	GBImageWidth = 0,		//ͼ���� (��λ:�ֽ�)
	GBImageHeight,			//ͼ��߶� (��λ:�ֽ�)
	GBImagePixelSize,		//ͼ�����ش�С (��λ:�ֽ�)
	GBImageBufferSize,		//ͼ�񻺳�����С (��λ:�ֽ�)
	GBImageBufferAddr,		//ͼ�񻺳�����ַ
	GBGrabberTypeSN			//�ɼ������ͱ��
};

//������붨��
const int GBOK = 0;

class CGrabber
{
//����
public:
	CGrabber()
	{
	}
	virtual ~CGrabber()
	{
	}
	
	//��ʼ��
	virtual BOOL Init(const s_GBINITSTRUCT* pInitParam) = 0;

	//�ر�
	virtual BOOL Close() = 0;

	//��ʼ�ɼ�
	virtual BOOL StartGrab() = 0;

	//ֹͣ�ɼ�
	virtual BOOL StopGrab() = 0;
	
	//��֡�ɼ�
	virtual BOOL Snapshot() = 0;

	//���ò���
	virtual BOOL SetParamInt(GBParamID Param, int nInputVal) = 0;
	
	//�õ�����
	virtual BOOL GetParamInt(GBParamID Param, int &nOutputVal) = 0;
	
	//���ò����Ի���
	virtual void CallParamDialog() = 0;
	
	//�õ�������Ϣ
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0;
};

#endif// !defined(DHGrabber_h_)



#if !defined(DHGrabberBAUMER_h_)
#define DHGrabberBAUMER_h_

//////////////////////////////////////////////////////////////////////////
//Baumerר�ò���
enum BaumerParamID	
{
	BaumerFramesPerSecondsContinuous = 0,
	BaumerExposure,
	BaumerExposureMin,
	BaumerExposureMax,
	BaumerGain,
	BaumerGainMin,
	BaumerGainMax,
	BaumerTriggerDelay
};

//Baumerר�ò���ֵ
enum BaumerParamVal
{
	BaumerTriggerOff = 0,
	BaumerTriggerOn
};

//������붨��
enum ErrorStruct
{
	NormalState = 0,    // ����״̬
	ErrorNoFindCam,	    // û���ҵ����
	ErrorValOverFlow,	// �������
	ErrorGrabberSN,		// �����ų����ܹ��ҵ��������  ��������� 
	ErrorGetCamInfo,	// �õ������Ϣʧ��              ��������� 
	ErrorOpenCam,		// �����ʧ��                  ���������
	ErrorInit,			// ��ʼ��ʧ��                    ���������
	ErrorStartGrab,		// ��ʼ�ɼ�ʧ��                  ���������
	ErrorStopGrab,		// ֹͣ�ɼ�ʧ��                  ���������
	ErrorClose,			// �ر�ʧ��                      ���������
	ErrorSendBufAdd,	// ����ͼ���ڴ��ַʧ��          ���������
	ErrorGetParam,		// �Ƿ���ȡ����                  ���������
	ErrorSetParam,		// �Ƿ����ò���                  ���������
	ErrorParamDlg,	    // ���ò������öԻ���ʧ��        ���������
	ErrorReadIniFile,	// ��ȡ�����ļ�ʧ��              ���������
	ErrorLostFrame,     // �ɼ���TrashBuffer��֡         ���������
	ErrorSysLostFrame,  // ϵͳ�ڲ������Ķ�֡
	ErrorTriggerIgnored,// ͨ����Ϊ�ⴥ��Ƶ�ʹ���
	ErrorSaveInitFile	//�����ʼ���ļ�ʧ��
};

//////////////////////////////////////////////////////////////////////////
//�ɼ���
#define	_EXPORTING

#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)  //�������ʱʹ��
#else
#define CLASS_DECLSPEC    __declspec(dllimport)	 //��̬��Ӧ��ʱʹ��
#endif

class CLASS_DECLSPEC CDHGrabberBaumer : public CGrabber
{
//����
public:
	CDHGrabberBaumer();
	virtual ~CDHGrabberBaumer();
	
	//��ʼ��
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//�ر�
	BOOL Close();

	//��ʼ�ɼ�
	BOOL StartGrab();

	//ֹͣ�ɼ�
	BOOL StopGrab();

	//����ɼ�
	BOOL Snapshot();
	
	//���ò���
	BOOL SetParamInt(GBParamID Param, int nInputVal);
	
	//�õ�����
	BOOL GetParamInt(GBParamID Param, int &nOutputVal);

	//���ò����Ի���
	void CallParamDialog();

	//�õ�������Ϣ
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////////////////////////////////////////
	// Baumerר�нӿ�
	
	/************************************************************************/
	/*  ���ܣ����òɼ�������
	/*  ���룺Ŀǰֻ֧�� DSLineCropHeight�� �� DSLineMaxCropHeight��
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerSetParamPro(BaumerParamID Param, int nInputVal);	


	/************************************************************************/
	/*  ���ܣ���ȡ�ɼ�������(Ŀǰû���κι���)
	/*  ���룺��
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerGetParamPro(BaumerParamID Param, int &nOutputVal);


	/************************************************************************/
	/*  ���ܣ����òɼ�������
	/*  ���룺Ŀǰֻ֧�� DSLineExternalTriggerOnOff ��
	/*        �������ã�
	/*        ֡�ź�ʹ�� DSLineExternalTriggerOnOff + DSLineTriggerOn
	/*        ֡�ź�ʧЧ DSLineExternalTriggerOnOff + DSLineTriggerOff
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerSetParamPro(BaumerParamID Param, BaumerParamVal nInputVal);	


	/************************************************************************/
	/*  ���ܣ���ȡ�ɼ�������
	/*  ���룺Ŀǰֻ֧�� DSLineExternalTriggerOnOff ��
	/*	�����֡�ź�ʹ���򷵻� DSLineTriggerOn    ֡�ź�ʧЧ�򷵻�DSLineTriggerOff
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerGetParamPro(BaumerParamID Param, BaumerParamVal& nOutputVal);


	/************************************************************************/
	/*  ���ܣ����ô���״̬
	/*  ���룺BaumerParamVal
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerSetTriggerParam(BaumerParamVal ParamValInput);
	/************************************************************************/
	/*  ���ܣ���ȡ����״̬
	/*  ���룺��
	/*	�����BaumerParamVal
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerGetTriggerParam(BaumerParamVal &ParamValInput);

	BOOL BaumerSetParamPro(BaumerParamID Param, float nInputVal);	

	BOOL BaumerGetParamPro(BaumerParamID Param, float& nOutputVal);



	/************************************************************************/
	/*  ���ܣ����òɼ���������(��ɾ������)
	/*  ���룺��
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerGetAOI(RECT &rtAOI);


	/************************************************************************/
	/*  ���ܣ����òɼ���������(��ɾ������)
	/*  ���룺��
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL BaumerSetAOI(RECT rtAOI);


//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberBAUMER_h_)


//////////////////////////////////////////////////////////////////////////
//ʹ��˵��
/*

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//�޸ļ�¼
/*

*/
//////////////////////////////////////////////////////////////////////////

