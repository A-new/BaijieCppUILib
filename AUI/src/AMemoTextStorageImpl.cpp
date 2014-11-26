#include "stdafx.h"
#include "AMemoTextStorageImpl.h"

AMemoTextStorageImpl::AMemoTextStorageImpl():base_class()
{
	m_iTabWidth = 4;
	m_iRightSpace = 1;
	m_iBottomSpace = 1;
}

AMemoTextStorageImpl::~AMemoTextStorageImpl()
{

}

//=== �����ı����� ===
void AMemoTextStorageImpl::SetSingleText(const AString& sText)
{
	m_Matrix.SetText(sText);

	int iLineCount = m_Matrix.GetLineCount();
	int c=0;
	if( iLineCount > 0 ) c = m_Matrix.GetLineCharCount(iLineCount-1);

	_doTint(0,0,iLineCount-1,c);
	_doMeasure(0,0,iLineCount-1,c);
	_onchange();

}
AString AMemoTextStorageImpl::GetSingleText(const AString& sCR/*=_T("\r\n")*/)
{
	return m_Matrix.GetText(sCR);
}
void AMemoTextStorageImpl::Clear()//��������ı�
{
	m_Matrix.Clear();
	_onchange();
}

ASize AMemoTextStorageImpl::GetEditorSize()
{
	return m_Matrix.GetEditorSize();
}


//=== �в��� =====
int AMemoTextStorageImpl::GetLineCount()//�õ�������
{
	return m_Matrix.GetLineCount();
}
int AMemoTextStorageImpl::GetLineCharCount(int iLine)//�õ�������
{
	return m_Matrix.GetLineCharCount(iLine);
}
AString AMemoTextStorageImpl::GetLine(int iLine)//�õ�ָ��������
{
	return m_Matrix.GetLine(iLine);
}
void AMemoTextStorageImpl::AddLine(const AString& sText)//������
{
	m_Matrix.AddLine(sText);
	int iLineCount = m_Matrix.GetLineCount();
	int c = m_Matrix.GetLineCharCount(iLineCount-1);
	_doTint(iLineCount-1,0,iLineCount-1,c-1);
	_doMeasure(iLineCount-1,0,iLineCount-1,c-1);
	_onchange();
}
void AMemoTextStorageImpl::SetLine(int iLine,const AString& sNewText)//���滻
{
	m_Matrix.RemoveLine(iLine);
	m_Matrix.InsertLine(iLine,sNewText);
	int c = m_Matrix.GetLineCharCount(iLine);
	_doTint(iLine,0,iLine,c-1);
	_doMeasure(iLine,0,iLine,c-1);
	_onchange();
}
void AMemoTextStorageImpl::RemoveLine(int iLine)//ɾ����
{
	m_Matrix.RemoveLine(iLine);
	if( iLine < m_Matrix.GetLineCount()-1)
	{
		_doTint(iLine,0,iLine,m_Matrix.GetLineCharCount(iLine)-1,taRemove);
	}
	_onchange();
}
void AMemoTextStorageImpl::InsertLine(int iLine,const AString& sText)//������
{
	m_Matrix.InsertLine(iLine,sText);
	int c = m_Matrix.GetLineCharCount(iLine);
	if( c > 0 ) c--;
	_doTint(iLine,0,iLine,c,taInsert);
	_doMeasure(iLine,0,iLine,c);
	_onchange();
}

//=== �����ַ����� ===
void AMemoTextStorageImpl::InsertChar(ACHAR ch,ACaretSeat seat)//�����ַ���ָ��λ��
{
	m_Matrix.InsertChar(seat,ch);
	int r = seat.iRow;
	int c = seat.iCol;
	int ic = m_Matrix.GetLineCharCount(r);
	_doTint(r,c,r,ic-1,taInsert);
	_doMeasure(r,0,r,ic-1);
	_onchange();
}

ACHAR AMemoTextStorageImpl::GetChar(ACaretSeat seat)//�õ�ָ��λ�ӵ��ַ�
{
	return m_Matrix.GetChar(seat);
}
void AMemoTextStorageImpl::RemoveChar(ACaretSeat seat)//ɾ��ָ��λ�ӵ��ַ�
{
	m_Matrix.RemoveChar(seat);
	int r = seat.iRow;
	int c = seat.iCol;
	int ic = m_Matrix.GetLineCharCount(r);
	_doTint(r,c,r,ic-1,taRemove);
	_doMeasure(r,c,r,ic-1);
	_onchange();
}

