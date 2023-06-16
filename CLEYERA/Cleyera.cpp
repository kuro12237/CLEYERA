#include"Cleyera.h"

//cleyera//クレイラ
//CLEYERA ENGINE


Cleyera::Cleyera()
{
	WinSetup_ = new WindowsSetup();
	DXSetup_ = new DirectXSetup();
	SceSetup_ = new ScenceSetup();

	Model_ = new Model();
	Rect_ = new Rect();
	ImGuiManager_ = new ImGuiManager();

	vectorTransform_ = new VectorTransform();
	matrixTransform_ = new MatrixTransform();

}

Cleyera::~Cleyera()
{
	delete WinSetup_;
	delete DXSetup_;
	delete SceSetup_;

	delete ImGuiManager_;

	delete Model_;
	delete Rect_;

	delete vectorTransform_;
	delete matrixTransform_;

}

/// <summary>
/// 
/// </summary>
/// <param name="Width"></param>
/// <param name="Height"></param>
void Cleyera::Initialize(const int32_t Width, const int32_t Height)
{
	//windows
	WinSetup_->Initialize(Width,Height);
	//終了

	//DirectX
    DXSetup_->CreateDXGiFactory();

	DXSetup_->CreateDevice();

#ifdef _DEBUG
	//エラー、警告
	DXSetup_->DebugErrorInfoQueue();

#endif // _DEBUG
	
	//CommandList
	DXSetup_->CreateCommands();
	//swapChain
	DXSetup_->CreateSwapChain(Width,Height,WinSetup_->GetHwnd());
	//rtvDescritor
	DXSetup_->CreatertvDescritorHeap();
	//swapChainを引っ張る
	DXSetup_->CreateSwapChainResorce();
	//RTVの設定と作成
	DXSetup_->SettingandCreateRTV();
	//フェンスの生成
	DXSetup_->CreateFence();
	//DXCの初期化
	DXSetup_->DXCInitialize();
	//PSOの生成
	DXSetup_->CreatePSO();
	//終了

	//コマンドとデバイスの情報を送る
	Model_->DirectXSetDevice(DXSetup_->GetDevice());
	Model_->DirectXSetCommands(DXSetup_->GetCommands());

	Rect_->DirectXSetDevice(DXSetup_->GetDevice());
	Rect_->DirectXSetCommands(DXSetup_->GetCommands());
	
	//カメラの初期化
	 
	CameraTransform camera = { {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} },0.0f};
	SceSetup_->SceneInitialize(camera, Width, Height);
	
	
	ImGuiManager_->Initialize(WinSetup_,DXSetup_);

}

void Cleyera::WinMSG(MSG &msg)
{

	WinSetup_->WinMSG(msg);

}




void Cleyera::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{

	DXSetup_->BeginFlame(kClientWidth,kClientHeight);
	DXSetup_->ScissorViewCommand(kClientWidth, kClientHeight);
	ImGuiManager_->BeginFlame(DXSetup_);


}

void Cleyera::EndFlame()
{
	
	ImGuiManager_->EndFlame(DXSetup_);
	DXSetup_->EndFlame();
}


void Cleyera::TriangleResourceCreate(BufferResource&bufferResource)
{
	Model_->CreateVertex(bufferResource);
}


void Cleyera::RectResourceCreate(RectBufferResource& bufferResource)
{
	Rect_->BufferCreate(bufferResource);
}


void Cleyera::TriangleDraw(Vector4 top, Vector4 left, Vector4 right, unsigned int ColorCode, Matrix4x4 matrixTransform, BufferResource bufferResource)
{
	
	Matrix4x4 Scene = SceSetup_->worldViewProjectionMatrixFanc(matrixTransform);

	Model_->Draw( top, left,  right,ColorCode,Scene,bufferResource);
}



void Cleyera::RectDraw(Vector4 leftTop, Vector4 rightTop, Vector4 leftDown, Vector4 rightDown, unsigned int ColorCode, Matrix4x4 matrixTransform, RectBufferResource bufferResouce)
{

	Matrix4x4 Scene = SceSetup_->worldViewProjectionMatrixFanc(matrixTransform);

	Rect_->Draw(leftTop, rightTop, leftDown, rightDown,ColorCode,Scene,bufferResouce);
}

void Cleyera::CameraUpdate(Transform cameraTransform)
{

	SceSetup_->TransformUpdate(cameraTransform);

}

void Cleyera::TriangleRelease(BufferResource Resource)
{
	Model_->VartexRelease(Resource);


}

void Cleyera::RectRelese(RectBufferResource Resource)
{
	Model_->VartexRelease(Resource.left);
	Model_->VartexRelease(Resource.right);

}


void Cleyera::Deleate()
{
	ImGuiManager_->Release();

	DXSetup_->Deleate();
	WinSetup_->Deleate();
	DXSetup_->ChackRelease();
}




