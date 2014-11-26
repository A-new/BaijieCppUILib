#include "stdafx.h"
#include "ACaptureMsgExtend.h"
#include "AWindow.h"

ACaptureMsgExtend::ACaptureMsgExtend():AMsgExtend()
{
	//
}


ACaptureMsgExtend::~ACaptureMsgExtend()
{
	//
}

ACaptureMsgExtend::ACaptureMsgExtend(AWindow* pWin):AMsgExtend(),m_pWindow(pWin)
{
	//
}

//��Ϣ����ǰ׺���������false���򲻽��к�������
bool ACaptureMsgExtend::BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	//AWinControlBase* pBase = m_pWindow->GetOwner();
	return true;
}

//��Ϣ�����׺
void ACaptureMsgExtend::AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	//
}
//��Ϣ���˴���
bool ACaptureMsgExtend::DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)
{
	AWinControlBase* pBase = m_pWindow->GetOwner();
	if( pBase->GetUICore() == NULL ) return true;

	AControl* pCaptureControl = pBase->GetUICore()->GetCaptureControl();
	if( pCaptureControl != NULL )
	{
		ARect rCapture = pCaptureControl->GetAbsPosition();
		//OutputDebugString(_T("����CaptureMsgExtend...")+AString().Format(_T("classtype=%s"),pCaptureControl->GetClass()));

		if( uMsg == WM_LBUTTONDOWN )
		{
			AFlagSet DownFlag;

			if( wParam & MK_CONTROL ) DownFlag << ksCtrl;
			if( wParam & MK_LBUTTON ) DownFlag << ksLeftButton;
			if( wParam & MK_RBUTTON ) DownFlag << ksRightButton;
			if( wParam & MK_MBUTTON ) DownFlag << ksMiddleButton;
			if( wParam & MK_SHIFT ) DownFlag << ksShift;
			if((GetKeyState(VK_MENU) & (1<<(sizeof(SHORT)*8-1))) != 0) DownFlag << ksAlt;

			int X= GET_X_LPARAM(lParam);
			int Y= GET_Y_LPARAM(lParam);

			AMouseEvent evt;
			evt.m_wParam = wParam;
			evt.m_lParam = lParam;
			evt.m_X = X;
			evt.m_Y = Y;
			evt.m_KeyStates = DownFlag;

			AControl* pHit = pCaptureControl->_HitTest(X,Y);

			DebugStr(_T("׼���жϵ����λ��"));
			if( rCapture.PtInRect(APoint(X,Y)) )
			{
				pCaptureControl->DoMouseDown(&evt);
			}
			else
			{
				DebugStr(_T("��CaptureControl��"));
				pCaptureControl->DoLostFocus(&evt);
			}
		}
		else if( uMsg == WM_MOUSEMOVE )
		{
			AFlagSet flag;

			if( wParam & MK_CONTROL ) flag << ksCtrl;
			if( wParam & MK_LBUTTON ) flag << ksLeftButton;
			if( wParam & MK_RBUTTON ) flag << ksRightButton;
			if( wParam & MK_MBUTTON ) flag << ksMiddleButton;
			if( wParam & MK_SHIFT ) flag << ksShift;
			if((GetKeyState(VK_MENU) & (1<<(sizeof(SHORT)*8-1))) != 0) flag << ksAlt;

			int X= GET_X_LPARAM(lParam);
			int Y= GET_Y_LPARAM(lParam);

			AMouseEvent evt;
			evt.m_wParam = wParam;
			evt.m_lParam = lParam;
			evt.m_X = X;
			evt.m_Y = Y;
			evt.m_KeyStates = flag;

			AControl* pHit = pCaptureControl->_HitTest(X,Y);
			pBase->GetUICore()->SetMouseOverControl(pCaptureControl);
			pBase->GetUICore()->SetMovePoint(APoint(X,Y));
			pCaptureControl->DoMouseMove(&evt);
			pBase->GetUICore()->Refresh(pBase->GetAbsPosition());
		}
		else if( uMsg == WM_LBUTTONUP )
		{
			AFlagSet state;
			if( wParam & MK_CONTROL ) state << ksCtrl;
			//if( wParam & MK_LBUTTON )
				state << ksLeftButton;//��Ȼ���������ˣ��ǿ϶��Ͱ����������
			if( wParam & MK_RBUTTON ) state << ksRightButton;
			if( wParam & MK_MBUTTON ) state << ksMiddleButton;
			if( wParam & MK_SHIFT ) state << ksShift;
			if((GetKeyState(VK_MENU) & (1<<(sizeof(SHORT)*8-1))) != 0) state << ksAlt;

			int X= GET_X_LPARAM(lParam);
			int Y= GET_Y_LPARAM(lParam);

			AMouseEvent evt;
			evt.m_wParam = wParam;
			evt.m_lParam = lParam;
			evt.m_X = X;
			evt.m_Y = Y;
			evt.m_KeyStates = state;

			pCaptureControl->DoMouseUp(&evt);
			if( pCaptureControl->GetUICore()->GetMouseDownControl() == pCaptureControl )
				pCaptureControl->DoClick(&evt);

			AControl* pHit = pCaptureControl->_HitTest(X,Y);

			pCaptureControl->GetUICore()->SetMouseDownControl(NULL);
			pCaptureControl->GetUICore()->SetMouseOverControl(NULL);
			//OutputDebugString(_T("ȡ��CaptureControl..."));
			pCaptureControl->GetUICore()->SetCaptureControl(NULL);
		}
		else //if( uMsg == WM_PAINT )
		{
			return true;
		}
		//OutputDebugString(_T("�뿪CaptureMsgExtend..."));
		return false;
	}
	return true;
}


