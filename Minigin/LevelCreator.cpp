#include "LevelCreator.h"
#include <iostream>
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 33010)
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <filereadstream.h>
#pragma warning(pop)

#include "Scene.h"
#include "SpriteCompenent.h"
#include "CollisionComponent.h"
#include "GridComponent.h"


bool dae::LevelCreator::CreateLevel(const std::wstring& filePath, std::shared_ptr<dae::Scene> scene)
{
	std::wstring fileName = filePath;
	rapidjson::Document jsonFile;
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, fileName.c_str(), L"rb");

	if (pFile != nullptr)
	{
		fseek(pFile, 0, SEEK_END);
		const size_t size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		char* readBuffer = new char[size];
		rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
		jsonFile.ParseStream(inputStream);
		delete[] readBuffer;
		fclose(pFile);
	}

	//const rapidjson::Value& testValue = jsonFile["levelData"];
	const rapidjson::Value& r = jsonFile["BlockColums"];
	const rapidjson::Value& c = jsonFile["BlockRows"];
	const rapidjson::Value& positionBlocks = jsonFile["BlockSpawns"];
	
	auto places = positionBlocks.IsArray();
	std::vector<int> positions;

	for (rapidjson::SizeType i = 0; i < positionBlocks.Size(); i++) // Uses SizeType instead of size_t
		 positions.push_back(positionBlocks[i].GetInt());

	
	SDL_Rect src = { 0,0,30,30 };
	SDL_Rect rect{ 0,0,24,24 };
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new GridComponent(go.get(), r.GetInt(), c.GetInt(),positions));
	go->SetPosition(0, 0);
	scene->Add(go);

	//src = { 0,0,16,24 };
	//for (int i = 0; i < r.GetInt(); ++i)
	//{
	//	
	//	go = std::make_shared<dae::GameObject>();
	//	go->AddComponent(new SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
	//	go->AddComponent(new CollisionComponent(go.get(), rect)); 
	//	go->SetPosition(150 + i * 25, 50);
	//	scene->Add(go);

	//	go = std::make_shared<dae::GameObject>();
	//	go->AddComponent(new SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
	//	go->AddComponent(new CollisionComponent(go.get(), rect)); 
	//	go->SetPosition(150 + i * 25, 50 + (c.GetInt()+1)* 25);
	//	scene->Add(go);
	//}
	//for (int i = -1; i <= c.GetInt(); ++i)
	//{

	//	go = std::make_shared<dae::GameObject>();
	//	go->AddComponent(new SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
	//	go->AddComponent(new CollisionComponent(go.get(), rect)); 
	//	go->SetPosition(125 , 75 + 25 *i);
	//	scene->Add(go);

	//	go = std::make_shared<dae::GameObject>();
	//	go->AddComponent(new SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
	//	go->AddComponent(new CollisionComponent(go.get(), rect));
	//	go->SetPosition(125 + (r.GetInt() + 1) * 25, 75 + 25 * i);
	//	scene->Add(go);


	//}



	return false;
}
