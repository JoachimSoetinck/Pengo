#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "PengoComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(dae::GameObject* go) : BaseComponent(go),
pTextComponent{ m_pGameObject->GetComponent<dae::TextComponent>() },
m_text{ "" }
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
		m_text = "Score: 0";
		pTextComponent->SetText(m_text);
		break;
	case dae::Event::GivePoints:
		m_text = "Score: " + std::to_string(go->GetComponent<dae::PengoComponent>()->GetScore());
		pTextComponent->SetText(m_text);
		break;
	default:
		break;
	}
}

