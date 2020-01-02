#ifndef DLGBALLREG_H
#define DLGBALLREG_H

#include "CItemDlg.h"
#include "ui_DlgBAllReg.h"

class CDlgBAllReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBAllReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBAllReg();
	void autoAccept();
	
private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
	void expandDlg();
private:
	Ui::CDlgBAllReg ui;
	void initDialog();
	void setHelpTips();

	QPushButton *buttonReject[90];
};

#endif // DLGBALLREG_H
