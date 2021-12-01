#pragma once

#include <Windows.h>

class KeyboardEvent
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int code) = 0;
	virtual void OnKeyUp(int code) = 0;
};
