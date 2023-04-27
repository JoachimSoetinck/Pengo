#include "MiniginPCH.h"
#include "InputManager.h"

#include "Scene.h"
#include "SceneManager.h"



dae::InputManager::InputManager()
{

}

dae::InputManager::~InputManager()
{

	for (auto element : m_ConsoleCommands)
	{
		delete element;
		element = nullptr;
	}

}

bool dae::InputManager::ProcessInput()
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);

		if (e.type == SDL_QUIT) {
			return false;
		}

		if (e.type == SDL_MOUSEBUTTONUP)
		{
		}

		if (e.type == SDL_KEYDOWN) {
			for (const auto& controller : m_ConsoleCommands)
			{
				if (controller->state == EInputState::Down )
				{
					if (e.key.keysym.scancode == controller->Key)
						controller->command.get()->Execute();
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		if (e.type == SDL_KEYUP) {
			for (const auto& controller : m_ConsoleCommands)
			{
				if (controller->state == EInputState::Up || controller->state == EInputState::Pressed)
				{
					if (e.key.keysym.scancode == controller->Key)
						controller->command.get()->Execute();
				}
			}

		}

	

		if (e.type == SDL_MOUSEBUTTONDOWN && m_isPressed == false)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				m_isPressed = true;
		}

		if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				m_isPressed = false;
		}
	}

	Update();

	for (const auto& controller : m_ConsoleCommands)
	{

		switch (controller->state)
		{
		case EInputState::Down:
			if (IsDownThisFrame(controller->controllerButton, controller->playerNr))
				controller->command->Execute();
			break;
		case EInputState::Pressed:
			if (IsPressed(controller->controllerButton, controller->playerNr))
				controller->command->Execute();
			break;
		case EInputState::Up:
			if (IsUpThisFrame(controller->controllerButton, controller->playerNr))
				controller->command->Execute();
			break;
		}
	}


	return true;
}

void dae::InputManager::Update()
{

	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}


}

int dae::InputManager::AddPlayer(bool IsKeyBoard)
{

	int index = static_cast<int>(m_pControllers.size());
	m_pControllers.push_back(std::make_unique<XboxController>(index));
	return index;
}


bool dae::InputManager::IsPressed(XboxController::Button button, int  playerNr) const
{
	return m_pControllers[playerNr]->IsPressed(button);
}



bool dae::InputManager::IsDownThisFrame(XboxController::Button button, int playerNr) const
{
	return m_pControllers[playerNr]->IsDown(button);
}



bool dae::InputManager::IsUpThisFrame(XboxController::Button button, int playerNr) const
{
	return m_pControllers[playerNr]->IsUp(button);
}


void dae::InputManager::AddCommand(XboxController::Button Controllerbutton, SDL_Scancode keyboardButton, std::shared_ptr<Command> command, int playerNr, EInputState state)
{
	if (playerNr > m_pControllers.size())
	{
		std::cout << "No Player" << std::endl;
		return;
	}
	ControllerAction* action = new ControllerAction();
	action->command = command;
	action->controllerButton = Controllerbutton;
	action->state = state;
	action->playerNr = playerNr;
	action->Key = keyboardButton;
	m_ConsoleCommands.emplace_back(action);

}


void dae::InputManager::RemoveCommand(XboxController::Button, std::shared_ptr<Command>, int, EInputState)
{
}



