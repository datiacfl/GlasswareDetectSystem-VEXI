#ifndef DLGSIDEWALLLOCATE_H
#define DLGSIDEWALLLOCATE_H

#include "CItemDlg.h"
#include "ui_DlgSidewallLocate.h"

class CDlgSidewallLocate : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSidewallLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSidewallLocate();	
	void autoAccept();

private slots:
	void accept();
	void apply();
	void methodChanged(int index);
	void loctionCalibrate();
	void drawFirstLine();
	void drawSecondLine();
	void drawThirdLine();
	void setNewModel();
	void autoDrawLine();
	//void ResetReg();
private:
	Ui::CDlgSidewallLocate ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSIDEWALLLOCATE_H
