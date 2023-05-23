#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "PengoComponent.h"

dae::LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* go) : BaseComponent(go),
m_TextComponent{ m_pGameObject->GetComponent<dae::TextComponent>() },
m_Text{ "" }
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
		m_Text = "Lives: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetLives());;
		m_TextComponent->SetText(m_Text);
		break;
		break;
	case dae::Event::PlayerDied:
		m_Text = "Lives: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetLives());
		m_TextComponent->SetText(m_Text);
		break;
	case dae::Event::DestroySpawner:
		
		break;
	default:
		break;
	}
}
