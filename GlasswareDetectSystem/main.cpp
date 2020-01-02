//#include <QtGui/QApplication> update to 5
#include <QApplication>
#include <QTextCodec>
#include <QSharedMemory>
#include <QSplashScreen>
#include <QTranslator>
#include <QSettings>

//QTϵͳ����
#define DAHENGBLPKP_QT			//QTϵͳʱ��������ͣ�����ע�͵�
#include "glasswaredetectsystem.h"
//QT����ڴ�й©ͷ�ļ�
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
	//���ù̶���񣬲�����ϵͳ�仯���仯
	//QApplication::setStyle("plastique");
	//��ֹͼ�겻��ʾ
	QApplication::addLibraryPath("./plugins");
	//��ֹ��������
// 	a.addLibraryPath("plugins/codecs/");
	QTextCodec *codec = QTextCodec::codecForName("GBK"); 
	QTextCodec::setCodecForLocale(codec); 
	//QT 5.12.6 update
	/*QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForCStrings(codec);*/	

	//ִ���ļ�����+��չ��
	QString exepath = argv[0];
	//QT 5.12.6 update
	/*QString exenameext = exepath.right(exepath.length()-exepath.findRev("\\")-1);
	QString apppath = exepath.left(exepath.findRev("\\")+1);
	QString exename = exenameext.left(exenameext.findRev("."));*/
	QString exenameext = exepath.right(exepath.length() - exepath.lastIndexOf("\\") - 1);
	QString apppath = exepath.left(exepath.lastIndexOf("\\") + 1);
	QString exename = exenameext.left(exenameext.lastIndexOf("."));
	//ֻ����һ��ʵ��
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
	//����QSS��ʽ��
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
	w.raise();//�ŵ�����
	w.activateWindow();
	spLoading.finish(&w);
	int nResult = a.exec();
	return nResult; 
}