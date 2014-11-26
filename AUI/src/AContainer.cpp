#include "stdafx.h"
#include "AContainer.h"

//=============================== AContainer ==================================
AContainer::AContainer(AComponent* pOwner):
	base_class(pOwner),
	m_pMaximizedControl(NULL)
{
	m_iBorderWidth = 0;

	m_pHorzScrollBar = NULL;
	m_pVertScrollBar = NULL;
	m_bFirstLayout = true;


	m_bAutoHScrollBar = true;
	m_bAutoVScrollBar = true;

	//��ʼ������
	m_bHorzScrollBarShow = false;
	m_bVertScrollBarShow = false;
	m_ContentSize = ASize(0,0);
	m_rView = ARect(0,0,0,0);
}

AContainer::~AContainer()
{
	
}

void AContainer::_addWatch(AControl* p)
{
	if( p == NULL ) return;
	p->WatchDelete(this);
	AContainer* pBase = dynamic_cast<AContainer*>(p);
	if( pBase )
	{
		int i,iCount = pBase->GetChildControls()->GetCount();
		for(i=0;i<iCount;i++)
		{
			_addWatch(dynamic_cast<AControl*>(pBase->GetChildControls()->GetItem(i)));
		}
	}
}


void AContainer::Destroy()
{
	if( m_bDestroyed ) return;
	m_pUICore->WatchTo(this);
	RemoveAllChild();

	if( m_pHorzScrollBar ) 
	{
		m_pHorzScrollBar->Release();
		m_pHorzScrollBar = NULL;
	}
	if( m_pVertScrollBar ) 
	{
		m_pVertScrollBar->Release();
		m_pVertScrollBar=NULL;
	}
	base_class::Destroy();
}

void AContainer::RemoveAllChild()
{
// 	AObjectArray a;
// 	a.Assign( *(GetChildControls()) );
// 	int i,iCount = a.GetCount();
// 	for(i=0;i<iCount;i++)
// 	{
// 		AControl* p = dynamic_cast<AControl*>(a.GetItem(i));
// 		if( p )
// 			p->Destroy();
// 	}
// 	GetChildControls()->Clear();
	while( GetChildControls()->GetCount() )
	{
		AControl* p = dynamic_cast<AControl*>(GetChildControls()->GetItem(0));
		//OutputDebugString(AString().Format(_T("RemoveAllChild::Child:%s %p Destroyed:%d\r\n"),p->GetClass(),p,p->IsDestroyed() ? 1 : 0));
		p->Destroy();
		if( GetChildControls()->GetCount() > 0 && p == dynamic_cast<AControl*>(GetChildControls()->GetItem(0)) )
		{//�ж��Ƿ��Ѿ��Ƴ���������ڣ���ǿ���Ƴ���������ѭ��
			GetChildControls()->Delete(p);
		}
	}
}

AObjectArray* AContainer::GetChildControls()
{
	return &m_aChildren;
}

void AContainer::SetAutoHScrollBar(bool v)
{
	m_bAutoHScrollBar = v;
	if( v && m_pHorzScrollBar == NULL )
	{
		AHorzScrollBar* p = new AHorzScrollBar(this);
		p->SetHeight(AApplication::Get()->GetCurSkin()->m_ScrollBarWidth);
		SetHScrollBar(p);
	}
}
bool AContainer::GetAutoHScrollBar()
{
	return m_bAutoHScrollBar;
}
void AContainer::SetAutoVScrollBar(bool v)
{
	m_bAutoVScrollBar = v;
	if( v && m_pVertScrollBar == NULL )
	{
		AVertScrollBar* p = new AVertScrollBar(this);
		p->SetWidth(AApplication::Get()->GetCurSkin()->m_ScrollBarWidth);
		SetVScrollBar(p);
	}
}
bool AContainer::GetAutoVScrollBar()
{
	return m_bAutoVScrollBar;
}
static int ZOrderCompare(void* p1,void* p2)
{
	AControl* w1 = (AControl *)p1;
	AControl* w2 = (AControl *)p2;
	if( w1->GetZOrder() > w2->GetZOrder() ) return 1;
	if( w1->GetZOrder() < w2->GetZOrder() ) return -1;
	return 0;
}

