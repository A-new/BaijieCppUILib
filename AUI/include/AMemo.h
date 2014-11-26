#ifndef AMEMO_H
#define AMEMO_H

class AUI_API AMemo:public AContainer
{
	CLASS_INFO(Memo,Container);
public:
	AMemo(AComponent* pOwner);
	virtual ~AMemo();

	virtual bool GetReadOnly();
	virtual void SetReadOnly(bool b);

	virtual void SetTextStorage(AMemoTextStorage* p);
	virtual AMemoTextStorage* GetTextStorage();

	virtual AMemoAction* GetAction();
	virtual void SetAction(AMemoAction* p);

	//=== ����ϵ����׾���
	virtual int GetLeftSpace();
	virtual void SetLeftSpace(int v);

	virtual int GetTopSpace();
	virtual void SetTopSpace(int v);

	//=== �м��
	virtual int GetRowSpace();
	virtual void SetRowSpace(int v);

	virtual void SetText(AString s);
	virtual AString GetText();

	virtual int GetTabChars();
	virtual void SetTabChars(int v);

	virtual AControl* GetEditor();
	virtual void DoLayout();

	virtual bool CanFocus();
protected:
	bool			m_bReadOnly;
	int			m_iLeftSpace;//Left �� Top���׾���
	int			m_iTopSpace;
	int			m_iRowSpace;//�м��
	int			m_iTabChars;//һ��Tab���ڼ����ո�Ŀռ�
	int			m_iCaret;

	AMemoTextStorage*	m_pTextStorage;
	AMemoAction*		m_pAction;

	AControl*	m_pEdit;
	int		m_nCaretTimerID;

	
	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);
	virtual void DoFocus(AEvent* pEvent);
	virtual void OnEditDblClick(AObject* pSender,AEvent* pEvent);
	virtual void OnEditPaint(AObject* pSender,AEvent* pEvent);
	virtual void OnEditFocus(AObject* pSender,AEvent* pEvent);
	virtual void OnEditLostFocus(AObject* pSender,AEvent* pEvent);
	virtual void OnEditMouseDown(AObject* pSender,AEvent* pEvent);
	virtual void OnEditMouseMove(AObject* pSender,AEvent* pEvent);
	virtual void OnEditMouseUp(AObject* pSender,AEvent* pEvent);
	virtual void OnEditKeyBoard(AObject* pSender,AEvent* pEvent);

	void _onCaretTimer(AObject* pAsso,int nTimerID);

	virtual void _drawText(ACanvas* cs,const AString& sText,int x,int y,int w,int iLineHeight,int indexColoration);
};



#endif//AMEMO_H