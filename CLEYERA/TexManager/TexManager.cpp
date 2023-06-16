#include"TexManager.h"

TexManager::TexManager()
{
}

TexManager::~TexManager()
{
}

void TexManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

}

void TexManager::EndFlame()
{

	CoUninitialize();
}
