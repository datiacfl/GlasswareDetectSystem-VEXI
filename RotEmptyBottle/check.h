/**************
文件名：check.h
功能: 核心检测算法
日期：2013/3/4
作者：tyx
***************/
#pragma once
#include "rotemptybottle.h"
#include "InnerData.h"
#include <QString>
#include <QMap>
#include <QVariant>
#include <QDir>
#include <QSettings>
#include <QVector>
#include <QDate>
#include <QTime>
#include <QObject>
#include <QMutex>

Q_DECLARE_METATYPE(s_pSideLoc);
Q_DECLARE_METATYPE(s_oSideLoc);
Q_DECLARE_METATYPE(s_pFinLoc);
Q_DECLARE_METATYPE(s_oFinLoc);
Q_DECLARE_METATYPE(s_pBaseLoc);
Q_DECLARE_METATYPE(s_oBaseLoc);
Q_DECLARE_METATYPE(s_pHoriSize);
Q_DECLARE_METATYPE(s_oHoriSize);
Q_DECLARE_METATYPE(s_pVertSize);
Q_DECLARE_METATYPE(s_oVertSize);
Q_DECLARE_METATYPE(s_pFullHeight);
Q_DECLARE_METATYPE(s_oFullHeight);
Q_DECLARE_METATYPE(s_pBentNeck);
Q_DECLARE_METATYPE(s_oBentNeck);
Q_DECLARE_METATYPE(s_pVertAng);
Q_DECLARE_METATYPE(s_oVertAng);
Q_DECLARE_METATYPE(s_pCirSize);
Q_DECLARE_METATYPE(s_oCirSize);
Q_DECLARE_METATYPE(s_pSBriSpotReg);
Q_DECLARE_METATYPE(s_oSBriSpotReg);
Q_DECLARE_METATYPE(s_pSGenReg);
Q_DECLARE_METATYPE(s_oSGenReg);
Q_DECLARE_METATYPE(s_pSSideFReg);
Q_DECLARE_METATYPE(s_oSSideFReg);
Q_DECLARE_METATYPE(s_pSInFReg);
Q_DECLARE_METATYPE(s_oSInFReg);
Q_DECLARE_METATYPE(s_pSScrewFReg);
Q_DECLARE_METATYPE(s_oSScrewFReg);
Q_DECLARE_METATYPE(s_pFRLInReg);
Q_DECLARE_METATYPE(s_oFRLInReg);
Q_DECLARE_METATYPE(s_pFRLMidReg);
Q_DECLARE_METATYPE(s_oFRLMidReg);
Q_DECLARE_METATYPE(s_pFRLOutReg);
Q_DECLARE_METATYPE(s_oFRLOutReg);
Q_DECLARE_METATYPE(s_pFBLInReg);
Q_DECLARE_METATYPE(s_oFBLInReg);
Q_DECLARE_METATYPE(s_pFBLMidReg);
Q_DECLARE_METATYPE(s_oFBLMidReg);
Q_DECLARE_METATYPE(s_pBInReg);
Q_DECLARE_METATYPE(s_oBInReg);
Q_DECLARE_METATYPE(s_pBMidReg);
Q_DECLARE_METATYPE(s_oBMidReg);
Q_DECLARE_METATYPE(s_pBOutReg);
Q_DECLARE_METATYPE(s_oBOutReg);
Q_DECLARE_METATYPE(s_pBAllReg);
Q_DECLARE_METATYPE(s_oBAllReg);
Q_DECLARE_METATYPE(s_pSSideReg);
Q_DECLARE_METATYPE(s_oSSideReg);
Q_DECLARE_METATYPE(s_pDistReg);
Q_DECLARE_METATYPE(s_oDistReg);
Q_DECLARE_METATYPE(s_pFinCont);
Q_DECLARE_METATYPE(s_oFinCont);
Q_DECLARE_METATYPE(s_pNeckCont);
Q_DECLARE_METATYPE(s_oNeckCont);
Q_DECLARE_METATYPE(s_pBodyCont);
Q_DECLARE_METATYPE(s_oBodyCont);
Q_DECLARE_METATYPE(s_pSBaseReg);
Q_DECLARE_METATYPE(s_oSBaseReg);
Q_DECLARE_METATYPE(s_pSBaseConvexReg);
Q_DECLARE_METATYPE(s_oSBaseConvexReg);

class CDlgMainWindow;
using namespace std;


