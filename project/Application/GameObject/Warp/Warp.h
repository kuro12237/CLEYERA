#pragma once
#include"primitive/LineModel.h"

#include"WarpGate/WarpGate.h"
#include"WarpRuate/WarpRuate.h"

class Warp
{
public:
	Warp() {};
	~Warp() {};

	void Initlaize();

	void ImGuiUpdate();

	void Update();

	void DebugDrawLine();

#pragma region Get

	WarpGate* GetWarpGate(){ return warpGate_.get(); }

#pragma endregion


private:

	unique_ptr<Primitive::LineModel>line_ = nullptr;
	unique_ptr<Game3dObject>railPointGameObject_ = nullptr;

    shared_ptr<WarpGate>warpGate_ = nullptr;
	unique_ptr<WarpRuate>warpRute_ = nullptr;

	RailData p_RailData_ = {};

	
};