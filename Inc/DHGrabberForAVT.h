/************************************************************************/
/* Copyright (c) 2012, �������ͼ���Ӿ����޹�˾  
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForAVT.h	
/* ժҪ�� ���AVT���FGCamera�汾(3.00) ���и��߰汾����Ҫ����
/*
/* ��ǰ�汾�� 6.0.0.1Beta1
/* �޸��ߣ� ���ǿ
/* �޸����ݣ��������
/* ������ڣ� 2012-07-31
/************************************************************************/

/*
�ɼ������ͱ�Ŷ�������
0:ģ��ɼ���
1:DALSA X64�ɼ���
2:AVT���
3:ǧ�������
4:��˾CG300ģ��ɼ���
5:��˾1394���
6:EURESYS �ɼ���*/


#if !defined(DHGrabber_h_)
#define DHGrabber_h_

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

typedef struct _GBSignalInfoStruct//�ص���Ϣ�ṹ
{
	PVOID Context;								// ���ӵ�лص������Ķ����thisָ��
	int iGrabberTypeSN;							// �ɼ������ͱ��
	int nGrabberSN;								// �ɼ������
	int nErrorCode;								// ������루0��������
	int nFrameCount;							// �Ѳɼ���֡����
	char strDescription[GBMaxTextLen];			// ������Ϣ
	int iReserve1;								// �����ֶ�1
	int iReserve2;								// �����ֶ�2	
}s_GBSIGNALINFO;//�ص���Ϣ�ṹ

