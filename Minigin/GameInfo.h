#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{


	class GameInfo final : public Singleton<GameInfo>
	{
	public:
		GameInfo();
		~GameInfo() = default;
		

		int GetNrOfRows() const { return NrOfRows; };
		int GetNrOfColumns() const { return NrOfColums; };

		void SetRows(int rows) { NrOfRows = rows; };
		void SetColumns(int cols) { NrOfColums = cols; };

	private:
		int NrOfRows;
		int NrOfColums;

	
	};

}

