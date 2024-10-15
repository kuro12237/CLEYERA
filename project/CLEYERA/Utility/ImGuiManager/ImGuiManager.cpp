#include"ImGuiManager.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;

ImGuiManager::ImGuiManager()
{
}

ImGuiManager::~ImGuiManager()
{
}

void ImGuiManager::Initialize()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();


	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Resources/Default/font/komorebiGothic/komorebi-gothic-P.ttf", 13.0f, nullptr, glyphRangesJapanese);
	

	ImGui_ImplWin32_Init(WinApp::GetInstance()->GetHwnd());
	ImGui_ImplDX12_Init(
		DirectXCommon::GetInstance()->GetDevice(),
		DirectXCommon::GetInstance()->GetswapChain().swapChainDesc.BufferCount,
		DirectXCommon::GetInstance()->GetRtv().rtvDesc.Format,
		DirectXCommon::GetInstance()->GetSrvHeap(),
		DirectXCommon::GetInstance()->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		DirectXCommon::GetInstance()->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart()

	);
}

void ImGuiManager::BeginFlame()
{

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ID3D12DescriptorHeap* descripterHeap[] = { DirectXCommon::GetInstance()->GetSrvHeap()};
	DirectXCommon::GetInstance()->GetCommands().m_pList->SetDescriptorHeaps(1, descripterHeap);

}

void ImGuiManager::EndFlame()
{
	
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DirectXCommon::GetInstance()->GetCommands().m_pList.Get());

}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX12_Shutdown();
}
