#include"GameManager.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	unique_ptr<GameManager>gameManager_ = make_unique<GameManager>();
	gameManager_->Run();
	return 0;
}