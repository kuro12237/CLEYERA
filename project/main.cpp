#include"GameManager.h"

/// <summary>
/// ƒƒCƒ“ŠÖ”
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	unique_ptr<GameManager>gameManager_ = make_unique<GameManager>();
	gameManager_->Run();
	return 0;
}