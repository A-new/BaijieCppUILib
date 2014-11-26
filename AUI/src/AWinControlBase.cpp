#include "StdAfx.h"

AWinControlBase::AWinControlBase(AComponent* pOwner):
	base_class(pOwner)
{
	m_pWindow = NULL;
	m_bVisible = false;
	m_pUICore = new AUICore(this);
	DebugStr(AString().Format(_T("����һ��UICore:%p wincontrol:%p"),m_pUICore,this));
	m_pUICore->AddRef();
	m_bModal = false;
	m_WindowPos = wpDesign;
	m_bSizable = true;
	m_bDestroyFromWin = false;//�ɴ��ڴ������ٶ���
}

AWinControlBase::~AWinControlBase()
{
	DebugStr(AString().Format(_T("�ͷ�һ��UICore:%p wincontrol:%p"),m_pUICore,this));
	m_pUICore->Release();
	m_pUICore = NULL;
}


void AWinControlBase::Destroy()
{
	if( m_bDestroyed ) 
		return;
	//bool bLast=false;
	if( !m_bDestroyFromWin )
	{
		if( ::IsWindow(GetHandle()) )
		{
			::PostMessage(GetHandle(),WM_CLOSE,0,0);
			//AddRef();//���ⱻ�ͷţ���AWindow���ͷ�
			return;
			//m_pWindow->Close();
			//AddRef();//���ⱻ�ͷţ���AWindow���ͷ�
		}
		else
		{
			//bLast = true;
			//AddRef();
		}
	}
	
	base_class::Destroy();
	//if( bLast )
		//_lastRelease();
}

//��ӹ�ע����ʾ��p��ע�Լ���pҪ���������˲����ͷ���
void AWinControlBase::WatchDelete(AControl* p)
{
	if( ::IsWindow( GetHandle() ) )
		m_aWatchDelete.Add(p);
}

//���һ���������ͷŶ���
//�ͷ��Լ���Ҳ�ͷŹ�ע�Լ��Ķ���
void AWinControlBase::_lastRelease()
{
	AContainer* pcParent = dynamic_cast<AContainer*>(GetParent());
	if( pcParent )
		pcParent->GetUICore()->RemoveWatcher(this);

	m_aWatchDelete.Clear();
	Release();
}

AWindow* AWinControlBase::GetWindow()
{
	return m_pWindow;
}
void AWinControlBase::SetSizable(bool v)
{
	m_bSizable = v;
}

bool AWinControlBase::GetSizable()
{
	return m_bSizable;
}

HWND AWinControlBase::GetHandle()
{
	if( m_pWindow ) return m_pWindow->GetHandle();
	else return NULL;
}

TWindowPos AWinControlBase::GetPositionType()
{
	return m_WindowPos;
}

void AWinControlBase::SetPositionType(TWindowPos wp)
{
	m_WindowPos = wp;
}

void AWinControlBase::SetVisible(bool b)
{
	if( m_bVisible != b )
	{
		if( b )
		{
			if( m_pWindow == NULL ) 
			{
				if( !Create() ) return;
				DoLayout();
				if( (AControl*)this == (AControl*)AApplication::Get()->GetMainForm() )
					m_pWindow->SetPostQuitFlag(true);
			}
			ARect rPos;
			::GetWindowRect(GetHandle(),&rPos);
			//if(!( rPos.left == GetLeft() && rPos.top == GetTop() && rPos.GetWidth() == GetWidth() && rPos.GetHeight() == GetHeight() ))
			//	::MoveWindow(GetHandle(),GetLeft(),GetTop(),GetWidth(),GetHeight(),TRUE);
			//else
				::ShowWindow(GetHandle(), SW_SHOW);
			//fix me later : ����ĳЩ����ϵͳ�汾����WinXP������ֲ�����ȷ��ʾ�����⣬��ʱͨ�����²����źͰ취���
			if( AApplication::Get()->GetOSName().Find(_T("Windows XP")) > -1 )
			{
				int iWidth = GetWidth();
				::MoveWindow(GetHandle(),GetLeft(),GetTop(),iWidth+1,GetHeight(),TRUE);
				::MoveWindow(GetHandle(),GetLeft(),GetTop(),iWidth,GetHeight(),TRUE);
				//::MoveWindow(GetHandle(),GetLeft(),GetTop(),GetWidth()+1,GetHeight(),TRUE);
			}
			
			::SetFocus(GetHandle());//ʹ֮���������ϳ���
			//::UpdateWindow(GetHandle());
			//Refresh();
			AEvent evt;
			OnShow.Call(this,&evt);
		}
		else
		{
			if( ::IsWindow(GetHandle()) )
				::ShowWindow(GetHandle(),SW_HIDE);
			AEvent evt;
			OnHide.Call(this,&evt);
		}
		m_bVisible = b;
	}
}
void AWinControlBase::InitControls()
{
	//must be override;
}

