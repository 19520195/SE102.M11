#pragma once

#include <Windows.h>

#undef max
#undef min

constexpr int DEBUG_MSG_BUFFER_SIZE = 2048;

class Debug
{
public:
  static void Print(const wchar_t* fmt, ...);
};

#define DEBUG_MSG(...) Debug::Print(__VA_ARGS__)
