#ifndef DLGBMIDREG_H
#define DLGBMIDREG_H

#include "CItemDlg.h"
#include "ui_DlgBMidReg.h"

class CDlgBMidReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBMidReg();
	void autoAccept();
private slots:
	void accept();	
	void apply();
	void drawInCircle();
	void drawOutCircle();
private:
	Ui::CDlgBMidReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBMIDREG_H
