#ifndef DLGSBASECONVEXREG_H
#define DLGSBASECONVEXREG_H

#include "CItemDlg.h"
#include "ui_DlgSBaseConvexReg.h"

class CDlgSBaseConvexReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSBaseConvexReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSBaseConvexReg();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void expandDlg();
	void drawReg();
	void ResetReg();
private:
	Ui::CDlgSBaseConvexReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSBASECONVEXREG_H
