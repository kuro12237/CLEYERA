#pragma once
#include"Pch.h"
#include"ModelObjData.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Graphics/NormalMap/NormalMap.h"
#include<vector>

class ModelManager
{
public:

	static ModelManager* GetInstance();

	static void Initialize();

	static void Finalize();

	/// <summary>
	/// NormalMapを読み込む際LLOadObjFile関数の前にこれを呼び出す
	/// </summary>
	static void ModelLoadNormalMap();

	static void ModelUseSubsurface();

	/// <summary>
	/// objファイルの読み込み
	/// </summary>
	/// <param name="Modelfileの中のファイル名"></param>
	/// <returns></returns>
	static uint32_t LoadObjectFile(string directoryPath);

	/// <summary>
	/// ハンドルのobjデータのGet
	/// </summary>
	static SModelData GetObjData(uint32_t index);

	static Model* GetModel(uint32_t index);

private:

	static bool ChackLoadObj(string filePath);

	static bool checkLoadNormalMap(const string filePath);

	map<string,unique_ptr<ModelObjData>>objModelDatas_;
	uint32_t objHandle_ = 0;

	bool isLoadNormalMap_ = false;
	bool isUsesubsurface_ = false;

#pragma region 
	//Singleton
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	const ModelManager& operator=(const ModelManager&) = delete;
#pragma endregion 

};

