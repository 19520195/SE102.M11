#pragma once
#include "Engine/Core/Object.hh"
#include "Engine/Core/Input.hh"
#include "Object/State.hh"

class Player : public Object 
{
public:
  virtual Ref<KeyboardEvent> GetKeyboard() const;

protected:
  Ref<KeyboardEvent> m_Keyboard;
};

#include "SophiaIII.hh"
#include "Jason.hh"
