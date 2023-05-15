#pragma once
#include "Scene.h"

namespace dae
{
	class VersusScene final : public Scene
	{
	public:
		VersusScene(const std::string& name, int level);
		~VersusScene();

		void Initialize() override;

		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) = delete;
		VersusScene& operator=(const VersusScene& other) = delete;
		VersusScene& operator=(VersusScene&& other) = delete;
	};
}


