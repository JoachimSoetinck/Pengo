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



void load()
{
	auto Start = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(Start);

	auto scene = std::make_shared<dae::SinglePlayerScene>("Level01");
	dae::SceneManager::GetInstance().AddScene(scene);

	/*scene = std::make_shared<dae::Scene>("Level02");
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
	dae::SceneManager::GetInstance().AddScene(scene);*/


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	

	std::string buttonText{ "Single Player" };
	glm::ivec2 position{ 150,80 };
	CreateButton(buttonText, font2, position, Start);

	buttonText = "COOP";
	position = { 150,170 };
	CreateButton(buttonText, font2, position, Start);

	buttonText = "VERSUS";
	position = { 150,300 };
	CreateButton(buttonText, font2, position, Start);

	
	glm::ivec2 pos{ 0,50 };
	glm::ivec2 pos2{ 0,35 };



	//CreateInfo(font, l1, pos2, pos);


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



int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}