#pragma once
#include "Scene.h"

namespace dae
{
	class Font;
	class PengoComponent;
	class CoopScene : public Scene
	{
	public:
		CoopScene(const std::string& name);

		void Initialize() override;
		void Update() override;


		CoopScene(const CoopScene& other) = delete;
		CoopScene(CoopScene&& other) = delete;
		CoopScene& operator=(const CoopScene& other) = delete;
		CoopScene& operator=(CoopScene&& other) = delete;

	private:
		void CreatePlayer(std::shared_ptr<dae::Font>& font);
		void CreateCoopPlayer(std::shared_ptr<dae::Font>& font);
		void CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos);

		float m_Elapsed{ 0.0f }, m_SpawnTimer{ 2.0f };
		int m_NrOfEnemiesInLevel{ 3 };

		PengoComponent* m_Player1;
		PengoComponent* m_Player2;
	};
}
