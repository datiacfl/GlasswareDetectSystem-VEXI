#ifndef DLGBENTNECK_H
#define DLGBENTNECK_H

#include "CItemDlg.h"
#include "ui_DlgBentNeck.h"

class CDlgBentNeck : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBentNeck(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBentNeck();
	void autoAccept();
private slots:
	void accept();	
	void apply();
	void drawFinRect();

private:
	Ui::CDlgBentNeck ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBENTNECK_H
