#pragma once
#include "Scene.h"

namespace dae
{
	class Font;
	class SnoBeeCompontent;
	class WallComponent;

	class SinglePlayerScene : public Scene
	{
	public:
		SinglePlayerScene(const std::string& name);

		void Initialize() override;
		void Update() override;

		SinglePlayerScene(const SinglePlayerScene& other) = delete;
		SinglePlayerScene(SinglePlayerScene&& other) = delete;
		SinglePlayerScene& operator=(const SinglePlayerScene& other) = delete;
		SinglePlayerScene& operator=(SinglePlayerScene&& other) = delete;




	private:
		void CreatePlayer(std::shared_ptr<dae::Font>& font);
		void CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos);

		float m_Elapsed{ 0.0f }, m_SpawnTimer{ 3.0f };
		int m_NrOfEnemiesInLevel{ 3 };
		std::string m_NextLevel;
	
	};
}


