#include "Neoworm.hh"

Neoworm::Neoworm(Vector2F p)
{
  m_X = p.GetX();
  m_Y = p.GetY();

  m_Width = NEOWORMFALL_WIDTH;
  m_Height = NEOWORMFALL_HEIGHT;
  m_SpriteID = SPRID_NEOWORM_FALL;
}

void Neoworm::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(m_SpriteID)->Render(m_X, m_Y);
}
