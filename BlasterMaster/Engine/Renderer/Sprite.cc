#include "Sprite.hh"
#include "Renderer.hh"

Sprite::Sprite(float top, float left, float bottom, float right, Texture* texture)
{
  m_Rect.top    = static_cast<LONG>(top);
  m_Rect.left   = static_cast<LONG>(left);
  m_Rect.bottom = static_cast<LONG>(bottom);
  m_Rect.right  = static_cast<LONG>(right);
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

void Sprite::Render(float X, float Y, TimeStep elapsed)
{
  Renderer::DrawSprite(X, Y, this);
}

Ref<SpriteBase> SpriteBase::s_Instance = CreateRef<SpriteBase>();
Ref<SpriteBase> SpriteBase::GetInstance() { return s_Instance; }

Ref<Sprite> SpriteBase::Add(const std::string& name, float top, float left, float bottom, float right, Texture* texture)
{
  m_Sprites[name] = CreateRef<Sprite>(top, left, bottom, right, texture);
  return m_Sprites[name];
}

Ref<Sprite> SpriteBase::Get(const std::string& name)
{
  return m_Sprites[name];
}
