#include "StdAfx.h"
#include "UIXMLGen.h"


UIXMLGen::UIXMLGen(AMLBody* pRoot):m_pRoot(pRoot)
{
}


UIXMLGen::~UIXMLGen(void)
{
}

afc_object<AMLBody> UIXMLGen::ToNode()
{
	return GenControl(m_pRoot);
}
AString UIXMLGen::ToString()
{
	afc_object<AMLBody> p;
	p = GenControl(m_pRoot);
	return p->ToXML();
}

afc_object<AMLBody> UIXMLGen::GenControl(AMLBody* pRoot)
{
	AString sType = pRoot->GetName();

	afc_object<AMLBody> pn(new AMLBody());
	pn->SetName(_T("c"));
	pn->SetProp(_T("type"),sType);

	//AControl��������
	AStringMapEnumerator em(&(pRoot->m_aProp));
	while( em.Next() )
	{
		pn->SetProp(em.Index(),(ACHAR *)em.Cur());
	}

	//����
	afc_object<AMLBody> pnFind;
	pnFind = pRoot->FindBody(_T("font"));
	if( pnFind != ANULL )
	{
		pn->AddBody(&pnFind);
	}

	//========== �ض��ؼ����������� ====================
	if( sType == _T("Form") )
	{
		//fix me later : �ƺ��Ѿ�ûʲô�ô������
	}
	else if( sType == _T("ScrollBar") )
	{
		AString s = pn->GetProp(_T("aim"));
		if( s == _T("��ֱ") ) pn->SetProp(_T("type"),_T("VertScrollBar"));
		else pn->SetProp(_T("type"),_T("HorzScrollBar"));
	}
	else if( sType == _T("Slide") )
	{
		AString s = pn->GetProp(_T("aim"));
		if( s == _T("��ֱ") ) pn->SetProp(_T("type"),_T("VertSlide"));
		else pn->SetProp(_T("type"),_T("HorzSlide"));
	}

	//---- �����ӿؼ�
	pnFind = pRoot->FindBody(_T("@"));
	if( pnFind != ANULL )
	{
		afc_object<AMLBody> pChildren(new AMLBody());
		
		pChildren->SetName(_T("children"));

		for(int i=0;i<pnFind->GetChildCount();i++)
		{
			afc_object<AMLBody> pChild;
			pChild = pnFind->GetChild(i);
			if( pChild->GetName() == _T("Array") )
			{
				AMLBody* pa = pChild->FindBody(_T("@"));
				if( pa != NULL)
				{
					afc_object<AMLBody> pc(new AMLBody());
					pc->SetName(_T("children"));
					for(int j=0;j<pa->GetChildCount();j++)
					{
						afc_object<AMLBody> pChild2;
						pChild2 = pa->GetChild(j);
						afc_object<AMLBody> pnTmp;
						pnTmp = GenControl(&pChild2);
						pc->AddBody(&pnTmp);
					}
					if( pc->GetChildCount() > 0 )
						pn->AddBody( &pc );
				}
				
			}
			else
			{
				afc_object<AMLBody> pnTmp;
				pnTmp = GenControl(&pChild);
				pChildren->AddBody(&pnTmp);
			}
		}
		if( pChildren->GetChildCount() > 0 )
			pn->AddBody( &pChildren );
		
	}
	return pn;
}