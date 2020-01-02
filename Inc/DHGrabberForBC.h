/************************************************************************/
/* Copyright (c) 2010, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�з�����     
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForBC.h	
/* ժҪ�� �����ɼ����ࣨBasler 1394�����

/* ��ǰ�汾�� 3.0.0.1 beta1
/* �޸��ߣ� ���ǿ
/* �޸�����ժҪ���޸Ľӿ��ļ�
/* ������ڣ� 2010��11��2��
/*
/* ��ǰ�汾�� 1.0
/* ���ߣ� ��׿��,������
/* ������ڣ� 2006��08��15��
/*
/* ��ǰ�汾�� 1.0.1
/* ���ߣ� ���ǿ
/* �޸����ڣ� 2010��11��2��
/************************************************************************/


/*
�ɼ������ͱ�Ŷ�������
0:ģ��ɼ���
1:DALSA X64�ɼ���
2:AVT���
3:ǧ�������
4:��˾CG300ģ��ɼ���
5:��˾1394���
6:EURESYS �ɼ���
7.��˾USB���
10.Basler 1394���*/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

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
	char strDeviceMark[GBMaxTextLen];		// �豸��ʶ
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



//////////////////////////////////////////////////////////////////////////
//�ɼ���
#if !defined(DHGrabberBC_h_)
#define DHGrabberBC_h_

//////////////////////////////////////////////////////////////////////////
//Basler���ר�в���
enum BCParamID	
{
	BCColorCode = 0,		//��ɫ���룬��ͼ���ʽ(Mono8, YUV422�ȵ�)
	BCTriggerOnOff,			//����Ƿ����ⴥ��ģʽ 1���� 0����
	BCTriggerMode,			//����ģʽ
	BCTriggerPolarity,		//��������
	BCBrightness,			//������ȴ�С
	BCShutter,				//�������ֵ
	BCBytes,				//��������ֽ���
	BCGain,					//��������С
	BCU,					//���Uֵ
 	BCV						//���Vֵ
};

enum BCParamVal	
{
	BCColor_Mono8 = 0,			//Mono8��ʽ
	BCColor_YUV8_411,			//YUV8_411
	BCColor_YUV8_422,			//YUV8_422
	BCColor_YUV8_444,			//YUV8_444
	BCColor_Raw8,				//Raw8(Bayerת��ǰ����)
	BCColor_Mono16U,			//Mono16(unsigned)
	BCColor_Mono16S,			//Mono16(signed)
	BCColor_RGB8,				//RGB8
	BCColor_RGB16U,				//RGB16(unsigned)
	BCColor_RGB16S,				//RGB16(signed)
	BCColor_Raw16,				//Raw16
	BCColor_Unknown,			//����δ֪����ɫ����
	BCTriggerOn,				//�ⴥ������
	BCTriggerOff,				//�ⴥ���ر�
	BCTriggerMode0,				//�ⴥ��ģʽ0����BCTriggerOn����Ч
	BCTriggerMode1,				//�ⴥ��ģʽ1����BCTriggerOn����Ч
	BCTriggerPolarityLowActive, //�ⴥ���͵缫����BCTriggerOn����Ч
	BCTriggerPolarityHighActive //�ⴥ���ߵ缫����BCTriggerOn����Ч
};

//////////////////////////////////////////////////////////////////////////
//�ɼ���
class _declspec(dllexport) CDHGrabberBC : public CGrabber
{
//����
public:

	CDHGrabberBC();
	virtual ~CDHGrabberBC();
	
	//��ʼ��
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//�ر�
	BOOL Close();

	//��ʼ�ɼ�
	BOOL StartGrab();

	//ֹͣ�ɼ�
	BOOL StopGrab();

	//���ò���
	BOOL SetParamInt(GBParamID Param, int nInputVal);
	
	//�õ�����
	BOOL GetParamInt(GBParamID Param, int &nOutputVal);

	//���ò����Ի���
	void CallParamDialog();

	//�õ�������Ϣ
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////Basler�����չ�ӿں���
	
	//SnapShot��֡�ɼ�
	BOOL Snapshot();

	//���òɼ���������
	BOOL BCSetAOI(RECT rtAOI);

	//��ȡ�ɼ���������
	BOOL BCGetAOI(RECT &rtAOI);
	
	//�����������
	BOOL BCSetParamPro(BCParamID Param, int nInputVal);
	BOOL BCSetParamPro(BCParamID Param, BCParamVal ParamValInput);

	//��ȡ�������
	BOOL BCGetParamPro(BCParamID Param, int &nOutputVal);
	BOOL BCGetParamPro(BCParamID Param, BCParamVal &ParamValOutput);

	//�õ�������к�
 	BOOL GetCameraSN(CString& strRetCameraSN);
	//  [7/10/2006]
 
	//! Converts a 422YUV8 to a R,G,B three channel  (works on raw pointers)  //  [8/15/2006]
    void BCConvertYUV422ToRGB(BYTE* pDestR, BYTE* pDestG, BYTE* pDestB, const BYTE* pSource,  const CSize& Size, unsigned int lineoffset = 0);

	//! Converts a 422YUV8 to a RGB8 image (works on raw pointers)  //  [8/15/2006]
    void BCConvertYUV422ToRGB(BYTE* pDest, const BYTE* pSource,  const CSize& Size, unsigned int lineoffset = 0);

//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(GrabberExport_h_)
