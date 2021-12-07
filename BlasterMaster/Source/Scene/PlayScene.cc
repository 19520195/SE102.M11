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
  m_Camera.SetXY(m_Player->GetX() - 100, m_Player->GetY() - 100);
  // SetCamera(dynamic_cast<Camera*>(dynamic_cast<Vector2D*>(m_Player)));
}

void PlayScene::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(30101)->Render(0, 0);

  #ifdef _DEBUG
  LPDIRECT3DTEXTURE9 blueBox = TextureBase::GetInstance()->GetTexture(-1);
  LPDIRECT3DTEXTURE9 redBox = TextureBase::GetInstance()->GetTexture(-2);
  for (size_t i = 0; i < DEBUG_Collision.size(); ++i)
  {
    const auto& object = m_Objects[i]; 
    LPDIRECT3DTEXTURE9 bbox = (DEBUG_Collision[i] ? redBox : blueBox); 
    Sprite sprite(0, 0, 0, (size_t)object->GetHeight(), (size_t)object->GetWidth(), bbox);
    Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
  }

  Sprite sprite(0, 0, 0, (size_t)m_Player->GetHeight(), (size_t)m_Player->GetWidth(), blueBox);
  Renderer::DrawSprite(m_Player->GetX(), m_Player->GetY(), &sprite);

  #endif // _DEBUG

  ((SophiaIII*)(m_Player))->Render(elapsed); 
  for (const auto& object : m_RenderableObjects)
    object->Render(elapsed);
}
