#pragma once

void CreatePlayer(std::shared_ptr<dae::Font>& font, std::shared_ptr<dae::Scene>& scene, std::shared_ptr<dae::GameObject>& go);

void CreateInfo(std::shared_ptr<dae::Font>& font, std::shared_ptr<dae::Scene>& scene, glm::ivec2& pos2, glm::ivec2& pos);

void CreateButton(std::string& buttonText, std::shared_ptr<dae::Font>& font2, glm::ivec2& position, std::shared_ptr<dae::Scene>& Start);
