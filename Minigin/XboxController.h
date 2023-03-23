#pragma once
#include <XInput.h>

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
			ButtonA = XINPUT_GAMEPAD_A,
			ButtonB = XINPUT_GAMEPAD_B,
			ButtonX = XINPUT_GAMEPAD_X,
			ButtonY = XINPUT_GAMEPAD_Y,
			ButtonDPADUp = XINPUT_GAMEPAD_DPAD_UP,
			ButtonDPADDown = XINPUT_GAMEPAD_DPAD_DOWN,
			ButtonDPADLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			ButtonDPADRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			ButtonStart = XINPUT_GAMEPAD_START,
			ButtonBack = XINPUT_GAMEPAD_BACK,
			ButtonLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
			ButtonRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
			ButtonLeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			ButtonRightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		};
		void Update() const override;

		bool IsDown(Button button) const;
		bool IsUp(Button button) const;
		bool IsPressed(Button button) const;

		XboxController(int controllerNr);
		~XboxController() override;

	};
}
