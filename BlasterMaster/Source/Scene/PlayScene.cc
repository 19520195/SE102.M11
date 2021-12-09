#include "PlayScene.hh"

PlayScene::PlayScene()
{
  m_Player = nullptr; 
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

  size_t numberEnemies = 0;
  for (auto& object : m_Objects)
    if (dynamic_cast<Enemy*>(object))
      numberEnemies += !object->IsDied();
  DEBUG_MSG(L"Number of alive enemies: %d\n", numberEnemies);

  for (auto& object : m_Objects)
    if (object->IsDied() == false)
      object->Update(elapsed);
}

void PlayScene::Render(TimeStep elapsed)
{
  #ifdef _DEBUG
  Texture* DEBUG_RED_BBOX  = TextureBase::GetInstance()->Get(TEXID_RED_BBOX);
  Texture* DEBUG_BLUE_BBOX = TextureBase::GetInstance()->Get(TEXID_BLUE_BBOX);
  #endif // _DEBUG

  // Draw background
  SpriteBase::GetInstance()->Get(m_BackgroundID)->Render(0, 0);

  for (size_t i = 0; i < DEBUG_COLLISION.size(); ++i)
  {
    const auto& object = m_Objects[i];
    if (!object->IsDied())
    {
      object->Render(elapsed);

      #ifdef _DEBUG
      Texture* bbox = (DEBUG_COLLISION[i] ? DEBUG_RED_BBOX : DEBUG_BLUE_BBOX); 
      Sprite sprite(0, 0, 0, object->GetHeight(), object->GetWidth(), bbox);
      Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
      #endif // _DEBUG
    }
  }

  m_Player->Render(elapsed);

  #ifdef _DEBUG
  Sprite sprite(0, 0, 0, m_Player->GetHeight(), m_Player->GetWidth(), DEBUG_BLUE_BBOX);
  Renderer::DrawSprite(m_Player->GetX(), m_Player->GetY(), &sprite);
  #endif // _DEBUG

  for (const auto& bullet : (static_cast<SophiaIII*>(m_Player))->GetBullets())
  {
    if (bullet->IsDied() == false)
    {
      const auto& object = bullet;
      object->Render(elapsed);

      #ifdef _DEBUG
      Sprite sprite(0, 0, 0, object->GetHeight(), object->GetWidth(), DEBUG_BLUE_BBOX);
      Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
      #endif // _DEBUG
    }
  }
}
