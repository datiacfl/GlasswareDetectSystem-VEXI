#include "SetModel.h"

extern bool bCreateApp;

CSetModel::CSetModel(void)
{
	qtApp = NULL;
	mainWindow = NULL;
}


CSetModel::~CSetModel(void)
{
}

s_Status CSetModel::SetModelDlg(s_AlgModelPara sAlgModelPara,CBottleCheck *pChecker,
	s_InputCheckerAry checkerAry,void *parent/* = NULL*/)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	strcpy_s(sError.chErrorInfo,"");
	strcpy_s(sError.chErrorContext,"");
	try
	{
		int i;
		//保证qt进程唯一
		if (qtApp==NULL && bCreateApp)
		{
			int argc = 1;
			qtApp = new QApplication(argc,0);
			//2013.12.13 移到初始化库中，防止界面为启动时，中文乱码
			////防止图标不显示
			QApplication::addLibraryPath("./QtPlugins");
			////防止中文乱码
			QTextCodec*codec=QTextCodec::codecForName("GBK");
			QTextCodec::setCodecForLocale(codec);
			QTextCodec::setCodecForTr(codec);
			QTextCodec::setCodecForCStrings(codec);
		}

		//保证主窗口唯一
		if (mainWindow == NULL)
		{
			mainWindow = new CDlgMainWindow(sAlgModelPara);
			if (NULL != parent)
			{
				mainWindow->setParent((QWidget*)parent,Qt::SubWindow/* 子窗体Qt::Widget*/);
			}
			mainWindow->setAttribute(Qt::WA_DeleteOnClose);	
			mainWindow->setWindowModality(Qt::ApplicationModal);
			//2013.9.11 nanjc 窗口置顶，禁用最小化
#ifndef _DEBUG//2014.7.10 nanjc Debug模式取消置顶，方便断点调试
			mainWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
			mainWindow->setWindowFlags(mainWindow->windowFlags() & ~Qt::WindowMinimizeButtonHint);
		}
		else
		{
			QMessageBox::information(mainWindow,QObject::tr("Note"),QObject::tr("Window is already open!"));
			return sError;
		}
		
		//窗口初始化
		bool initResult;
		initResult = true;
		if (NULL != parent)
		{
			initResult = mainWindow->init((QWidget*)parent);	
		}
		else
		{
			initResult = mainWindow->init();	
		}
		
		//2017.6---窗口初始化失败
		if (initResult == false)
		{
			sError.nErrorID = RETURN_CHECK_ERROR;
			if (mainWindow!=NULL)
			{
				mainWindow->close();
				//if (bCreateApp)
				//{
				//	mainWindow = NULL;
				//}
				mainWindow = NULL;  //2017.6-防止调用野指针
			}
			return sError;
		}

		mainWindow->show();	
		////窗口居中(左移100,上移10)
		QWidget *parentWidget;
		if (NULL != parent)
		{
			parentWidget = (QWidget*)parent;
		}
		else
		{
			parentWidget = QApplication::desktop();
		}
#ifdef DAHENGBLPKP_QT
		mainWindow->move((parentWidget->width() - mainWindow->width())/2,0);
//		((CCheck*)(pChecker->m_pAlg))->writeErrDataRecord(QString("移动完成"));
#else
		mainWindow->move((parentWidget->width() - mainWindow->width())/2-100,
			(parentWidget->height() - mainWindow->height())/2-10);
#endif
		if (bCreateApp)
		{
			qtApp->exec();
			//2014.10.29 修改mainWindow，当算法中创建控制台时置空，走自己的消息处理机制
			//QT版系统中不置空，通过CloseModelDlg置空
			mainWindow = NULL;
		}
		//((CCheck*)(pChecker->m_pAlg))->writeErrDataRecord(QString("关闭"));
		return sError;
	}
	catch (...)
	{
		sError.nErrorID = RETURN_CHECK_ERROR;
		strcpy_s(sError.chErrorInfo,"Analyze image abnormal");//分析图像异常
		strcpy_s(sError.chErrorContext,"CSetModel::SetModelDlg");
		if (mainWindow!=NULL)
		{
			mainWindow->close();
			//if (bCreateApp)
			//{
			//	mainWindow = NULL;
			//}
			mainWindow = NULL;
		}
		return sError;
	}
}

s_Status CSetModel::CloseModelDlg()
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	strcpy_s(sError.chErrorInfo,"");
	strcpy_s(sError.chErrorContext,"");
	try
	{
		if (NULL != mainWindow && !bCreateApp)
		{
			//QString strTemp = mainWindow->strCloseWindow;
			if (mainWindow->close())
			{
				//delete mainWindow;
				mainWindow = NULL;
			}
			else
			{
				sError.nErrorID = RETURN_NO_CLOSE;
			}
		}
		return sError;
	}
	catch (...)
	{
		sError.nErrorID = RETURN_CHECK_ERROR;
		strcpy_s(sError.chErrorInfo,"Analyze image abnormal");//分析图像异常
		strcpy_s(sError.chErrorContext,"CSetModel::CloseModelDlg");
		return sError;
	}
}

/* ！qt5.0之后版本取消setCodecForTr和setCodecForCStrings两个函数，中文乱码很难解决
/Qt4.8版本做英文版国际化的步骤：
1. $qmake -project生成*.pro文件
2. 记事本打开pro文件，末尾加入：
	TRANSLATIONS += AlgLang_EN.ts  #*.ts为文件名

	CODECFORTR = gbk #指定tr()待翻译串的编码
	#DEFAULTCODEC = utf-8
	#CODEC = utf-8
	CODECFORSRC = SYSTEM #MSVC编译器特有，指定源文件的编码
3.  输入$lupdate *.pro -codecfortr gbk -ts *.ts 生成*.ts文件
4.	用linguist打开ts，翻译之后生成*.qm文件
*/

