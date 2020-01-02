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
	//��ȡ���������
	QString name() const{return strName;}
	//������ʽ��(δѡ��ʱ����ɫ)
	void setColStyle();

public:
	int nID;
	bool bParaChanged;			//��ʶ������Ϊ�����ʾģ������ı䣬��Ҫд��
	bool bShapeChanged;			//��ʶ������Ϊ�����ʾģ����״�ı䣬��Ҫд��
	bool bEnabled;
	bool bClicked;
	QVariant *pPara;			//������ģ�����ָ��
	QVariant *pShape;			//������ģ����״ָ��
	QString labelStyle_Loc;		//��λ��ʽ��
	QString labelStyle_Size;	//�ߴ���ʽ��
	QString labelStyle_Reg;		//������ʽ��
	QString labelStyle_Reg_Dtb;	//����������ʽ��
	QString labelStyle_Con;		//������ʽ��
	QString labelPressStyle;	//���µ���ʽ��
	QString labelErrorStyle;	//�������ʽ��
	QString labelDisableStyle;  //ͣ�õ���ʽ��
protected:
//	void mousePressEvent(QMouseEvent *ev);
private:
	//������ʽ��
	void genStyleSheet();
	
};

#endif // MYLABELITEM_H
