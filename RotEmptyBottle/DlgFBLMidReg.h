#ifndef DLGFBLMIDREG_H
#define DLGFBLMIDREG_H

#include "CItemDlg.h"
#include "ui_DlgFBLMidReg.h"

class CDlgFBLMidReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFBLMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFBLMidReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
private:
	Ui::CDlgFBLMidReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFBLMIDREG_H
