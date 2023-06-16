
#include"ImGuiManager.h"


ImGuiManager::ImGuiManager()
{
}

void ImGuiManager::Initialize(WindowsSetup* WinSetup_, DirectXSetup* DXSetup_)
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(WinSetup_->GetHwnd());
	ImGui_ImplDX12_Init(
		DXSetup_->GetDevice(),
		DXSetup_->GeSwapChainDesc().BufferCount,
		DXSetup_->GetRTV().rtvDesc.Format,
		DXSetup_->GetSrvDescripterHeap(),
		DXSetup_->GetSrvDescripterHeap()->GetCPUDescriptorHandleForHeapStart(),
		DXSetup_->GetSrvDescripterHeap()->GetGPUDescriptorHandleForHeapStart()

	);
}

void ImGuiManager::BeginFlame(DirectXSetup *DXSetup_)
{

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	ID3D12DescriptorHeap* descripterHeap[] = { DXSetup_->GetSrvDescripterHeap()};
	DXSetup_->GetCommands().List->SetDescriptorHeaps(1, descripterHeap);

}

void ImGuiManager::EndFlame(DirectXSetup* DXSetup_)
{
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DXSetup_->GetCommands().List);

}

void ImGuiManager::Release()
{
	ImGui_ImplDX12_Shutdown();
}


