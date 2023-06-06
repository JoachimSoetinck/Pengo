#pragma once
#include "BaseComponent.h"

namespace dae {
	class GameObject;
	
	class HighScoreComponent final : public dae::BaseComponent
	{
	public:
		HighScoreComponent(dae::GameObject* go, const std::string file);

		~HighScoreComponent() override = default;

		HighScoreComponent(const HighScoreComponent& other) = delete;
		HighScoreComponent(HighScoreComponent&& other) noexcept = delete;
		HighScoreComponent& operator=(const HighScoreComponent& other) = delete;
		HighScoreComponent& operator=(HighScoreComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void AddNewScore(int score);
		void CreateHighscores();

	private:
		std::string m_File;
		
		
		std::vector<int> m_Scores;
		bool ReadFile();
	};

	
}


