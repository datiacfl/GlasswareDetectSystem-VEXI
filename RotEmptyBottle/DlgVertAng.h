#ifndef DLGVERTANG_H
#define DLGVERTANG_H

#include "CItemDlg.h"
#include "ui_DlgVertAng.h"

class CDlgVertAng : public CItemDlg
{
	Q_OBJECT

public:
	CDlgVertAng(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgVertAng();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void calibRuler();
private:
	Ui::CDlgVertAng ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGVERTANG_H