void AContainer::SetHScrollBar(AScrollBar* p)
{
	if( m_pHorzScrollBar == p || m_pVertScrollBar == p ) return;

	if( m_pHorzScrollBar )
	{
		m_pHorzScrollBar->Destroy();
		m_pHorzScrollBar = NULL;
	}
	if( p == NULL || p->GetKind() != sbHorz ) return;

	//fix me later : Ϊʲô������ô����p->SetParent(this);//��ȷ�������ӿؼ�
	for(int i=0;i<GetChildControls()->GetCount();i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w == (AControl*)p )
		{
			m_pHorzScrollBar = p;
			p->AddRef();

			GetChildControls()->Delete( w ); 
			GetChildren()->Delete(w); 

			DoLayout();
			break;
		}
	}

}

void AContainer::SetVScrollBar(AScrollBar* p)
{
	if( m_pHorzScrollBar == p || m_pVertScrollBar == p ) 
		return;

	if( m_pVertScrollBar )
	{
		m_pVertScrollBar->Destroy();
		m_pVertScrollBar = NULL;
	}
	if( p == NULL || p->GetKind() != sbVert ) 
		return;

	//fix me later : Ϊʲô������ô����p->SetParent(this);//��ȷ�������ӿؼ�
	for(int i=0;i<GetChildControls()->GetCount();i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w == (AControl*)p )
		{
			m_pVertScrollBar = p;
			p->AddRef();

			GetChildControls()->Delete( w );
			GetChildren()->Delete(w);

			DoLayout();
			break;
		}
	}
}

AScrollBar* AContainer::GetHScrollBar()
{
	return m_pHorzScrollBar;
}

AScrollBar* AContainer::GetVScrollBar()
{
	return m_pVertScrollBar;
}

ARect AContainer::GetViewRect()
{
	ARect r = GetAbsPosition();
	ARect rx = m_rView;
	rx.Offset(r.left,r.top);
	return rx;
}
AControl* AContainer::FindControl(const AString& sName)
{
	AControl* pr = NULL;
	int i,iCount = GetChildControls()->GetCount();
	for(i=0;i<iCount;i++)
	{
		AControl* p = dynamic_cast<AControl*>(GetChildControls()->GetItem(i));
		if( p && p->GetName() == sName )
		{
			pr = p;
			break;
		}
	}
	if( pr == NULL )
	{
		for(i=0;i<iCount;i++)
		{
			AContainer* p = dynamic_cast<AContainer*>( GetChildControls()->GetItem(i) );
			if( p )
			{
				pr = p->FindControl(sName);
				if( pr ) break;
			}
		}
	}
	return pr;
}

void AContainer::SetPropFromNode(AMLBody* pNode)
{
	base_class::SetPropFromNode(pNode);
	if( pNode->HasProp(_T("sb")) )
	{
		AString s = pNode->GetProp(_T("sb"));
		if( s == _T("n") )
		{
			SetVScrollBar(NULL);
			SetHScrollBar(NULL);
		}
		else if( s == _T("a") || s == _T("hv") )
		{
			//do nothing : default
		}
		else if( s == _T("h") )
		{
			SetVScrollBar(NULL);
		}
		else if( s == _T("v"))
		{
			SetHScrollBar(NULL);
		}
	}
}
void AContainer::DoLayout()
{
	if( !m_pUICore->GetLayoutEnabled() ) return;
	_Layout(false);//m_bFirstLayout);
	//m_bFirstLayout = false;
	base_class::DoLayout();
}

