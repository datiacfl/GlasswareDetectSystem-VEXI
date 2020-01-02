#ifndef DLGCHECKITEMWIZARD_H
#define DLGCHECKITEMWIZARD_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "ui_QDlgCheckItemWizard.h"

class CDlgCheckItemWizard : public QDialog
{
	Q_OBJECT

public:
	CDlgCheckItemWizard(QWidget *parent = 0);
	~CDlgCheckItemWizard();
	int nItemID;

private slots:
	void showItemTips(QTreeWidgetItem* item);
private:
	Ui::QDlgCheckItemWizard ui;

	void initItemTree();

	//�������ڵ�
	//root
	QTreeWidgetItem *rootFrequentItem;
	QTreeWidgetItem *rootLocate;
	QTreeWidgetItem *rootSize;
	QTreeWidgetItem *rootRegion;
	QTreeWidgetItem *rootContour;
	//frequentItem 2017.9���ü���ƿ��λ����������ƿ���ڻ�������Ӧ������������
	QTreeWidgetItem *sidewallLocateF;
	QTreeWidgetItem *sGeneralRegionF;
	QTreeWidgetItem *bInnerRegionF;
	QTreeWidgetItem *sSidewallRegionF;
	QTreeWidgetItem *finishContourF;
	//locate
	QTreeWidgetItem *sidewallLocate;
	QTreeWidgetItem *finishLocate;
	QTreeWidgetItem *baseLocate;
	//size
	QTreeWidgetItem *horiSize;
	QTreeWidgetItem *vertSize;
	QTreeWidgetItem *fullHeight;
	QTreeWidgetItem *bentNeck;
	QTreeWidgetItem *vertAng;
	QTreeWidgetItem *circleSize;
	//region
	QTreeWidgetItem *sidewallRegion;
	QTreeWidgetItem *sGeneralRegion;
	QTreeWidgetItem *sSideFinishRegion;
	QTreeWidgetItem *sInFinishRegion;
	QTreeWidgetItem *sScrewFinishRegion;
	QTreeWidgetItem *sBrightSpotRegion;
	QTreeWidgetItem *sBaseConvexRegion;

	QTreeWidgetItem *finishRegion;
	QTreeWidgetItem *fRingLightRegion;
	QTreeWidgetItem *fRLInnerRegion;
	QTreeWidgetItem *fRLMiddleRegion;
	QTreeWidgetItem *fRLOuterRegion;
	QTreeWidgetItem *fBackLightRegion;
	QTreeWidgetItem *fBLInnerRegion;
	QTreeWidgetItem *fBLMiddleRegion;

	QTreeWidgetItem *baseRegion;
	QTreeWidgetItem *bInnerRegion;
	QTreeWidgetItem *bMiddleRegion;
	QTreeWidgetItem *bOuterRegion;
	QTreeWidgetItem *bAllRegion;

	QTreeWidgetItem *stressRegion;
	QTreeWidgetItem *sSidewallRegion;
	QTreeWidgetItem *sBaseRegion;

	QTreeWidgetItem *disturbRegion;
	//contour
	QTreeWidgetItem *finishContour;
	QTreeWidgetItem *neckContour;
	QTreeWidgetItem *bodyContour;
};

#endif // DLGCHECKITEMWIZARD_H
