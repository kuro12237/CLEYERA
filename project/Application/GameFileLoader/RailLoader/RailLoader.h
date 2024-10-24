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
/// ���[���f�[�^��ǂݍ��݃N���X
/// </summary>
class RailLoader
{
public:

	/// <summary>
	/// �ǂݍ��݃N���X
	/// </summary>
	static RailData LoadRail(const string& filePath);

private:

	/// <summary>
	/// S,R,T�̓ǂݍ��݊֐�
	/// </summary>
	static TransformEular GetWorldTransform(nlohmann::json transform);
};

