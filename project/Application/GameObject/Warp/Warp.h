#pragma once
#include"primitive/LineModel.h"

#include"WarpGate/WarpGate.h"
#include"WarpRuate/WarpRuate.h"

/// <summary>
/// ワープクラス
/// </summary>
class Warp
{
public:
	Warp() {};
	~Warp() {};

	void Initlaize(uint32_t index);

	void ImGuiUpdate();

	void Update();

	/// <summary>
	/// デバック用の線表示
	/// </summary>
	void DebugDrawLine();

#pragma region Get

	WarpGate* GetWarpGate(){ return warpGate_.get(); }

#pragma endregion


private:

	unique_ptr<Primitive::LineModel>line_ = nullptr;
	unique_ptr<Engine::Objects::Game3dObject>railPointGameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_{};

    shared_ptr<WarpGate>warpGate_ = nullptr;
	unique_ptr<WarpRuate>warpRute_ = nullptr;

	RailData p_RailData_ = {};

	
};