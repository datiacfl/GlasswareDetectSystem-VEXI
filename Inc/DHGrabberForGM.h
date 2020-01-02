/************************************************************************/
/* Copyright (c) 2006, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�з�����     
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForGM.h												
/* �ļ���ʶ�� �����ù���ƻ���
/*
/* ժҪ�� �����ɼ�����
/* ��ǰ�汾�� 3.0.0.2 beta 2
/* �޸��ߣ����ļ�
/* �޸�����ժҪ����ͷ�ļ���DC����������ΪGM��
/* ������ڣ� 2010��06��10��
/*
/* ��ǰ�汾�� 3.0.0.2 beta 1
/* �޸��ߣ����ļ�
/* �޸�����ժҪ�������������ƿ��ơ�
/* ������ڣ� 2010��06��10��
/*
/* ��ǰ�汾�� 3.0.0.1 beta 3
/* �޸��ߣ����ļ�
/* �޸�����ժҪ���޸�DHGrabberForGM.h�к궨�壬��ΪDHGrabber_h_��
/* ������ڣ� 2010��01��11��
/*
/* ��ǰ�汾�� 3.0.0.1 beta 2
/* �޸��ߣ����ļ�
/* �޸�����ժҪ�����±���ɼ�����̬�⡣
/* ������ڣ� 2010��01��05��
/*
/* ��ǰ�汾�� 3.0.0.1 beta 1
/* �޸��ߣ����ļ�
/* �޸�����ժҪ����ʼ���ṹ�弰�ɼ��ص��ṹ����롰�ɼ������ͱ�š���
/* ������ڣ� 2009��12��25��
/*
/* ��ǰ�汾�� 1.0
/* ���ߣ� ���ļ�
/* ������ڣ� 2009��12��03��
/************************************************************************/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

/*
�ɼ������ͱ�Ŷ�������
0:ģ��ɼ���
1:DALSA X64�ɼ���
2:AVT���
3:ǧ�������
4:��˾CG300ģ��ɼ���
5:��˾1394���
6:EURESYS �ɼ���*/

typedef struct _GBSignalInfoStruct//�ص���Ϣ�ṹ
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

typedef struct _GBInitStruct//�ɼ�����ʼ���ṹ
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

typedef struct _GBErrorInfoStruct//������Ϣ�ṹ
{
   	int  nErrorCode;						//������루0��������
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

#endif// !defined(Grabber_h_)

#if !defined(DHGrabberGM_h_)
#define DHGrabberGM_h_

//////////////////////////////////////////////////////////////////////////
//
//��˾���ר�в���
enum GMParamID
{
	GMSnapMode = 0,			// �ɼ�ģʽ
	GMShutterUnit,			// �ع�ʱ�䵥λ
	GMShutterTime,			// �ع�ʱ��
	GMGain,					// ����
	GMStrobeOnOff,			// ����ƿ���
	GMStrobeTrigger,		// ������źż���
	GMAutoStrobeOnOff		// �Զ�����ƿ���
};

//������붨��
enum GMErrorStruct
{
	GMErrorNoFindCam = 0,		// û���ҵ����
	GMErrorGrabberSN,			// �����ų����ܹ��ҵ��������
	GMErrorGetCamInfo,			// ��ȡ�����Ϣʧ��
	GMErrorValOverFlow,			// �������
	GMErrorOpenCam,				// �����ʧ��
	GMErrorInit,				// ��ʼ��ʧ��
	GMErrorStartGrab,			// ��ʼ�ɼ�ʧ��
	GMErrorStopGrab,			// ֹͣ�ɼ�ʧ��
	GMErrorClose,				// �ر�ʧ��
	GMErrorSendBufAdd,			// ��ȡͼ���ڴ��ַʧ��
	GMErrorGetParam,			// �Ƿ���ȡ����
	GMErrorSetParam,			// �Ƿ����ò���
	GMErrorParamDlg,			// ���ò������öԻ���ʧ��
	GMErrorReadIniFile,			// ��ȡ�����ļ�ʧ��
	GMErrorSaveCamSetting,		// �������������ʧ��
	GMErrorLoadCamSetting,		// �������������ʧ��
	GMErrorStartupCamSetting,	// �����������������ʧ��
	GMErrorGetCurCamSetting		// �õ������ǰʹ�õĲ�����ʧ��
};

//�����������ģʽ
enum CamMemSet
{
	Manufacturer = 0,
	UserSet1,
	UserSet2,
	UserSet3
};
//
//////////////////////////////////////////////////////////////////////////

//�ɼ���
class _declspec(dllexport) CDHGrabberGM : public CGrabber
{
//����
public:
	CDHGrabberGM();
	virtual ~CDHGrabberGM();
	
	//��ʼ��
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//�ر�
	BOOL Close();

	//��ʼ�ɼ�
	BOOL StartGrab();

	//ֹͣ�ɼ�
	BOOL StopGrab();

	//��֡�ɼ�
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
	// ǧ�������ר�нӿ�

	//���ò���
	BOOL GMSetParamInt(GMParamID Param, int nInputVal);
	
	//�õ�����
	BOOL GMGetParamInt(GMParamID Param, int &nOutputVal);

	//�����������������
	BOOL SaveCameraSetting(CamMemSet Param);
	
	//�����������������
	BOOL LoadCameraSetting(CamMemSet Param);

	//�����������������
	BOOL SetStartupCameraSetting(CamMemSet Param);

	//
	//////////////////////////////////////////////////////////////////////////
	
//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberGM_h_)
