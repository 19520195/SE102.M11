#include "PlayScene.hh"
#include "../Object/Player/SophiaIII.hh"

PlayScene::PlayScene()
{
  m_Player = nullptr; 
  m_Camera.SetXY(1344, 544);
}

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

void PlayScene::AddObject(Object* object)
{
  m_Objects.emplace_back(object);
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
  SpriteBase::GetInstance()->Get(30101)->Render(0, 0);
  ((SophiaIII*)(m_Player))->Render(elapsed); 
  for (const auto& object : m_RenderableObjects)
    object->Render(elapsed);
}
