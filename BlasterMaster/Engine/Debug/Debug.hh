#pragma once

#include <Windows.h>

constexpr int DEBUG_MSG_BUFFER_SIZE = 2048;

class Debug
{
public:
  static void Print(const wchar_t* fmt, ...);
};

#define DEBUG_MSG(...) Debug::Print(__VA_ARGS__)
