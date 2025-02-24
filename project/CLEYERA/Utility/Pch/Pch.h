#pragma once

/// コンパイルファイル

#include <cassert>
#include <thread>

#include <cstdint>
#include <format>
#include <wrl.h>

#include <chrono>
#include <numbers>
#include <random>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include <vector>

#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "imgui.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"

#pragma region Json

#include <json.hpp>

#pragma endregion

#pragma comment(lib, "winmm.lib")

#include "imgui.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"

#pragma region DirectX

#include "DirectXTex/d3dx12.h"
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxcapi.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <wrl.h>
#pragma comment(lib, "d3dcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
#include <Xinput.h>
#include <dinput.h>
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")
#include "DirectXTex/DirectXTex.h"

#pragma endregion

#pragma region assimp

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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
#pragma comment(lib, "xaudio2.lib")

#pragma endregion

using Microsoft::WRL::ComPtr;
using namespace std;
using namespace std::chrono;

#include "Vector/Vector2.h"
#include "Vector/Vector3.h"
#include "Vector/Vector4.h"

#include "Matrix/Matrix2x2.h"
#include "Matrix/Matrix3x3.h"
#include "Matrix/Matrix4x4.h"

#include "Quaternion/Quaternion.h"