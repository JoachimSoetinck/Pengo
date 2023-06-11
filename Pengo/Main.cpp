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
#include "SinglePlayerScene.h"
#include "CoopScene.h"
#include "VersusScene.h"
#include "HighScoreComponent.h"



void load()
{
	


	auto Start = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(Start);

	auto scores = std::make_shared<dae::Scene>("HighScores");
	dae::SceneManager::GetInstance().AddScene(scores);

	auto scene = std::make_shared<dae::SinglePlayerScene>("Level01",1, "Level02");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::SinglePlayerScene>("Level02", 2, "Level03");
	dae::SceneManager::GetInstance().AddScene(scene);

	scene = std::make_shared<dae::SinglePlayerScene>("Level03", 3, "HighScores");
	dae::SceneManager::GetInstance().AddScene(scene);

	auto coopscene = std::make_shared<dae::CoopScene>("COOP01", 1, "COOP02");
	dae::SceneManager::GetInstance().AddScene(coopscene);

	coopscene = std::make_shared<dae::CoopScene>("COOP02", 2, "COOP03");
	dae::SceneManager::GetInstance().AddScene(coopscene);

	coopscene = std::make_shared<dae::CoopScene>("COOP03", 3, "HighScores");
	dae::SceneManager::GetInstance().AddScene(coopscene);

	auto vScene = std::make_shared<dae::VersusScene>("VERSUS01", 1, "VERSUS02");
	dae::SceneManager::GetInstance().AddScene(vScene);

	vScene = std::make_shared<dae::VersusScene>("VERSUS02", 2, "VERSUS03");
	dae::SceneManager::GetInstance().AddScene(scene);

	vScene = std::make_shared<dae::VersusScene>("VERSUS03", 3, "HighScores");
	dae::SceneManager::GetInstance().AddScene(scene);


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);



	std::string buttonText{ "Single Player" };
	glm::ivec2 position{ 150,80 };
	CreateButton(buttonText, font2, position, Start, "Level01");

	buttonText = "COOP";
	position = { 150,200 };
	CreateButton(buttonText, font2, position, Start, "COOP01");

	buttonText = "VERSUS";
	position = { 150,320 };
	CreateButton(buttonText, font2, position, Start,"VERSUS01");


	
	Start->Initialize();


	auto score = std::make_shared<dae::GameObject>();
	score->AddComponent(new dae::HighScoreComponent(score.get(), "../Data/highscores.txt"));
	score->SetPosition(0, 0);
	scores->Add(score);

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>()); 
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/PushBlokc.mp3");
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/Destroyed.mp3");
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/SnobeeSpawning.mp3");
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/ActClear.mp3");
	dae::ServiceLocator::GetSoundSystem()->AddSound("../Data/Sound/Death.mp3");

	scores->Initialize();

}

void CreateButton(std::string& buttonText, std::shared_ptr<dae::Font>& font2, glm::ivec2& position, std::shared_ptr<dae::Scene>& Start, const std::string level)
{
	auto button = std::make_shared<dae::GameObject>();
	button->AddComponent(new dae::RenderComponent(button.get(), "../Data/Button.png"));
	button->AddComponent(new dae::MenuButtonComponent(button.get(), button->GetComponent<dae::RenderComponent>(), level));
	button->AddComponent(new dae::TextComponent(button.get(), buttonText, font2));
	button->SetPosition(position.x, position.y);
	Start->Add(button);
}



int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}