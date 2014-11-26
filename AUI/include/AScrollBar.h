#ifndef ASCROLLBAR_H
#define ASCROLLBAR_H

//��ť������־
#define SCROLLBAR_ELEM_NONE		0 //��
#define SCROLLBAR_ELEM_BUTTON1		1 //���ϣ���ť
#define SCROLLBAR_ELEM_BUTTON2		2 //�ң��£���ť
#define SCROLLBAR_ELEM_SLIDE		3 //���鰴ť
#define SCROLLBAR_ELEM_RAIL_1		4 //������ϣ����󣩲���
#define SCROLLBAR_ELEM_RAIL_2		5 //������£����ң�����
#define SCROLLBAR_ELEM_TOP1		1 //�����ϣ���ť
#define SCROLLBAR_ELEM_TOP2		2 //���ң��£���ť

//��ť����״̬
#define SCROLLBAR_STATUS_NORMAL		0 //����
#define SCROLLBAR_STATUS_DOWN		1 //MouseDown
#define SCROLLBAR_STATUS_OVER		2 //MouseOver
#define SCROLLBAR_STATUS_UP		3 //MouseUp

class AUI_API AScrollBar: public AControl
{
	CLASS_INFO(ScrollBar,Control);
public:
	friend class AContainer;
	AScrollBar(AComponent* pOwner);
	virtual ~AScrollBar();

	//-- ���ͣ���ֱ��ˮƽ
	virtual eScrollBarKind GetKind()=0;

	//-- ��Χ
	virtual void SetRange(int v);
	virtual int GetRange();

	//-- ��ǰλ��
	virtual void SetPosition(int v);
	virtual int GetPosition();

	//-- ��ť������
	virtual bool GetShowButton();
	virtual void SetShowButton(bool v);
	virtual bool GetShowTop();
	virtual void SetShowTop(bool v);

	//������㸨������
	virtual ARect GetButton1Pos();
	virtual ARect GetButton2Pos();
	virtual ARect GetTopButton1Pos();//�ö�
	virtual ARect GetTopButton2Pos();//�õ�
	virtual ARect GetRailPos_1();
	virtual ARect GetRailPos_2();
	virtual ARect GetRailPos();
	virtual ARect GetSlideButtonPos();
	virtual int GetElemStatus();
	virtual int GetVirtualSize();
	virtual int GetTrueSize();
	virtual double GetRate();
	virtual int GetRailLen();
	virtual int GetMouseOnElem();

	virtual void DoMouseDown(AEvent* pEvent);
	virtual void DoMouseUp(AEvent* pEvent);
	virtual void DoMouseMove(AEvent* pEvent);
	
	
	virtual void DoEnter(AEvent* pEvent);
	virtual void DoLeave(AEvent* pEvent);
	virtual void DoMouseWheel(AEvent* pEvent);
	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);

	virtual void SetMiniStep(int v);
	virtual int GetMiniStep();
	virtual void SetBigStep(int v);
	virtual int GetBigStep();

	virtual void SetWidth(int v);
	virtual void SetHeight(int v);

	//��ES��֧��
	virtual void ESGet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESSet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESCall(const AString& sPath,AUI_ES_VALUE_GROUP_INTF* args,AUI_ES_VALUE_INTF* pRetValue);

	bool IsContainerScrollBar();

	virtual AControl* _HitTest(int X,int Y);

	AEventHandler	OnScroll;

protected:
	int		m_iPosition;
	int		m_iRange;

	int		m_MouseOnElem;
	int		m_ElemStatus;

	int		m_iMiniStep;
	int		m_iBigStep;
	APoint		m_ptMouse;
	int		m_iDownPosition;

	bool		m_bShowButton;
	bool		m_bShowTop;//�ö����ף�

	eScrollBarKind	m_Kind;

	int ButtonElemOnPos(int X,int Y);
	virtual void _Change(int iSize);
	
};

class AUI_API AHorzScrollBar : public AScrollBar
{
	CLASS_INFO(HorzScrollBar,ScrollBar);
public:
	friend class AContainer;
	AHorzScrollBar(AComponent* pOwner);
	virtual ~AHorzScrollBar(){m_Kind = sbHorz;}
	virtual eScrollBarKind GetKind(){ return m_Kind; }
};

class AUI_API AVertScrollBar : public AScrollBar
{
	CLASS_INFO(VertScrollBar,ScrollBar);
public:
	friend class AContainer;
	AVertScrollBar(AComponent* pOwner);
	virtual ~AVertScrollBar(){m_Kind= sbVert;}

	virtual eScrollBarKind GetKind(){ return m_Kind; }
};

#endif//ASCROLLBAR_H
