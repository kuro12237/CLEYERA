#pragma once
#include"Setup/WinSetup.h"
#include "Setup/DirectXSetup.h"
#include"Draw/Model.h"
#include"Draw/Rect.h"
#include"Struct.h"
class Cleyera
{
public:
	Cleyera();
	~Cleyera();

	/// <summary>
	/// Adapterの初期化
	/// </summary>
	/// <param name="Width"></param>
	/// <param name="Height"></param>
	void Initialize(const int32_t Width, const int32_t Height);

	/// <summary>
	/// WinMessageをWinSetupに送る
	/// </summary>
	/// <param name="msg"></param>
	void WinMSG( MSG &msg);

	/// <summary>
	/// ループの最初に行う処理
	/// </summary>
	/// <param name="kClientWidth"></param>
	/// <param name="kClientHeight"></param>
	void BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight);

	/// <summary>
	/// ループの最終処理
	/// </summary>
	void EndFlame();

	/// <summary>
	/// 三角形の頂点の生成
	/// </summary>
	/// <param name="vertex"></param>
	void TriangleVertexCreate(VertexProperty &vertex);
		

	void RectVartexCreate(RectVertexProrertys &vertex);

	/// <summary>
	/// 三角形の表示
	/// </summary>
	/// <param name="top"></param>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="三角形の頂点"></param>
	void TriangleDraw(Vec4 top, Vec4 left, Vec4 right, VertexProperty vertex);

	/// <summary>
	/// 四角形の表示/// </summary>
	/// <param name="左上"></param>
	/// <param name="右上"></param>
	/// <param name="左下"></param>
	/// <param name="右下"></param>
	/// <param name="vertex"></param>
	void RectDraw(Vec4 lefttop, Vec4 righttop, Vec4 leftdown, Vec4 rightDown, RectVertexProrertys vertex);
	
	/// <summary>
	/// 三角形の頂点の解放処理
	/// </summary>
	/// <param name="vartex"></param>
	void TriangleRelease(VertexProperty vartex);

	void RectRelese(RectVertexProrertys vartex);


	/// <summary>
	/// adapterのデリーと::絶対に先に三角形の頂点をReleaseすること
	/// </summary>
	void Deleate();

private:


	WindowsSetup* WinSetup_ = new WindowsSetup();
	DirectXSetup* DXSetup_ = new DirectXSetup();
	Model* Model_ = new Model();
	Rect* Rect_ = new Rect();


};



