#include "Scene.hh"

Camera Scene::GetCamera() const
{
  return m_Camera; 
}

KeyboardEvent* Scene::GetKeyboardHandler() const
{
  return m_KeyboardHandler;
}
