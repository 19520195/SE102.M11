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

void PlayScene::Update(TimeStep elapsed)
{
  m_Player->Update(elapsed);
}

void PlayScene::Render(TimeStep elapsed)
{
  ((SophiaIII*)(m_Player))->Render(elapsed); 
  for (const auto& object : m_Objects);
}
