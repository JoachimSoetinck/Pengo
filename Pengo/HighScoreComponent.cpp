#include "HighScoreComponent.h"
#include <fstream>
#include <algorithm>
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"

dae::HighScoreComponent::HighScoreComponent(dae::GameObject* go, const std::string file) :BaseComponent(go), m_File{ file }
{
	//Adding Scores to list
	ReadFile();
	

}

void dae::HighScoreComponent::Initialize()
{

}

void dae::HighScoreComponent::Update()
{
}

void dae::HighScoreComponent::Render() const
{
}

void dae::HighScoreComponent::FixedUpdate()
{
}

void dae::HighScoreComponent::AddNewScore(int score)
{

	m_Scores.push_back(score);
	std::sort(m_Scores.rbegin(), m_Scores.rend());


	std::ofstream outputFile(m_File);
	if (outputFile.is_open()) {
		for (const int& score : m_Scores) {
			outputFile << score << "\n";
		}
		outputFile.close();
	}
	else {
		std::cout << "Failed to write to the highscores file.\n";

	}
}

void dae::HighScoreComponent::CreateHighscores()
{
	int i = 1;
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	for (auto score : m_Scores)
	{
		auto obj = std::make_shared<GameObject>();
		std::string text = std::to_string(i) + ". " + std::to_string(score);
		obj->AddComponent(new TextComponent(obj.get(), text, font));
		obj->SetPosition(0, 0 + 25 * i);
		m_pGameObject->AddChild(obj);
		++i;

		if (i >= 10)
			break;
	}
}



bool dae::HighScoreComponent::ReadFile()
{
	std::ifstream inputFile(m_File);


	if (inputFile.is_open()) {
		int score;

		while (inputFile >> score) {
			m_Scores.push_back({ score });

		}


		inputFile.close();

	}
	else {
		std::cout << "Failed to open the highscores file.\n";
		return false;
	}


	std::sort(m_Scores.rbegin(), m_Scores.rend());


	return true;

}
