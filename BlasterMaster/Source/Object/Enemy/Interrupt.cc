#include "Interrupt.hh"
#include "Neoworm.hh"

Interrupt::Interrupt()
{
  m_Width = INTERRUPT_WIDTH;
  m_Height = INTERRUPT_HEIGHT;

  m_IsActived = false;
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
  if (m_IsActived)
  {
    std::unique_ptr<Neoworm> neoworm;
    neoworm = std::make_unique<Neoworm>(Vector2F(m_X + 7, m_Y - 4));
    neoworm->Render(elapsed);
  }
}
