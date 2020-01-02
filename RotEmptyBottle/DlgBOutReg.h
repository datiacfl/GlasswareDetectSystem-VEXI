#ifndef DLGBOUTREG_H
#define DLGBOUTREG_H

#include "CItemDlg.h"
#include "ui_DlgBOutReg.h"

class CDlgBOutReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBOutReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBOutReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawInCircle();
	void drawOutCircle();
	void autodraw();
private:
	Ui::CDlgBOutReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBOUTREG_H
