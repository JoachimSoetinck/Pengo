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


dae::VersusScene::VersusScene(const std::string& name, int level):Scene(name)
{
}

dae::VersusScene::~VersusScene()
{
}

void dae::VersusScene::Initialize()
{

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", this);

	CreatePlayer(font);
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };
	CreateInfo(font, pos2, pos);

	Scene::Initialize();
}

void dae::VersusScene::CreatePlayer(std::shared_ptr<dae::Font>& font)
{
}

void dae::VersusScene::CreateInfo(std::shared_ptr<dae::Font>& font, glm::ivec2& pos2, glm::ivec2& pos)
{
}
