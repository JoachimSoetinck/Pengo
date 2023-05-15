#include "MenuButtonComponent.h"
#include "SceneManager.h"
#include "RenderComponent.h"
#include "Scene.h"

dae::MenuButtonComponent::MenuButtonComponent(dae::GameObject* obj, dae::RenderComponent* pRenderComp, const std::string& sceneName):ButtonComponent(obj,pRenderComp),
m_SceneName{sceneName}
{
}

dae::MenuButtonComponent::~MenuButtonComponent()
{
}

void dae::MenuButtonComponent::ProcessClicked()
{
	auto s = SceneManager::GetInstance().GetScene(m_SceneName);
	s->Initialize();
	SceneManager::GetInstance().SetActiveScene(m_SceneName);
	
}
