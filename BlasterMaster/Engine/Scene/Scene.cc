#include "Scene.hh"

void Scene::SetCamera(Camera camera)
{
  m_Camera = camera; 
}

Camera Scene::GetCamera() const
{
  return m_Camera; 
}

Ref<KeyboardEvent> Scene::GetKeyboardHandler() const
{
  return m_KeyboardHandler;
}
