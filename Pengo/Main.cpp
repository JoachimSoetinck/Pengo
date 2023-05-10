#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "LevelCreator.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "SpriteCompenent.h"
#include "CollisionComponent.h"
#include "XboxController.h"
#include "InputManager.h"
#include "PengoComponent.h"
#include "CustomCommands.h"
#include "ServiceLocator.h"	
#include <SDLSoundSystem.h>
#include "RenderComponent.h"
#include "MenuButtonComponent.h"
#include "Main.h"



void load()
{
	auto Start = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(Start);

	auto scene = std::make_shared<dae::Scene>("Level01");
	dae::SceneManager::GetInstance().AddScene(scene);

	auto button = std::make_shared<dae::GameObject>();
	button->AddComponent(new dae::RenderComponent(button.get(), "../Data/Button.png"));
	button->AddComponent(new dae::MenuButtonComponent(button.get(), button->GetComponent<dae::RenderComponent>(), "Level01"));
	button->SetPosition(150, 150);
	Start->Add(button);

	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", scene);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,25 };


	CreateInfo(font, scene, pos2, pos);


	auto go = std::make_shared<dae::GameObject>();

	CreatePlayer(font, scene, go);

	
	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_SPACE, std::make_shared<dae::PushCommand>(go), 0, dae::InputManager::EInputState::Pressed);


	//tc = std::make_shared<dae::GameObject>();
	//tc->AddComponent(new dae::TextComponent(tc.get(), "Lives:", font));
	//tc->AddComponent(new dae::LivesDisplayComponent(tc.get()));
	//tc->SetPosition(530, 350);
	//scene->Add(tc);
	//score = std::make_shared<dae::GameObject>();
	//score->AddComponent(new dae::TextComponent(score.get(), "Score:", font));
	//score->AddComponent(new dae::ScoreDisplayComponent(score.get()));
	//score->SetPosition(530, 370);
	//scene->Add(score);
	//go = std::make_shared<dae::GameObject>();
	//src = { 0,80,16,16 };
	//go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), { 0,0,20,20 }, 0.8f)); 
	//go->AddComponent(new dae::RigidBody(go.get()));
	//pengo = new dae::PengoComponent(go.get());
	//pengo->AddObserver(tc->GetComponent<dae::LivesDisplayComponent>());
	//pengo->AddObserver(score->GetComponent<dae::ScoreDisplayComponent>());
	//go->AddComponent(new dae::CollisionComponent(go.get(), dest));
	//go->AddComponent(pengo);
	//go->SetPosition(50, 250);
	//pengo->Start();
	//scene->Add(go);
	//dae::InputManager::GetInstance().AddPlayer(false);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_W, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 1, dae::InputManager::EInputState::Down);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_W, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_S, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 1, dae::InputManager::EInputState::Down);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_S, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_D, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 1, dae::InputManager::EInputState::Down);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_D, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_A, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 1, dae::InputManager::EInputState::Down);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_A, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Idle), 1, dae::InputManager::EInputState::Up);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_V, std::make_shared<dae::DieCommand>(go), 1, dae::InputManager::EInputState::Up);
	//dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonB, SDL_SCANCODE_N, std::make_shared<dae::GivePointsCommand>(go, 100), 1, dae::InputManager::EInputState::Up);

	for (auto& s : dae::SceneManager::GetInstance().GetScenes())
	{
		s->Initialize();
	}

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/Jump.wav");

	
}

void CreateInfo(std::shared_ptr<dae::Font>& font, std::shared_ptr<dae::Scene>& scene, glm::ivec2& pos2, glm::ivec2& pos)
{
	auto How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "HOW TO PLAY (Controller)", font));
	How->SetPosition(0, 0);
	scene->Add(How);

	How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "DIE: X ", font));
	How->SetPosition(pos2.x, pos.y);
	scene->Add(How);
	How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "Points: B ", font));
	How->SetPosition(pos.x, pos.y);
	scene->Add(How);
}

void CreatePlayer(std::shared_ptr<dae::Font>& font, std::shared_ptr<dae::Scene>& scene, std::shared_ptr<dae::GameObject>& go)
{
	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Lives:", font));
	tc->AddComponent(new dae::LivesDisplayComponent(tc.get()));
	tc->SetPosition(10, 350);
	scene->Add(tc);

	auto score = std::make_shared<dae::GameObject>();
	score->AddComponent(new dae::TextComponent(score.get(), "Score:", font));
	score->AddComponent(new dae::ScoreDisplayComponent(score.get()));
	score->SetPosition(10, 370);
	scene->Add(score);



	SDL_Rect src{ 0,0,16,16 };
	SDL_Rect dest{ 0,0,20,20 };

	go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), dest, 0.8f));
	go->AddComponent(new dae::RigidBody(go.get()));
	go->AddComponent(new dae::CollisionComponent(go.get(), dest));
	auto pengo = new dae::PengoComponent(go.get());
	pengo->AddObserver(tc->GetComponent<dae::LivesDisplayComponent>());
	pengo->AddObserver(score->GetComponent<dae::ScoreDisplayComponent>());
	go->AddComponent(pengo);
	go->SetPosition(50, 150);
	pengo->Start();


	scene->Add(go);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}