class CCheck :
	public QObject,public CAlgorithm
{
	Q_OBJECT
public:
	CCheck(void);
	~CCheck(void);
	CCheck &operator =(CCheck &cpCheck);	//重载等号
	
	s_Status init(s_AlgInitParam sAlgInitParam);
	s_Status Free();
	s_Status Check(s_AlgCInP sAlgCInP,s_AlgCheckResult **sAlgCheckResult);
	s_Status CopySizePara(s_SizePara4Copy &sSizePara);
	bool setsSystemInfo(s_SystemInfoforAlg &sSystemInfo);
	bool FindTwoPointsSubpix(Alg::s_ImagePara sImagePara,double inRow,POINT &pLeft,POINT &pRight,int nEdge);

signals:
	void signals_stopContinue();	//2013.9.12 nanjc 发送信号让界面停止连续显示

public:	
	void getVersion(QString strFullName);
	void getAppPath();
	void writeErrDataRecord(QString strData);
	void writeErrorInfo(QString strData);
	void writeAlgOperationRecord(QString strData); //2017.8-添加算法操作日志
	void writeAlgLogLx(char *acLoginfo);
	void writeAlgLog(QString str);
	//*模板读写函数
	void	readModel(QString strPath);	
	QVariant readParabyType(int nType,QSettings &set);	//根据检测项类型，返回QVariant型的参数结构体
	QVariant readShapebyType(int nType,QSettings &set);
	void saveParabyType(int nType,QSettings &set,QVariant &vItemPara,bool bCopy=false);//bCopy（复制参数时，比例尺不进行复制）
	void saveShapebyType(int nType,QSettings &set,QVariant &vItemShape);
	void readXLDbyPts(QSettings &set,Hobject *oXLD);
	void saveXLDbyPts(QSettings &set,Hobject &oXLD);
	void XLDToPts(Hobject &oXLD,s_Xld_Point &xldPoint);
	void PtsToXLD(s_Xld_Point &xldPoint,Hobject &oXLD);
	//*区域仿射变换,尺寸和轮廓只平移，不旋转，瓶身外观区域要旋转,圆形区域重新生成
	void affineAllShape();
	void affineRegion(Hobject &oRegion,bool bRotate = false,int iMethod = 0);
	void affineCircle(Hobject &oRegion);
	//排除缺陷
	//*提取排除缺陷
	void ExtExcludeDefect(RtnInfo &rtnInfo, Hobject &regBig,Hobject &regSmall,
		int nDefectCause,int nDefectType,QString strName,bool bModify=true);
	//*提取排除缺陷（极坐标）
	void ExtExcludePolarDefect(RtnInfo &rtnInfo, Hobject &regBig,Hobject &regSmall,double dInR,double dOutR,
		int nDefectCause,int nDefectType,QString strName,bool bModify=true);	
	//*提取排除缺陷（仿射变换）
	void ExtExcludeAffinedDefect(RtnInfo &rtnInfo, Hobject &regBig,Hobject &regSmall,int noffSet,HTuple homMat,
		int nDefectCause,int nDefectType,QString strName,bool bModify=true);	
	//*过滤排除缺陷
	void FilterExcludeDefect(RtnInfo &rtnInfo);
	//核心算法
	//*定位
	RtnInfo fnFindCurrentPos(Hobject &bottleXld, bool bInit = false);
	//*瓶身定位
	RtnInfo fnFindPosSidewall(Hobject &imgSrc,QVariant &para,QVariant &shape,Hobject &bottleXld, bool bInit = false);
	int findEdgePointSingle(const Hobject &Image, const Hobject &LineSeg, 
		HTuple *RowPt, HTuple *ColPt, int nEdge = 10, int nDirect = L2R, int nType = 0, 
		BOOL bMean = FALSE);
	int FindEdgePointSubPix(const Hobject &Image, const Hobject &LineSeg, 
		HTuple *RowPt, HTuple *ColPt, int nEdge = 10, int nDirect = T2B, int nType = 0);
	int findEdgePointDouble(const Hobject &Image, const Hobject &LineSeg, 
		HTuple *RowPt, HTuple *ColPt, int nEdge=10, int nDirect=L2R,int nType=0,BOOL bMean=FALSE);
	int testEdgePointDouble(const Hobject &Image, const Hobject &LineSeg, 
		HTuple &RowPt,HTuple &ColPt, int nEdge, float fRange,
		int FirOrSecLine,SideOrigin &oldOri,int nType=0,BOOL bMean=FALSE);
	RtnInfo findPosThreeLine(const Hobject &Image, const Hobject &FirstLine, const Hobject &SecondLine,	const Hobject &ThirdLine,
		SideOrigin oldOri,SideOrigin &newOri,int nEdge,float fRange,int nType=0, bool bMean=FALSE, bool bFindPointSubPix=FALSE);
	RtnInfo findXTwoLine(const Hobject &Image, const Hobject &FirstLine, const Hobject &SecondLine,
		SideOrigin &newOri, int nEdge, int nDirect,int nType=0,BOOL bMean=FALSE);
	double CalcDistPt3ToOri(const Hobject &Image, const Hobject &FirstLine, const Hobject &SecondLine,
		const Hobject &ThirdLine, int nEdge,int nDirect,int nType=0,BOOL bMean=FALSE);
	RtnInfo findPosThreePoints(const Hobject &Image, const Hobject &FirstLine, const Hobject &SecondLine,
		const Hobject &ThirdLine,SideOrigin &newOri,int nEdge,int nDirect,int nType=0,BOOL bMean=FALSE);
	//*2013.9.23 nanjc 获取区域内瓶子轮廓，用于应力定位
	void getBottleXld(const Hobject &Image,const Hobject &bottleRegion,Hobject &bottleXld,int xldwidth,int xldheight,int nDirect);
	RtnInfo findXYTwoLine(const Hobject &Image, const Hobject &FirstLine, const Hobject &ThirdLine,
			 SideOrigin oldOri,SideOrigin &newOri, int nEdge,float fRange,int nType=0,BOOL bMean=FALSE,BOOL bFindPointSubPix=FALSE);
	RtnInfo findXTwoLineConBottle(const Hobject &Image, const Hobject &FirstLine, const Hobject &SecondLine,
		SideOrigin oldOri,SideOrigin &newOri, int nEdge,float fRange,int nDirect,int nType=0,BOOL bMean=FALSE);
	// 2018.1-mj 瓶身应力定位
	RtnInfo findPosThreeLineStress(const Hobject &Image,const Hobject &FirstLine,const Hobject &SecondLine,const Hobject &ThirdLine,
		SideOrigin oldOri,SideOrigin &newOri,int nEdge,float fRange,int nType=0, bool bMean=FALSE);

	//*瓶口定位
	RtnInfo fnFindPosFinish(Hobject &imgSrc,QVariant &para,QVariant &shape);
	RtnInfo findPosRingLight(const Hobject &Image,s_oFinLoc &oFinLoc,s_pFinLoc &pFinLoc);
	RtnInfo findPosBackLight(const Hobject &Image,s_oFinLoc &oFinLoc,s_pFinLoc &pFinLoc);
	RtnInfo findPosRingLight_ZhangYu(const Hobject &Image,s_oFinLoc &oFinLoc,s_pFinLoc &pFinLoc);
	//*瓶底定位
	RtnInfo fnFindPosBase(Hobject &imgSrc,QVariant &para,QVariant &shape);
	RtnInfo findPosBaseSeg(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);   //分割定位
	RtnInfo findPosBaseEdge(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);  //边缘定位
	RtnInfo findPosBaseBelt(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);  //防滑带定位
	RtnInfo findPosBaseBeltEx(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc); //防滑块定位
	RtnInfo findPosBaseBeltShape(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);//防滑块形状定位
	RtnInfo findPosBaseCircle(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc); //内圈定位（红酒）
	RtnInfo findPosBaseEdgeMode(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);//瓶底边缘定位(模号)
	RtnInfo findPosBaseRing(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);    //瓶底内环定位（红酒）
	RtnInfo findPosBaseGray(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc);    //瓶底灰度定位---2017.12
   //RtnInfo findPosBaseBelt_Shape(const Hobject &Image,s_oBaseLoc &oBaseLoc,s_pBaseLoc &pBaseLoc); //防滑块定位(形状)
	void fitCircle(const HTuple &tRows,const HTuple &tCols,float & CircleRow,float &CircleCol,float & CircleRadius);
	//*横向尺寸
	RtnInfo fnHoriSize(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*纵向尺寸
	RtnInfo fnVertSize(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶全高
	RtnInfo fnFullHeight(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*圆形尺寸
	RtnInfo fnCircleSize(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*歪脖度
	RtnInfo fnBentNeck(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*垂直度
	RtnInfo fnVertAng(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶身普通区域
	RtnInfo fnSGenReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*检测区域预处理
	RtnInfo genValidROI(Hobject &imgSrc,s_ROIPara &roiPara,Hobject &ROI,Hobject *validROI);
	//*排除条纹干扰
	void distRegStripe(Hobject &imgSrc,s_pDistReg &pDistReg,s_oDistReg &oDistReg,Hobject *regStripe);
	void distRegStripe(s_pDistReg &pDistReg,Hobject &ROI,Hobject *regStripe);
	//*排除气泡干扰
	void distBubble(Hobject &imgSrc,s_pDistReg &pDistReg,Hobject &ROI,Hobject *regBubble);
	//*口部区域
	RtnInfo fnSSideFReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*内口区域
	RtnInfo fnSInFReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*螺纹口区域
	RtnInfo fnSScrewFReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*环形光内环区域
	RtnInfo fnFRLInnerReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*环形光口平面区域
	RtnInfo fnFRLMiddleReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*环形光外环区域
	RtnInfo fnFRLOuterReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*背光内环区域
	RtnInfo fnFBLInnerReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*背光口平面区域
	RtnInfo fnFBLMiddleReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底内环区域
	RtnInfo fnBInnerReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底中环区域
	RtnInfo fnBMiddleReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底外环区域
	RtnInfo fnBOutterReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶身应力区域
	RtnInfo fnSSidewallReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	////裂纹检测--从瓶身应力区域修改
	//RtnInfo fnSSideCrack(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底应力区域
	RtnInfo fnSBaseReg(Hobject &imgSrc,QVariant &para,QVariant &shape);	
	//*瓶底凸起区域
	RtnInfo fnSBaseConvexReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底凸起区域（现场图像较次，效果不好，修改为上面的方法）
	RtnInfo fnSBaseConvexReg1(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶口轮廓
	RtnInfo fnFinishCont(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//搜索轮廓
	int SearchContourPoints(Hobject &imgSrc,Hobject &regRect,int nThresh,vector<HTuple> *contPoints);
	//*瓶肩轮廓
	RtnInfo fnNeckCont(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶身轮廓
	RtnInfo fnBodyCont(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶身亮斑
	RtnInfo fnSBriSpotReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	//*瓶底整体区域(用于检测瓶底模号，修改为下面方法fnBModeNOReg)
	RtnInfo fnBAllReg(Hobject &imgSrc,QVariant &para,QVariant &shape);	
	//*瓶底模号区域
	RtnInfo fnBModeNOReg(Hobject &imgSrc,QVariant &para,QVariant &shape);	
	//*瓶底模号区域---2017.7
	RtnInfo fnBMouldNOReg(Hobject &imgSrc,QVariant &para,QVariant &shape);
	int strDistance(const string source,const string target);
	void calculate_lines_gauss_parameters (HTuple hv_MaxLineWidth, HTuple hv_Contrast, 
		HTuple *hv_Sigma, HTuple *hv_Low, HTuple *hv_High);

	//核心算法
	
public:
	//带星标的不要在拷贝构造函数中复制
	QString strVision;								//算法版本
	QString strAppPath;								//系统路径
	QString strModelPath;							//模板路径
	QVector <int > vItemFlow;						//检测流程
	QVector <QVariant > vModelParas;				//模板参数
	QVector <QVariant > vModelShapes;				//模板形状
	Hobject	m_ImageSrc;								//原始图像
	Hobject m_normalbotXld;							//2013.9.22 nanjc 正常瓶子轮廓
	Hobject m_pressbotXld;							//2013.9.22 nanjc 应力瓶子轮廓
	Hobject oRegError;								//报错缺陷
	int		m_nWidth;								//图像宽度
	int		m_nHeight;								//图像高度
	int		m_nCamIndex;							//相机序号
	MyOri	modelOri;								//模板原点
	MyOri	currentOri;								//当前原点
	MyOri	normalOri;								//2013.9.22 nanjc 用于正常定位应力，接收正常图像原点坐标
	Hlong     m_nBaseCharModelID;					//瓶底字符定位MARK
	SideOrigin	oldSideOri;							//瓶身旧原点，用于自动纠错 
	bool	m_bLocate;								//是否定位
	int		m_nLocateItemID;						//定位检测项ID
	bool	m_bDisturb;								//是否排除干扰
	QVector<int> m_vDistItemID;						//干扰区域检测项ID
	int		m_nMaxErrNum;							//缺陷数量上限
	s_AlgCheckResult m_sCheckResult;				//返回系统的结果
	RtnInfo rtnInfo;								//返回算法的结果
	double m_dLastTime;								//上一次检测完成时间
	double m_dTimeProcess;							//当前检测耗时
	CDlgMainWindow *m_pMainWnd;						//*保存调试窗口指针	
	volatile bool m_bContinueShow;					//*连续显示标识符	
	volatile bool m_bStopAtError;					//*遇错自动停止
	double dLOFHei;									//剪刀印检测时极坐标变换的图像高度，用于缺陷信息显示
	int m_nColBodyCont;								//横向平移时瓶身轮廓用到
	double m_dAngBodyCont;							//横向平移时瓶身轮廓用到
	s_InputCheckerAry checkerAry;					//相机检测链表
	int m_nCheckType;								//检测类型
	bool m_bExtExcludeDefect;						//*提取排除缺陷标识
	QList <ExcludeInfo> m_vExcludeInfo;				//*所有排除缺陷
	bool m_bSaveErrorInfo;							//保存错误信息（图像，模板等）,便于测试问题所在
	QStringList strMoldOrderList;                      //瓶底模点排序
	bool m_bIsChecking;                             //系统是否正在检测
	QMutex qmutex;

private:
};

