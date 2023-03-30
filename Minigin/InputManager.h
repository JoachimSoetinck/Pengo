#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <memory>

#include "Command.h"

#include "XboxController.h"


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
		glm::ivec2 GetMousePos()const { return m_MousePos; };
		bool IsMousePress() const { return m_isPressed; };
	private:
		
		
		const Uint8* m_pCurrentState{};
		Uint8* m_pPreviousState{};

		std::vector<ControllerAction*> m_ConsoleCommands{};

		std::vector<std::unique_ptr<XboxController>> m_pControllers{};
	

		SDL_Event m_Event{};

		glm::ivec2 m_MousePos{};

		bool m_isPressed{ false };



	};

}
