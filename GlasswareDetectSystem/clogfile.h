#ifndef CLOGFILE_H
#define CLOGFILE_H

#include <QString>
#include <QApplication>
#include <QMutex>
//#include "common.h"
#include "stateTool.h"
#include "ConfigInfo.h"

class CLogFile
{
public:
	//enum e_SaveLogType	    //��־����
	//{
	//	OperationLog = 0,			//������־
	//	CheckLog,		            //�����־
	//	MendParamLog,			    //�޸Ĳ�����־
	//	AbnormityLog,               //�쳣��־
	//	StatInfo,					//���ͳ����Ϣ��־
	//	AlgorithmDLL				//�㷨����־
	//};
public:
	CLogFile();
	~CLogFile();

	static void write(QString strInfo,e_SaveLogType logtype, int showInterface = 1);
private:
	QMutex mutxLogFile;
	static void Initpath(e_SaveLogType logtype);
	QString strLastFilePath;
};

#endif // CLOGFILE_H
