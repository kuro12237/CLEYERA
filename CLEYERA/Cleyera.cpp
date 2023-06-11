#include"Cleyera.h"


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
	DXSetup_->CreateSwapChain(Width,Height,WinSetup_->SetHwnd());
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
}

void Cleyera::WinMSG(MSG &msg)
{

	WinSetup_->WinMSG(msg);

}

void Cleyera::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{
	DXSetup_->BeginFlame(kClientWidth,kClientHeight);
}

void Cleyera::EndFlame()
{
	DXSetup_->EndFlame();
}

/// <summary>
/// 三角形の頂点の作成
/// </summary>
/// <param name="vertex"></param>
void Cleyera::TriangleVertexCreate(BufferResource&vertex)
{
	Model_->CreateVertex(vertex);
}

/// <summary>
/// 四角形の頂点作成
/// </summary>
/// <param name="vertex"></param>
void Cleyera::RectVartexCreate(RectBufferResource& vertex)
{
	Rect_->BufferCreate(vertex);
}

/// <summary>
/// 三角形の描画
/// </summary>
/// <param name="top"></param>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="vertex"></param>
void Cleyera::TriangleDraw(Vector4 top, Vector4 left, Vector4 right, unsigned int ColorCode, BufferResource vertex)
{
	Model_->Draw( top, left,  right,ColorCode,vertex);
}


/// <summary>
/// 四角形の描画
/// </summary>
/// <param name="左上"></param>
/// <param name="右上"></param>
/// <param name="左下"></param>
/// <param name="右下"></param>
/// <param name="vertex"></param>
void Cleyera::RectDraw(Vector4 leftTop, Vector4 rightTop, Vector4 leftDown, Vector4 rightDown, unsigned int ColorCode, RectBufferResource vertex)
{
	Rect_->Draw(leftTop, rightTop, leftDown, rightDown,ColorCode, vertex);
}

/// <summary>
/// 三角形の頂点の解放処理
/// </summary>
/// <param name="vartex"></param>
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

	DXSetup_->Deleate();
	WinSetup_->Deleate();
	DXSetup_->ChackRelease();
}

Cleyera::Cleyera()
{
	
}

Cleyera::~Cleyera()
{
	DXSetup_->~DirectXSetup();
	WinSetup_->~WindowsSetup();
}
