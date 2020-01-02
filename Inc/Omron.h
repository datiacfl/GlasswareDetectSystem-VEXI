#ifdef UNICODE
#define   MAXBUFFER 1024
#else
#define   MAXBUFFER 512
#endif // !UNICODE
#pragma once
#include "serial.h"

class COmron :
	public CSerial
{
protected:
	int GetHexInt(char ch);
	char GetHexChar(int nData);
	int GetControlData(char* csData,int nAddr);//
public:
	bool GetBit(const int nData, int nBit);
	bool SetControlData(int nAddr,int nData);//�򵥸���ַд�����ݣ�nAddr��0��ʼ��nData=0~65535
	bool SetControlData(int nAddr,int nDataLen,int nDatas[]);//��������ַд������
	bool GetControlData(int nAddr,int& nData);//��ȡ������ַ����
	bool GetControlData(int nAddr,int nDataLen,int nDatas[]);//��ȡ������ַ����

	int SeachComm(const int nDataLen,int nDatas[],int& nCount);
	bool TestComm(int nComm,int nBaud = 9600,int nByteSize = 8,int nParity = 0, int nStopBits = 0);
	COmron(void);
	~COmron(void);
};

