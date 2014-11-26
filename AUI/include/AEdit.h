
#ifndef AEDIT_H
#define AEDIT_H

/* Afc���б༭��
 *֧�ֹ��ܣ�
 *	1. �ַ����롢ɾ��
 *	2. ������ת��δʵ�֣�
 *	3. ��������ƶ�
 *	4. �����ȷ�����λ��
 *	5. ���ѡ��δʵ�֣�
 *	6. ����ѡ��δʵ�֣�
 *	7. ���а������δʵ�֣�ע�⣺����ģʽ�²���������ȥ
 *	8. ����/�滻ģʽ��δʵ�֣�
 *	9. �ƶ���곬����������ʱ�Զ�����
 *	10.�����֧��
 *
 *
 */
class AUI_API AEdit : public AControl
{
	CLASS_INFO(Edit,Control);
public:
	AEdit(AComponent* pOwner);
	virtual ~AEdit(void);

	virtual bool GetReadOnly();
	virtual void SetReadOnly(bool b);

	virtual void DoFocus(AEvent* pEvent);
	virtual void DoLostFocus(AEvent* pEvent);

	virtual void DoMouseDown(AEvent* pEvent);
	virtual void DoMouseMove(AEvent* pEvent);

	virtual int GetCaretPos();
	virtual int GetScrollPos();
	virtual int GetSelStartPos();
	virtual int GetSelEndPos();

	virtual void SetCaretIndex(int iPos);//�ַ�λ��
	virtual int GetCaretIndex();

	virtual int GetSelStart();
	virtual void SetSelStart(int iIndex);

	virtual int GetSelCount();
	virtual void SetSelCount(int iCount);

	virtual ACHAR GetMaskChar();
	virtual void SetMaskChar(ACHAR ch);

	virtual bool CanFocus();

	virtual bool ShowCaret();

	virtual void SetPropFromNode(AMLBody* pNode);
	virtual void CreateChildren(AMLBody* pNode);

	AEventHandler		OnKeyDown;
	AEventHandler		OnKeyPress;
	AEventHandler		OnKeyUp;
	AEventHandler		OnChange;


	void OnFontChange();

	virtual void DoKeyboard(AEvent* pEvent);
	virtual void DoDblClick(AEvent* pEvent);
protected:
	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);

	virtual void _updatePos();//���¹������͹�������
	virtual void _updateSelPos();
	void _onCaretTimer(AObject* pAsso,int nTimerID);

	bool			m_bReadOnly;
	int			m_iCaretPos;
	int			m_iCaretIndex;
	int			m_iScrollPos;//����λ�ã����룩
	int			m_nCaretTimerID;
	int			m_iCaret;//�Ƿ���ʾ��꣨������˸��꣩
	ACHAR			m_chMaskChar;
	int			m_iSelStart;
	int			m_iSelCount;
	int			m_iSelStartPos;
	int			m_iSelEndPos;
};


#endif//AEDIT_H
