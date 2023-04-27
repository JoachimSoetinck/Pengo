#pragma once
#include "BaseComponent.h"

class GameObject;

class GridComponent final : public dae::BaseComponent
{
public:
	GridComponent(dae::GameObject* go, int columns, int rows, std::vector<int> specialBlocks ,glm::ivec2 startPos = {150,150}, SDL_Rect dest = {0,0,25,25});

	~GridComponent() override = default;

	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) noexcept = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) noexcept = delete;

	void Initialize() override;
	void Update() override;
	void Render() const override;
	void FixedUpdate() override;

private:
	int m_rows, m_colums;
	SDL_Rect m_BlockSize;
	glm::ivec2 m_startPos;
	std::vector<int> m_Wallpositions;


};