//=== �ı������ ====
void AMemoTextStorageImpl::InsertString(const AString& s,ACaretSeat seat)//�����ı��鵽ָ��λ��
{
	AStringArray sa;
	m_Matrix.SplitString(s,sa);
	int iCount = sa.GetCount();
	if( iCount < 1 ) return;
	int r = seat.iRow;
	int c = seat.iCol;
	if( iCount == 1 ) 
	{
		m_Matrix.InsertChars(seat,s);
		int ic = m_Matrix.GetLineCharCount(r);
		_doTint(r,c,r,ic-1,taInsert);
		_doMeasure(r,c,r,ic-1);
	}
	else
	{
		if( seat.iRow >= m_Matrix.GetLineCount() )
			m_Matrix.AddLine(_T(""));
		AString sLine = m_Matrix.GetLine( seat.iRow );
		m_Matrix.RemoveChars(seat,sLine.Length()-seat.iCol);
		m_Matrix.InsertChars(seat,sa[0]);

		sLine = sa[iCount-1]+sLine.Right(sLine.Length()-seat.iCol);
		m_Matrix.InsertLine(seat.iRow+1,sLine);
		for(int i=1;i<iCount-1;i++)
		{
			m_Matrix.InsertLine(seat.iRow+i,sa[i]);
		}

		int ic = m_Matrix.GetLineCharCount(r+iCount-1);
		_doTint(r,c,r+iCount-1,ic-1,taInsert);
		_doMeasure(r,c,r+iCount-1,ic-1);
	}
	_onchange();
}
AString AMemoTextStorageImpl::GetString(ACaretSeat seatStart,ACaretSeat seatEnd)//��ȡָ��λ�ӷ�Χ���ı���
{
	AStringArray sa;
	for(int i=seatStart.iRow;i<=seatEnd.iRow;i++)
	{
		AString s;
		AString sLine = m_Matrix.GetLine(i);
		if( i == seatStart.iRow && i == seatEnd.iRow )
		{
			s = sLine;
			s = s.Mid(seatStart.iCol,seatEnd.iCol - seatStart.iCol + 1 );
			return s;//����
		}
		if( i == seatStart.iRow )
		{
			s = sLine;
			s = s.Right(s.Length()-seatStart.iCol);
			sa.Add( s );
		}
		else if( i == seatEnd.iRow )
		{
			s = sLine;
			s = s.Left(seatEnd.iCol+1);
			sa.Add( s );
		}
		else
			sa.Add( sLine );
	}
	return sa.ToString(_T("\r\n"));
}

void AMemoTextStorageImpl::RemoveString(ACaretSeat seatStart,ACaretSeat seatEnd)//ɾ��ָ����Χ���ı���
{
	if( seatStart.iRow == seatEnd.iRow )
	{
		m_Matrix.RemoveChars(seatStart,seatEnd.iCol-seatStart.iCol+1);
		int ic = m_Matrix.GetLineCharCount(seatStart.iRow);
		_doTint(seatStart.iRow,seatStart.iCol,seatStart.iRow,ic-1,taRemove);
		_doMeasure(seatStart.iRow,seatStart.iCol,seatStart.iRow,ic-1);
	}
	else
	{
		ACaretSeat seat;
		int iCount;
		seat.iRow = seatStart.iRow;
		seat.iCol = seatStart.iCol;
		iCount = m_Matrix.GetLineCharCount(seat.iRow) - seatStart.iCol+1;
		m_Matrix.RemoveChars(seat,iCount);
		seat.iRow = seatEnd.iRow;
		seat.iCol = 0;
		iCount = seatEnd.iCol+1;
		m_Matrix.RemoveChars(seat,iCount);
		for(int i=seatStart.iRow+1;i<seatEnd.iRow;i++)
		{
			m_Matrix.RemoveLine(seatStart.iRow+1);
		}
		int r = seatStart.iRow;
		int r2 = r + 1;
		if( r == m_Matrix.GetLineCount()-1 ) r2 = r;
		int ic = m_Matrix.GetLineCharCount(r2);
		_doTint(r,0,r2,ic-1,taRemove);
		_doMeasure(r,0,r2,ic-1);
	}
	_onchange();
}
void AMemoTextStorageImpl::ReplaceString(ACaretSeat seatStart,ACaretSeat seatEnd,const AString& s)//��ָ���ı����滻ָ����Χ���ı��飻����ʵ�ֵ����ַ����滻����
{
	RemoveString(seatStart,seatEnd);
	InsertString(s,seatStart);
}

