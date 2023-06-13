#pragma once
#include"Setup/WinSetup.h"
#include "Setup/DirectXSetup.h"
#include"Setup/SceneSetup.h"
#include"Draw/Model.h"
#include"Draw/Rect.h"
#include"CleyeraStruct.h"


#include<string>
#include<format>
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
	void TriangleResourceCreate(BufferResource &bufferResource);
		
	/// <summary>
	/// 四角形の頂点の作成
	/// </summary>
	/// <param name="bufferResource"></param>
	void RectResourceCreate(RectBufferResource &bufferResource);

	/// <summary>
	/// 三角形の表示
	/// </summary>
	/// <param name="top"></param>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="三角形の頂点"></param>
	void TriangleDraw(Vector4 top, Vector4 left, Vector4 right, unsigned int ColorCode, Matrix4x4 matrixTransform, BufferResource vertex);

	/// <summary>
	/// 四角形の表示/// </summary>
	/// <param name="左上"></param>
	/// <param name="右上"></param>
	/// <param name="左下"></param>
	/// <param name="右下"></param>
	/// <param name="vertex"></param>
	void RectDraw(Vector4 lefttop, Vector4 righttop, Vector4 leftdown, Vector4 rightDown, unsigned int ColorCode, Matrix4x4 matrixTransform, RectBufferResource vertex);
	
	/// <summary>
	/// カメラ位置更新処理
	/// </summary>
	/// <param name="cameraTransform"></param>
	void CameraUpdate(Transform cameraTransform);

	/// <summary>
	/// 三角形の頂点の解放処理
	/// </summary>
	/// <param name="vartex"></param>
	void TriangleRelease(BufferResource vartex);

	/// <summary>
	/// 四角形の頂点解放処理
	/// </summary>
	/// <param name="vartex"></param>
	void RectRelese(RectBufferResource vartex);


	/// <summary>
	/// CleyeraEngineの解放
	/// </summary>
	void Deleate();

	void ConvertNormalise();




	
private:


	WindowsSetup* WinSetup_ = new WindowsSetup();
	DirectXSetup* DXSetup_ = new DirectXSetup();
	ScenceSetup* SceSetup_ = new ScenceSetup();
	Model* Model_ = new Model();
	Rect* Rect_ = new Rect();



	//
	VectorTransform* vectorTransform_ = new VectorTransform();
	MatrixTransform* matrixTransform_ = new MatrixTransform();

	
};



