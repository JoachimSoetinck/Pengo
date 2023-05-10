#include "ButtonComponent.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "GameObject.h"


dae::ButtonComponent::ButtonComponent(GameObject* go, RenderComponent* pRenderComp):BaseComponent(go),
m_pRenderComponent{pRenderComp}
{
}

dae::ButtonComponent::~ButtonComponent()
{
	
}

void dae::ButtonComponent::Initialize()
{
}

void dae::ButtonComponent::Update()
{
	const bool mouseClicked = dae::InputManager::GetInstance().GetMouseUp();
	if (mouseClicked)
	{
		const auto mousePos = dae::InputManager::GetInstance().GetMousePosition();
		const float rWidth = m_pRenderComponent->GetWidth();
		const float rHeight = m_pRenderComponent->GetHeight();
		const auto pos = m_pGameObject->GetLocalPosition();

		if (pos.x <= mousePos.x && mousePos.x <= pos.x + rWidth &&
			pos.y <= mousePos.y && mousePos.y <= pos.y + rHeight)
			ProcessClicked();
	}
}

void dae::ButtonComponent::Render() const
{
}

void dae::ButtonComponent::FixedUpdate()
{
}

void dae::ButtonComponent::ProcessClicked()
{
}


