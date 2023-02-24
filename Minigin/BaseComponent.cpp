#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"


using namespace dae;
dae::BaseComponent::BaseComponent()
{

}


dae::BaseComponent::~BaseComponent()
{

}

GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

dae::BaseComponent::BaseComponent(dae::GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
	, m_position{ pGameObject->GetLocalPosition() }
{

}

