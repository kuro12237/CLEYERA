#pragma once

#include<cassert>
#include<thread>

#include<format>
#include<wrl.h>
#include<cstdint>

#include<numbers>
#include<chrono>
#include<random>

#include<map>
#include<array>
#include<queue>
#include<list>
#include<vector>

#include <variant>

#include<fstream>
#include<sstream>
#include<string>

#include<Windows.h>
#pragma comment(lib,"winmm.lib")

#include"imgui.h"
#include"imgui_impl_dx12.h"
#include"imgui_impl_win32.h"

#pragma region Json

#include<json.hpp>

#pragma endregion

#include<Windows.h>
#pragma comment(lib,"winmm.lib")

#include"imgui.h"
#include"imgui_impl_dx12.h"
#include"imgui_impl_win32.h"

#pragma region DirectX

#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dinput8.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")
#include"DirectXTex/DirectXTex.h"

#pragma endregion

#pragma region assimp

#include <assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#pragma endregion

#pragma region XAudio


#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#pragma endregion

using Microsoft::WRL::ComPtr;
using namespace std;
using namespace std::chrono;

#include"Vector/Vector2.h"
#include"Vector/Vector3.h"
#include"Vector/Vector4.h"

#include"Matrix/Matrix2x2.h"
#include"Matrix/Matrix3x3.h"
#include"Matrix/Matrix4x4.h"

#include"Quaternion/Quaternion.h"