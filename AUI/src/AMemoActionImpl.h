#ifndef AMEMOACTIONIMPL_H
#define AMEMOACTIONIMPL_H

#include "AMemoTextStorage.h"
class AMemo;

class AUI_API AMemoActionImpl : public AMemoAction
{
	CLASS_INFO(MemoActionImpl,MemoAction);
public:
	AMemoActionImpl(AMemo* pMemo);
	virtual ~AMemoActionImpl();

	//���ͼ����¼�
	virtual void OnMouseDown(AObject* pSender,AEvent* pEvent);
	virtual void OnMouseMove(AObject* pSender,AEvent* pEvent);
	virtual void OnMouseUp(AObject* pSender,AEvent* pEvent);
	virtual void OnKeyBoard(AObject* pSender,AEvent* pEvent);
	virtual void OnDblClick(AObject* pSender,AEvent* pEvent);

	//������
	virtual ACaretSeat GetCaretSeat();
	virtual void SetCaretSeat(ACaretSeat seat);//���ù��λ��
	virtual ARect GetCaretPos();
	virtual ARect GetCaretPosBySeat(ACaretSeat seat);//����ָ��λ�ӻ�ù����ʾ����

	//�ı�ѡ��
	virtual ACaretSeat GetSelStart();
	virtual ACaretSeat GetSelEnd();
	virtual int GetSelCount();
	virtual AString GetSelText();
	virtual void SetSel(ACaretSeat seatStart,ACaretSeat seatEnd);//��ѡ��
	virtual void SetColSel(ACaretSeat seatStart,ACaretSeat seatEnd);//�п�ѡ��
	virtual int GetSelType();

	//�ı�����
	virtual void Copy();//������ǰѡ���ı������п�
	virtual void Cut();//�����ı���
	virtual void Paste();//ճ�����ı�����ǰ���λ��
	virtual void InputChar(ACHAR ch);//��ͨ�ַ������루���뵽��괦��
	virtual void InputTab();
	virtual void InputEnter();
	virtual void InputEsc();
	virtual void InputDel();
	virtual void InputBackspace();
protected:
	AMemo*		m_pMemo;

	int			m_iCaretStep;//���ƹ����˸
	ACaretSeat		m_seatCaret;//���λ��
	ARect			m_rCaret;
	APoint			m_ptDown;

	//ѡ��
	ACaretSeat		m_seatSelStart;
	ACaretSeat		m_seatSelEnd;
	int			m_iSelType;

	virtual void _updateCaretPos();
	virtual int _getLineHeight(int iLine);
	virtual void UpdateEditorSize();
	virtual void _unselect();
	virtual void _delSelected();
	virtual ACaretSeat _toNext(ACaretSeat seat);
	virtual ACaretSeat _toPrev(ACaretSeat seat);
};


#endif//AMEMOACTIONIMPL_H

