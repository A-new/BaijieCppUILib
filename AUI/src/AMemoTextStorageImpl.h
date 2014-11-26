#ifndef AMEMOTEXTSTORAGEIMPL_H
#define AMEMOTEXTSTORAGEIMPL_H

#include "AMemoTextMatrix.h"
#include <map>

/*
 * �༭����ı����������ṩ�ı��Ĵ洢���顢�С��ַ��Ĳ�������ʱ��֧���в���
 * 
 */
class AUI_API AMemoTextStorageImpl : public AMemoTextStorage
{
	CLASS_INFO(MemoTextStorageImpl,MemoTextStorage);
public:
	AMemoTextStorageImpl();
	virtual ~AMemoTextStorageImpl();

	//=== �����ı����� ===
	virtual void SetSingleText(const AString& sText);
	virtual AString GetSingleText(const AString& sCR=_T("\r\n"));
	virtual void Clear();//��������ı�
	virtual ASize GetEditorSize();

	//=== �в��� =====
	virtual int GetLineCount();//�õ�������
	virtual int GetLineCharCount(int iLine);
	virtual AString GetLine(int iLine);//�õ�ָ��������
	virtual void AddLine(const AString& sText);//������
	virtual void SetLine(int iLine,const AString& sNewText);//���滻
	virtual void RemoveLine(int iLine);//ɾ����
	virtual void InsertLine(int iLine,const AString& sText);//������
	
	//=== �����ַ����� ===
	virtual void InsertChar(ACHAR ch,ACaretSeat seat);//�����ַ���ָ��λ��
	virtual ACHAR GetChar(ACaretSeat seat);//�õ�ָ��λ�ӵ��ַ�
	virtual void RemoveChar(ACaretSeat seat);//ɾ��ָ��λ�ӵ��ַ�

	//=== �ı������ ====
	virtual void InsertString(const AString& s,ACaretSeat seat);//�����ı��鵽ָ��λ��
	virtual AString GetString(ACaretSeat seatStart,ACaretSeat seatEnd);//��ȡָ��λ�ӷ�Χ���ı���
	virtual void RemoveString(ACaretSeat seatStart,ACaretSeat seatEnd);//ɾ��ָ����Χ���ı���
	virtual void ReplaceString(ACaretSeat seatStart,ACaretSeat seatEnd,const AString& s);//��ָ���ı����滻ָ����Χ���ı��飻����ʵ�ֵ����ַ����滻����

	//=== �в��� ===
	virtual void InsertColBlock(AStringArray& s,ACaretSeat seatFrom);//�����п�
	virtual void GetColBlock(AStringArray& s,ACaretSeat seatStart,ACaretSeat seatEnd);//�õ��п�
	virtual void RemoveColBlock(ACaretSeat seatStart,ACaretSeat seatEnd);//ɾ���п�
	virtual void ReplaceColBlock(AStringArray& s,ACaretSeat seatStart,ACaretSeat seatEnd);//�п��滻

	//=== ������Ϣ���� ===
	virtual int GetMeasure(ACaretSeat seat);//�õ�ָ��λ�ӵĶ���ֵ����ȣ����������ʼλ�ã�
	virtual void SetMeasure(ACaretSeat seat,int v);//����ָ��λ�ӵĶ���ֵ
	virtual int GetLineHeight(int iRow);//�õ��и�
	virtual int GetLineWidth(int iRow);//�õ��п�
	virtual int GetLineTop(int iRow);//�õ��еĶ���
	virtual void SetLineHeight(int iRow,int iHeight);//�����и�
	virtual int GetRowSpace();//�õ��м��
	virtual void SetRowSpace(int v);//�����м��

	//=== ��ɫ��Ϣ���� ===
	virtual int GetColoration(ACaretSeat seat);//�õ�ָ��λ�õ���ɫ����
	virtual void SetColoration(ACaretSeat seat,int iIndex);//����ָ��λ�õ���ɫ����
	virtual int RegColorationItem(AMemoColorationItem* pItem,const AString& sKey);//ע��һ����ɫ��Ϣ����������Ӧ���±�
	virtual void UnregColorationItem(const AString& sKey);//ͨ��Key����ע��һ����ɫ��Ϣ
	virtual void UnregColorationItem(int iIndex);//ͨ�������±�����ע��һ����ɫ��Ϣ
	virtual int GetColorationIndex(const AString& sKey);//����Key��ȡ�±�
	virtual AMemoColorationItem* GetColorationByIndex(int index);

	//=== ����
	virtual void SetTabWidth(int v);
	virtual void SetDefaultFont(AFont f);

	//=== ��λ
	virtual ACaretSeat SeatByPos(APoint pt);

	
protected:
	AMemoTextMatrix		m_Matrix;
	int			m_iRowSpace;
	AObjectArray		m_aColoration;
	AStringMap		m_aColorationMap;
	int			m_iTabWidth;//TAB��ȣ�Ӱ�쵽������
	ASize			m_szEditor;
	int			m_iRightSpace;//�ұ�����
	int			m_iBottomSpace;//�±�����
	//=== ���ڶ�����ȱʡ����
	AFont	m_DefaultFont;


	//�����ı��ĸı���¸�ʽ���Ͷ�����Ϣ
	virtual void DoMeasure(ATextEvent* pEvent);
	virtual void DoTint(ATextEvent* pEvent);

	//��������
	virtual void _doMeasure(int rs,int cs,int re,int ce);
	virtual void _doTint(int rs,int cs,int re,int ce,TextAction ta=taInsert);
	virtual void _onchange();

	virtual void _measureBlock(ACanvas* cs,ACaretSeat seat,int iCount);//�����ڿ����
};

#endif//AMEMOTEXTSTORAGEIMPL_H