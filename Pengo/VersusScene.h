#pragma once
#include "Scene.h"

namespace dae
{
	class Font;
	class SnoBeeCompontent;
	class VersusScene final : public Scene
	{
	public:
		VersusScene(const std::string& name, const std::string& nextLevel);
		~VersusScene();

		void Initialize() override;
		void Update() override;

		

		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) = delete;
		VersusScene& operator=(const VersusScene& other) = delete;
		VersusScene& operator=(VersusScene&& other) = delete;


	private:
		void CreatePlayer(std::shared_ptr<Font>& font);
		void CreateVersusPlayer(std::shared_ptr<Font>& font);
		void CreateInfo(std::shared_ptr<Font>& font, glm::ivec2& pos2, glm::ivec2& pos);
		bool FindVersusPlayer();

		std::string m_NextLevel{};
		
	};
}


