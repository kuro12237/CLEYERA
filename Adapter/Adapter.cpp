#include"Adapter.h"


void Adapter::Initialize(const int32_t Width, const int32_t Height)
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

void Adapter::WinMSG(MSG &msg)
{

	WinSetup_->WinMSG(msg);

}

void Adapter::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{
	DXSetup_->BeginFlame(kClientWidth,kClientHeight);
}

void Adapter::EndFlame()
{
	DXSetup_->EndFlame();
}

/// <summary>
/// 三角形の頂点の作成
/// </summary>
/// <param name="vertex"></param>
void Adapter::TriangleVertexCreate(VertexProperty&vertex)
{
	Model_->CreateVertex(vertex);
}

/// <summary>
/// 四角形の頂点作成
/// </summary>
/// <param name="vertex"></param>
void Adapter::RectVartexCreate(RectVertexProrertys& vertex)
{
	Rect_->CreateVertex(vertex);
}

/// <summary>
/// 三角形の描画
/// </summary>
/// <param name="top"></param>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="vertex"></param>
void Adapter::TriangleDraw(Vec4 top, Vec4 left, Vec4 right, VertexProperty vertex)
{
	Model_->Draw( top, left,  right, vertex);
}


/// <summary>
/// 四角形の描画
/// </summary>
/// <param name="左上"></param>
/// <param name="右上"></param>
/// <param name="左下"></param>
/// <param name="右下"></param>
/// <param name="vertex"></param>
void Adapter::RectDraw(Vec4 leftTop, Vec4 rightTop, Vec4 leftDown, Vec4 rightDown, RectVertexProrertys vertex)
{
	Rect_->Draw(leftTop, rightTop, leftDown, rightDown, vertex);
}

/// <summary>
/// 三角形の頂点の解放処理
/// </summary>
/// <param name="vartex"></param>
void Adapter::TriangleRelease(VertexProperty vartex)
{
	Model_->VartexRelease(vartex);

}

void Adapter::RectRelese(RectVertexProrertys vartex)
{
	Model_->VartexRelease(vartex.left);
	Model_->VartexRelease(vartex.right);

}


void Adapter::Deleate()
{

	DXSetup_->Deleate();
	WinSetup_->Deleate();
	DXSetup_->ChackRelease();
}

Adapter::Adapter()
{
	
}

Adapter::~Adapter()
{
	DXSetup_->~DirectXSetup();
	WinSetup_->~WindowsSetup();
}
