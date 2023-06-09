#include"Adapter/Adapter.h"
#define Triangle_Property_MAX 15




struct  TriangleProperty
{
	Vec4 top;
	Vec4 left;
	Vec4 right;
	VertexProperty vertexData;
};

struct  RectProperty
{
	Vec4 leftTop;
	Vec4 rightTop;
	Vec4 leftDown;
	Vec4 rightDown;
	RectVertexProrertys vartexData;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	Adapter* adapter_ = new Adapter;

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;


	TriangleProperty TriangleProperty_[Triangle_Property_MAX];
	{
		TriangleProperty_[0] =
		{

			{-0.8f,1.0f,0.0f,1.0f },
			{-1.0f,0.5f,0.0f,1.0f },
			{-0.6f,0.5f,0.0f,1.0f },
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

	adapter_->Initialize(kClientWidth, kClientHeight);




	for (int i = 0; i < Triangle_Property_MAX; i++)
	{

		adapter_->TriangleVertexCreate(TriangleProperty_[i].vertexData);
	}


	RectProperty rect;
	{
		 //rect.leftTop={ -0.5f,-0.5f,0.0f,1.0f };
		 //rect.rightTop={  0.5f,-0.5f,0.0f,1.0f };
		 //rect.leftDown= { -0.5f, 0.5f, 0.0f, 1.0f };
		 //{  0.5f,0.5f,0.0f,1.0f };

		rect.leftTop= { -0.5f,0.5f,0.0f,1.0f };
		rect.rightTop = { 0.5f,0.5f,0.0f,1.0f };
		rect.leftDown = { -0.5f,-0.5f,0.0f,1.0f };
		rect.rightDown = { 0.5f,-0.5f,0.0f,1.0f };
		adapter_->RectVartexCreate(rect.vartexData);
	}

	MSG msg{};
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			adapter_->WinMSG(msg);


		}
		else
		{

		}
		adapter_->BeginFlame(kClientWidth,kClientHeight);
		
	
		for (int i = 0; i < Triangle_Property_MAX	; i++)
		{

			//adapter_->TriangleDraw(TriangleProperty_[i].top, TriangleProperty_[i].left, TriangleProperty_[i].right,TriangleProperty_[i].vertexData);
			

		}
		adapter_->RectDraw(rect.leftTop, rect.rightTop, rect.leftDown, rect.rightDown, rect.vartexData);

		adapter_->EndFlame();

		
	}

	//’¸“_‚Ì‰ð•ú
	for (int i = 0; i < Triangle_Property_MAX; i++)
	{
		adapter_->TriangleRelease(TriangleProperty_[i].vertexData);
	}
	adapter_->RectRelese(rect.vartexData);

	adapter_->Deleate();
	adapter_->~Adapter();

	return 0;
}