#pragma once

#include <Windows.h>
#include "Engine/Core/Object.hh"

class KeyboardEvent
{
public:
	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int code);
	virtual void OnKeyUp(int code);
};
