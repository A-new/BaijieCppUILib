#include "stdafx.h"

AComponent::AComponent(AComponent* pOwner):
	AObject(),
	m_pOwner(pOwner)
{
	if( m_pOwner )
		m_pOwner->GetChildren()->Add(this);
}

AComponent::~AComponent()
{

}

 AObjectArray* AComponent::GetChildren()
 {
	 return &m_aChildComponent;
 }

void AComponent::Free()
{
	if( m_pOwner ) 
	{
		m_pOwner->GetChildren()->Delete(this);//������ӹ�ϵ
	}
	//����Լ�ֻά�����ӹ�ϵ������ж�������ã������ⲿ��Release base_class::Release();
}

AComponent* AComponent::GetOwner()
{
	return m_pOwner;
}

