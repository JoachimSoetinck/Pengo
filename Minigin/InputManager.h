#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <memory>
#include "Command.h"
#include "XboxController.h"
#include "MiniginPCH.h"


namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{

	public:

		//Mouse 
		enum class EMouseButton
		{
			Left, Middle, Right
		};

		//Type Press
		enum class EInputState
		{
			Down,
			Pressed,
			Up
		};



		struct ControllerAction 
		{
			EInputState state{};
			std::shared_ptr<Command> command{};
			int playerNr{};
			SDL_Scancode Key{};
			ControllerAction() = default;
			~ControllerAction() = default;
			XboxController::Button controllerButton{};
		};


		InputManager();
		~InputManager();
		bool ProcessInput();
		void Update();


		int AddPlayer(bool IsKeyBoard);
		

		bool IsPressed(XboxController::Button button, int playerNr) const;
		bool IsDownThisFrame(XboxController::Button button, int playerNr) const;
		bool IsUpThisFrame(XboxController::Button button, int playerNr) const;
		void AddCommand(XboxController::Button button,  SDL_Scancode keyboardButton,std::shared_ptr<Command> command, int playerNr, EInputState state = EInputState::Down);
		void RemoveCommand(XboxController::Button button, std::shared_ptr<Command> command, int playerNr, EInputState state = EInputState::Down);
		POINT GetMousePos()const { return m_MousePosition; };
		bool IsMousePress() const { return m_isPressed; };

		bool GetMouseUp() const;
		POINT GetMousePosition() const;
	private:
		
		
		const Uint8* m_pCurrentState{};
		Uint8* m_pPreviousState{};

		std::vector<ControllerAction*> m_ConsoleCommands{};

		std::vector<std::unique_ptr<XboxController>> m_pControllers{};
	

		SDL_Event m_Event{};

		POINT m_MousePosition = POINT();
		bool m_MouseUp = false;

		bool m_isPressed{ false };



	};

}