void AContainer::_Layout(bool bInitLayout)
{
	int iBorderWidth = (int)m_iBorderWidth;
	ARect rPos = GetControlPosition();//
	int bp = iBorderWidth + m_iPadding;
	rPos.Deflate(bp,bp);

	m_pUICore->SetLayoutEnabled(false);
	int i;
	int iCount = GetChildControls()->GetCount();
	int iTop = 0;
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alTop )
		{
			w->SetLeft(0);
			w->SetTop(iTop);
			w->SetWidth(rPos.GetWidth());
			iTop += w->GetHeight();
		}
	}
	int iBottom = 0;
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alBottom )
		{
			iBottom += w->GetHeight();
			w->SetLeft(0);
			w->SetTop(rPos.bottom-iBottom);
			w->SetWidth(rPos.GetWidth());
		}
	}
	int iLeft = 0;
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alLeft )
		{
			w->SetLeft(iLeft);
			w->SetTop(iTop);
			w->SetHeight(rPos.GetHeight()-iTop-iBottom);
			iLeft += w->GetWidth();
		}
	}
	int iRight = 0;
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alRight )
		{
			iRight += w->GetWidth();
			w->SetLeft(rPos.GetWidth()-iRight);
			w->SetTop(iTop);
			w->SetHeight(rPos.GetHeight() -iTop-iBottom );

		}
	}
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alClient )
		{
			w->SetLeft(iLeft);
			w->SetTop(iTop);
			w->SetWidth(rPos.GetWidth()-iLeft-iRight);
			w->SetHeight(rPos.GetHeight()-iTop-iBottom);
		}
	}

	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( (eAlign)w->GetAlign() == alNone )
		{
			if( w->Anchors.m_bRight )
			{
				int dw = w->Anchors.m_iRightDelta;
				if( bInitLayout ) 
				{
					dw = rPos.GetWidth() - w->GetLeft()-w->GetWidth();
					w->Anchors.m_iRightDelta = dw;
				}
				if( w->Anchors.m_bLeft )
					w->SetWidth(rPos.GetWidth()-w->GetLeft()-dw);
				else
					w->SetLeft(rPos.GetWidth()-w->GetWidth()-dw);
			}
			if( w->Anchors.m_bBottom )
			{
				int dh = w->Anchors.m_iBottomDelta;
				if( bInitLayout )
				{
					dh = rPos.GetHeight() - w->GetTop() - w->GetHeight();
					w->Anchors.m_iBottomDelta = dh;
				}
				if( w->Anchors.m_bTop )
					w->SetHeight(rPos.GetHeight()-w->GetTop()-dh);
				else
					w->SetTop(rPos.GetHeight()-w->GetHeight()-dh);
			}
		}
	}
	m_pUICore->SetLayoutEnabled(true);

	//����ContentSize
	int cx=0,cy=0;
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false || w->GetFloatType() == ftFloat || (eAlign)w->GetAlign() != alNone ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		if( w->Anchors.m_bRight == false && (w->GetFloatType() == ftFloatNone || w->GetFloatType() == ftFloatY) )
		{
			if( cx < w->GetLeft()+w->GetWidth() ) cx = w->GetLeft()+w->GetWidth();
		}
		if( w->Anchors.m_bBottom == false && (w->GetFloatType() == ftFloatNone || w->GetFloatType() == ftFloatX))
		{
			if( cy < w->GetTop()+w->GetHeight() ) cy = w->GetTop()+w->GetHeight();
		}
	}
	m_ContentSize = ASize(cx,cy);

	m_szDelta = ASize(iLeft,iTop);
// 	if( iLeft > 0 || iTop > 0 )
// 	{
// 		DebugStr(AString().Format(_T("szDelta(%d,%d)"),iLeft,iTop));
// 	}

	//����rView
	m_rView = ARect(rPos.left+iLeft,rPos.top+iTop,rPos.right-iRight,rPos.bottom-iBottom);
	//����������Ƿ���ʾ
	IsScrollBarShow(m_bHorzScrollBarShow,m_bVertScrollBarShow);

	if( m_bHorzScrollBarShow && m_pHorzScrollBar != NULL )
	{
		int vDelta = 0;
		if( m_bVertScrollBarShow && m_pVertScrollBar ) vDelta = m_pVertScrollBar->GetWidth();

		//����λ��
		m_pHorzScrollBar->SetLeft( iLeft );
		m_pHorzScrollBar->SetTop(m_rView.top +m_rView.GetHeight()- m_pHorzScrollBar->GetHeight());
		m_pHorzScrollBar->SetWidth(m_rView.GetWidth() - vDelta);
		m_pHorzScrollBar->SetRange(m_ContentSize.cx - (m_rView.GetWidth() - vDelta));
	}
	if( m_bVertScrollBarShow && m_pVertScrollBar != NULL )
	{
		int hDelta = 0;
		if( m_bHorzScrollBarShow && m_pHorzScrollBar ) hDelta = m_pHorzScrollBar->GetHeight();

		//����λ��
		m_pVertScrollBar->SetLeft(m_rView.right -m_pVertScrollBar->GetWidth());
		m_pVertScrollBar->SetTop(m_rView.top-rPos.top);
		m_pVertScrollBar->SetHeight(m_rView.GetHeight() - hDelta);
		m_pVertScrollBar->SetRange(m_ContentSize.cy - (m_rView.GetHeight() - hDelta));
	}
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		w->DoLayout();
	}
	//
	_updateChildrenAbsPos();
}

