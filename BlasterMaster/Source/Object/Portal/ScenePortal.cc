#include "ScenePortal.hh"
#include "Engine/Core/Game.hh"
#include "Scene/SceneManager.hh"

void ScenePortal::SetScene(const std::string& name)
{
  m_SceneName = name;
}

void ScenePortal::Activate() const
{
  if (auto scene = SceneManager::GetInstance()->Get(m_SceneName))
    Game::GetInstance()->SwitchScene(scene);
}

void ScenePortal::Render(TimeStep elapsed)
{
  auto texture = TextureBase::GetInstance()->Get("Red-BBox");
  Sprite sprite(0, 0, m_Height, m_Width, texture);
  sprite.Render(m_X, m_Y);
  
}
