#include "HighScoreComponent.h"
#include <fstream>
#include <algorithm>

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


	std::ofstream outputFile("highscores.txt");
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
