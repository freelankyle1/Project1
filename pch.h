#pragma once



#include "Headers/winh.h" //includes windows.h
#include <windowsx.h>

#include <d3d11.h>
//#include <d3dx11.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

#include <wrl.h>
#include <winerror.h>

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <queue>
#include <optional>
#include <chrono>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

struct NonCopyable
{
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};


