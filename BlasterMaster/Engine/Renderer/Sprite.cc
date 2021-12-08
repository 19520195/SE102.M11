#include "Sprite.hh"
#include "Renderer.hh"

Sprite::Sprite(size_t ID, size_t top, size_t left, size_t bottom, size_t right, Texture* texture) 
{
  m_Rect.top    = top;
  m_Rect.left   = left;
  m_Rect.bottom = bottom;
  m_Rect.right  = right;
  m_Texture     = texture;
}

RECT* Sprite::GetRect()
{
  return &m_Rect;
}

Texture* Sprite::GetTexture()
{
  return m_Texture;
}

void Sprite::Render(float X, float Y)
{
  Renderer::DrawSprite(X, Y, this);
}

std::shared_ptr<SpriteBase> SpriteBase::s_Instance = std::make_shared<SpriteBase>();

Sprite* SpriteBase::Add(size_t ID, size_t top, size_t left, size_t bottom, size_t right, Texture* texture)
{
  m_Sprites[ID].reset(new Sprite(ID, top, left, bottom, right, texture));
  return m_Sprites[ID].get(); 
}

Sprite* SpriteBase::Get(size_t ID)
{
  return m_Sprites[ID].get();
}

SpriteBase* SpriteBase::GetInstance()
{
  return s_Instance.get();
}
