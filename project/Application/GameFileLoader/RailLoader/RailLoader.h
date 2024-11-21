#pragma once
#include"Utility/LevelData/LevelData.h"
#include"Utility/FileLoader/FileLoader.h"

struct RailData
{
	vector<Engine::Transform::WorldTransform>data;
	size_t size = 0;
	string fileName = "";
};

/// <summary>
/// レールデータを読み込みクラス
/// </summary>
class RailLoader
{
public:

	/// <summary>
	/// 読み込みクラス
	/// </summary>
	static RailData LoadRail(const string& filePath);

private:

	/// <summary>
	/// S,R,Tの読み込み関数
	/// </summary>
	static Engine::Transform::TransformEular GetWorldTransform(nlohmann::json transform);
};

