#include "PlayScene.hh"
#include "../Object/Player/SophiaIII.hh"

Player* PlayScene::GetPlayer() const
{
  return m_Player;
}

void PlayScene::SetPlayer(Player* player)
{
  m_Player = player;
}

void PlayScene::SetKeyboardHandler(KeyboardEvent* handler)
{
  m_KeyboardHandler = handler;
}

void PlayScene::AddRenderableObject(RenderableObject* object)
{
  m_Objects.emplace_back(object);
  m_RenderableObjects.emplace_back(object);
}

void PlayScene::Update(TimeStep elapsed)
{
  m_Player->Update(elapsed, m_Objects);
}

void PlayScene::Render(TimeStep elapsed)
{
  ((SophiaIII*)(m_Player))->Render(elapsed); 
  for (const auto& object : m_RenderableObjects)
    object->Render(elapsed);
}
