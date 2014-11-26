#ifndef AWINCONTROLBASE_H
#define AWINCONTROLBASE_H

class ATooltip;

/*
 * AWinControlBase �� AFC�д����ھ���Ŀؼ����������ڿؼ�������������κοؼ����ǡ��޾�����Ŀؼ�
 */
class AUI_API AWinControlBase: public AContainer
{
	CLASS_INFO(WinControlBase,Container);
public:
	friend class AWindow;
	friend class AApplication;

	AWinControlBase(AComponent* pOwner);
	virtual ~AWinControlBase();

	//=== λ��
	virtual ARect GetAbsPosition();//�ؼ�����λ���������AFC���ڵ�λ�ã�������Ļλ��
	virtual ARect GetControlScrollPosition();//�ؼ����λ�ã���������������λ�õ�������
	virtual ARect GetControlPosition();//�ؼ����λ�ã���������ĸ��ؼ���λ��

	//=== ���ھ����Microsoft Windows�е�������
	virtual HWND GetHandle();
	virtual AWindow* GetWindow();//�õ���֮��Ӧ�ľ������

	//=== ����
	virtual bool Create();

	//=== ��ʾ������
	virtual void SetVisible(bool b);
	virtual void Show();
	virtual void ShowModal();
	virtual void Hide();

	//=== �����Դ����������ڵĹ�ϵ
	virtual void Destroy();
	virtual void WatchDelete(AControl* p);//�ڲ�ʹ��

	virtual void DoMove(AEvent* pEvent);
	virtual void DoResize(AEvent* pEvent);

	//=== λ��
	virtual int GetLeft();
	virtual int GetTop();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual TWindowPos GetPositionType();
	virtual void SetPositionType(TWindowPos wp);
	virtual void DoLayout();
	virtual bool GetSizable();
	virtual void SetSizable(bool v);


	virtual void SetPropFromNode(AMLBody* pNode);
	virtual void CreateChildren(AMLBody* pNode);

	//��ES��֧��
	virtual void ESGet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESSet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESCall(const AString& sPath,AUI_ES_VALUE_GROUP_INTF* args,AUI_ES_VALUE_INTF* pRetValue);

	//=== �¼�
	AEventHandler		OnShow;
	AEventHandler		OnHide;
	AEventHandler		OnMove;
	AEventHandler		OnResize;
	AEventHandler		OnCreate;
	AEventHandler		OnCloseQuery;
	AEventHandler		OnClose;
protected:
	AWindow*	m_pWindow;
	bool		m_bModal;
	TWindowPos	m_WindowPos;
	bool		m_bSizable;
	bool		m_bDestroyFromWin;
	
	

	
	virtual void InitControls();
	virtual void ConnectEvent();
	virtual void DoCreate();
	virtual AWindow* CreateWnd();

	
	virtual void _lastRelease();

	static void MessageLoop();
	
};
#endif//AWINCONTROLBASE_H