//�ص�����ָ������
typedef void (WINAPI *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

typedef struct _GBInitStruct//�ɼ�����ʼ���ṹ
{
	int iGrabberTypeSN;						// �ɼ������ͱ��
	int nGrabberSN;							// �ɼ������
    char strDeviceName[GBMaxTextLen];		// �豸����
	char strDeviceMark[GBMaxTextLen];		// �豸��ʶ  ���ڱ�ʶ���ӵ������˱�ʶһ��
	char strGrabberFile[GBMaxFileNameLen];	// ���ڳ�ʼ�����ļ�
	PGBCALLBACK CallBackFunc;				// �ص�����ָ��
	PVOID Context;							// ���ӵ�лص������Ķ����thisָ��	
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

//�ɼ���
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
	
	/////////////////////////////////////////�߸�ͨ�ýӿں���
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
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0 ;
	
};

#endif // !define(DHGrabber_h_)

#if !defined(DHGrabberAVT_h_)
#define DHGrabberAVT_h_

//////////////////////////////////////////////////////////////////////////
//�ɼ���
#define	_EXPORTING
#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)  //�������ʱʹ��
#else
#define CLASS_DECLSPEC    __declspec(dllimport)	 //��̬��Ӧ��ʱʹ��
#endif


enum AVTParamID	//AVT���ר�в���
{
	AVTColor,               //�������  �ڰ׺Ͳ�ɫ 
	AVTBrightness,			//������ȴ�С
	AVTShutter,				//�������ֵ
	AVTGain,				//��������С
	AVTU,					//���Uֵ
 	AVTV,					//���Vֵ
	AVTTriggerOnOff,		//����ⴥ���Ƿ���
	AVTTemperature			//����¶�
};


// AVT���ר�нӿ�
enum AVTParamVal
{
	AVTTriggerOff = 0,		//�ⴥ���ر�//�ڲ�����,�����ɼ�
	AVTTriggerOn,	    	//�����ش���//�ⴥ������
	AVTTriggerMode2,		//�½��ش���
	AVTTriggerMode3,		//�ߵ�ƽ����
	AVTTriggerMode4,		//�͵�ƽ����
	AVTTriggerMode5,		//���ģʽ�����ش���
	AVTTriggerMode6,		//���ģʽ�½��ش���	
};

class CLASS_DECLSPEC CDHGrabberAVT : public CGrabber
{
//����
public:
	CDHGrabberAVT();
	virtual ~CDHGrabberAVT();
	
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
	// AVT���ר�нӿ�
	/************************************************************************/
	/*  ���ܣ������������
	/*  ���룺AVTParamID  �������� ������Ķ���
	/*	���룺int nInputVal  ������Ӧ��ֵ  
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTSetParamPro(AVTParamID Param, int nInputVal);	

	/************************************************************************/
	/*  ���ܣ���ȡ������� 
	/*  ���룺AVTParamID  �������� ������Ķ���
	/*	�����int nOutputVal  ������Ӧ��ֵ  
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTGetParamPro(AVTParamID Param, int &nOutputVal);

	/************************************************************************/
	/*  ���ܣ������������
	/*  ���룺AVTParamID  �������� ������Ķ���
	/*	���룺AVTParamVal  ������Ӧ��ֵ  ������Ķ���
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTSetParamPro(AVTParamID Param, AVTParamVal ParamValInput);

	/************************************************************************/
	/*  ���ܣ���ȡ������� 
	/*  ���룺AVTParamID  �������� ������Ķ���
	/*	�����AVTParamVall  ������Ӧ��ֵ   ������Ķ���
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTGetParamPro(AVTParamID Param, AVTParamVal &ParamValOutput);

	/************************************************************************/
	/*  ���ܣ���������ɼ���ʽ 
	/*  ���룺AVTParamVal  �������� ������Ķ���
	/*	�������
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTSetTriggerParam(AVTParamVal ParamValInput);

	/************************************************************************/
	/*  ���ܣ������������к�
	/*  �����nGaidHigh  ����λ
	/*	�����nGaidLow   �;�λ
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTGetCamGuid(int &nGaidHigh,int &nGaidLow);

	/************************************************************************/
	/*  ���ܣ���òɼ���������
	/*  �����RECT    �ɼ����ڴ�С
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTGetAOI(RECT &rtAOI);

	/************************************************************************/
	/*  ���ܣ����òɼ���������
	/*  ���룺RECT    �ɼ����ڴ�С
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL AVTSetAOI(RECT rtAOI);

	/************************************************************************/
	/*  ���ܣ����������λ������������������쳣�޻ص������ʹ�ã�
	/*  ��������������
	/*  ��һ��:����ڲ�����Ĭ������;
	/*  �ڶ���: bus resets will occur;
	/*	������:	The FPGA will be rebooted; 
	/*	���Ĳ�:����INI�����ļ�����;
	/*  ���룺
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
	BOOL Reset();

	/************************************************************************/
	/*  ���ܣ�����Ĭ��INI�����ļ�
	/*  ���룺sInitFile ��ȷ��ʽ��D:\\Run\\CameraParm.ini
	/*	���أ���ȷ:TRUE   ����:FALSE
	/************************************************************************/
//	BOOL CreateDefaultINI(CString &sInitFile);

	//////////////////////////////////////////////////////////////////////////
//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberAVT_h_)

//////////////////////////////////////////////////////////////////////////
//ʹ��˵��:   Ŀǰ�ɼ������AVT����������汾Ϊ2.10  
//����������ͣ�Guppy��Stingray��Marlinϵ��
//1. ��ԭ����ini������������ļ�ֱ�Ӹ���Ϊ���Ĭ�ϵĲ��������ļ�XML
//2. ����������޸����£�
//   �豸A���=0
//   �豸A����=6735372523180860609 (�����Լ�����һ������)
//   �豸A��ʶ=6735372523180860609
//   �豸A��ʼ���ļ���=GuppyConfig.xml   //����AVT ��SmartView�����xml�ļ����Ƹ���������
//3. ���⽫�����XML�ļ�������Config�ļ�����(��ԭ����GuppyConfig.iniͬ��Ŀ¼��)
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//�޸ļ�¼
/*
2010.12.7  V4.0.0.3  �ɭ**Ŀ�ģ��޸Ķ�������дXML�ļ��ļ�***
�޸����ݣ�
1. ���������ʱ���޸Ĳ������浽XML�ļ������⣻
2. ����������кţ�����ֻ��д��ǰ���15λ(6+9),����������޸����£�
�豸A���=0
�豸A����=AVT
�豸A��ʶ=673537252318086
�豸A��ʼ���ļ���=GuppyConfig.xml   //����AVT ��SmartView�����xml�ļ����Ƹ���������
���⻹���ݺ������0609�汾
3. �޸Ľӿ�AVTGetCamGuid���ƣ���ԭ����AVTGetCamGaid�޸ĳ�AVTGetCamGuid
4. �����˳�Ĭ�ϱ���XML�ļ�

2010.5.24  V4.0.0.1Beta1  **Ŀ�ģ���ԭ�е�ini�����ļ�����ֱ��ʹ����������xml�ļ�***
�޸����ݣ�
1. ��ԭ����ini������������ļ�ֱ�Ӹ���Ϊ���Ĭ�ϵĲ��������ļ�XML��
2. ����������޸����£�
�豸A���=0
�豸A����=6735372523180860609
�豸A��ʶ=6735372523180860609
�豸A��ʼ���ļ���=GuppyConfig.xml   //����AVT ��SmartView�����xml�ļ����Ƹ���������
3. ���⽫�����XML�ļ�������Config�ļ�����(��ԭ����GuppyConfig.iniͬ��Ŀ¼��)

2010.5.26  V4.0.0.1Beta2  **Ŀ�ģ���ֹͣ�ɼ�ʱ����������������Ի����ϣ����޸ĵ������������ΪXML**
�޸����ݣ�
1. ��������������б���ΪXML��Beta2
2. ��ӻ�ȡ�������(�ڰ׺Ͳ�ɫ)���ܣ�ͨ��AVTColor������ã�

2010.6.21  V4.0.0.1Beta3  **Ŀ�ģ������ڼ�������(������ڲɼ�ʱ)���������������������һ��ʹ��**
�޸����ݣ�
1. ����˳�ʱ�ٱ���һ��XML��

2010.6.23  V4.0.0.1Beta4  
�޸����ݣ�
1. ������AVT����ɼ������⣻
*/
//////////////////////////////////////////////////////////////////////////