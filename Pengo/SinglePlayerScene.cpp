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
#include "HighScoreComponent.h"
#include "SimpleAIComponent.h"




dae::SinglePlayerScene::SinglePlayerScene(const std::string& name, int levelToload, const std::string& nextLevel) : Scene(name), m_NextLevel{ nextLevel }, m_Player1{ nullptr }, m_Level{ levelToload }
{
}

void dae::SinglePlayerScene::Initialize()
{
	std::wstring myString = L"data";
	std::wstring extension = L".json";
	std::wstring level = L"../Data/Levels/Level" + std::to_wstring(m_Level)  + extension;

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	dae::WallManager::GetInstance().ClearWalls();

	bool r = dae::LevelCreator::CreateLevel(level, this);

	CreatePlayer(font);
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };
	CreateInfo(font, pos2, pos);

	Scene::Initialize();


}

void dae::SinglePlayerScene::Update()
{


	HandleEnemies();
	HandleDeath();
	HandleWinningState();

	Scene::Update();
}

void dae::SinglePlayerScene::HandleWinningState()
{
	if (dae::EnemyManager::GetInstance().GetEnemies().size() == 0 && dae::WallManager::GetInstance().GetSpawners().size() == 0)
	{

		GoToNextLevel();
	}
}

void dae::SinglePlayerScene::HandleDeath()
{
	if (m_Player1->GetLives() == 0)
	{
		auto scene = dae::SceneManager::GetInstance().GetScene("HighScores");
		for (auto o : scene->GetObjects())
		{
			if (o->GetComponent<dae::HighScoreComponent>())
			{
				o->GetComponent<dae::HighScoreComponent>()->AddNewScore(m_Player1->GetScore());
				o->GetComponent<dae::HighScoreComponent>()->CreateHighscores();

			}
		}
		dae::SceneManager::GetInstance().SetActiveScene("HighScores");
	}
}

void dae::SinglePlayerScene::HandleEnemies()
{
	if (dae::EnemyManager::GetInstance().GetEnemies().size() < m_NrOfEnemiesInLevel && dae::WallManager::GetInstance().GetSpawners().size() != 0)
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

				go->AddComponent(new dae::SimpleAIComponent(go.get()));
				this->Add(go);

				m_Elapsed = 0;

			}

		}
	}
}

void dae::SinglePlayerScene::GoToNextLevel()
{
	dae::InputManager::GetInstance().ClearControlls();

	auto s = dae::SceneManager::GetInstance().GetScene(m_NextLevel);
	Sleep(100);

	s->Initialize();

	for (auto o : s->GetObjects())
	{
		if (o->GetComponent<PengoComponent>())
		{

			o->GetComponent<PengoComponent>()->Start();
			o->GetComponent<PengoComponent>()->GivePoints(m_Player1->GetScore());


		}

		else if (o->GetComponent<HighScoreComponent>())
		{
			o->GetComponent<HighScoreComponent>()->AddNewScore(m_Player1->GetScore());
			o->GetComponent<HighScoreComponent>()->CreateHighscores();
		}
	}
	ClearLevel();
	dae::SceneManager::GetInstance().SetActiveScene(m_NextLevel);
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
	m_Player1 = pengo;

	dae::InputManager::GetInstance().AddPlayer(false);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADDown, SDL_SCANCODE_DOWN, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Down), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADUp, SDL_SCANCODE_UP, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Up), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADRight, SDL_SCANCODE_RIGHT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Right), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonDPADLeft, SDL_SCANCODE_LEFT, std::make_shared<dae::MoveCommand>(go, dae::PengoComponent::PengoState::Left), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonX, SDL_SCANCODE_SPACE, std::make_shared<dae::PushCommand>(go), 0, dae::InputManager::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(dae::XboxController::Button::ButtonLeftThumb, SDL_SCANCODE_F1, std::make_shared<dae::GoToNextLevelCommand>(go, m_NextLevel), 0, dae::InputManager::EInputState::Pressed);



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
