#include "MiniginPCH.h"
#include "InputManager.h"

#include "Timer.h"

#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

using PlayerAction = std::map<dae::KeyBinding, std::unique_ptr<dae::Command>>;

class dae::InputManager::XboxControllerImpl
{
	public:
		bool IsPressed(const Button& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const;
		bool IsDown(const Button& button, const XINPUT_STATE& currentState) const;
		bool IsReleased(const Button& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const;
	
		void ProcessInput();
		void HandlePlayers();

	private:
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousStatePlayer2{};
		XINPUT_STATE m_CurrentStatePlayer2{};

		PlayerAction m_Player1Commands{};
		PlayerAction m_Player2Commands{};

		void HandleCommands( PlayerAction& commandMap, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState);

};

bool dae::InputManager::XboxControllerImpl::IsPressed(const Button& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const
{
	return currentState.Gamepad.wButtons & static_cast<WORD>(button) &&
		!(previousState.Gamepad.wButtons & static_cast<WORD>(button));
}

bool dae::InputManager::XboxControllerImpl::IsDown(const Button& button, const XINPUT_STATE& currentState) const
{
	return currentState.Gamepad.wButtons & static_cast<WORD>(button);
}

bool dae::InputManager::XboxControllerImpl::IsReleased(const Button& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const
{
	return !(currentState.Gamepad.wButtons & static_cast<WORD>(button)) &&
		previousState.Gamepad.wButtons & static_cast<WORD>(button);
}

void dae::InputManager::XboxControllerImpl::ProcessInput()
{
	m_PreviousState = m_CurrentState;
	m_PreviousStatePlayer2 = m_CurrentStatePlayer2;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentStatePlayer2, sizeof(XINPUT_STATE));
	DWORD dwResult{};
	dwResult = XInputGetState(0, &m_CurrentState);
	dwResult = XInputGetState(1, &m_CurrentStatePlayer2);
}

void dae::InputManager::XboxControllerImpl::HandlePlayers()
{
	
	HandleCommands(dae::InputManager::GetInstance().GetPlayer1Commands(), m_CurrentState, m_PreviousState);
	HandleCommands(dae::InputManager::GetInstance().GetPlayer1Commands(), m_CurrentState, m_PreviousState);
}

void dae::InputManager::XboxControllerImpl::HandleCommands( PlayerAction& commandMap, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState)
{
	// https://stackoverflow.com/questions/26281979/c-loop-through-map
	for (PlayerAction::const_iterator it = commandMap.begin(); it != commandMap.end(); ++it)
	{
		switch ((*it).first.InputState)
		{
		case InputState::Up:
			if (IsReleased((*it).first.ControllerButton, currentState, previousState)) (*it).second->Execute();
			break;
		case InputState::Down:
			if (IsDown((*it).first.ControllerButton, currentState)) (*it).second->Execute();
			break;
		case InputState::Pressed:
			if (IsPressed((*it).first.ControllerButton, currentState, previousState)) (*it).second->Execute();
			break;
		}
	}
}



dae::InputManager::InputManager()
{
	m_pImpl = new XboxControllerImpl();
}

dae::InputManager::~InputManager()
{
	m_pImpl = nullptr;
	delete m_pImpl;
}

void dae::InputManager::Destroy()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

bool dae::InputManager::ProcessInput()
{
	
	m_pImpl->ProcessInput();
	const bool isPlaying = HandleKeyBoard();
	m_pImpl->HandlePlayers();
	

	return isPlaying;
}


bool dae::InputManager::HandleKeyBoard()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (!HandleEvent(e, m_Player1Commands))
			return false;

		if (!HandleEvent(e, m_Player2Commands))
			return false;

	}

	HandleKeyDown(m_Player1Commands);
	HandleKeyDown(m_Player2Commands);

	return true;
}

bool dae::InputManager::HandleEvent(const SDL_Event& e, const PlayerAction& commands)
{
	if (e.type == SDL_QUIT) return false;

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		for (PlayerAction::const_iterator it = commands.begin(); it != commands.end(); ++it)
		{
			if ((*it).first.KeyboardKey == e.key.keysym.scancode
				&& (*it).first.InputState == InputState::Pressed)
				(*it).second->Execute();
		}
	}

	if (e.type == SDL_KEYUP)
	{
		for (PlayerAction::const_iterator commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
		{
			if ((*commandIt).first.KeyboardKey == e.key.keysym.scancode
				&& (*commandIt).first.InputState == InputState::Up)
				(*commandIt).second->Execute();
		}
	}

	return true;
}

void dae::InputManager::HandleKeyDown(const PlayerAction& commands) const
{
	for (PlayerAction::const_iterator it = commands.begin(); it != commands.end(); ++it)
	{
		switch ((*it).first.InputState)
		{
		case InputState::Down:
			if (IsKeyDown((*it).first.KeyboardKey)) (*it).second->Execute();
			break;
		default:
			break;
		}
	}
}


bool dae::InputManager::IsKeyDown(const SDL_Scancode& key) const
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	return pStates[key];
}

void dae::InputManager::AddInput(const int& playerNr, const KeyBinding& button, Command* pCommand)
{
	switch (playerNr)
	{
	case 0:
		m_Player1Commands.insert(std::make_pair(button, pCommand));
		break;
	case 1:
		m_Player2Commands.insert(std::make_pair(button, pCommand));
		break;
	default:
		break;
	}
}

PlayerAction& dae::InputManager::GetPlayer2Commands()
{
	return m_Player2Commands;
}

PlayerAction& dae::InputManager::GetPlayer1Commands()
{
	return m_Player1Commands;
}




