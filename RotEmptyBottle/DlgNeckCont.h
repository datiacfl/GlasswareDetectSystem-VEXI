#ifndef DLGNECKCONT_H
#define DLGNECKCONT_H

#include "CItemDlg.h"
#include "ui_DlgNeckCont.h"

class CDlgNeckCont : public CItemDlg
{
	Q_OBJECT

public:
	CDlgNeckCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgNeckCont();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void drawReg();
private:
	Ui::CDlgNeckCont ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGNECKCONT_H