void AContainer::_updateChildrenAbsPos()
{
	int i;
	int iCount = GetChildControls()->GetCount();
	ARect rb = GetAbsPosition();
	int dp = m_iBorderWidth+m_iPadding;
	rb.Offset(dp,dp);
	

	//����ÿ���ӿؼ��ľ���λ��
	for(i=0;i<iCount;i++)
	{
		AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
		if( w->GetVisible() == false ) continue;
		if( w->GetDesignMode() == false && dynamic_cast<AInvisibleControl*>(w) != NULL ) continue;

		ARect r = w->GetControlScrollPosition();
		r.Offset(rb.left,rb.top);
		if( w->GetAlign() == alNone ) r.Offset(m_szDelta.cx,m_szDelta.cy);
		w->m_rAbsPos = r;
		//DebugStr(AString().Format(_T("SetAbsPos cls:%s r(l:%d,t:%d,w:%d,h:%d)"),w->GetClass(),r.left,r.top,r.GetWidth(),r.GetHeight()));
		AContainer* c = dynamic_cast<AContainer*>(w);
		if( c ) c->_updateChildrenAbsPos();
	}
	if( m_pHorzScrollBar )
	{
		ARect r = m_pHorzScrollBar->GetControlPosition();
		r.Offset(rb.left,rb.top);
		m_pHorzScrollBar->m_rAbsPos = r;
	}
	if( m_pVertScrollBar )
	{
		ARect r = m_pVertScrollBar->GetControlPosition();
		r.Offset(rb.left,rb.top);
		m_pVertScrollBar->m_rAbsPos = r;
	}
}
void AContainer::SetWidth(int v)
{
	base_class::SetWidth(v);
	Refresh();
}

void AContainer::SetHeight(int v)
{
	base_class::SetHeight(v);
	Refresh();
}
void AContainer::IsScrollBarShow(bool& bHorz,bool& bVert)
{
	//�������޷Ǿ����ֿ����ԣ�
	//1:ȫ����ʾ
	//2:ֻ��ʾˮƽ��
	//3:ֻ��ʾ��ֱ��
	//4:һ��������ʾ
	//�����㷨���ӣ�Ϊ�������������̽���㷨���ų��㷨

	//--- �ж��Ƿ�ȫ������ʾ
	if(	(GetAutoHScrollBar() == false || m_ContentSize.cx > m_rView.GetWidth() - ( m_pVertScrollBar ? (int)m_pVertScrollBar->GetWidth() : 0) ) &&
		m_pHorzScrollBar != NULL &&
		m_pVertScrollBar != NULL &&
		(GetAutoVScrollBar() == false || m_ContentSize.cy > m_rView.GetHeight() - (m_pHorzScrollBar ? (int)m_pHorzScrollBar->GetHeight() : 0 ) )
	)
	{
		bHorz = true;
		bVert = true;
		return;
	}
	//--- �ж��Ƿ���ʾ��ֱ������
	if( m_pVertScrollBar != NULL && ( GetAutoVScrollBar() == false || m_ContentSize.cy > m_rView.GetHeight() ) )
	{
		bVert = true;
		bHorz = false;
		return;
	}
	//--- �ж��Ƿ���ʾˮƽ������
	if( m_pHorzScrollBar != NULL && (GetAutoHScrollBar() == false || m_ContentSize.cx > m_rView.GetWidth() ) )
	{
		bVert = false;
		bHorz = true;
		return;
	}
	bVert = false;
	bHorz = false;
}

