#include "stdafx.h"
#include "ADelMsgExtend.h"
#include "AWindow.h"

ADelMsgExtend::ADelMsgExtend():AMsgExtend()
{
	//
}


ADelMsgExtend::~ADelMsgExtend()
{
	//
}

ADelMsgExtend::ADelMsgExtend(AWindow* pWin):AMsgExtend(),m_pWindow(pWin)
{
	//
}

//��Ϣ����ǰ׺���������false���򲻽��к�������
bool ADelMsgExtend::BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	return true;
}

//��Ϣ�����׺
void ADelMsgExtend::AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	
}
//��Ϣ���˴���
bool ADelMsgExtend::DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	//
	return true;
}


