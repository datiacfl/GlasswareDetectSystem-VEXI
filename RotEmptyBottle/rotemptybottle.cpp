#include "rotemptybottle.h"
#include "check.h"
#include "SetModel.h"

int nMaxCamareWidth;//所有相机图像中的最大宽度,全局变量
int g_nAlgType;		//算法类型
//float fPressScale;	//应力图像增亮系数
bool bCreateApp;	//是否创建控制台，QT不自己创建，与系统共用APP
bool g_bSizeComplex;//是否尺寸综合

RotEmptyBottle::RotEmptyBottle()
{

}

RotEmptyBottle::~RotEmptyBottle()
{

}

//RotEmptyBottle theApp;-lx

void MyHalconExceptionHandler(const HException& except)
{
	throw except;
}

//初始化检测动态库
s_Status init_bottle_module(int nWidth, int nHeight, int nChannel)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	if (!bCreateApp)
	{
		//防止图标不显示
		QApplication::addLibraryPath("./QtPlugins");
		//防止中文乱码
		QTextCodec*codec=QTextCodec::codecForName("GBK");
		QTextCodec::setCodecForLocale(codec);
		QTextCodec::setCodecForTr(codec);
		QTextCodec::setCodecForCStrings(codec);
	}
	//系统设置
	set_system("parallelize_operators","false");//halcon内部并行机制：多线程时关闭，单线程时开启
	set_system("no_object_result","true");
	set_system("empty_region_result","true");
	set_system("image_cache_capacity", 16777216); //2017.6
	set_system("clip_region","false");//2018.2
	//初始化异常（注释后可用于调试Halcon函数报错信息）
	HException::InstallHHandler(&MyHalconExceptionHandler);
	
	nMaxCamareWidth = nWidth;
	QString strConfigPath = "./Config\\Config.ini";
	QSettings groupSet(strConfigPath,QSettings::IniFormat);
	//读取应力增亮系数
	groupSet.beginGroup("system");
	//g_nAlgType = groupSet.value("nAlgType",1).toInt();
	//瓶身和瓶底分开，由系统传递
	//fPressScale = groupSet.value("fPressScale",1).toFloat();
	bCreateApp = groupSet.value("bCreateApp",1).toBool();
	g_bSizeComplex = groupSet.value("bSizeComplex",0).toBool();
	groupSet.endGroup();
	//算法系统类型
	//根据不同算法类型启动不同界面
#ifdef DAHENGBLPKP_QT
	g_nAlgType = 2;
#else
	g_nAlgType = 1;
#endif
	//if (fPressScale <= 0 || fPressScale>=10)
	//{
	//	fPressScale = 1;
	//}

	try
	{		
		reset_obj_db(HTuple(nWidth), HTuple(nHeight), HTuple(0));		
	}
	catch (...)
	{
		sError.nErrorID = RETURN_CHECK_INIT;
		strcpy_s(sError.chErrorInfo,"程序初始化错误");
		strcpy_s(sError.chErrorContext,"init_bottle_module");
		return sError; 
	}

	return sError;
}

s_Status free_bottle_module()
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;

	return sError;
}

//检测接口类
CBottleCheck::CBottleCheck()
{
	
	m_pAlg = new CCheck;	
}
CBottleCheck::~CBottleCheck()
{
	if(m_pAlg != NULL)
		delete m_pAlg;
}

s_Status CBottleCheck::init(s_AlgInitParam sAInitParam)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	sError = m_pAlg->init(sAInitParam);

	return sError;
}

s_Status CBottleCheck::Free()
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	sError = m_pAlg->Free();

	return sError;
}

s_Status CBottleCheck::Check(s_AlgCInP sAlgCInP,s_AlgCheckResult **sAlgCheckResult)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	((CCheck*)m_pAlg)->qmutex.lock();
	//m_pAlg->qmutex.lock();
	sError = m_pAlg->Check(sAlgCInP,sAlgCheckResult);
	//m_pAlg->qmutex.unlock();
	((CCheck*)m_pAlg)->qmutex.unlock();

	return sError;
}

s_Status CBottleCheck::CopySizePara(s_SizePara4Copy &sSizePara)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	m_pAlg->CopySizePara(sSizePara);

	return sError;
}

bool CBottleCheck::setsSystemInfo(s_SystemInfoforAlg &sSystemInfo)
{
	m_pAlg->setsSystemInfo(sSystemInfo);

	return true;
}

bool CBottleCheck::FindTwoPointsSubpix(s_ImagePara sImagePara,double inRow,POINT &pLeft,POINT &pRight,int nEdge)
{
	m_pAlg->FindTwoPointsSubpix(sImagePara,inRow,pLeft,pRight,nEdge);
	return true;
}

//模板接口类
CBottleModel::CBottleModel()
{
	m_pModel=new CSetModel;
}

CBottleModel::~CBottleModel()
{
	if(m_pModel!=NULL)
		delete m_pModel;
}

s_Status CBottleModel::SetModelDlg(s_AlgModelPara sAlgModelPara,CBottleCheck *pChecker,
	s_InputCheckerAry checkerAry,void *parent/* = NULL*/)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	if(NULL == pChecker || NULL == pChecker->m_pAlg)  MessageBoxA(NULL,"pChecker is null rotemptybot_line180", "risk", MB_OK);
	if(NULL == checkerAry.pCheckerlist)  MessageBoxA(NULL,"pCheckerlist is null rotemptybot_line181", "risk", MB_OK);	
	sError = m_pModel->SetModelDlg(sAlgModelPara,pChecker, checkerAry,parent);
	return sError;
}

s_Status CBottleModel::CloseModelDlg()
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;	
	sError = m_pModel->CloseModelDlg();
	return sError;
}
