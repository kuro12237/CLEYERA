#include"CLEYERA/Cleyera.h"
#define Triangle_Property_MAX 15

#include"CLEYERA/Matrix/MatrixTransform.h"
#include"CLEYERA/Vector/VectorTransform.h"



struct  TriangleProperty
{
	Vector4 top;
	Vector4 left;
	Vector4 right;
	Matrix4x4 matrixTransform;
	BufferResource ResourceData;
};

struct  RectProperty
{
	Vector4 leftTop;
	Vector4 rightTop;
	Vector4 leftDown;
	Vector4 rightDown;
	Matrix4x4 matrixTransform;
	RectBufferResource ResourceData;
};




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	
	
	Cleyera* Cleyera_ = new Cleyera;

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	MatrixTransform* matrixTransform_ = new MatrixTransform();
	VectorTransform* VectorTransform_ = new VectorTransform();

	Cleyera_->Initialize(kClientWidth, kClientHeight);

    //初期化


	TriangleProperty TriangleProperty_[Triangle_Property_MAX];
	{
		TriangleProperty_[0] =
		{


		{ -0.5f,0.5f,0.0f,1.0f },
		{ 0.5f,0.5f,0.0f,1.0f },
		{ -0.5f,-0.5f,0.0f,1.0f }
		};
		TriangleProperty_[1] =
		{

			{-0.4f,1.0f,0.0f,1.0f },
			{-0.6f,0.5f,0.0f,1.0f },
			{-0.2f,0.5f,0.0f,1.0f }
		};
		TriangleProperty_[2] =
		{

			{0.0f,1.0f,0.0f,1.0f },
			{-0.2f,0.5f,0.0f,1.0f },
			{0.2f,0.5f,0.0f,1.0f }
		};
		TriangleProperty_[3] =
		{

			{0.4f,1.0f,0.0f,1.0f },
			{0.2f,0.5f,0.0f,1.0f },
			{0.6f,0.5f,0.0f,1.0f }
		};
		TriangleProperty_[4] =
		{

			{0.8f,1.0f,0.0f,1.0f },
			{0.6f,0.5f,0.0f,1.0f },
			{1.0f,0.5f,0.0f,1.0f }
		};

		TriangleProperty_[5] =
		{

			{-0.8f,0.5f,0.0f,1.0f },
			{-1.0f,0.0f,0.0f,1.0f },
			{-0.6f,0.0f,0.0f,1.0f }
		};
		TriangleProperty_[6] =
		{

			{-0.4f,0.5f,0.0f,1.0f },
			{-0.6f,0.0f,0.0f,1.0f },
			{-0.2f,0.0f,0.0f,1.0f }
		};
		TriangleProperty_[7] =
		{

			{0.0f,0.5f,0.0f,1.0f },
			{-0.2f,0.0f,0.0f,1.0f },
			{0.2f,0.0f,0.0f,1.0f }
		};
		TriangleProperty_[8] =
		{

			{0.4f,0.5f,0.0f,1.0f },
			{0.2f,0.0f,0.0f,1.0f },
			{0.6f,0.0f,0.0f,1.0f }
		};
		TriangleProperty_[9] =
		{

			{0.8f,0.5f,0.0f,1.0f },
			{0.6f,0.0f,0.0f,1.0f },
			{1.0f,0.0f,0.0f,1.0f }
		};

		TriangleProperty_[10] =
		{

			{-0.8f,0.0f,0.0f,1.0f },
			{-1.0f,-0.5f,0.0f,1.0f },
			{-0.6f,-0.5f,0.0f,1.0f }
		};
		TriangleProperty_[11] =
		{

			{-0.4f,0.0f,0.0f,1.0f },
			{-0.6f,-0.5f,0.0f,1.0f },
			{-0.2f,-0.5f,0.0f,1.0f }
		};
		TriangleProperty_[12] =
		{

			{0.0f,0.0f,0.0f,1.0f },
			{-0.2f,-0.5f,0.0f,1.0f },
			{0.2f,-0.5f,0.0f,1.0f }
		};
		TriangleProperty_[13] =
		{

			{0.4f,0.0f,0.0f,1.0f },
			{0.2f,-0.5f,0.0f,1.0f },
			{0.6f,-0.5f,0.0f,1.0f }
		};
		TriangleProperty_[14] =
		{

			{0.8f,0.0f,0.0f,1.0f },
			{0.6f,-0.5f,0.0f,1.0f },
			{1.0f,-0.5f,0.0f,1.0f }
		};

	}

	
	TriangleProperty_[0] =
	{
	{ -0.5f,0.5f,0.0f,1.0f },

	{ -0.5f,-0.5f,0.0f,1.0f},
	{ 0.5f,-0.5f,0.0f,1.0f }
	};

	for (int i = 0; i < 2; i++)
	{
		TriangleProperty_[i].matrixTransform = matrixTransform_->Identity();
		Cleyera_->TriangleResourceCreate(TriangleProperty_[i].ResourceData);
	}


	RectProperty rect;
	{

		rect.leftTop = { -0.5f,0.5f,0.0f,1.0f };
		rect.rightTop = { 0.5f,0.5f,0.0f,1.0f };
		rect.leftDown = { -0.5f,-0.5f,0.0f,1.0f };
		rect.rightDown = { 0.5f,-0.5f,0.0f,1.0f };
		rect.matrixTransform = matrixTransform_->Identity();
		Cleyera_->RectResourceCreate(rect.ResourceData);
	}

	

	MSG msg{};

	float rotate = 0.0f;
	Vector3 translate = {0.03f,0.0f,0.0f};
	float speed = 0.01;

	
	int timer = 0;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			Cleyera_->WinMSG(msg);


		}

		Cleyera_->BeginFlame(kClientWidth, kClientHeight);




		///
		///更新処理
		/// 
		for (int i = 0; i < Triangle_Property_MAX; i++)
		{
			
		}
		rotate += 0.03;
		Transform CameraPosition = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
		timer++;
		if (timer>=120)
		{
			//CameraPosition.translate.z -= 1.0f;
			timer = 0;
		}
	
		Cleyera_->CameraUpdate(CameraPosition);

		if (translate.x<=-2.0f)
		{
			speed = 0.01;
		}if (translate.x >= 2.0f)
		{
			speed = -0.01;
		}
		//translate.x += speed;
		/// 
		/// 更新処理終了
		/// 

		
		///
		///描画処理
		/// 
		Cleyera_->RectDraw(rect.leftTop, rect.rightTop, rect.leftDown, rect.rightDown, 0x6400FFFF, rect.matrixTransform, rect.ResourceData);

		
		for (int i = 0; i < 2; i++)
		{

			Cleyera_->TriangleDraw(TriangleProperty_[i].top, TriangleProperty_[i].left, TriangleProperty_[i].right, RED,
				TriangleProperty_[i].matrixTransform,
				TriangleProperty_[i].ResourceData);
		}


		ImGui::ShowDemoWindow();

		///
		///描画処理終了
		/// 
		Cleyera_->EndFlame();

	}

	//頂点の解放
	for (int i = 0; i < 2; i++)
	{
		Cleyera_->TriangleRelease(TriangleProperty_[i].ResourceData);
	}
	Cleyera_->RectRelese(rect.ResourceData);


	Cleyera_->Deleate();
	delete Cleyera_;

	return 0;
}