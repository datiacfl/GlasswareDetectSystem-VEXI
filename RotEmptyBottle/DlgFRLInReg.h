#ifndef DLGFRLINREG_H
#define DLGFRLINREG_H

#include "CItemDlg.h"
#include "ui_DlgFRLInReg.h"

class CDlgFRLInReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFRLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFRLInReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
	void autodraw();	
private:
	Ui::CDlgFRLInReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFRLINREG_H
