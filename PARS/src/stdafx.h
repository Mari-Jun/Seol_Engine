#pragma once

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <Windows.h>
#include <windowsx.h>

#include <wrl.h>
#include <shellapi.h>

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_4.h>
#include <dxgidebug.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

using Microsoft::WRL::ComPtr;

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <array>
#include <charconv>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <limits>
#include <filesystem>
#include <typeinfo>
#include <chrono>
#include <iomanip>

#include "PARS/Core/Log.h"

static std::string ENGINE_CONTENT_DIR = "../EngineContents";
static std::string CONTENT_DIR = "../Contents";
static std::string LEVEL_DIR = "../Levels";

