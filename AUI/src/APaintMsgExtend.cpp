#include "stdafx.h"
#include "APaintMsgExtend.h"
#include "AWindow.h"

APaintMsgExtend::APaintMsgExtend():AMsgExtend()
{
	//
}


APaintMsgExtend::~APaintMsgExtend()
{
	//
}

APaintMsgExtend::APaintMsgExtend(AWindow* pWin):AMsgExtend(),m_pWindow(pWin)
{
	//
}

//��Ϣ����ǰ׺���������false���򲻽��к�������
bool APaintMsgExtend::BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	//����ˢ����ʾ�������NeedRefresh m_pWindow->GetOwner()->GetUICore()->m_bNeedRefresh = false;
	//m_pWindow->GetOwner()->GetUICore()->m_rRefreshArea = ARect(0,0,0,0);
	return true;
}

//��Ϣ�����׺
void APaintMsgExtend::AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	AWinControlBase* pBase = m_pWindow->GetOwner();
	if( pBase == NULL ) return ;

	AUICore* pCore = pBase->GetUICore();
	if( pCore->m_bNeedRefresh )
	{
		HWND hWnd = m_pWindow->GetHandle();
		ARect r = pCore->m_rRefreshArea;
		::InvalidateRect(hWnd,&r,FALSE);
		::UpdateWindow(hWnd);
		//pCore->m_bNeedRefresh = false;
		//pCore->m_rRefreshArea = ARect(0,0,0,0);
	}
}
//��Ϣ���˴���
bool APaintMsgExtend::DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	return true;
}


