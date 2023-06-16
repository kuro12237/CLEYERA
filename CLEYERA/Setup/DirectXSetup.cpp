#include "DirectXSetup.h"


#include"WinSetup.h"
#include<string>
#include<format>





std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}

//Log
void Log(const std::string& message)
{
	OutputDebugStringA(message.c_str());


}







/// <summary>
/// Compiler
/// </summary>
/// <param name="filePath"></param>
/// <param name="profile"></param>
/// <param name="dxcUtils"></param>
/// <param name="dxcCompiler"></param>
/// <param name="includeHandler"></param>
/// <returns></returns>
IDxcBlob* DirectXSetup::CompilerShader(
	//compilerするshaderファイルへのパス
	const std::wstring& filePath,
	//compilerに使用するProfile
	const wchar_t* profile,
	//初期化で生成したものを3つ
	IDxcUtils* dxcUtils,
	IDxcCompiler3* dxcCompiler,
	IDxcIncludeHandler* includeHandler)
{
	//1.hlslファイルを読む

	//これからシェーダーをコンパイルする旨をログに出す
	Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));


	//1.hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);

	//読めなかったら止める
	assert(SUCCEEDED(hr));

	//読み込んだファイルの内容の設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8; //UTF8の文字コードであることを通知


	//2.Compileする
	LPCWSTR arguments[] =
	{
		filePath.c_str(), //コンパイル対象のhlslファイル名
		L"-E",L"main", //エントリーポイントの指定。基本敵にmain以外にはしない
		L"-T",profile, //ShaderProfileの設定
		L"-Zi",L"-Qembed_debug", //デバッグ用の情報を埋め込む
		L"-Od", //最適化を外しておく
		L"-Zpr",//メモリレイアウトは行優先
	};

	//実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	hr = dxcCompiler->Compile(
		&shaderSourceBuffer, //読み込んだファイル
		arguments, //コンパイルオプション
		_countof(arguments), //コンパイルオプションの数
		includeHandler, //includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult) //コンパイル結果
	);

	//コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr));



	//3.警告エラーがでていないか確認する

	//警告、エラーが出てたらログに出して止める
	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);

	if (shaderError != nullptr && shaderError->GetStringLength() != 0)
	{
		Log(shaderError->GetStringPointer());

		//警告・エラーダメゼッタイ
		assert(false);
	}

	//4.Compile結果を受け取って返す

	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));

	//成功したログを出す
	Log(ConvertString(std::format(L"Compile Succeeded, path:{},profile:{}\n", filePath, profile)));

	//もう使わないリソースを解放
	shaderSource->Release();
	shaderResult->Release();

	//実行用のバイナリを返却
	return shaderBlob;

}

ID3D12DescriptorHeap* DirectXSetup::CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType,UINT numDescriptors, bool shaderVisible)
{
	ID3D12DescriptorHeap* descriptHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;
	descriptorHeapDesc.NumDescriptors = numDescriptors;
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptHeap));
	assert(SUCCEEDED(hr));
	return descriptHeap;

}


DirectXSetup::DirectXSetup()
{
	
}

DirectXSetup::~DirectXSetup()
{
	
}



void DirectXSetup::CreateDXGiFactory()
{


    #ifdef _DEBUG


	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		
		debugController->EnableDebugLayer();

		
		debugController->SetEnableGPUBasedValidation(TRUE);

	}
 
    #endif

	//DXGIファクトリーの生成
	dxgiFactory = nullptr;
	hr=CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	assert(SUCCEEDED(hr));
	
	//Adapter

	//いい順にアダプタを頼む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) !=
		DXGI_ERROR_NOT_FOUND; i++)
	{
		
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr)); 

		
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			
			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));
			break;
		}

	
		useAdapter = nullptr;

	}

	assert(useAdapter != nullptr);

}




void DirectXSetup::CreateDevice()
{
   D3D_FEATURE_LEVEL featureLevels[]=
   {
	   D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
   };
   const char* featureLevelStrings[] = { "12.2","12.1","12.0"};

   //高い順に生成できるか試していく
   for (size_t i = 0; i < _countof(featureLevels); i++)
   {
	 
	   hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));

	  
	   if (SUCCEEDED(hr))
	   {
		
		   Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
		   break;

	   }
   }

   assert(device != nullptr);


}

