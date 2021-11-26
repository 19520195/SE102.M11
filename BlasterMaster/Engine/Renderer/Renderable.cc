#include "Renderable.hh"

Renderable::Renderable()
{
  m_ID = 0;
}

void Renderable::SetID(size_t ID)
{
  m_ID = ID;  
}

void AnimationRender::Render(float X, float Y)
{
  AnimationBase::GetInstance()->Get(m_ID)->Render(X, Y);
}

void SpriteRender::Render(float X, float Y)
{
  SpriteBase::GetInstance()->Get(m_ID)->Render(X, Y);
}
