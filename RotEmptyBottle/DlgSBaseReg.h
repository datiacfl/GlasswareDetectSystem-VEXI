#ifndef DLGSBASEREG_H
#define DLGSBASEREG_H

#include "CItemDlg.h"
#include "ui_DlgSBaseReg.h"

class CDlgSBaseReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSBaseReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSBaseReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void methodChanged(int index);
	void drawInCircle();
	void drawOutCircle();
private:
	Ui::CDlgSBaseReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSBASEREG_H