//=== �в��� ===
void AMemoTextStorageImpl::InsertColBlock(AStringArray& sa,ACaretSeat seatFrom)//�����п�
{
	int iLineCount = m_Matrix.GetLineCount();
	int iCount = sa.GetCount();
	if( seatFrom.iRow+iCount-1 > iLineCount )
	{
		for(int i=0;i<seatFrom.iRow+iCount-1 - iLineCount;i++)
			m_Matrix.AddLine(_T(""));
	}
	for(int i=0;i<iCount;i++)
	{
		ACaretSeat seat;
		seat.iRow = seatFrom.iRow+i;
		seat.iCol = seatFrom.iCol;
		m_Matrix.InsertChars(seat,sa[i]);

		int ic = m_Matrix.GetLineCharCount(seat.iRow);
		int r = seat.iRow;
		_doTint(r,0,r,ic-1,taInsert);
		_doMeasure(r,0,r,ic-1);
	}
	_onchange();
}
void AMemoTextStorageImpl::GetColBlock(AStringArray& sa,ACaretSeat seatStart,ACaretSeat seatEnd)//�õ��п�
{
	int iCount = seatEnd.iCol-seatStart.iCol+1;
	for(int i=seatStart.iRow;i<=seatEnd.iRow;i++)
	{
		ACaretSeat seat;
		seat.iRow = i;
		seat.iCol = seatStart.iCol;
		sa.Add( m_Matrix.GetChars(seat,iCount));
	}
}
void AMemoTextStorageImpl::RemoveColBlock(ACaretSeat seatStart,ACaretSeat seatEnd)//ɾ���п�
{
	int iCount = seatEnd.iCol-seatStart.iCol+1;
	for(int i=seatStart.iRow;i<=seatEnd.iRow;i++)
	{
		ACaretSeat seat;
		seat.iRow = i;
		seat.iCol = seatStart.iCol;
		m_Matrix.RemoveChars(seat,iCount);

		int r = i;
		int ic = m_Matrix.GetLineCharCount(r);

		_doTint(r,0,r,ic-1,taRemove);
		_doMeasure(r,0,r,ic-1);
	}
	_onchange();
}
void AMemoTextStorageImpl::ReplaceColBlock(AStringArray& sa,ACaretSeat seatStart,ACaretSeat seatEnd)//�п��滻
{
	RemoveColBlock(seatStart,seatEnd);
	InsertColBlock(sa,seatStart);
	_onchange();
}

//=== ������Ϣ���� ===
int AMemoTextStorageImpl::GetMeasure(ACaretSeat seat)//�õ�ָ��λ�ӵĶ���ֵ����ȣ����������ʼλ�ã�
{
	return m_Matrix.GetMeasure(seat);
}
void AMemoTextStorageImpl::SetMeasure(ACaretSeat seat,int v)//����ָ��λ�ӵĶ���ֵ
{
	m_Matrix.SetMeasure(seat,v);
}
int AMemoTextStorageImpl::GetLineHeight(int iRow)//�õ��и�
{
	return m_Matrix.GetLineHeight(iRow);
}
int AMemoTextStorageImpl::GetLineTop(int iRow)//�õ��еĶ���
{
	return m_Matrix.GetLineTop(iRow);
}

int AMemoTextStorageImpl::GetLineWidth(int iRow)//�õ��п�
{
	return m_Matrix.GetLineWidth(iRow);
}
void AMemoTextStorageImpl::SetLineHeight(int iRow,int iHeight)//�����и�
{
	m_Matrix.SetLineHeight(iRow,iHeight);
}
int AMemoTextStorageImpl::GetRowSpace()//�õ��м��
{
	return m_Matrix.GetRowSpace();
}
void AMemoTextStorageImpl::SetRowSpace(int v)//�����м��
{
	m_Matrix.SetRowSpace(v);
}

