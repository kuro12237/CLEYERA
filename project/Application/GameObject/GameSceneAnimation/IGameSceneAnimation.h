#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"

#include"Utility/convert/convert.h"
#include"PostEffect/PostEffect.h"

class IGameSceneAnimation
{
public:
	IGameSceneAnimation() { postEffect_ = Engine::PostEffect::GetInstance(), gameObjectManager_ = GameObjectManager::GetInstance(); }
	~IGameSceneAnimation() {};


#pragma region Get
	const bool GetIsCompleteAnimation() { return isCompliteAniamtion_; }
#pragma endregion

protected:

	/// <summary>
	/// スプラインクラスの設定
	/// </summary>
	void SettingSplineMotionData();

	/// <summary>
	/// レールのデータを読み込む
	/// </summary>
	void LoadRailData();

	/// <summary>
	/// フレームの更新しレールのポジションを求める
	/// </summary>
	Math::Vector::Vector3 CalcRailData(const size_t& index,const float& flame);

	void EndUpdate(function<void()>func) { func(); };

	string cameraName_ = "";

	Engine::PostEffect* postEffect_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

	vector<unique_ptr<SplineMotion>>splineMotions_;
	uint32_t splineMotionsMax_ = 0;
	vector<RailData>railData_;

	bool isCompliteAniamtion_ = false;

	uint32_t splineSelectIndex_ = 0;

private :

};
