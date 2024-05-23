#pragma once
#include"Pch.h"
#include"FileLoader.h"


class SceneFileLoader
{
public:
	
	static SceneFileLoader* GetInstance();

	void Initlaize();

	void ReLoad(const string& filePath);

private:
	nlohmann::json deserialized = nullptr;


#pragma region 
	//Singleton
	SceneFileLoader() = default;
	~SceneFileLoader() = default;
	SceneFileLoader(const SceneFileLoader&) = delete;
	const SceneFileLoader& operator=(const SceneFileLoader&) = delete;
#pragma endregion 
};
