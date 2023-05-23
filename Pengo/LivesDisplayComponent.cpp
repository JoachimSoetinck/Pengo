#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "PengoComponent.h"

dae::LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* go) : BaseComponent(go),
pTextComponent{ m_pGameObject->GetComponent<dae::TextComponent>() },
m_text{ "" }
{
}

dae::LivesDisplayComponent::~LivesDisplayComponent()
{
}

void dae::LivesDisplayComponent::Initialize()
{
}

void dae::LivesDisplayComponent::Update()
{
}

void dae::LivesDisplayComponent::Render() const
{
}

void dae::LivesDisplayComponent::FixedUpdate()
{
}

void dae::LivesDisplayComponent::OnNotify(Event event, GameObject* go)
{
	switch (event)
	{
	case dae::Event::PlayerStart:
		m_text = "Lives: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetLives());;
		pTextComponent->SetText(m_text);
		break;
		break;
	case dae::Event::PlayerDied:
		m_text = "Lives: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetLives());
		pTextComponent->SetText(m_text);
		break;
	case dae::Event::DestroySpawner:
		
		break;
	default:
		break;
	}
}
