/**************
�ļ�����SetModel.h
����: ģ���������
���ڣ�2013/3/4
���ߣ�tyx
***************/
#pragma once
#include "rotemptybottle.h"
#include "InnerData.h"
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QTextcodec>
#include "DlgMainWindow.h"
#include <QtGui/QDesktopWidget>
class CSetModel :
	public CModel
{
	
public:
	CSetModel(void);
	~CSetModel(void);
	s_Status SetModelDlg(s_AlgModelPara sAlgModelPara,CBottleCheck *pChecker,
		s_InputCheckerAry checkerAry,void *parent = NULL);
	s_Status CloseModelDlg();
	CDlgMainWindow *mainWindow;
private:
	QApplication *qtApp;
};

