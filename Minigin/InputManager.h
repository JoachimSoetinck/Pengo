#pragma once
#include <map>
#include <SDL.h>
#include <XInput.h>
#include "Command.h"
#include "Singleton.h"
#include <map>
#include <memory>


namespace dae
{
	enum class Button
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK
	};

	enum class InputState
	{
		Pressed,
		Up,
		Down
	};

	struct KeyBinding
	{
		KeyBinding(const Button& cButton, const SDL_Scancode& key, const InputState& state)
			: ControllerButton(cButton)
			, KeyboardKey(key)
			, InputState(state)
		{}

		Button ControllerButton;
		SDL_Scancode KeyboardKey;
		InputState InputState;
	};

	inline bool operator<(const KeyBinding& lhs, const KeyBinding& rhs)
	{
		return lhs.ControllerButton < rhs.ControllerButton;
	};

	class InputManager : public Singleton<InputManager>
	{
		

	public:
		//reducing long name in code

		InputManager();
		~InputManager();

		void Destroy();
		
		bool ProcessInput();
		bool IsKeyDown(const SDL_Scancode& key) const;
		void AddInput(const int& playerNr, const KeyBinding& button, Command* pCommand);
		
		std::map<KeyBinding, std::unique_ptr<Command>>& GetPlayer2Commands();
		std::map<KeyBinding, std::unique_ptr<Command>>& GetPlayer1Commands();
	

	private:
		class XboxControllerImpl;
		XboxControllerImpl* m_pImpl = nullptr;

		bool HandleKeyBoard();
		bool HandleEvent(const SDL_Event& e, const std::map<KeyBinding, std::unique_ptr<Command>>& commands);
		void HandleKeyDown(const std::map<KeyBinding, std::unique_ptr<Command>>& action) const;
	

		std::map<KeyBinding, std::unique_ptr<Command>> m_Player1Commands{};
		std::map<KeyBinding, std::unique_ptr<Command>> m_Player2Commands{};

		
		
	};
}