AControl* AContainer::_HitTest(int X,int Y)
{
	ARect rs = GetAbsPosition();
	if( rs.PtInRect(APoint(X,Y)) )
	{
		int bp = m_iBorderWidth + m_iPadding;
		//X -= (rs.left+bp);
		//Y -= (rs.top+bp);

		int i;
		//�����жϹ�����
		if( m_pHorzScrollBar != NULL && m_pHorzScrollBar->GetVisible() )
		{
			AControl* hit = m_pHorzScrollBar->_HitTest(X,Y);
			if( hit ) 
				return hit;
		}
		if( m_pVertScrollBar != NULL && m_pVertScrollBar->GetVisible() )
		{
			AControl* hit = m_pVertScrollBar->_HitTest(X,Y);
			if( hit ) 
				return hit;
		}

		//���жϴ���Float״̬�Ŀؼ�
		AArray aFloatHited;
		for(i=GetChildControls()->GetCount()-1;i >= 0 ;i--)
		{
			AControl* w = dynamic_cast<AControl*>( GetChildControls()->operator[](i) );
			if( w == NULL ) continue;
			if( dynamic_cast<AWinControlBase*>(w) ) continue;//�����о���Ĵ��ڿؼ��������Լ���UICore�Ͷ�����HitTest
			if( w->GetVisible() == false ) continue;
			if( w->GetFloatType() != ftFloatNone )
			{
				//�жϸ����ؼ�ʱ�Ȳ��ж������ӿؼ�
				if( w->_HitTest(X,Y) )
					aFloatHited.Add(w);
			}
		}
		if( aFloatHited.GetCount() > 0 )
		{
			//ZOrder�ж�
			aFloatHited.Sort(ZOrderCompare);

			AControl* w = (AControl *)aFloatHited[aFloatHited.GetCount() - 1];
			AControl* zHit = w->_HitTest(X,Y);
			if( zHit ) 
				return zHit;
			else
			{
				return w;
			}

		}
		
		//���жϷǸ����ؼ�
		for(i=GetChildControls()->GetCount()-1;i>=0;i--)
		{
			AControl* w = dynamic_cast<AControl*>(GetChildControls()->operator[](i));
			if( w == NULL ) continue;
			if( dynamic_cast<AWinControlBase*>(w) ) continue;//�����о���Ĵ��ڿؼ��������Լ���UICore�Ͷ�����HitTest
			if( w->GetVisible() == false ) continue;
			if( w->GetFloatType() != ftFloatNone ) continue;

			AControl* hit = w->_HitTest(X,Y);
			if( hit ) 
				return hit;
		}

		return this;
	}
	else return NULL;
}

