#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "SpriteCompenent.h"
#include "LevelCreator.h"
#include "InputManager.h"
#include "RotationComponent.h"
#include "PengoComponent.h"
#include "LivesDisplayComponent.h"


void load()
{
	auto scene = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(scene);

	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", scene);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Lives", font));
	tc->AddComponent(new dae::LivesDisplayComponent(tc.get()));
	tc->SetPosition(10, 350);
	scene->Add(tc);

	auto go = std::make_shared<dae::GameObject>();
	SDL_Rect src{ 0,0,16,16 };
	go->AddComponent(new SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), { 0,0,20,20 }, 0.8f));
	go->AddComponent(new dae::RigidBody(go.get()));
	auto pengo = new dae::PengoComponent(go.get(), tc.get());
	go->AddComponent(pengo);
	go->SetPosition(50, 150);

	pengo->Start();


	scene->Add(go);

	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP,std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 0, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 0, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 0, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 0, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 0, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 0, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 0, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 0, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_SPACE, std::make_shared<dae::DieCommand>(go), 0, dae::InputManager::EInputState::Up);

	go = std::make_shared<dae::GameObject>();
	src ={ 0,80,16,16 };
	go->AddComponent(new SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), { 0,0,20,20 }, 0.8f));
	go->AddComponent(new dae::RigidBody(go.get()));
	go->AddComponent(new dae::PengoComponent(go.get()));
	go->SetPosition(50, 250);
	scene->Add(go);

	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_W, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 1, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_W, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);

	

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_S, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 1, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_S, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_D, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 1, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_D, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);

	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_A, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 1, dae::InputManager::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_A, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);

	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}