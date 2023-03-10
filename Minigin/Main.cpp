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


void load()
{
	auto scene = std::make_shared<dae::Scene>("StartScene");
	dae::SceneManager::GetInstance().AddScene(scene);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto tc = std::make_shared<dae::GameObject>();
	tc->AddComponent(new dae::TextComponent(tc.get(), "Programming 4 Assignment", font));
	tc->SetPosition(80, 10);

	scene->Add(tc);

	auto go = std::make_shared<dae::GameObject>();
	SDL_Rect src{ 0,0,16,16 };
	go->AddComponent(new SpriteComponent(go.get(), Sprite("Pengo.png", 2, 1, src), { 0,0,20,20 }, 0.8f));
	go->SetPosition(50, 150);

	auto child = std::make_shared<dae::GameObject>();
	src = { 0,0,16,16 };
	child->AddComponent(new SpriteComponent(child.get(), Sprite("Pengo.png", 2, 1, src), { 0,0,20,20 }, 0.8f));
	child->SetPosition(40, 10);

	go->AddChild(child, true);
	scene->Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::RenderComponent(go.get(),"logo.tga"));
	go->AddComponent(new dae::RotationComponent(go.get()));
	go->SetPosition(250, 250);
	scene->Add(go);

	//bool r = dae::LevelCreator::CreateLevel(L"../Data/Levels/Level1.json", scene);
	//dae::InputManager::GetInstance().AddInput(0, dae::KeyBinding{ dae::Button::ButtonA, SDL_SCANCODE_A, dae::InputState::Up }, new dae::TestCommand());
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}