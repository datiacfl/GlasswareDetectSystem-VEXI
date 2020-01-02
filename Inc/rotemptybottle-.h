#ifndef ROTEMPTYBOTTLE_H
#define ROTEMPTYBOTTLE_H


#define DLL_EXT _declspec(dllexport) 

#include "alg_struct.h"
using namespace Alg;

#include <vector>
using namespace std;

#include <iostream>

const int RETURN_OK           = 0; //��������
const int RETURN_CHECK_INIT   = 1; //��ʼ������
const int RETURN_MODEL_MANAGE = 2; //ģ��������
const int RETURN_PARA_MANAGE  = 3; //���������ô���
const int RETURN_CHECK_ERROR  = 4; //����㷨����
const int RETURN_CHECK_FREE   = 5; //�ͷŴ���
const int RETURN_NO_CLOSE	  = 6; //��ֹ�رմ���


class DLL_EXT RotEmptyBottle
{
public:
	RotEmptyBottle();
	~RotEmptyBottle();
private:

};
class CBottleCheck;

typedef struct 
{
	int nID;   //����ID
	CBottleCheck  *pChecker;   //��������
}s_CheckerList;

//2013.9.11 nanjc ��߽紫�ݷ����쳣���������鴫��
typedef struct 
{
	int iValidNum; //������������������
	s_CheckerList *pCheckerlist; //������ָ��
}s_InputCheckerAry;

typedef struct 
{
	bool bIsChecking; //�Ƿ����ڼ��

	bool bReserve;  //����
	int nReserve;	//����
	char* cReserve; //����
}s_SystemInfoforAlg;

///*****����Ϊ�㷨��̬����ؽӿڶ���*****//

// ��������
class DLL_EXT CAlgorithm  
{
public:
	CAlgorithm()
	{
	}
	virtual ~CAlgorithm()
	{
	}
	virtual Alg::s_Status init(Alg::s_AlgInitParam sAInitParam)=0;
	virtual Alg::s_Status Free()=0;
	virtual Alg::s_Status Check(Alg::s_AlgCInP sAlgCInP,Alg::s_AlgCheckResult **sAlgCheckResult)=0;
	virtual Alg::s_Status CopySizePara(Alg::s_SizePara4Copy &sSizePara)=0;
	virtual bool setsSystemInfo(s_SystemInfoforAlg &sSystemInfo)=0;
	virtual bool FindTwoPointsSubpix(Alg::s_ImagePara sImagePara,double inRow,POINT &pLeft,POINT &pRight,int nEdge)=0;
};

// ģ�������
class DLL_EXT CModel 
{
public:
	CModel()
	{
	}
	virtual ~CModel()
	{
    }

	virtual Alg::s_Status SetModelDlg(Alg::s_AlgModelPara sAlgModelPara,CBottleCheck *pChecker,
		s_InputCheckerAry checkerAry,void *parent = NULL)=0;
	virtual Alg::s_Status CloseModelDlg() = 0;

};


///*****����Ϊ�㷨������������*****//

/************************************************************************
	���ܣ���ʼ����⶯̬�⣬������������̬�⿪ʼǰ���Ǹı�������������ǰ
    int nWidth, int nHeight������ͼ����
	���Ƕ�����������Ҫͳһ��ʼ���Ĳ��� 
/************************************************************************/
s_Status DLL_EXT init_bottle_module(int nWidth, int nHeight, int nChannel);

s_Status DLL_EXT free_bottle_module();

//���ӿ���
class DLL_EXT CBottleCheck : public CAlgorithm
{
public:
	CBottleCheck();
	virtual ~CBottleCheck();
	
   /************************************************************************
	    ���ܣ���ʼ����������
 	/************************************************************************/
	s_Status init(Alg::s_AlgInitParam sAlgInitParam);
	/************************************************************************
	    ���ܣ��ͷż����������Դ
 	/************************************************************************/
	s_Status Free();	
	/************************************************************************
	    ���ܣ��������
	    s_AlgCInP sAlgCInP  ����������
        s_AlgCheckResult **sAlgCheckResult   ����������
 	/************************************************************************/
	s_Status Check(s_AlgCInP sAlgCInP,s_AlgCheckResult **sAlgCheckResult);	
	/************************************************************************
	    ���ܣ����ڳߴ��������ۺ�ʱ���Ʋ�������ǰ���ģ���ļ�
 	/************************************************************************/	
	Alg::s_Status CopySizePara(Alg::s_SizePara4Copy &sSizePara);
	bool setsSystemInfo(s_SystemInfoforAlg &sSystemInfo);
	bool FindTwoPointsSubpix(Alg::s_ImagePara sImagePara,double inRow,POINT &pLeft,POINT &pRight,int nEdge);

public:
	CAlgorithm *m_pAlg;
};

//ģ��ӿ��� 
class DLL_EXT CBottleModel : public CModel
{
public:
	// �����ָ�룬���ڸ��¶Ի��������õ�����
	CBottleCheck *m_pChecker;

	CBottleModel();
	virtual ~CBottleModel();
	
	/************************************************************************
	    ���ܣ����ü��ģ�����
        s_AlgModelPara sAlgModelPara ģ���������ݣ���ʱֻ����ͼ����Ϣ
	    CBottleCheck *pChecker  ��ǰ���ָ��
        s_InputCheckerAry checkerAry ���м�����飬����-
		        ������������ʹ��
	/************************************************************************/	
	Alg::s_Status SetModelDlg(Alg::s_AlgModelPara sAlgModelPara,CBottleCheck *pChecker,
		s_InputCheckerAry checkerAry,void *parent = NULL);
	Alg::s_Status CloseModelDlg();

protected:
	CModel *m_pModel;

};
#endif // ROTEMPTYBOTTLE_H
