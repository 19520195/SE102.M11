#include "Interrupt.hh"

Interrupt::Interrupt()
{
  m_Width = INTERRUPT_WIDTH;
  m_Height = INTERRUPT_HEIGHT;
}

void Interrupt::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(15)->Render(m_X, m_Y);
}
