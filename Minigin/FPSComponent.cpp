#include "FPSComponent.h"
#include "TextComponent.h"
#include "Timer.h"



dae::FPSComponent::FPSComponent(dae::GameObject* go, TextComponent* tc)
	:BaseComponent(go),
	pTextComponent{ tc }
{
}

void dae::FPSComponent::Initialize()
{
}

void dae::FPSComponent::Update()
{
	if (pTextComponent)
	{
		m_TimeSinceLastUpdate += Time::GetDeltaTime();
		const float fps = 1.0f / Time::GetInstance().GetDeltaTime();

		if (m_TimeSinceLastUpdate >= m_UpdateFPSInterval)
		{
			m_text = std::to_string(int(fps)) + "FPS";
			pTextComponent->SetText(m_text);
			m_TimeSinceLastUpdate = 0;
		}
	}
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::FixedUpdate()
{

}
