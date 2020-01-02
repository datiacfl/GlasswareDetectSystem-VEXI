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
		//��֤qt����Ψһ
		if (qtApp==NULL && bCreateApp)
		{
			int argc = 1;
			qtApp = new QApplication(argc,0);
			//2013.12.13 �Ƶ���ʼ�����У���ֹ����Ϊ����ʱ����������
			////��ֹͼ�겻��ʾ
			QApplication::addLibraryPath("./QtPlugins");
			////��ֹ��������
			QTextCodec*codec=QTextCodec::codecForName("GBK");
			QTextCodec::setCodecForLocale(codec);
			QTextCodec::setCodecForTr(codec);
			QTextCodec::setCodecForCStrings(codec);
		}

		//��֤������Ψһ
		if (mainWindow == NULL)
		{
			mainWindow = new CDlgMainWindow(sAlgModelPara);
			if (NULL != parent)
			{
				mainWindow->setParent((QWidget*)parent,Qt::SubWindow/* �Ӵ���Qt::Widget*/);
			}
			mainWindow->setAttribute(Qt::WA_DeleteOnClose);	
			mainWindow->setWindowModality(Qt::ApplicationModal);
			//2013.9.11 nanjc �����ö���������С��
#ifndef _DEBUG//2014.7.10 nanjc Debugģʽȡ���ö�������ϵ����
			mainWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
			mainWindow->setWindowFlags(mainWindow->windowFlags() & ~Qt::WindowMinimizeButtonHint);
		}
		else
		{
			QMessageBox::information(mainWindow,QObject::tr("Note"),QObject::tr("Window is already open!"));
			return sError;
		}
		
		//���ڳ�ʼ��
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
		
		//2017.6---���ڳ�ʼ��ʧ��
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
				mainWindow = NULL;  //2017.6-��ֹ����Ұָ��
			}
			return sError;
		}

		mainWindow->show();	
		////���ھ���(����100,����10)
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
//		((CCheck*)(pChecker->m_pAlg))->writeErrDataRecord(QString("�ƶ����"));
#else
		mainWindow->move((parentWidget->width() - mainWindow->width())/2-100,
			(parentWidget->height() - mainWindow->height())/2-10);
#endif
		if (bCreateApp)
		{
			qtApp->exec();
			//2014.10.29 �޸�mainWindow�����㷨�д�������̨ʱ�ÿգ����Լ�����Ϣ�������
			//QT��ϵͳ�в��ÿգ�ͨ��CloseModelDlg�ÿ�
			mainWindow = NULL;
		}
		//((CCheck*)(pChecker->m_pAlg))->writeErrDataRecord(QString("�ر�"));
		return sError;
	}
	catch (...)
	{
		sError.nErrorID = RETURN_CHECK_ERROR;
		strcpy_s(sError.chErrorInfo,"Analyze image abnormal");//����ͼ���쳣
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
		strcpy_s(sError.chErrorInfo,"Analyze image abnormal");//����ͼ���쳣
		strcpy_s(sError.chErrorContext,"CSetModel::CloseModelDlg");
		return sError;
	}
}

/* ��qt5.0֮��汾ȡ��setCodecForTr��setCodecForCStrings��������������������ѽ��
/Qt4.8�汾��Ӣ�İ���ʻ��Ĳ��裺
1. $qmake -project����*.pro�ļ�
2. ���±���pro�ļ���ĩβ���룺
	TRANSLATIONS += AlgLang_EN.ts  #*.tsΪ�ļ���

	CODECFORTR = gbk #ָ��tr()�����봮�ı���
	#DEFAULTCODEC = utf-8
	#CODEC = utf-8
	CODECFORSRC = SYSTEM #MSVC���������У�ָ��Դ�ļ��ı���
3.  ����$lupdate *.pro -codecfortr gbk -ts *.ts ����*.ts�ļ�
4.	��linguist��ts������֮������*.qm�ļ�
*/

