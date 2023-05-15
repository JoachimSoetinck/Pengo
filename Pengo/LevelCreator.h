#pragma once
#include <string>
#include "MiniginPCH.h"



namespace dae
{
	class Scene;
	class LevelCreator final
	{
	public:
		static bool CreateLevel(const std::wstring& filePath, Scene* scene);
	};
}


#pragma once
