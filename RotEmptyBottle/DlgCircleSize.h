#ifndef DLGCIRCLESIZE_H
#define DLGCIRCLESIZE_H

#include "CItemDlg.h"
#include "ui_DlgCircleSize.h"

class CDlgCircleSize : public CItemDlg
{
	Q_OBJECT

public:
	CDlgCircleSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgCircleSize();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void calibRuler();
	void drawCircle();
private:
	Ui::CDlgCircleSize ui;
	void initDialog();
	void setHelpTips();
};
#endif // DLGCIRCLESIZE_H
