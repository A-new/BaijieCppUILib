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

#include "AFC.h"
#ifdef _DEBUG
#pragma comment(lib, "afcd.lib")
#else
#pragma comment(lib,"afc.lib")
#endif

#include "ASys.h"


extern HMODULE g_hInstance;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
