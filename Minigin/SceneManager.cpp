#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::FixedUpdate(float)
{
	m_ActiveScene->FixedUpdate();
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_scenes.push_back(scene);
	if (!m_ActiveScene)
		m_ActiveScene = scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene() const
{
	return m_ActiveScene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			//m_ActiveScene->ResetScene();
			return;
		}
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name)
{
	for (auto& scene : m_scenes)
	{
		if (scene->GetName() == name)
		{
		
			return scene;
		}
	}

	return nullptr;
}



void dae::SceneManager::RemoveMarkedForDeleteItems()
{
	m_ActiveScene->DeleteObjects();
}


