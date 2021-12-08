#include "PlayScene.hh"
#include "../Object/Player/SophiaIII.hh"

PlayScene::PlayScene()
{
  m_Player = nullptr; 
  m_Camera.SetXY(1344, 544);

  m_BackgroundID = 0;
}

Player* PlayScene::GetPlayer() const
{
  return m_Player;
}

void PlayScene::SetBackground(size_t ID)
{
  m_BackgroundID = ID; 
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

void PlayScene::Update(TimeStep elapsed)
{
  m_Player->Update(elapsed, m_Objects);

  m_Camera.SetXY(m_Player->GetX() - 100, m_Player->GetY() - 100);
  if (m_Camera.GetX() < 0) m_Camera.SetX(0);
  if (m_Camera.GetY() < 0) m_Camera.SetY(0);
  if (m_Camera.GetX() > 1344) m_Camera.SetX(1344);
  if (m_Camera.GetY() > 560) m_Camera.SetY(560);

  SophiaIII* s3 = dynamic_cast<SophiaIII*>(m_Player);
  for (const auto& bullet : s3->GetBullets())
    bullet->Update(elapsed, m_Objects);

  int counter = 0;
  for (auto& object : m_Objects)
    if (dynamic_cast<Enemy*>(object))
      ++counter;
  DEBUG_MSG(L"Number of Enemies: %d\n", counter);

  for (auto& object : m_Objects)
    if (object->IsDied() == false)
      object->Update(elapsed);
}

void PlayScene::Render(TimeStep elapsed)
{
  // Draw background
  SpriteBase::GetInstance()->Get(m_BackgroundID)->Render(0, 0);

  #ifdef _DEBUG
  Texture* blueBox = TextureBase::GetInstance()->Get(1);
  Texture* redBox = TextureBase::GetInstance()->Get(2);
  for (size_t i = 0; i < DEBUG_Collision.size(); ++i)
  {
    const auto& object = m_Objects[i];
    if (!object->IsDied())
    {
      Texture* bbox = (DEBUG_Collision[i] ? redBox : blueBox); 
      Sprite sprite(0, 0, 0, (size_t)object->GetHeight(), (size_t)object->GetWidth(), bbox);
      // Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
      object->Render(elapsed);
    }
  }

  Sprite sprite(0, 0, 0, (size_t)m_Player->GetHeight(), (size_t)m_Player->GetWidth(), blueBox);
  // Renderer::DrawSprite(m_Player->GetX(), m_Player->GetY(), &sprite);
  #endif // _DEBUG

  m_Player->Render(elapsed);
  SophiaIII* s3 = dynamic_cast<SophiaIII*>(m_Player);
  for (const auto& bullet : s3->GetBullets())
  {
    if (bullet->IsDied() == false)
    {
      const auto& object = bullet;
      Sprite sprite(0, 0, 0, (size_t)object->GetHeight(), (size_t)object->GetWidth(), blueBox);
      // Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
      object->Render(elapsed);
    }
  }
}
