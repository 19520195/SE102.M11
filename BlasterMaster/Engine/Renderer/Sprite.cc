#include "Sprite.hh"

Sprite::Sprite(size_t ID, size_t top, size_t left, size_t bottom, size_t right, LPDIRECT3DTEXTURE9 texture) 
{
  m_ID      = ID;
  m_Top     = top;
  m_Left    = left;
  m_Bottom  = bottom;
  m_Right   = right;

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

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
  return m_Texture;
}

void Sprite::Draw(float X, float Y)
{
}

std::shared_ptr<SpriteBase> SpriteBase::s_Instance = std::make_shared<SpriteBase>();

void SpriteBase::InsertSprite(size_t ID, size_t top, size_t left, size_t bottom, size_t right, LPDIRECT3DTEXTURE9 texture)
{
  m_Sprites[ID].reset(new Sprite(ID, top, left, bottom, right, texture));
}

Sprite* SpriteBase::Get(size_t ID)
{
  return m_Sprites[ID].get();
}

SpriteBase* SpriteBase::GetInstance()
{
  return s_Instance.get();
}
