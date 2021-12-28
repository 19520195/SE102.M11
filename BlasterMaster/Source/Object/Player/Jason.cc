#include "Jason.hh"

constexpr float __JASON_WIDTH = 6.f;
constexpr float __JASON_HEGIHT = 18.f;
constexpr float __JASON_SPEED = 0.1f;

Jason::Jason()
{
  m_Keyboard = CreateRef<JasonKeyboard>(this);
  m_Render = AnimationBase::GetInstance()->Get("Jason-Walk-Up");
}

void Jason::SetBehavior(const Behavior& behavior)
{
  // Direction
  if (behavior.GetDirect() != m_Behavior.GetDirect())
  switch (behavior.GetDirect())
  {
  case Behavior::Direct::Up:
    m_Render = AnimationBase::GetInstance()->Get("Jason-Walk-Up");
    break;

  case Behavior::Direct::Down:
    m_Render = AnimationBase::GetInstance()->Get("Jason-Walk-Down");
    break;

  case Behavior::Direct::Left:
    m_Render = AnimationBase::GetInstance()->Get("Jason-Walk-Left");
    break;

  case Behavior::Direct::Right:
    m_Render = AnimationBase::GetInstance()->Get("Jason-Walk-Right");
    break;
  }

  Player::SetBehavior(behavior);
}

JasonKeyboard::JasonKeyboard(Jason* player)
{
  m_Player = player;
}

void JasonKeyboard::KeyState(BYTE* state)
{
  Vector2F velocity;
  if (IS_KEYDOWN(state, DIK_UP)) velocity.SetY(__JASON_SPEED);
  if (IS_KEYDOWN(state, DIK_DOWN)) velocity.SetY(-__JASON_SPEED);
  if (IS_KEYDOWN(state, DIK_LEFT)) velocity.SetX(-__JASON_SPEED);
  if (IS_KEYDOWN(state, DIK_RIGHT)) velocity.SetX(__JASON_SPEED);
  m_Player->SetVelocity(velocity);

  Behavior behavior = m_Player->GetBehavior();
  if (IS_KEYDOWN(state, DIK_UP)) behavior.SetDirect(Behavior::Direct::Up);
  else if (IS_KEYDOWN(state, DIK_DOWN)) behavior.SetDirect(Behavior::Direct::Down);
  else if (IS_KEYDOWN(state, DIK_LEFT)) behavior.SetDirect(Behavior::Direct::Left);
  else if (IS_KEYDOWN(state, DIK_RIGHT)) behavior.SetDirect(Behavior::Direct::Right);
  m_Player->SetBehavior(behavior);
}
