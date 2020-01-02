#ifndef DLGFRLOUTREG_H
#define DLGFRLOUTREG_H

#include "CItemDlg.h"
#include "ui_DlgFRLOutReg.h"

class CDlgFRLOutReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFRLOutReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFRLOutReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
	void autodraw();

private:
	Ui::CDlgFRLOutReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFRLOUTREG_H
