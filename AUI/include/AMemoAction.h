#ifndef AMEMOACTION_H
#define AMEMOACTION_H

#define SEL_TYPE_NONE	0 //δѡ��
#define SEL_TYPE_ROW	1 //��ѡ��
#define SEL_TYPE_COL	2 //��ѡ��

class AUI_API AMemoAction : public AObject
{
	CLASS_INFO(MemoAction,Object);
public:
	//���ͼ����¼�
	virtual void OnMouseDown(AObject* pSender,AEvent* pEvent)=0;
	virtual void OnMouseMove(AObject* pSender,AEvent* pEvent)=0;
	virtual void OnMouseUp(AObject* pSender,AEvent* pEvent)=0;
	virtual void OnKeyBoard(AObject* pSender,AEvent* pEvent)=0;
	virtual void OnDblClick(AObject* pSender,AEvent* pEvent)=0;

	//������
	virtual ACaretSeat GetCaretSeat()=0;
	virtual void SetCaretSeat(ACaretSeat seat)=0;//���ù��λ��
	virtual ARect GetCaretPos()=0;
	virtual ARect GetCaretPosBySeat(ACaretSeat seat)=0;//����ָ��λ�ӻ�ù����ʾ����

	//�ı�ѡ��
	virtual ACaretSeat GetSelStart()=0;
	virtual ACaretSeat GetSelEnd()=0;
	virtual int GetSelCount()=0;
	virtual AString GetSelText()=0;
	virtual void SetSel(ACaretSeat seatStart,ACaretSeat seatEnd)=0;//��ѡ��
	virtual void SetColSel(ACaretSeat seatStart,ACaretSeat seatEnd)=0;//�п�ѡ��
	virtual int GetSelType()=0;

	//�ı�����
	virtual void Copy()=0;//������ǰѡ���ı������п�
	virtual void Cut()=0;//�����ı���
	virtual void Paste()=0;//ճ�����ı�����ǰ���λ��
	virtual void InputChar(ACHAR ch)=0;//��ͨ�ַ������루���뵽��괦��
	virtual void InputTab()=0;
	virtual void InputEnter()=0;
	virtual void InputEsc()=0;
	virtual void InputDel()=0;
	virtual void InputBackspace()=0;

};


#endif//AMEMOACTION_H

