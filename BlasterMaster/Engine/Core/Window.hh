#pragma once

#include <Windows.h>
#include <string>

constexpr int      WINDOW_LOCATION_X  = 8;
constexpr int      WINDOW_LOCATION_Y  = 8;
constexpr wchar_t  WINDOW_CLASSNAME[] = (L"ONYX_ENGINE_CLASS");

class Window
{
public:
  HWND GetHandle() const;
  
  HWND Create(int width, int height, std::wstring title, HINSTANCE hInstance);

  void Show(int cmdShow);
  
  static void Register(HINSTANCE hInstance);

  static LRESULT CALLBACK WindowProc(_In_ HWND   hwnd,
                                     _In_ UINT   uMsg,
                                     _In_ WPARAM wParam,
                                     _In_ LPARAM lParam);

  
  
private:
  HWND m_HWindow;

  int          m_Width;
  int          m_Height;
  std::wstring m_Title;
};