void AContainer::DoPaint(ACanvas* cs,AEvent* pEvent)
{
	APaintEvent* evt = dynamic_cast<APaintEvent*>(pEvent);
	if( evt == NULL ) return;

	if( OnPaint.IsValid() )
	{
		OnPaint.Call(this,pEvent);
	}
	else
	{
		//ȱʡ����£�����������
	}
	if( m_pUICore->InDrawArea(GetAbsPosition()) ) //������ڻ�ͼ�����������ӿؼ�Ҳ���û���
		DoPaintChildren(pEvent);
}
void AContainer::DoPaintChildren(AEvent* pEvent)
{
	
	APaintEvent* evt = dynamic_cast<APaintEvent *>(pEvent);
	if( evt == NULL ) return;
	
	ARect r = GetAbsPosition();
	ACanvas* cs = m_pUICore->GetCanvas();
	int bp = m_iBorderWidth + m_iPadding;
	r.Deflate(bp,bp);
	//r.Deflate(m_iBorderWidth,m_iBorderWidth,m_iBorderWidth,m_iBorderWidth);
	AAutoClip autoClip(cs,r);

	int i;
	for( i=0;i<GetChildControls()->GetCount();i++)
	{
		AControl* pChildControl = dynamic_cast<AControl*>((AControl *)GetChildControls()->operator[](i));
		if( pChildControl == NULL ) continue;
		if( pChildControl->GetVisible() == false ) continue;
		if( pChildControl->GetFloatType() != ftFloatNone ) continue;//�Ȼ����Ǹ�����
		
		if( dynamic_cast<AInvisibleControl*>(pChildControl) != NULL && pChildControl->GetDesignMode() == false  ) continue;

		if( dynamic_cast<APopupContainer *>(pChildControl) ) continue;//�������ڿؼ������Լ�����
		if( m_pUICore->InDrawArea(pChildControl->GetAbsPosition()) ) 
		{
			AAutoClip cp(cs,pChildControl->GetAbsPosition());
			pChildControl->DoPaint(cs,pEvent);
		}
	}
	for( i=0;i<GetChildControls()->GetCount();i++)
	{
		AControl* pChildControl = dynamic_cast<AControl*>((AControl *)GetChildControls()->operator[](i));
		if( pChildControl == NULL ) continue;
		if( pChildControl->GetVisible() == false ) continue;
		if( pChildControl->GetFloatType() == ftFloatNone ) continue;//�ٻ��Ǹ�����
		
		if( dynamic_cast<AInvisibleControl*>(pChildControl) != NULL && pChildControl->GetDesignMode() == false ) continue;

		if( dynamic_cast<APopupContainer *>(pChildControl) ) continue;//�������ڿؼ������Լ�����
		if( m_pUICore->InDrawArea(pChildControl->GetAbsPosition()) )  
		{
			AAutoClip cp(cs,pChildControl->GetAbsPosition());
			pChildControl->DoPaint(cs,pEvent);
		}
	}
	if( m_bHorzScrollBarShow && m_pHorzScrollBar != NULL && m_pUICore->InDrawArea(m_pHorzScrollBar->GetAbsPosition()) ) 
	{
		AAutoClip cp(cs,m_pHorzScrollBar->GetAbsPosition());
		m_pHorzScrollBar->DoPaint(cs,pEvent);
	}
	if( m_bVertScrollBarShow && m_pVertScrollBar != NULL && m_pUICore->InDrawArea(m_pVertScrollBar->GetAbsPosition()) ) 
	{
		AAutoClip cp(cs,m_pVertScrollBar->GetAbsPosition());
		m_pVertScrollBar->DoPaint(cs,pEvent);
	}

	//���������ص�����
	if( m_bHorzScrollBarShow && m_bVertScrollBarShow )
	{
		ARect rOverlap;
		rOverlap.left = m_pHorzScrollBar->GetLeft() + m_pHorzScrollBar->GetWidth();
		rOverlap.top = m_pVertScrollBar->GetTop() + m_pVertScrollBar->GetHeight();
		rOverlap.right = rOverlap.left+m_pVertScrollBar->GetWidth();
		rOverlap.bottom = rOverlap.top + m_pHorzScrollBar->GetHeight();
		rOverlap.Offset(r.left,r.top);
		if( m_pUICore->InDrawArea(rOverlap) )
		{
			AAutoClip cp(cs,rOverlap);
			AApplication::Get()->GetCurSkin()->DrawScrollBarOverlap(cs,this,rOverlap);
		}
	}
}


AControl* AContainer::GetMaximizedControl()
{
	return m_pMaximizedControl;
}
void AContainer::SetMaximizedControl(AControl* p)
{
	m_pMaximizedControl = p;
}

void AContainer::DoLButtonDown(AEvent* pEvent)
{
	//

}

void AContainer::DoLButtonUp(AEvent* pEvent)
{
	//
}

void AContainer::DoMouseMove(AEvent* pEvent)
{
	AControl::DoMouseMove(pEvent);
}

void AContainer::DoMouseWheel(AEvent* pEvent)
{
	AMouseEvent* evt = dynamic_cast<AMouseEvent *>(pEvent);
	if( evt == NULL ) return;
	if( evt->m_KeyStates.Has(ksShift))
	{
		if( m_pHorzScrollBar != NULL && m_bHorzScrollBarShow )
			m_pHorzScrollBar->DoMouseWheel(pEvent);
	}
	else
	{
		if( m_pVertScrollBar != NULL && m_bVertScrollBarShow )
		{
			m_pVertScrollBar->DoMouseWheel(pEvent);
		}
	}
	AControl::DoMouseWheel(pEvent);
}

ASize AContainer::GetScrollSize()
{
	ASize sz;
	if( m_bHorzScrollBarShow && m_pHorzScrollBar != NULL ) sz.cx = (int)m_pHorzScrollBar->GetPosition();
	if( m_bVertScrollBarShow && m_pVertScrollBar != NULL ) sz.cy = (int)m_pVertScrollBar->GetPosition();
	return sz;
}

void AContainer::CreateChildren(AMLBody* pNode)
{
	for(int i=0;i<pNode->GetChildCount();i++)
	{
		AMLBody* pChildBody = pNode->GetChild(i);
		AControl* pc = CreateInstance(pChildBody,this);
	}
}