#ifndef AMEMOTEXTSTORAGE_H
#define AMEMOTEXTSTORAGE_H

//��ɫ��Ϣ
class AUI_API AMemoColorationItem : public AObject
{
	CLASS_INFO(MemoColorationItem,Object);
public:
	AMemoColorationItem():base_class(){}
	virtual ~AMemoColorationItem(){}

	AFont		m_Font;//����
	AColor		m_BackColor;//����ɫ
};

/*
 * �༭����ı����������ṩ�ı��Ĵ洢���顢�С��ַ��Ĳ�����ͬʱ�ṩ��ʽ����Ϣ���ַ�������Ϣ�Ĵ洢��
 * TextStorage��ʵ�ֱ��뱣�ϸ�ʽ���Ͷ�����Ϣ���ı���Ϣ��ͬ����
 */
class AUI_API AMemoTextStorage : public AObject
{
	CLASS_INFO(MemoTextStorage,Object);
public:
	//=== �����ı����� ===
	virtual void SetSingleText(const AString& sText)=0;
	virtual AString GetSingleText(const AString& sCR=_T("\r\n"))=0;
	virtual void Clear()=0;//��������ı�
	virtual ASize GetEditorSize()=0;

	//=== �в��� =====
	virtual int GetLineCount()=0;//�õ�������
	virtual int GetLineCharCount(int iLine)=0;//�õ������ַ�����
	virtual AString GetLine(int iLine)=0;//�õ�ָ��������
	virtual void AddLine(const AString& sText)=0;//������
	virtual void SetLine(int iLine,const AString& sNewText)=0;//���滻
	virtual void RemoveLine(int iLine)=0;//ɾ����
	virtual void InsertLine(int iLine,const AString& sText)=0;//������
	
	//=== �����ַ����� ===
	virtual void InsertChar(ACHAR ch,ACaretSeat seat)=0;//�����ַ���ָ��λ��
	virtual ACHAR GetChar(ACaretSeat seat)=0;//�õ�ָ��λ�ӵ��ַ�
	virtual void RemoveChar(ACaretSeat seat)=0;//ɾ��ָ��λ�ӵ��ַ�

	//=== �ı������ ====
	virtual void InsertString(const AString& s,ACaretSeat seat)=0;//�����ı��鵽ָ��λ��
	virtual AString GetString(ACaretSeat seatStart,ACaretSeat seatEnd)=0;//��ȡָ��λ�ӷ�Χ���ı���
	virtual void RemoveString(ACaretSeat seatStart,ACaretSeat seatEnd)=0;//ɾ��ָ����Χ���ı���
	virtual void ReplaceString(ACaretSeat seatStart,ACaretSeat seatEnd,const AString& s)=0;//��ָ���ı����滻ָ����Χ���ı��飻����ʵ�ֵ����ַ����滻����

	//=== �в��� ===
	virtual void InsertColBlock(AStringArray& s,ACaretSeat seatFrom)=0;//�����п�
	virtual void GetColBlock(AStringArray& s,ACaretSeat seatStart,ACaretSeat seatEnd)=0;//�õ��п�
	virtual void RemoveColBlock(ACaretSeat seatStart,ACaretSeat seatEnd)=0;//ɾ���п�
	virtual void ReplaceColBlock(AStringArray& s,ACaretSeat seatStart,ACaretSeat seatEnd)=0;//�п��滻

	//=== ������Ϣ���� ===
	virtual int GetMeasure(ACaretSeat seat)=0;//�õ�ָ��λ�ӵĶ���ֵ����ȣ����������ʼλ�ã�
	virtual void SetMeasure(ACaretSeat seat,int v)=0;//����ָ��λ�ӵĶ���ֵ
	virtual int GetLineHeight(int iRow)=0;//�õ��и�
	virtual int GetLineWidth(int iRow)=0;//�õ��п�
	virtual void SetLineHeight(int iRow,int iHeight)=0;//�����и�
	virtual int GetLineTop(int iRow)=0;//�õ��еĶ���
	virtual int GetRowSpace()=0;//�õ��м��
	virtual void SetRowSpace(int v)=0;//�����м��

	//=== ��ɫ��Ϣ���� ===
	virtual int GetColoration(ACaretSeat seat)=0;//�õ�ָ��λ�õ���ɫ����
	virtual void SetColoration(ACaretSeat seat,int iIndex)=0;//����ָ��λ�õ���ɫ����
	virtual int RegColorationItem(AMemoColorationItem* pItem,const AString& sKey)=0;//ע��һ����ɫ��Ϣ����������Ӧ���±�
	virtual void UnregColorationItem(const AString& sKey)=0;//ͨ��Key����ע��һ����ɫ��Ϣ
	virtual void UnregColorationItem(int iIndex)=0;//ͨ�������±�����ע��һ����ɫ��Ϣ
	virtual int GetColorationIndex(const AString& sKey)=0;//����Key��ȡ�±�
	virtual AMemoColorationItem* GetColorationByIndex(int index)=0;

	//=== ����
	virtual void SetTabWidth(int v)=0;
	virtual void SetDefaultFont(AFont f)=0;

	//=== ��λ
	virtual ACaretSeat SeatByPos(APoint pt)=0;

	//=== ͨ����Ӧ�����¼����޸Ļ���չ�༭��Ĺ��� ===
	//     �¼���������ATextEvent����  
	AEventHandler		OnMeasure;//��Ҫ����
	AEventHandler		OnTint;//��Ҫ��ɫ
	AEventHandler		OnChange;//�ı��б仯
};

#endif//AMEMOTEXTSTORAGE_H