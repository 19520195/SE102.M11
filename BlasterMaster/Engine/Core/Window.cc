#include "Window.hh"

HWND Window::GetHandle() const
{
	return m_HWindow;
}

HWND Window::Create(int width, int height, std::wstring title, HINSTANCE hInstance)
{
	Register(hInstance);

	m_Title = title;
	m_Width = width;
	m_Height = height;

	m_HWindow = CreateWindow(
		WINDOW_CLASSNAME,
		m_Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_Width,
		m_Height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!m_HWindow)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return NULL;
	}

	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	return m_HWindow;
}

void Window::Show(int cmdShow)
{
	ShowWindow(m_HWindow, cmdShow);
	UpdateWindow(m_HWindow);
}

void Window::Register(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASSNAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
}

LRESULT CALLBACK Window::WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			return EXIT_SUCCESS; 

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
