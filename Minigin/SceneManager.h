#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void AddScene(std::shared_ptr<Scene> scene);
		std::shared_ptr<dae::Scene> GetCurrentScene() const;

		void SetActiveScene(const std::string& name);
		void RemoveMarkedForDeleteItems();

		void Update();
		void FixedUpdate(float fixedTimeStep);
		void Render();

		std::vector<std::shared_ptr<Scene>> GetScenes() const { return m_scenes; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}