//=== ��ɫ��Ϣ���� ===
int AMemoTextStorageImpl::GetColoration(ACaretSeat seat)//�õ�ָ��λ�õ���ɫ����
{
	return m_Matrix.GetColoration(seat);
}
void AMemoTextStorageImpl::SetColoration(ACaretSeat seat,int iIndex)//����ָ��λ�õ���ɫ����
{
	m_Matrix.Tint(seat,iIndex);
}
int AMemoTextStorageImpl::RegColorationItem(AMemoColorationItem* pItem,const AString& sKey)//ע��һ����ɫ��Ϣ����������Ӧ���±�
{
	if( m_aColorationMap.IsExist(sKey) )
	{
		AMemoColorationItem* p = (AMemoColorationItem *)m_aColorationMap.GetItem(sKey);
		return m_aColoration.IndexOf(p);
	}
	m_aColoration.Add( pItem );
	m_aColorationMap.SetItem(sKey,pItem);
	return m_aColoration.GetCount()-1;
	
}
void AMemoTextStorageImpl::UnregColorationItem(const AString& sKey)//ͨ��Key����ע��һ����ɫ��Ϣ
{
	if( m_aColorationMap.IsExist(sKey) )
	{
		AMemoColorationItem* p = (AMemoColorationItem *)m_aColorationMap.GetItem(sKey);
		m_aColoration.Delete( m_aColoration.IndexOf(p) );
		m_aColorationMap.RemoveItem(sKey);
	}
}
void AMemoTextStorageImpl::UnregColorationItem(int iIndex)//ͨ�������±�����ע��һ����ɫ��Ϣ
{
	AMemoColorationItem* p = (AMemoColorationItem *)m_aColoration[iIndex];
	m_aColoration.Delete(iIndex);
	AStringMapEnumerator em(&m_aColorationMap);
	while( em.Next() )
	{
		if( p == (AMemoColorationItem *)em.Cur() )
		{
			m_aColorationMap.RemoveItem(em.Index());
			break;
		}
	}
}
int AMemoTextStorageImpl::GetColorationIndex(const AString& sKey)//����Key��ȡ�±�
{
	if( m_aColorationMap.IsExist(sKey) )
	{
		AMemoColorationItem* p = (AMemoColorationItem *)m_aColorationMap.GetItem(sKey);
		return m_aColoration.IndexOf(p);
	}
	return -1;
}

AMemoColorationItem* AMemoTextStorageImpl::GetColorationByIndex(int index)
{
	return (AMemoColorationItem*)m_aColoration[index];
}

void AMemoTextStorageImpl::_measureBlock(ACanvas* cs,ACaretSeat seat,int iCount)
{
	if( seat.iRow >= m_Matrix.GetLineCount() ) return;//�����߽�

	AString s;
	s = m_Matrix.GetLine(seat.iRow);
	AString sTab;
	for(int j=0;j<m_iTabWidth;j++) sTab += _T(" ");

	int iLen = s.Length();
	int iSize = 0;
	for(int i=0;i<iLen;i++)
	{
		int cx=0;//��������ĵ�ǰ�ַ����

		ACHAR ch = s[i];
		AString s2;
		if( ch == '\t' ) s2 = sTab;
		else s2 = AString(ch);

		int iColorIndex = m_Matrix.GetColoration(ACaretSeat(seat.iRow,i));
		AMemoColorationItem* pItem = NULL;
		AFont* pFont = NULL;
		if( iColorIndex == -1 ) pFont = &m_DefaultFont;
		else
		{
			pItem = GetColorationByIndex(iColorIndex);
			if( pItem ) pFont = &(pItem->m_Font);
			else pFont = &m_DefaultFont;
		}
		cx = cs->Use(pFont)->MeasureText(s2).cx;
		iSize += cx;
		if( i >= seat.iCol )
			m_Matrix.SetMeasure(ACaretSeat(seat.iRow,i),iSize);
	}
	int w = 0;
	int iChars = m_Matrix.GetLineCharCount(seat.iRow);
	if( iChars > 0 ) w = GetMeasure( ACaretSeat(seat.iRow,iChars-1) );
	w += m_iRightSpace;
	if( w > m_szEditor.cx ) m_szEditor.cx = w;
}

