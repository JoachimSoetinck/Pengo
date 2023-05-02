#pragma once
#include "Singleton.h"
#include "MiniginPCH.h"
#include "GameObject.h"

namespace dae
{

	class GameInfo final : public Singleton<GameInfo>
	{
	public:
		GameInfo();
		~GameInfo() = default;
		

		int GetNrOfRows() const { return NrOfRows; };
		int GetNrOfColumns() const { return NrOfColums; };

		SDL_Rect GetCollisionSize() const { return m_CollisionSize; };
		SDL_Rect GetPlayerSize() const { return m_PlayerSize; };
		GameObject* GetGridObj() const { return m_ParentGrid; };

		void SetRows(int rows) { NrOfRows = rows; };
		void SetColumns(int cols) { NrOfColums = cols; };
		void SetGameObject(GameObject* obj) { m_ParentGrid = obj; };

	private:
		int NrOfRows;
		int NrOfColums;

		SDL_Rect m_CollisionSize{0,0,24,24};
		SDL_Rect m_PlayerSize{0,0,25,25};

		GameObject*  m_ParentGrid;

	
	};

}

