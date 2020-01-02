/**************
文件名：SetModel.h
功能: 模板参数调试
日期：2013/3/4
作者：tyx
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

