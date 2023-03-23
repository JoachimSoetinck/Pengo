#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"xinput.lib")
#include "XboxController.h"


using namespace dae;

class XboxController::XboxControllerImpl final
{
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	int m_ControllerNr{};
	WORD m_IsPressedThisFrame{};
	WORD m_IsReleasedThisFrame{};

public:
	XboxControllerImpl(int controllerNr)
		:m_ControllerNr(controllerNr)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}
	void Update()
	{
		m_PreviousState = m_CurrentState;
		//CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerNr, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_IsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_IsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
	bool IsPressed(XboxController::Button button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned>(button);
	}

	bool IsDown(XboxController::Button button) const
	{
		return m_IsPressedThisFrame & static_cast<unsigned>(button);
	}

	bool IsUp(XboxController::Button button) const
	{
		return m_IsReleasedThisFrame & static_cast<unsigned>(button);
	}

};

void dae::XboxController::Update() const
{
	m_pImpl->Update();
}

bool dae::XboxController::IsDown(XboxController::Button button) const
{
	return m_pImpl->IsDown(button);
}

bool dae::XboxController::IsUp(XboxController::Button button) const
{
	return m_pImpl->IsUp(button);
}

bool dae::XboxController::IsPressed(XboxController::Button button) const
{
	return m_pImpl->IsPressed(button);
}

dae::XboxController::XboxController(int controllerNr)
	:BaseController(),
	m_pImpl{ new XboxControllerImpl(controllerNr) }
{
}

dae::XboxController::~XboxController()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}