void AWinControlBase::ConnectEvent()
{
	//must be override;
}

AWindow* AWinControlBase::CreateWnd()
{
	//�������������أ��Դ���m_pWindow��ʵ��
	return NULL;
}
bool AWinControlBase::Create()
{
	if( m_pWindow ) return true;
	
	InitControls();

	m_pWindow = CreateWnd();
	if( m_pWindow == NULL ) return false;
	m_pWindow->AddRef();

	HWND hParent = NULL;
	AControl* pParent = dynamic_cast<AControl*>( GetParent() );
	if( pParent ) hParent = pParent->GetUICore()->GetHandle();
	
	if( !m_pWindow->Create(hParent,m_WindowPos) ) 
	{
		m_pWindow->Release();
		m_pWindow = NULL;
		throw AException(_T("���ڴ���ʧ�ܣ�"));
		return false;
	}

	AContainer* pcParent = dynamic_cast<AContainer*>(GetParent());
	if( pcParent )
		pcParent->GetUICore()->AddWatcher(this);

	//�ٽ�������Ĵ���
	if( m_WindowPos == wpDesign )
	{
		::SetWindowPos(GetHandle(),HWND_NOTOPMOST,GetLeft(),GetTop(),GetWidth(),GetHeight(),SWP_NOREDRAW|SWP_HIDEWINDOW);
	}
	else if( m_WindowPos == wpCenterScreen )
	{
		ARect rScreen;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rScreen,0);
		int dw = (rScreen.right-rScreen.left-GetWidth())/2;
		int dh = (rScreen.bottom-rScreen.top-GetHeight())/2;
		m_iLeft = (rScreen.left+dw);
		m_iTop = (rScreen.top+dh);
		::SetWindowPos(GetHandle(),HWND_NOTOPMOST,GetLeft(),GetTop(),GetWidth(),GetHeight(),SWP_NOREDRAW|SWP_HIDEWINDOW);
	}
	else
	{
		ARect r;
		::GetWindowRect(GetHandle(),&r);
		//::SetWindowPos(GetHandle(),HWND_NOTOPMOST,r.left,r.top+1,r.GetWidth(),r.GetHeight(),0);
		m_iLeft = r.left;
		m_iTop = r.top;
		m_iWidth = r.GetWidth();
		m_iHeight = r.GetHeight();
		
	}
	//::SetWindowPos(GetHandle(),HWND_NOTOPMOST,GetLeft(),GetTop(),GetWidth(),GetHeight(),0);//SWP_NOREDRAW|SWP_HIDEWINDOW);
	//::SetWindowPos(GetHandle(),HWND_NOTOPMOST,GetLeft(),GetTop(),GetWidth(),GetHeight(),SWP_NOREDRAW|SWP_HIDEWINDOW);
	DoCreate();
	ConnectEvent();
	DoLayout();
	Refresh();


	//HRGN hRgn = ::CreateRoundRectRgn(0,0,GetWidth()+1,GetHeight()+1,5,5);
	//::SetWindowRgn(m_pWindow->GetHandle(),hRgn,FALSE);
	//::DeleteObject(hRgn);

	AEvent evt;
	OnCreate.Call(this,&evt);
	return true;
}

int AWinControlBase::GetLeft()
{
	return m_iLeft;
}

int AWinControlBase::GetTop()
{
	return m_iTop;
}

int AWinControlBase::GetWidth()
{
	return m_iWidth;
}

int AWinControlBase::GetHeight()
{
	return m_iHeight;
}

void AWinControlBase::DoLayout()
{
	m_rAbsPos = ARect(0,0,m_iWidth,m_iHeight);
	base_class::DoLayout();
}
void AWinControlBase::DoCreate()
{
	//����������
}
void AWinControlBase::Show()
{
	SetVisible(true);
}

void AWinControlBase::DoMove(AEvent* pEvent)
{
	AMouseEvent* evt = dynamic_cast<AMouseEvent*>(pEvent);
	if( evt )
	{
		RECT rScreen;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rScreen,0);
		//if( evt->m_X < rScreen.right ) SetLeft( evt->m_X );
		//if( evt->m_Y < rScreen.bottom ) SetTop( evt->m_Y );
		m_iLeft = evt->m_X;
		m_iTop = evt->m_Y;
		//DoLayout(); ֻ���ƶ�λ�ã�����ҪDoLayout
	}
	
	Refresh();
	OnMove.Call(this,pEvent);
}

