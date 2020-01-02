#include "clogfile.h"
#include <QDate>
#include <QSettings>
#include <QApplication>
//#include <QDir>
#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;

static QString m_strlogfilepath;
static QString m_strLogInfo;
static QMutex mutxWriteLogFile;

//extern QString appPath;

CLogFile::CLogFile()
{
}

CLogFile::~CLogFile()
{

}
QString GetCurrentAppPath()
{
	QString AppPath;
	//因为Qt是UNICODE，GetModuXXX第一个参数需要LPWSTR类型
	TCHAR tcStr[MAX_PATH];
	//_splitpath第一个参数需要LPCSTR类型
	char cStr[MAX_PATH];
	char drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, tcStr, sizeof(tcStr));
	//需要把宽字节tcStr转换为多字节cStr
	int iLength ;  	
	iLength = WideCharToMultiByte(CP_ACP, 0, tcStr, -1, NULL, 0, NULL, NULL); 	
	WideCharToMultiByte(CP_ACP, 0, tcStr, -1, cStr, iLength, NULL, NULL); 
	//拆分
	_splitpath_s(cStr, drive, dir, fname, ext);
	strcat_s(drive, dir);
	//多字节再转换为UNICODE，以上可防止中文路径乱码
	AppPath = QString::fromLocal8Bit(drive);	
	return AppPath;
}
void CLogFile::Initpath(e_SaveLogType logtype)
{
	QString apppath;// = m_widget.GetCurrentAppPath();
	switch(logtype)
	{
	case OperationLog:
			m_strlogfilepath = apppath + "LogFiles/OperationLog/";
			m_strLogInfo = "OperationInfo";
			break;
	case CheckLog:
			m_strlogfilepath = apppath + "LogFiles/CheckLog/";
			m_strLogInfo = "CheckInfo";
			break;
	case MendParamLog:
			m_strlogfilepath = apppath + "LogFiles/MendParamLog/";
			m_strLogInfo = "MendParamInfo";
			break;
	case AbnormityLog:
			m_strlogfilepath = apppath + "LogFiles/AbnormityLog/";		
			m_strLogInfo = "AbnormityInfo";
			break;
	case StatInfo:
			m_strlogfilepath = apppath + "LogFiles/StatInfo/";		
			m_strLogInfo = "StatInfo";
			break;
	case AlgorithmDLL:
			m_strlogfilepath = apppath + "LogFiles/AlgorithmDLL/";
			m_strLogInfo = "AlgorithmInfo";
			break;
	default:
			m_strlogfilepath = apppath + "LogFiles/OtherLog/";
			m_strLogInfo = "OtherInfo";
			break;
	}
}

void CLogFile::write(QString strInfo,e_SaveLogType logtype, int showInferface)
{
	if (logtype == AbnormityLog)
	{
		showInferface = 0;
	}
	mutxWriteLogFile.lock();
	if ((1 == showInferface)||(2 == showInferface))
	{
		pMainFrm->writeLogText(strInfo,logtype);
	}
	if ((0 == showInferface)||(1 == showInferface))
	{
	// 	mutxLogFile.lock();
		QDate date = QDate::currentDate();
		QTime time = QTime::currentTime();

		Initpath(logtype);

		QString strFilePath = m_strlogfilepath +
			QString("%1-%2-%3.txt").arg(date.year()).arg(date.month()).arg(date.day());

		QDir *tempDir = new QDir;
		bool exist = true;
		int i = 0;
		QString strLastFilePath;
		strLastFilePath = strFilePath;
		exist = tempDir->exists(strFilePath);
		while(exist)
		{
			exist = tempDir->exists(strFilePath);

			if (exist)
			{
				strLastFilePath = strFilePath;
				strFilePath = m_strlogfilepath + \
					QString("%1-%2-%3_%4.txt").arg(date.year()).arg(date.month()).arg(date.day()).arg(++i);
			}
		}
		delete tempDir;
		tempDir = NULL;

		strFilePath = strLastFilePath;
		QSettings errorSet(strFilePath,QSettings::IniFormat);
		errorSet.setIniCodec("GBK");
		errorSet.beginGroup("setup");
		int nTotalNum = errorSet.value("total",0).toInt();

		if (nTotalNum > 1000)
		{
			strFilePath = m_strlogfilepath + \
				QString("%1-%2-%3_%4.txt").arg(date.year()).arg(date.month()).arg(date.day()).arg(i);
		
			QSettings errorSet(strFilePath,QSettings::IniFormat);
			errorSet.setIniCodec("GBK");
			errorSet.beginGroup("setup");
			int nTotalNum = errorSet.value("total",0).toInt();
			nTotalNum = ++nTotalNum;

			errorSet.endGroup();
			errorSet.beginGroup(m_strLogInfo);
			QString errorData = QString("%1-%2-%3 %4:%5:%6 "+strInfo).arg(date.year()).arg(date.month()).\
				arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
			errorSet.setValue(QString("INFO_%1").arg(nTotalNum),errorData);
			errorSet.endGroup();
			errorSet.beginGroup("setup");
			errorSet.setValue("total",QString::number(nTotalNum));
			errorSet.endGroup();	

		}
		else
		{
			nTotalNum = ++nTotalNum;
			errorSet.endGroup();
			errorSet.beginGroup(m_strLogInfo);
			QString errorData = QString("%1-%2-%3 %4:%5:%6 "+strInfo).arg(date.year()).arg(date.month()).\
				arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
			errorSet.setValue(QString("INFO_%1").arg(nTotalNum),errorData);
			errorSet.endGroup();
			errorSet.beginGroup("setup");
			errorSet.setValue("total",QString::number(nTotalNum));
			errorSet.endGroup();	
		}
	// 	mutxLogFile.unlock();
	//补充：日期和时间数字前面补0，对齐
	}
	mutxWriteLogFile.unlock();
}

