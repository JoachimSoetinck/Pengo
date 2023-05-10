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

	scene = std::make_shared<dae::Scene>("Level02");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("Level03");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("COOP01");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("COOP02");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("COOP03");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("VERSUS01");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("VERSUS02");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::Scene>("VERSUS03");
	dae::SceneManager::GetInstance().AddScene(scene);



	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	

	std::string buttonText{ "Single Player" };
	glm::ivec2 position{ 150,80 };
	CreateButton(buttonText, font2, position, Start);

	buttonText = "COOP";
	position = { 150,10 };
	CreateButton(buttonText, font2, position, Start);

	buttonText = "VERSUS";
	position = { 150,300 };
	CreateButton(buttonText, font2, position, Start);

	
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };


	auto l1 = dae::SceneManager::GetInstance().GetScene("Level01");
	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", l1);
	CreateInfo(font, l1, pos2, pos);

	auto go = std::make_shared<dae::GameObject>();
	CreatePlayer(font, l1, go);


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

void CreateButton(std::string& buttonText, std::shared_ptr<dae::Font>& font2, glm::ivec2& position, std::shared_ptr<dae::Scene>& Start)
{
	auto button = std::make_shared<dae::GameObject>();
	button->AddComponent(new dae::RenderComponent(button.get(), "../Data/Button.png"));
	button->AddComponent(new dae::MenuButtonComponent(button.get(), button->GetComponent<dae::RenderComponent>(), "Level01"));
	button->AddComponent(new dae::TextComponent(button.get(), buttonText, font2));
	button->SetPosition(position.x, position.y);
	Start->Add(button);
}

void CreateInfo(std::shared_ptr<dae::Font>& font, std::shared_ptr<dae::Scene>& scene, glm::ivec2& pos2, glm::ivec2& pos)
{
	auto How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "HOW TO PLAY (Controller)", font));
	How->SetPosition(0, 0);
	scene->Add(How);

	How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "DIE: X ", font));
	How->SetPosition(pos2.x, pos2.y);
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