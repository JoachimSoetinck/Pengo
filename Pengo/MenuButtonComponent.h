#pragma once
#include "ButtonComponent.h"

namespace dae
{
	class MenuButtonComponent final : public ButtonComponent
	{
	public:
		 MenuButtonComponent(GameObject* obj, RenderComponent* pRenderComp, const std::string& sceneName);
		~MenuButtonComponent();

		MenuButtonComponent(const MenuButtonComponent& other) = delete;
		MenuButtonComponent(MenuButtonComponent&& other) = delete;
		MenuButtonComponent& operator=(const MenuButtonComponent& other) = delete;
		MenuButtonComponent& operator=(MenuButtonComponent&& other) = delete;

	private:
		std::string m_SceneName;

		void ProcessClicked() override;
	};
}

