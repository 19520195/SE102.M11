#include "Debug.hh"
#include <cstdio>
#include <cstdarg>

void Debug::Print(const wchar_t* fmt, ...)
{
  // Create print buffer
  wchar_t msg[DEBUG_MSG_BUFFER_SIZE];

  // Parse arguments
  va_list args;
  va_start(args, fmt);
  vswprintf_s(msg, fmt, args);
  va_end(args);

  // Print debug
  OutputDebugString(msg);
}
