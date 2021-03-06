#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Event/KeyboardEvent.hh"
#include "Engine/Renderer/Camera.hh"

class Scene
{
public:
  Scene() = default;

  void SetCamera(Camera camera); 

  Camera             GetCamera() const; 
  Ref<KeyboardEvent> GetKeyboardHandler() const;

  virtual void Update(TimeStep elapsed) = 0;
  virtual void Render(TimeStep elapsed) = 0;

protected:
  size_t             m_ID;
  Camera             m_Camera;
  Ref<KeyboardEvent> m_Keyboard;
};
