#pragma once
#include "Omron.h"
const int maxpath=512;

typedef struct _PLCSTATUS
{
	bool bOnline;//PLC���߱�־������Ϊtrue������Ϊfalse
	bool bRunning;//�豸���б�־������Ϊtrue��ֹͣλfalse
	bool bManual;//�ֶ�״̬��־���豸�л����ֶ�״̬ʱΪtrue��falseʱ�ɲ����
	bool bTestMode;//����״̬��־�����Բ�����ֵʱΪtrue��falseʱ�ɲ����
	int nAlarm;
	int nCh0;
	int nCh1;
	int nCh100;
	int nCh101;
	int nEncoder;
	_PLCSTATUS()
	{
		bOnline=false;
		bRunning=false;
		bManual=false;
		bTestMode=false;
		nAlarm=0;
		nCh0=0;
		nCh1=0;
		nCh100=0;
		nCh101=0;
		nEncoder=0;
	}
}s_PLCStatus;


class __declspec(dllexport) CHMIDLL
{
public:
	CHMIDLL(void);
	~CHMIDLL(void);
public:
	//�������·��������InitSerialCommǰʹ��
	void InitPath(char szPath[maxpath]);
	//���ò������öԻ���
	void CallParamDlg(void);
	//��ʼ������
	bool InitSerialComm(void);
	//�رմ���
	void CloseComm(void);
	//��ȡPLC����״̬��������Ϣ/�������״̬��
	bool GetPLCStatus(s_PLCStatus &s);
	//�����Ƿ���ñ�־��falseʱGetPLCStatus����ʹ��
	bool m_bIsCommBusy;
	bool SetAlarm(int nAlarm);//������߱�����20160913
protected:
	void GetAppPath(char szFullPath[maxpath]);
	void SaveCommInfo();
	void LoadCommInfo();
	//�жϵ�ǰ·����Config�ļ����Ƿ���ڣ�����������򴴽�
	void IsFolderExist();
	int m_nPort;
	int m_nBaud;
	COmron *m_pOmron;
	char m_szPath[maxpath];
};
