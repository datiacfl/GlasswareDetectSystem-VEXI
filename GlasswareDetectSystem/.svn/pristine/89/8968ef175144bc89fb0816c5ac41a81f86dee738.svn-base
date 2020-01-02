#include <QtGui/QApplication>
#include <QTextCodec>
#include <QSharedMemory>
#include <QSplashScreen>
#include <QTranslator>
#include <QSettings>

//QT系统类型
#define DAHENGBLPKP_QT			//QT系统时定义该类型，否则注释掉
#include "glasswaredetectsystem.h"
//QT检测内存泄漏头文件
#include "setDebugNew.h"
#include "reportingHook.h"

#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#include "winuser.h"
#include "tlhelp32.h"
#include "tchar.h"

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	QApplication a(argc, argv);
	//设置固定风格，不跟随系统变化而变化
	//QApplication::setStyle("plastique");
	//防止图标不显示
	QApplication::addLibraryPath("./plugins");
	//防止中文乱码
// 	a.addLibraryPath("plugins/codecs/");
	QTextCodec *codec = QTextCodec::codecForName("GBK"); 
	QTextCodec::setCodecForLocale(codec); 
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForCStrings(codec);	

	//执行文件名称+扩展名
	QString exepath = argv[0];
	QString exenameext = exepath.right(exepath.length()-exepath.findRev("\\")-1);
	QString apppath = exepath.left(exepath.findRev("\\")+1);
	QString exename = exenameext.left(exenameext.findRev("."));
	//只运行一个实例
	QTranslator translator;  
	QSettings setTranslation(".\\Config\\Config.ini",QSettings::IniFormat);
	setTranslation.setIniCodec(QTextCodec::codecForName("GBK"));

	int iLanguage = setTranslation.value("/system/Language",0).toInt();//	m_sErrorInfo.m_iErrorTypeCount = erroriniset.value(strSession,0).toInt();
	if (0 == iLanguage)
	{
 		translator.load(".\\glasswaredetectsystem_zh.qm");  
 		a.installTranslator(&translator);  
	}
	a.addLibraryPath("plugins/codecs/");
	//加载QSS样式表
	QFile qss(".\\GlasswareDetect.qss");
	qss.open(QFile::ReadOnly);
 	qApp->setStyleSheet(qss.readAll());
	qss.close();


	QString strLoading = ":/loading/loading"; 
	QSplashScreen spLoading(QPixmap(strLoading.toLocal8Bit().constData()));
	spLoading.show();
	GlasswareDetectSystem w;
	w.Init();
	w.showNormal();
	w.raise();//放到最上
	w.activateWindow();
	spLoading.finish(&w);
	int nResult = a.exec();
	return nResult; 
}