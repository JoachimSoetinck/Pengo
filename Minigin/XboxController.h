#pragma once
#include "BaseController.h"

namespace dae
{
	class XboxController final : public BaseController
	{
		class XboxControllerImpl;
		XboxControllerImpl* m_pImpl = nullptr;
	public:
		enum class Button
		{
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			ButtonDPADUp = 0x0001,
			ButtonDPADDown = 0x0002,
			ButtonDPADLeft = 0x0004,
			ButtonDPADRight = 0x0008,
			ButtonStart = 0x0010,
			ButtonBack = 0x0020,
			ButtonLeftThumb = 0x0040,
			ButtonRightThumb = 0x0080,
			ButtonLeftShoulder = 0x0100,
			ButtonRightShoulder = 0x0200,
		};
		void Update() const override;

		bool IsDown(Button button) const;
		bool IsUp(Button button) const;
		bool IsPressed(Button button) const;

		XboxController(int controllerNr);
		~XboxController() override;

	};
}
