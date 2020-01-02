#include "CItemDlg.h"

CItemDlg::CItemDlg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: QDialog(parent)
{
	//�����Զ�����
	setAttribute(Qt::WA_DeleteOnClose);
	//���ݴ���ָ�룬���ð�ť״̬����ʽ
//	pDlgMainWnd = (CDlgMainWindow *)(parentWidget()->parentWidget()->parentWidget()->parentWidget());
//	pLabelItem = (MyLabelItem*)(parentWidget());
	//���ļ��Ի���ĸ�����ָ�� [10/13/2015 zhaodt]
	pDlgMainWnd = (CDlgMainWindow *)(parentWidget());
	pLabelItem = (MyLabelItem *)(pDlgMainWnd->pItemLabel);
	pDlgMainWnd->pItemDlg = this;//�����ڹر�/�ƶ�ʱ��Ҳ�ر�/�ƶ�ItemDlg
	//���ݲ�����ͼ��ָ��
	pPara = pCheckPara;
	pShape = pCheckShape;
	//��ť
	pBtnOK = new QPushButton(this);
	pBtnOK->setText(QObject::tr("Ok"));
	connect(pBtnOK,SIGNAL(clicked()),this,SLOT(accept()));	
	pBtnCancle = new QPushButton(this);
	pBtnCancle->setText(QObject::tr("Cancle"));
	connect(pBtnCancle,SIGNAL(clicked()),this,SLOT(reject()));	
	pBtnApply = new QPushButton(this);
	pBtnApply->setText(QObject::tr("Apply"));
	connect(pBtnApply,SIGNAL(clicked()),this,SLOT(apply()));	
	
#ifdef DAHENGBLPKP_QT
	setParent(pDlgMainWnd->paramWidget(),Qt::SubWindow);//���ø����壬Ƕ����ʾ1-SubWindow
	move(0,0);
#else
	//2014.8.27 QTϵͳ�²����ð�ť
	pDlgMainWnd->enableButtons(false);
	//�ƶ����������Ҳ�
	move(QPoint(pDlgMainWnd->width()+10,0)+pDlgMainWnd->pos());
#endif
	setEnabled(true);
}

CItemDlg::~CItemDlg()
{
	//�ָ����ڰ�ť����ʽ
	pDlgMainWnd->enableButtons(true);
	pDlgMainWnd->pItemDlg=NULL;
}

//���ܣ�����ȷ��ȡ����Ӧ��
//2014.8.27 QTϵͳǶ�봰�ڣ�ȡ��ȷ��ȡ����ť����Ӧ�ð�ť
void CItemDlg::addCtrLayout()
{
	if (0 != layout())
	{
		QHBoxLayout *ctrLayout = new QHBoxLayout;
		ctrLayout->addStretch();
#ifdef DAHENGBLPKP_QT
		ctrLayout->addWidget(pBtnApply);
		pBtnOK->setVisible(false);
		pBtnCancle->setVisible(false);
#else
		ctrLayout->addWidget(pBtnOK);
		ctrLayout->addWidget(pBtnCancle);
		pBtnApply->setVisible(false);
#endif
		//((QHBoxLayout*)layout())->addStretch();
		((QHBoxLayout*)layout())->addLayout(ctrLayout);
	}
}

//���ܣ����ô�С
//2014.8.27 QTϵͳ�趨�̶���С����
void CItemDlg::setDlgSize()
{
	//setFixedSize(parentWidget()->size());
	layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void CItemDlg::closeEvent(QCloseEvent *event)
{
	if (pDlgMainWnd->m_bDrawing)
	{
		pDlgMainWnd->close();
		event->ignore();
	}
}