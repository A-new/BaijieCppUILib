// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// AFC.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
#ifdef _DEBUG

void DebugStr(const AString& s)
{
	ADateTime dt = ADateTime::GetCurrentTime();
	AString sx;
	sx.Format(_T("\r\n[%02d:%02d:%02d:%02d] "),dt.GetHour(),dt.GetMinute(),dt.GetSecond(),dt.GetMSecond());
	sx += s;
	OutputDebugString(sx);
}

#endif

ADragInfo g_DragInfo;