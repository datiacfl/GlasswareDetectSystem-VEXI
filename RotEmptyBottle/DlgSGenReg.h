#ifndef DLGSGENREG_H
#define DLGSGENREG_H

#include "CItemDlg.h"
#include "ui_DlgSGenReg.h"

class CDlgSGenReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSGenReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSGenReg();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void expandDlg();
	void drawReg();
	void typeChanged(int index);
	void setStoneDisplay();
	void setDarkDotDisplay();
	void setTinyCrackDisplay();
	void setLightStripeDisplay();
	void setBubblesDisplay();
	void setBtnsStyle();
	void ResetReg();
	void expandDlgSpeDefects();
private:
	Ui::CDlgSGenReg ui;
	void initDialog();
	void setHelpTips();
	int nButtonClicked; //2017.8
};

#endif // DLGSGENREG_H
