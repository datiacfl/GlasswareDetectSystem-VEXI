#include "CItemDlg.h"

CItemDlg::CItemDlg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: QDialog(parent)
{
	//设置自动销毁
	setAttribute(Qt::WA_DeleteOnClose);
	//传递窗口指针，设置按钮状态和样式
//	pDlgMainWnd = (CDlgMainWindow *)(parentWidget()->parentWidget()->parentWidget()->parentWidget());
//	pLabelItem = (MyLabelItem*)(parentWidget());
	//更改检测对话框的父窗口指针 [10/13/2015 zhaodt]
	pDlgMainWnd = (CDlgMainWindow *)(parentWidget());
	pLabelItem = (MyLabelItem *)(pDlgMainWnd->pItemLabel);
	pDlgMainWnd->pItemDlg = this;//主窗口关闭/移动时，也关闭/移动ItemDlg
	//传递参数和图形指针
	pPara = pCheckPara;
	pShape = pCheckShape;
	//按钮
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
	setParent(pDlgMainWnd->paramWidget(),Qt::SubWindow);//设置父窗体，嵌入显示1-SubWindow
	move(0,0);
#else
	//2014.8.27 QT系统下不禁用按钮
	pDlgMainWnd->enableButtons(false);
	//移动到主窗口右侧
	move(QPoint(pDlgMainWnd->width()+10,0)+pDlgMainWnd->pos());
#endif
	setEnabled(true);
}

CItemDlg::~CItemDlg()
{
	//恢复窗口按钮和样式
	pDlgMainWnd->enableButtons(true);
	pDlgMainWnd->pItemDlg=NULL;
}

//功能：增加确定取消、应用
//2014.8.27 QT系统嵌入窗口，取消确定取消按钮，换应用按钮
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

//功能：设置大小
//2014.8.27 QT系统设定固定大小窗口
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