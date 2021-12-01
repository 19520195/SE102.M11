#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Event/KeyboardEvent.hh"
#include "Engine/Renderer/Camera.hh"

class Scene
{
public:
  Scene() = default;

  KeyboardEvent* GetKeyboardHandler() const;

  virtual void Update(TimeStep step) = 0;
  virtual void Render(TimeStep elapsed) = 0;

protected:
  size_t          m_ID;
  Camera          m_Camera;
  KeyboardEvent*  m_KeyboardHandler;
};
