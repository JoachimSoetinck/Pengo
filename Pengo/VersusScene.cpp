#include "VersusScene.h"
#include "LevelCreator.h"
#include "TextComponent.h"
#include "ScoreDisplayComponent.h"
#include "LivesDisplayComponent.h"
#include "SpriteCompenent.h"
#include "CollisionComponent.h"
#include "PengoComponent.h"
#include "InputManager.h"
#include "CustomCommands.h"
#include "SnoBeeCompontent.h"
#include "Font.h"


dae::VersusScene::VersusScene(const std::string& name) :Scene(name)
{
}

dae::VersusScene::~VersusScene()
{
}

void dae::VersusScene::Initialize()
{

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", this);

	Sleep(1000);

	CreateVersusPlayer(font);
	CreatePlayer(font);
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };
	CreateInfo(font, pos2, pos);

	Scene::Initialize();
}

void dae::VersusScene::CreatePlayer(std::shared_ptr<dae::Font>& font)
{
	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Lives:", font));
	tc->AddComponent(new dae::LivesDisplayComponent(tc.get()));
	tc->SetPosition(10, 350);
	Add(tc);

	auto score = std::make_shared<dae::GameObject>();
	score->AddComponent(new dae::TextComponent(score.get(), "Score:", font));
	score->AddComponent(new dae::ScoreDisplayComponent(score.get()));
	score->SetPosition(10, 370);
	Add(score);

	SDL_Rect src{ 0,0,16,16 };
	SDL_Rect dest{ 0,0,20,20 };

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), dest, 0.8f));
	go->AddComponent(new dae::RigidBody(go.get()));
	go->AddComponent(new dae::CollisionComponent(go.get(), dest));
	auto pengo = new dae::PengoComponent(go.get());
	pengo->AddObserver(tc->GetComponent<dae::LivesDisplayComponent>());
	pengo->AddObserver(score->GetComponent<dae::ScoreDisplayComponent>());
	go->AddComponent(pengo);
	go->SetPosition(0, 0);




	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_SPACE, std::make_shared<dae::PushCommand>(go), 0, dae::InputManager::EInputState::Pressed);



	Add(go);
}

void dae::VersusScene::CreateVersusPlayer(std::shared_ptr<Font>& font)
{
	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Lives:", font));
	tc->AddComponent(new dae::LivesDisplayComponent(tc.get()));
	tc->SetPosition(10, 350);
	Add(tc);

	auto score = std::make_shared<dae::GameObject>();
	score->AddComponent(new dae::TextComponent(score.get(), "Score:", font));
	score->AddComponent(new dae::ScoreDisplayComponent(score.get()));
	score->SetPosition(10, 370);
	Add(score);

	SDL_Rect src{ 0,160,16,16 };
	SDL_Rect dest{ 0,0,20,20 };
	 


	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), dest, 0.8f));
	go->AddComponent(new dae::RigidBody(go.get()));
	go->AddComponent(new dae::CollisionComponent(go.get(), dest));
	auto snowbee = new dae::SnoBeeCompontent(go.get(), 194);
	snowbee->AddObserver(tc->GetComponent<dae::LivesDisplayComponent>());
	snowbee->AddObserver(score->GetComponent<dae::ScoreDisplayComponent>());
	go->AddComponent(snowbee);
	go->SetPosition(50, 150);
	snowbee->Start();


	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_S, std::make_shared<dae::MoveCommand>(go, dae::SnoBeeCompontent::SnobeeState::Down), 1, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_W, std::make_shared<dae::MoveCommand>(go, dae::SnoBeeCompontent::SnobeeState::Up), 1, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_D, std::make_shared<dae::MoveCommand>(go, dae::SnoBeeCompontent::SnobeeState::Right), 1, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_A, std::make_shared<dae::MoveCommand>(go, dae::SnoBeeCompontent::SnobeeState::Left), 1, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_N, std::make_shared<dae::PushCommand>(go), 1, dae::InputManager::EInputState::Pressed);



	Add(go);

}

void dae::VersusScene::CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos)
{

}