void DirectXSetup::DebugErrorInfoQueue()
{

	ID3D12InfoQueue* infoQueue = nullptr;

	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		//やばいエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);

		//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		//警告時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		//
		//エラーと警告の抑制


		D3D12_MESSAGE_ID denyIds[] =
		{
			//windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互バグによるエラーメッセージ
			//https:,,stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11

			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};

		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;

		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

		//解放
		infoQueue->Release();
	}

}

void DirectXSetup::CreateCommands()
{
	///commands
	//コマンドキューの生成
	commands.Queue = nullptr;
	hr = device->CreateCommandQueue(&commands.QueueDesc, IID_PPV_ARGS(&commands.Queue));
	assert(SUCCEEDED(hr));

	//アローケーターの生成
	commands.Allocator = nullptr;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commands.Allocator));
    assert(SUCCEEDED(hr));
   
	//リストの作成
	commands.List = nullptr;
	hr=device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		commands.Allocator, nullptr,
		IID_PPV_ARGS(&commands.List));
	assert(SUCCEEDED(hr));
}


void DirectXSetup::CreateSwapChain(const int32_t Width,const int32_t Height, HWND hwnd_)
{
    swapChain.swapChain = nullptr;
	
	//スワップチェーンの設定
	swapChainDesc.Width = Width;
	swapChainDesc.Height = Height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2; 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; 


	//スワップチェーンの生成
	hr = dxgiFactory->CreateSwapChainForHwnd(commands.Queue, hwnd_, &swapChainDesc,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&swapChain.swapChain));

	assert(SUCCEEDED(hr));
}


void DirectXSetup::CreatertvDescritorHeap()
{
	rtv.DescritorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, false);
	srvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);

}

void DirectXSetup::CreateSwapChainResorce()
{
	hr = swapChain.swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChain.Resource[0]));

	
	assert(SUCCEEDED(hr));

	hr = swapChain.swapChain->GetBuffer(1, IID_PPV_ARGS(&swapChain.Resource[1]));

	assert(SUCCEEDED(hr));

}

void DirectXSetup::SettingandCreateRTV()
{
	rtv.rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; 
	rtv.rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D; 

	rtv.rtvStartHandle= rtv.DescritorHeap->GetCPUDescriptorHandleForHeapStart();

	rtv.rtvHandles[0] = rtv.rtvStartHandle;
	device->CreateRenderTargetView(swapChain.Resource[0], &rtv.rtvDesc, rtv.rtvHandles[0]);

	
	rtv.rtvHandles[1].ptr = rtv.rtvHandles[0].ptr + device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	device->CreateRenderTargetView(swapChain.Resource[1], &rtv.rtvDesc, rtv.rtvHandles[1]);

  
}


void DirectXSetup::CreateFence()
{
	//フェンスの作成
	fence = nullptr;
	fenceValue = 0;
	hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	assert(SUCCEEDED(hr));


	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent != nullptr);


}




void DirectXSetup::DXCInitialize()
{
	dxc.Compiler = nullptr;
	dxc.Utils = nullptr;

	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxc.Utils));
	assert(SUCCEEDED(hr));

	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxc.Compiler));
	assert(SUCCEEDED(hr));


}


