#include "widget_pie.h"
#include <QtGui>
#include <QStyleOption>

#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;

WidgetPie::WidgetPie(QWidget *parent)
	: QWidget(parent)
{
	setMaximumHeight(150);
	setupModel();
	setupViews();
	pieChart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pieChart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//	updatePie( 0, 0);
}

WidgetPie::~WidgetPie()
{

}


void WidgetPie::setupModel()
{
	model = new QStandardItemModel(6, 2, this);
	model->setHeaderData(0, Qt::Horizontal, tr("Error1"));
	model->setHeaderData(1, Qt::Horizontal, tr("Error2"));
	model->setHeaderData(2, Qt::Horizontal, tr("Error3"));
	model->setHeaderData(3, Qt::Horizontal, tr("Error4"));
	model->setHeaderData(4, Qt::Horizontal, tr("Error5"));
	model->setHeaderData(5, Qt::Horizontal, tr("Error6"));
}

void WidgetPie::setupViews()
{
	pieChart = new PieView;

	pieChart->setModel(model);

	QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
	pieChart->setSelectionModel(selectionModel);
	QVBoxLayout *vlayout = new QVBoxLayout(this);
	vlayout->addWidget(pieChart);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}
void WidgetPie::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(event);
}
void WidgetPie::resizeEvent(QResizeEvent *event)
{
	pieChart->setSize(geometry().height()-9);
}

void WidgetPie::updatePie(int Error[ERRORTYPE_MAX_COUNT])
{
	int count[6] = {0,0,0,0,0,0},errortype[6] = {0,0,0,0,0,0}, sum=0;
 	for (int j = 1; j< ERRORTYPE_MAX_COUNT; j++)
 	{
 		for (int i = 0;i<5;i++ )
 		{
			if (Error[j]>count[i])
			{
				for (int k = 5; k>i; k--)
				{
					count[k] = count[k-1];
					errortype[k] = errortype[k-1];
				}
				count[i] = Error[j];
				errortype[i] = j;
				break;
			}
 		}
		sum += Error[j];
	}
	count[5] = sum - count[4]-count[3]-count[2]-count[1]-count[0];
	QColor color[6];
	color[0] = QColor(153,230,0);
	color[1] = QColor(174,77,102);
	color[2] = QColor(128,255,128);
	color[3] = QColor(128,255,255);
	color[4] = QColor(0,128,255);
	color[5] = QColor(255,255,128);

	model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
// 	count[0] = 0;
// 	count[1] = 0;
// 	count[2] = 0;
// 	count[3] = 0;
// 	count[4] = 0;
// 	count[5] = 0;

	if (count[0]<=0)
	{
		model->insertRows(0, 1, QModelIndex());
		model->setData(model->index(0, 0, QModelIndex()), tr("Number:") + QString::number(count[0]));
		model->setData(model->index(0, 1, QModelIndex()), QString::number(count[0]));
		model->setData(model->index(0, 0, QModelIndex()), color[0], Qt::DecorationRole);

	}
	else
	{
		for (int i = 0 ; i<6&&count[i]>0 ; i++)
		{
			if (5 == i)
			{
				model->insertRows(i, 1, QModelIndex());
				model->setData(model->index(i, 0, QModelIndex()),  tr("Other:") + QString::number(count[i]));
				model->setData(model->index(i, 1, QModelIndex()), QString::number(count[i]));
				model->setData(model->index(i, 0, QModelIndex()), color[i], Qt::DecorationRole);
			}
			else
			{
				model->insertRows(i, 1, QModelIndex());
				model->setData(model->index(i, 0, QModelIndex()), pMainFrm->m_sErrorInfo.m_vstrErrorType[errortype[i]] + ":" + QString::number(count[i]));
				model->setData(model->index(i, 1, QModelIndex()), QString::number(count[i]));
				model->setData(model->index(i, 0, QModelIndex()), color[i], Qt::DecorationRole);
			}
		}
	}

//  	model->setData(model->index(5, 0, QModelIndex()), tr("Other:") + QString::number(count[5]));
//  	model->setData(model->index(5, 1, QModelIndex()), QString::number(count[5]));
//  	model->setData(model->index(5, 0, QModelIndex()), QColor(0,128,255), Qt::DecorationRole);
}