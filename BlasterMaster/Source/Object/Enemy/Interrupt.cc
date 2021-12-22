#include "Interrupt.hh"
#include "Neoworm.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Interrupt::Interrupt()
{
  m_Width = INTERRUPT_WIDTH;
  m_Height = INTERRUPT_HEIGHT;

  m_IsActived = false;
  m_SpriteID = SPRID_INTERRUPT_IDLE;
}

Trigger* Interrupt::CreateTrigger()
{
  Trigger* trigger = new Trigger(this);
  trigger->SetLocation(
    m_X + (m_Width - INTERRUPT_TRIGGER_WIDTH) / 2, 
    m_Y - INTERRUPT_TRIGGER_HEIGHT);
  trigger->SetSize(INTERRUPT_TRIGGER_WIDTH, INTERRUPT_TRIGGER_HEIGHT);
  return trigger;
}

void Interrupt::Activate()
{
  Enemy::Activate();

  m_Y += 3;
  m_Height -= 3;
  m_SpriteID = SPRID_INTERRUPT_ACTIVE;

  // Drop a Neoworm
  PlayScene* scene = dynamic_cast<PlayScene*>(Game::GetInstance()->GetScene());
  scene->AddObject(new Neoworm(Vector2F(m_X + 7, m_Y - 4)));
}

void Interrupt::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(m_SpriteID)->Render(m_X, m_Y);
}
