#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "PengoComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(dae::GameObject* go) : BaseComponent(go),
m_TextComponent{ m_pGameObject->GetComponent<dae::TextComponent>() },
m_Text{ "" }
{
}

void dae::ScoreDisplayComponent::Initialize()
{
}

void dae::ScoreDisplayComponent::Update()
{
}

void dae::ScoreDisplayComponent::Render() const
{
}

void dae::ScoreDisplayComponent::FixedUpdate()
{
}

void dae::ScoreDisplayComponent::OnNotify(Event event, GameObject* go)
{
	switch (event)
	{
	case dae::Event::PlayerStart:
		m_Text = "Score: 0";
		m_TextComponent->SetText(m_Text);
		break;
	case dae::Event::GivePoints:
		//go->GetComponent<dae::PengoComponent>()->GivePoints(100);
		m_Text = "Score: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetScore());
		m_TextComponent->SetText(m_Text);
		break;
	case dae::Event::DestroySpawner:
	{
		go->GetComponent<dae::PengoComponent>()->GivePoints(50);
		m_Text = "Score: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetScore());
		m_TextComponent->SetText(m_Text);
		break;
	}
	default:
		break;
	}
}

