#ifndef DLGFULLHEIGHT_H
#define DLGFULLHEIGHT_H

#include "CItemDlg.h"
#include "ui_DlgFullHeight.h"

class CDlgFullHeight : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFullHeight(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFullHeight();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void calibRuler();
	void drawSizeRect();
	void changeGroupName(int index);
private:
	Ui::CDlgFullHeight ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFULLHEIGHT_H
