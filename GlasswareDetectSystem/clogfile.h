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
	//enum e_SaveLogType	    //日志类型
	//{
	//	OperationLog = 0,			//操作日志
	//	CheckLog,		            //检测日志
	//	MendParamLog,			    //修改参数日志
	//	AbnormityLog,               //异常日志
	//	StatInfo,					//检测统计信息日志
	//	AlgorithmDLL				//算法库日志
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
