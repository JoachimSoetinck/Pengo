#pragma once
#include "BaseComponent.h"


namespace dae
{
	class RenderComponent;

	class ButtonComponent : public BaseComponent
	{
	public:
		 ButtonComponent(GameObject* go,RenderComponent* pRenderComp);
		virtual ~ButtonComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate()  override;

		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) = delete;

	protected:
		virtual void ProcessClicked();

	private:
		RenderComponent* m_pRenderComponent;
	};
}