void DirectXSetup::CreatePSO()
{

	IDxcIncludeHandler* includeHandler = nullptr;
	hr = dxc.Utils->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(hr));



	//RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};

	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//Material設定
	D3D12_ROOT_PARAMETER rootParameters[2] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	//VertexのTransform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].Descriptor.ShaderRegister = 0;
	
	
	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);



	//シリアライズしてバイナリにする
	
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}

	//バイナリを元に生成
	
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr));




	//InputLayoutの設定
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);


	//BlendStateの設定を行う
	D3D12_BLEND_DESC blendDesc{};
	//すべての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;


	//RasterrizerStateぼ設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};

	//裏面（時計回り）を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//Shaderをコンパイルする
	vertexShaderBlob = CompilerShader(L"Shader/Object3d.VS.hlsl",
		L"vs_6_0", dxc.Utils, dxc.Compiler, includeHandler);
	assert(vertexShaderBlob != nullptr);

	 pixeShaderBlob = CompilerShader(L"Shader/Object3d.PS.hlsl",
		L"ps_6_0", dxc.Utils, dxc.Compiler, includeHandler);
	assert(pixeShaderBlob != nullptr);

	//PSOの生成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = rootSignature; //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(),
	vertexShaderBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { pixeShaderBlob->GetBufferPointer(),
	pixeShaderBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState


	//書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//利用するトポロジ(形状)のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//どのように画面に色を打ち込むかの設定(気にしなくて良い)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));

	vertexShaderBlob->Release();
	pixeShaderBlob->Release();

	
}




void DirectXSetup::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{
	
	//書き込むスワップチェーンのindexをとる
	UINT backBufferIndex = swapChain.swapChain->GetCurrentBackBufferIndex();
    
	//バリア
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = swapChain.Resource[backBufferIndex];
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	commands.List->ResourceBarrier(1, &barrier);

	//描画先のRTYを設定
	commands.List->OMSetRenderTargets(1, &rtv.rtvHandles[backBufferIndex], false, nullptr);
	
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	//float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };
	commands.List->ClearRenderTargetView(rtv.rtvHandles[backBufferIndex], clearColor, 0, nullptr);
	

}

void DirectXSetup::ScissorViewCommand(const int32_t kClientWidth, const int32_t kClientHeight)
{

	D3D12_VIEWPORT viewport{};

	//クライアント領域のサイズを一緒にして画面全体に表示
	viewport.Width = float(kClientWidth);
	viewport.Height = float(kClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;


	//シザー矩形
	D3D12_RECT scissorRect{};

	//基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = kClientHeight;

	//コマンドを積む
	commands.List->RSSetViewports(1, &viewport); //
	commands.List->RSSetScissorRects(1, &scissorRect);
	commands.List->SetGraphicsRootSignature(rootSignature);
	commands.List->SetPipelineState(graphicsPipelineState);//


}

void DirectXSetup::EndFlame()
{

	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	commands.List->ResourceBarrier(1, &barrier);
	hr = commands.List->Close();
	assert(SUCCEEDED(hr));

	
	ID3D12CommandList* commandLists[] = { commands.List };

	commands.Queue->ExecuteCommandLists(1, commandLists);
    swapChain.swapChain->Present(0, 1);


	//Fence数値加算
	fenceValue++;

	//GPUにシグナル
	commands.Queue->Signal(fence, fenceValue);
	

	if (fence->GetCompletedValue() < fenceValue)
	{
	
		fence->SetEventOnCompletion(fenceValue, fenceEvent);

		
		WaitForSingleObject(fenceEvent, INFINITE);

	}

	swapChain.swapChain->Present(1, 0);


	hr = commands.Allocator->Reset();
	assert(SUCCEEDED(hr));

	hr = commands.List->Reset(commands.Allocator, nullptr);
	assert(SUCCEEDED(hr));

	
	

}



void DirectXSetup::Deleate()
{


	CloseHandle(fenceEvent);
	fence->Release();

	rtv.DescritorHeap->Release();
	srvDescriptorHeap->Release();

	swapChain.Resource[0]->Release();
	swapChain.Resource[1]->Release();
	swapChain.swapChain->Release();


	commands.List->Release();
	commands.Allocator->Release();
	commands.Queue->Release();
	
	device->Release();
	useAdapter->Release();
	dxgiFactory->Release();


	graphicsPipelineState->Release();

	signatureBlob->Release();
	if (errorBlob)
	{
		errorBlob->Release();
	}

	rootSignature->Release();


#ifdef _DEBUG

	debugController->Release();

#endif // _DEBUG


	
}

void DirectXSetup::ChackRelease()
{

	IDXGIDebug1* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
	{
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}


}

