// HMI.h : HMI DLL ����ͷ�ļ�
//

#pragma once


#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������




// CHMIApp
// �йش���ʵ�ֵ���Ϣ������� HMI.cpp
//

class CHMIApp : public CWinApp
{
public:
	CHMIApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
