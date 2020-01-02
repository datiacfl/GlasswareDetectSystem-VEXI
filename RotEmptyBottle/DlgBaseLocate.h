#ifndef DLGBASELOCATE_H
#define DLGBASELOCATE_H

#include "CItemDlg.h"
#include "ui_DlgBaseLocate.h"

class CDlgBaseLocate : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBaseLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBaseLocate();
	void autoAccept();
	//int i_shape;
private slots:
	void accept();
	void apply();
	void methodChanged(int index);
	void isRectShape(bool bRectSp);
	void drawCentReg();
	void drawModeNOEdge();
	void drawBeltDia();
	void loctionCalibrate();
	void handCalibrate();
private:
	Ui::CDlgBaseLocate ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBASELOCATE_H
