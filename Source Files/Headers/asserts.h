#pragma once
#include "pch.h"
#include <comdef.h>

#pragma comment(lib, "comsuppwd.lib")

void reportAssertionFailure(HRESULT hr, const char* error, const char* file, int line);

#ifndef NDEBUG
      
      #define ASSERT(hr, expr) if (FAILED(hr)){reportAssertionFailure(hr, #expr, __FILE__, __LINE__); __debugbreak();} else{}
      #define ASSERT_INFO(expr) OutputDebugStringW(L"\+\+\+\> \n[INFO]: "); OutputDebugStringW(expr); OutputDebugStringW(L": created!\n");
#else

      #define ASSERT     (...) 
      #define ASSERT_INFO(...)

#endif



