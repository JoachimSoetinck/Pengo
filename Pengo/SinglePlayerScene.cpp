#include "SinglePlayerScene.h"
#include "LevelCreator.h"
#include "TextComponent.h"
#include "ScoreDisplayComponent.h"
#include "LivesDisplayComponent.h"
#include "SpriteCompenent.h"
#include "CollisionComponent.h"
#include "PengoComponent.h"
#include "InputManager.h"
#include "CustomCommands.h"
#include "WallComponent.h"
#include "GridComponent.h"
#include "EnemyManager.h"
#include "WallManagers.h"
#include "Timer.h"




dae::SinglePlayerScene::SinglePlayerScene(const std::string& name) : Scene(name)
{

}

void dae::SinglePlayerScene::Initialize()
{



	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", this);

	CreatePlayer(font);
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };
	CreateInfo(font, pos2, pos);

	Scene::Initialize();


}

void dae::SinglePlayerScene::Update()
{


	if (dae::EnemyManager::GetInstance().GetEnemies().size() < 5 && dae::WallManager::GetInstance().GetSpawners().size() != 0)
	{
		m_Elapsed += dae::Time::GetInstance().GetDeltaTime();

		if (m_Elapsed >= m_SpawnTimer)
		{
			auto spawner = dae::WallManager::GetInstance().GetSpawners().front();
			if (spawner->GetType() == WallComponent::WallType::MoveableWall)
			{
				spawner->CreateSpawner(false);
				spawner->SetWallType(dae::WallComponent::WallType::Ground);
				if (spawner->GetGameObject() && spawner->GetGameObject()->GetComponent<SpriteComponent>())
				{
					
					spawner->GetGameObject()->GetComponent<SpriteComponent>()->SetVisibility(false);
				}
				if (spawner->GetGameObject() && spawner->GetGameObject()->GetComponent<dae::CollisionComponent>())
				{

					spawner->GetGameObject()->GetComponent<CollisionComponent>()->Disable();
				}

				SDL_Rect src{ 0,160,16,16 };
				SDL_Rect dest{ 0,0,20,20 };

				auto go = std::make_shared<dae::GameObject>();
				go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), dest, 0.8f));
				go->AddComponent(new dae::RigidBody(go.get()));
				go->AddComponent(new dae::CollisionComponent(go.get(), dest));
				auto snowbee = new dae::SnoBeeCompontent(go.get(), spawner->GetNr());
				go->AddComponent(snowbee);
				go->SetPosition(spawner->GetCenter().x, spawner->GetCenter().y);
				snowbee->Start();

				this->Add(go);

				m_Elapsed = 0;

			}


		}
	}

	Scene::Update();
}


void dae::SinglePlayerScene::CreatePlayer(std::shared_ptr<dae::Font>& font)
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
	go->SetPosition(50, 150);
	pengo->Start();


	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_SPACE, std::make_shared<dae::PushCommand>(go), 0, dae::InputManager::EInputState::Pressed);



	Add(go);
}


void  dae::SinglePlayerScene::CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos)
{
	auto How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "HOW TO PLAY (Controller)", font));
	How->SetPosition(0, 0);
	Add(How);

	How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "PUSH: X/Space ", font));
	How->SetPosition(pos2.x, pos2.y);
	Add(How);
	How = std::make_shared<dae::GameObject>();
	How->AddComponent(new dae::TextComponent(How.get(), "Points: B ", font));
	How->SetPosition(pos.x, pos.y);
	Add(How);
}
