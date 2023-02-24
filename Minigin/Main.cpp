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

void load()
{
	auto scene = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(scene);
	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Programming 4 Assignment", font));
	tc->SetPosition(80, 20);

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(go.get(), "background.tga"));
	go->SetPosition(0, 0);
	scene->Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(go.get(), "logo.tga"));
	go->SetPosition(216, 180);
	scene->Add(go);

	scene->Add(go);
	scene->Add(tc);


	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent(go.get(), "Programming 4 Assignment", font2));
	go->AddComponent(new dae::FPSComponent(go.get(),go->GetComponent<dae::TextComponent>()));
	go->SetPosition(0, 0);
	scene->Add(go);

	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}