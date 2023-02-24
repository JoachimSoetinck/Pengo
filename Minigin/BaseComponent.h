#pragma once
#include "MiniginPCH.h"

namespace dae {
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		GameObject* GetGameObject() const;


	private:

	protected:
		glm::vec2 m_position;
		GameObject* m_pGameObject = nullptr;
		BaseComponent(dae::GameObject* pGameObject);
	};

}



