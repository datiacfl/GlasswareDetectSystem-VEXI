#ifndef MYLABELITEM_H
#define MYLABELITEM_H

#include <QLabel>
#include <QVariant>
class MyLabelItem : public QLabel
{
	Q_OBJECT

public:
	MyLabelItem(QWidget *parent,int ID,QString sName,QVariant *pModelPara,QVariant *pModelShape);
	~MyLabelItem();
	QString strName;
	void initLabelItem(int nAlgType = 1);
	//获取检测项名称
	QString name() const{return strName;}
	//设置样式表(未选中时的颜色)
	void setColStyle();

public:
	int nID;
	bool bParaChanged;			//标识符，如为真则表示模板参数改变，需要写入
	bool bShapeChanged;			//标识符，如为真则表示模板形状改变，需要写入
	bool bEnabled;
	bool bClicked;
	QVariant *pPara;			//检测项的模板参数指针
	QVariant *pShape;			//检测项的模板形状指针
	QString labelStyle_Loc;		//定位样式表
	QString labelStyle_Size;	//尺寸样式表
	QString labelStyle_Reg;		//区域样式表
	QString labelStyle_Reg_Dtb;	//干扰区域样式表
	QString labelStyle_Con;		//轮廓样式表
	QString labelPressStyle;	//按下的样式表
	QString labelErrorStyle;	//报错的样式表
	QString labelDisableStyle;  //停用的样式表
protected:
//	void mousePressEvent(QMouseEvent *ev);
private:
	//生成样式表
	void genStyleSheet();
	
};

#endif // MYLABELITEM_H
