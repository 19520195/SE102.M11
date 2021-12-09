#pragma once

#include <Windows.h>
#include "Engine/Core/Object.hh"

class KeyboardEvent
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int code) = 0;
	virtual void OnKeyUp(int code) = 0;
	virtual void SetPlayer(Object* player);

protected:
	Object* m_Player;
};
