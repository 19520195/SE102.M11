#include "Interrupt.hh"

Interrupt::Interrupt()
{
  m_Width = INTERRUPT_WIDTH;
  m_Height = INTERRUPT_HEIGHT;

  m_IsActived = true;
  m_SpriteID = SPRID_INTERRUPT_IDLE;
}

void Interrupt::Activate()
{
  Enemy::Activate();
  m_SpriteID = SPRID_INTERRUPT_ACTIVE;

  m_Y += 3;
  m_Height -= 3;
}

void Interrupt::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(m_SpriteID)->Render(m_X, m_Y);
}
