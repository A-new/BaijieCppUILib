// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <winuser.h>
//#include <olectl.h>
#include <shellapi.h>
#include <Shlobj.h>

#include <map>

#include "AFC.h"

#ifdef _DEBUG
#pragma comment(lib, "afcd.lib")
#else
#pragma comment(lib,"afc.lib")
#endif


#include "ASys.h"

#ifdef _DEBUG
#pragma comment(lib, "asysd.lib")
#else
#pragma comment(lib,"asys.lib")
#endif

#include "AUI.h"



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#ifdef _DEBUG
extern void DebugStr(const AString& s);
#else
#define DebugStr(x) OutputDebugString(x)
#endif

extern HMODULE g_hInstance;

struct ADragInfo
{
	AControl*	pSource;
	ASize		szDraw;
	bool		bDragging;
	bool		bCanceled;//�Ƿ��Ѿ�ȡ��
	bool		bAccept;
	int		X;
	int		Y;//�ϴε�λ��
};
extern ADragInfo g_DragInfo;

class time_counter
{
public:
	time_counter()
	{
		m_dwStart = ::GetTickCount();
	}
	~time_counter()
	{

	}
	DWORD Tick()
	{
		DWORD dw = ::GetTickCount();
		DWORD delta;
		if( dw >= m_dwStart ) delta = dw - m_dwStart;
		else delta = (DWORD)-1 - m_dwStart + dw;
		return delta;
	}
	void Reset()
	{
		m_dwStart = ::GetTickCount();
	}
	void Print(const AString& str)
	{
		OutputDebugString(AString().Format(_T("\r\n####### [%d]%s ########"),Tick(),str.Text()));
	}
private:
	DWORD		m_dwStart;
};
