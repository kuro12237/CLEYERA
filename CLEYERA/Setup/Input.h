#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


class Input
{
public:
	Input();
	~Input();


	void Initialize();

private:

};
