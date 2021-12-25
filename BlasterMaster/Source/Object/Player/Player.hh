#pragma once
#include "Engine/Core/Object.hh"
#include "Engine/Event/KeyboardEvent.hh"

#include "Resources/Resources.hh"
#include "Object/State.hh"

class Player : public Object 
{
public:
  virtual Ref<KeyboardEvent> GetKeyboard() const;

protected:
  Ref<KeyboardEvent> m_Keyboard;
};

#include "SophiaIII.hh"
#include "JasonS.hh"