void AMemoTextStorageImpl::_doMeasure(int rs,int cs,int re,int ce)
{
	if( cs < 0 ) cs = 0;
	if( ce < 0 ) ce = 0;
	if( rs == rs && ce < cs ) ce = cs;
	int iLineCount = m_Matrix.GetLineCount();
	if( rs >= iLineCount ) return;//�����߽�
	if( re >= iLineCount ) re = iLineCount -1;

	ATextEvent te;
	te.seatStart = ACaretSeat(rs,cs);
	te.seatEnd = ACaretSeat(re,ce);
	DoMeasure(&te);
}
void AMemoTextStorageImpl::_doTint(int rs,int cs,int re,int ce,TextAction ta)
{
	if( cs < 0 ) cs = 0;
	if( ce < 0 ) ce = 0;
	if( rs == rs && ce < cs ) ce = cs;
	int iLineCount = m_Matrix.GetLineCount();
	if( rs >= iLineCount ) return;//�����߽�
	if( re >= iLineCount ) re = iLineCount -1;

	ATextEvent te;
	te.seatStart = ACaretSeat(rs,cs);
	te.seatEnd = ACaretSeat(re,ce);
	te.action = ta;
	DoTint(&te);
}
void AMemoTextStorageImpl::DoMeasure(ATextEvent* pEvent)
{
	if( OnMeasure.IsValid() )
	{
		OnMeasure.Call(this,pEvent);
	}
	else
	{
		//ȱʡ����ʵ��
		ACanvas* cs = AApplication::Get()->GetMainForm()->GetUICore()->GetCanvas();
		if( cs == NULL ) return;
		ACaretSeat ss = pEvent->seatStart;
		ACaretSeat se = pEvent->seatEnd;

		if( ss.iRow == se.iRow ) _measureBlock(cs,ss,se.iCol-ss.iCol+1);
		else
		{
			//�ȴ����һ��
			_measureBlock(cs,ss,m_Matrix.GetLineCharCount(ss.iRow)-ss.iCol);
			//�ٴ������һ��
			ACaretSeat csLast;
			csLast.iRow = se.iRow;
			csLast.iCol = 0;
			_measureBlock(cs,csLast,m_Matrix.GetLineCharCount(csLast.iRow));
			//������м���
			for(int i=ss.iRow+1;i<se.iRow;i++)
			{
				ACaretSeat seat;
				seat.iRow = i;
				seat.iCol = 0;
				_measureBlock(cs,seat,m_Matrix.GetLineCharCount(i));
			}
		}
	}

	//�����иߺ��п�
	for(int i = pEvent->seatStart.iRow;i<=pEvent->seatEnd.iRow;i++)
	{
		int iLineHeight = m_Matrix.GetLineHeight(i);

		//������ɫ�����µ��и�
		int iHeight = 0;
		int iCount = m_Matrix.GetLineCharCount(i);
		for(int j =0;j<iCount;j++)
		{
			ACaretSeat curSeat;
			curSeat.iRow = i;
			curSeat.iCol = j;
			int index = m_Matrix.GetColoration(curSeat);
			int v=0;
			if( index != -1 )
			{
				AMemoColorationItem* pItem = (AMemoColorationItem *) m_aColoration[index];
				v = pItem->m_Font.GetSize();
			}
			if( iHeight < v ) iHeight = v;
		}
		if( iHeight == 0 ) 
			iHeight = m_DefaultFont.GetSize();

		if( iHeight != iLineHeight ) 
		{
			m_Matrix.SetLineHeight(i,iHeight);
		}
		m_Matrix.UpdateLineWidth(i);
	}
}
void AMemoTextStorageImpl::DoTint(ATextEvent* pEvent)
{
	if( OnTint.IsValid() )
	{//�Զ�����ɫ
		OnTint.Call(this,pEvent);
	}
	else
	{//ȱʡ��ɫ
		//ȱʡ�ǲ���ɫ
		;//do nothing
	}
	
}

void AMemoTextStorageImpl::SetDefaultFont(AFont f)
{
	m_DefaultFont = f;
}

void AMemoTextStorageImpl::SetTabWidth(int v)
{
	m_iTabWidth = v;
	int iCount = m_Matrix.GetLineCount();
	for(int i=0;i<iCount;i++)
	{
		int iChars = m_Matrix.GetLineCharCount(i);
		if( iChars > 0 )
		{
			ATextEvent te;
			te.seatStart = ACaretSeat(i,0);
			te.seatEnd = ACaretSeat(i,iChars-1);
			DoMeasure(&te);
		}
	}
}

ACaretSeat AMemoTextStorageImpl::SeatByPos(APoint pt)
{
	return m_Matrix.SeatByPos(pt);
}
void AMemoTextStorageImpl::_onchange()
{
	AEvent evt;
	OnChange.Call(this,&evt);
}