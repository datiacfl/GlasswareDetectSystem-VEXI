/*��־�ڴ��ⱨ�棺setdebugnew.h
ע�⣬ֻ����cpp�����setdebugnew.h��������new��������Щ���������౻���ã��Ż�����ڴ�й¶����*/
#ifndef SET_DEBUG_NEW_H
#define SET_DEBUG_NEW_H

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#endif