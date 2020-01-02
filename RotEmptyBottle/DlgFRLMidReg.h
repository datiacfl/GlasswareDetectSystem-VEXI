#ifndef DLGFRLMIDREG_H
#define DLGFRLMIDREG_H

#include "CItemDlg.h"
#include "ui_DlgFRLMidReg.h"

class CDlgFRLMidReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFRLMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFRLMidReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
	void autodraw();
	void displayParas();

private:
	Ui::CDlgFRLMidReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFRLMIDREG_H
