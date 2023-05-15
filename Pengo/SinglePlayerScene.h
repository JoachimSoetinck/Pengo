#pragma once
#include "Scene.h"

namespace dae
{
	class Font;
	class SinglePlayerScene : public Scene
	{
	public:
		SinglePlayerScene(const std::string& name);

		void Initialize() override;

		SinglePlayerScene(const SinglePlayerScene& other) = delete;
		SinglePlayerScene(SinglePlayerScene&& other) = delete;
		SinglePlayerScene& operator=(const SinglePlayerScene& other) = delete;
		SinglePlayerScene& operator=(SinglePlayerScene&& other) = delete;

	private:
		void CreatePlayer(std::shared_ptr<dae::Font>& font);
		void CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos);
	};
}


