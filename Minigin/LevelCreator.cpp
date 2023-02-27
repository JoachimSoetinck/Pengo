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

bool dae::LevelCreator::CreateLevel(const std::wstring& filePath)
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

	const rapidjson::Value& testValue = jsonFile["levelData"];
	int test = testValue.GetInt();
	test;



	return false;
}
