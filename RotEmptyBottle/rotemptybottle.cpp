#include "rotemptybottle.h"
#include "check.h"
#include "SetModel.h"

int nMaxCamareWidth;//�������ͼ���е������,ȫ�ֱ���
int g_nAlgType;		//�㷨����
//float fPressScale;	//Ӧ��ͼ������ϵ��
bool bCreateApp;	//�Ƿ񴴽�����̨��QT���Լ���������ϵͳ����APP
bool g_bSizeComplex;//�Ƿ�ߴ��ۺ�

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

//��ʼ����⶯̬��
s_Status init_bottle_module(int nWidth, int nHeight, int nChannel)
{
	s_Status sError;
	sError.nErrorID = RETURN_OK;
	if (!bCreateApp)
	{
		//��ֹͼ�겻��ʾ
		QApplication::addLibraryPath("./QtPlugins");
		//��ֹ��������
		QTextCodec*codec=QTextCodec::codecForName("GBK");
		QTextCodec::setCodecForLocale(codec);
		QTextCodec::setCodecForTr(codec);
		QTextCodec::setCodecForCStrings(codec);
	}
	//ϵͳ����
	set_system("parallelize_operators","false");//halcon�ڲ����л��ƣ����߳�ʱ�رգ����߳�ʱ����
	set_system("no_object_result","true");
	set_system("empty_region_result","true");
	set_system("image_cache_capacity", 16777216); //2017.6
	set_system("clip_region","false");//2018.2
	//��ʼ���쳣��ע�ͺ�����ڵ���Halcon����������Ϣ��
	HException::InstallHHandler(&MyHalconExceptionHandler);
	
	nMaxCamareWidth = nWidth;
	QString strConfigPath = "./Config\\Config.ini";
	QSettings groupSet(strConfigPath,QSettings::IniFormat);
	//��ȡӦ������ϵ��
	groupSet.beginGroup("system");
	//g_nAlgType = groupSet.value("nAlgType",1).toInt();
	//ƿ���ƿ�׷ֿ�����ϵͳ����
	//fPressScale = groupSet.value("fPressScale",1).toFloat();
	bCreateApp = groupSet.value("bCreateApp",1).toBool();
	g_bSizeComplex = groupSet.value("bSizeComplex",0).toBool();
	groupSet.endGroup();
	//�㷨ϵͳ����
	//���ݲ�ͬ�㷨����������ͬ����
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
		strcpy_s(sError.chErrorInfo,"�����ʼ������");
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

//���ӿ���
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

//ģ��ӿ���
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
