#include "Interrupt.hh"
#include "Neoworm.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Interrupt::Interrupt()
{
  m_Width = INTERRUPT_WIDTH;
  m_Height = INTERRUPT_HEIGHT;
  m_Render = SpriteBase::GetInstance()->Get("Interrupt-Idle");
}

void Interrupt::Update()
{
  if (IsTriggered())
    return;

  Box2F trigger;
  trigger.SetLocation(
    m_X + (m_Width - INTERRUPT_TRIGGER_WIDTH) / 2,
    m_Y - INTERRUPT_TRIGGER_HEIGHT);
  trigger.SetSize(INTERRUPT_TRIGGER_WIDTH, INTERRUPT_TRIGGER_HEIGHT);
  auto scene = std::static_pointer_cast<PlayScene>(
    Game::GetInstance()->GetScene());
  
  if (Collision2D::AABB(*scene->GetPlayer(), trigger))
    this->Activate();
}

void Interrupt::Activate()
{
  m_IsTriggered = true;

  m_Y += 3;
  m_Height -= 3;
  m_Render = SpriteBase::GetInstance()->Get("Interrupt-Active");

  // Drop a Neoworm
  auto scene = std::static_pointer_cast<PlayScene>(
    Game::GetInstance()->GetScene());
  scene->AddObject(CreateRef<Neoworm>(Vector2F(m_X + 7, m_Y - 4)));
}
