/************************************************************************/
/* Copyright (c) 2009, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�Ӿ�ϵͳ��  
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForDC.h	
/* ժҪ�� �����ɼ����ࣨ��˾1394��USB�����
/*
/* ��ǰ�汾�� 3.0.0.1 Beta3
/* �޸��ߣ� ���ǿ
/* �޸�����ժҪ��3.0.0.1 Beta3:���������ع�����ȹ���
/* ������ڣ� 2010��2��21��

/* ��ǰ�汾�� 3.0.0.1 Beta2
/* �޸��ߣ� ���ǿ
/* �޸�����ժҪ��3.0.0.1 Beta2:���������ع�����ȹ���
/* ������ڣ� 2010��1��6��

/* ��ǰ�汾�� 3.0.0.1 Beta1
/* �޸��ߣ� ���ǿ
/* �޸�����ժҪ����ʼ���ṹ�弰�ɼ��ص��ṹ����롰�ɼ������ͱ�š���
/* ������ڣ� 2009��12��24��
/*
/* ��ǰ�汾�� 1.0.0.2
/* �޸��ߣ� ������
/************************************************************************/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

/*
�ɼ������ͱ�Ŷ�������
0:ģ��ɼ���
1:DALSA X64�ɼ���
2:AVT���
3:ǧ�������
4:��˾CG300ģ��ɼ���
5:��˾1394���
6:EURESYS �ɼ���*/

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

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
	char strDeviceMark[GBMaxTextLen];		//�豸��ʶ
	char strGrabberFile[GBMaxFileNameLen];	//���ڳ�ʼ�����ļ�
	PGBCALLBACK CallBackFunc;				//�ص�����ָ��
	PVOID Context;							//���ӵ�лص������Ķ����thisָ��
	
	int iReserve1;							// �����ֶ�1
	int iReserve2;							// �����ֶ�2

}s_GBINITSTRUCT;//�ɼ�����ʼ���ṹ

typedef struct _GBErrorInfoStruct//������Ϣ�ṹ
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

#if !defined(DHGrabberDC_h_)
#define DHGrabberDC_h_

// ��˾���ר�в���
enum DCParamID
{
	DCSnapMode,				// ͼ��ɼ�ģʽ
	DCGain,					// ����
	DCExposure,				// �ع�ʱ��
	DCBRIGHTNESS,			// ����
	DCPACKET,				// ����
	RESERVED0,				// �����������
	RESERVED1				// У������
};

//�ɼ���
class _declspec(dllexport) CDHGrabberDC : public CGrabber
{
	//����
public:
	CDHGrabberDC();
	virtual ~CDHGrabberDC();
	
	//��ʼ��
	BOOL Init(const s_GBINITSTRUCT* pInitParam);
	
	//�ر�
	BOOL Close();
	
	//��ʼ�ɼ�
	BOOL StartGrab();
	
	//ֹͣ�ɼ�
	BOOL StopGrab();
	
	// ��֡�ɼ� 
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
	// ��˾���ר�нӿ�	
	BOOL DCSetParamInt(DCParamID Param, int nInputVal1,int nInputVal2 = 0,int nInputVal3 = 0,int nInputVal4 = 0,int nInputVal5 = 0,void *sInputVal6 = NULL);
	BOOL DCGetParamInt(DCParamID Param, int &nOutputVal1,int &nOutputVal2,int &nOutputVal3);	
	
	void SaveParamToINI(const CString &strPathName);		// �������������Ϣ
	
	//
	//////////////////////////////////////////////////////////////////////////
	
	//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberDC_h_)