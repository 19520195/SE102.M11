#pragma once

#include <Windows.h>

#undef max
#undef min

#define TO_WSTR(str) std::wstring(str.begin(), str.end())
#define TO_LPWSTR(str) TO_WSTR(str).c_str()

constexpr int DEBUG_MSG_BUFFER_SIZE = 2048;

class Debug
{
public:
  static void Print(const wchar_t* fmt, ...);
};

#define DEBUG_MSG(...) Debug::Print(__VA_ARGS__)