void AWinControlBase::DoResize(AEvent* pEvent)
{
	if( m_pHorzScrollBar != NULL ) m_pHorzScrollBar->SetVisible(m_bHorzScrollBarShow);
	if( m_pVertScrollBar != NULL ) m_pVertScrollBar->SetVisible(m_bVertScrollBarShow);
	AMouseEvent* evt = dynamic_cast<AMouseEvent*>(pEvent);
	if( evt )
	{
		//SetWidth(evt->m_X);
		//SetHeight(evt->m_Y);
		m_iWidth = evt->m_X;
		m_iHeight = evt->m_Y;
		DoLayout();
	}
	
	Refresh();
	OnResize.Call(this,pEvent);
}

void AWinControlBase::ShowModal()
{
	AControl* pParent = dynamic_cast<AControl*>(GetParent());
	//if( pParent ) pParent->Refresh();

	
	
	HWND hWndParent = (pParent ? pParent->GetUICore()->GetHandle() : NULL );
	HWND hFirstParent = hWndParent;
	HWND hWnd = GetHandle();
	//��ʾ�Լ�   
	//ShowWindow(hWnd, SW_SHOW);  
	//BringWindowToTop(hWnd);   
	//if( pParent ) pParent->Refresh();
	//disable��������    
	while(hWndParent != NULL)   
	{   
		EnableWindow(hWndParent, FALSE);   
		//::InvalidateRect(hWndParent,NULL,FALSE);
		//::UpdateWindow(hWndParent);

		hWndParent = ::GetParent(hWndParent);   
	}  
	SetVisible(true);
	m_bModal = true;
	m_pWindow->SetPostQuitFlag(true);
	//�ӹ���Ϣѭ��   
	DebugStr(_T("\r\nBegin modalWin.Run"));
	while(true)   
	{   
		MSG msg;   
		if (!GetMessage(&msg, NULL, 0, 0))   
			break;   
		TranslateMessage(&msg);   
		DispatchMessage(&msg);   
	}   
	DebugStr(_T("\r\nEnd ModalWin.Run"));
	//���Լ�����   
	ShowWindow(hWnd, SW_HIDE);  
	//Close();
	//ģ̬�Ѿ��˳�   
	//�ָ������ڵ�enable״̬   
	hWndParent = hFirstParent;   
	while (hWndParent != NULL)   
	{   
		EnableWindow(hWndParent, TRUE);
		//::InvalidateRect(hWndParent,NULL,TRUE);
		//::UpdateWindow(hWndParent);
		hWndParent = ::GetParent(hWndParent);   
	}   
	SetForegroundWindow(hFirstParent);
	//SetFocus(hFirstParent);
}

void AWinControlBase::Hide()
{
	SetVisible(false);
}

ARect AWinControlBase::GetAbsPosition()
{
	return ARect(0,0,GetWidth(),GetHeight());
}

ARect AWinControlBase::GetControlScrollPosition()
{
	ARect r;
	r = ARect(0,0,GetWidth(),GetHeight());
	return r;
}

ARect AWinControlBase::GetControlPosition()
{
	ARect r;
	r = ARect(0,0,GetWidth(),GetHeight());
	return r;
}

void AWinControlBase::MessageLoop()
{
	MSG  msg;
	int status;

	while ((status = ::GetMessage (&msg, 0, 0, 0 )) != 0)
	{
		if (status == -1) {
			// handle the error, break
			break;
		}
		try
		{
			::TranslateMessage (&msg);
			::DispatchMessage (&msg); 
		}
		catch(AException& e)
		{
			//::MessageBox(NULL,e.GetDesc(),_T("����"),0);
			AMessageBox::Error(e.GetDesc());
		}
	}
}

void AWinControlBase::CreateChildren(AMLBody* pNode)
{
	base_class::CreateChildren(pNode);
	DoLayout();
}

void AWinControlBase::SetPropFromNode(AMLBody* pNode)
{
	base_class::SetPropFromNode(pNode);

	PROP_SET(OnShow);
	PROP_SET(OnHide);
	PROP_SET(OnMove);
	PROP_SET(OnResize);
	PROP_SET(OnCreate);
	PROP_SET(OnCloseQuery);
	PROP_SET(OnClose);
}

void AWinControlBase::ESGet(const AString& sPath,AUI_ES_VALUE_INTF* pValue)
{
	if( pValue == NULL ) return;
	base_class::ESGet(sPath,pValue);
}

void AWinControlBase::ESSet(const AString& sPath,AUI_ES_VALUE_INTF* pValue)
{
	if( pValue == NULL ) return;
	base_class::ESSet(sPath,pValue);
}

void AWinControlBase::ESCall(const AString& sPath,AUI_ES_VALUE_GROUP_INTF* args,AUI_ES_VALUE_INTF* pRetValue)
{
	if( sPath == _T("Show")) this->Show();
	else if( sPath == _T("ShowModal")) this->ShowModal();
	else if( sPath == _T("Hide")) this->Hide();
	else if( sPath == _T("Close")) this->Destroy();
}