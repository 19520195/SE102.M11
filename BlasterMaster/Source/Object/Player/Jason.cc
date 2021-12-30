#include "Jason.hh"

constexpr float JASON_SPEED  = 0.1f;

Jason::Jason()
{
  m_Keyboard = CreateRef<JasonKeyboard>(this);
  SetSprite("Jason-Idle-Up");
}

JasonWalkState Jason::GetWalkState() const
{
  return m_WalkState;
}

void Jason::SetWalkState(const JasonWalkState& ws)
{
  if (m_WalkState != ws)
  {
    switch (m_WalkState = ws)
    {
    case JasonWalkState::IdleUp   : SetSprite("Jason-Idle-Up")   ; break;
    case JasonWalkState::IdleLeft : SetSprite("Jason-Idle-Left") ; break;
    case JasonWalkState::IdleDown : SetSprite("Jason-Idle-Down") ; break;
    case JasonWalkState::IdleRight: SetSprite("Jason-Idle-Right"); break;

    case JasonWalkState::WalkUp   : SetAnimation("Jason-Walk-Up")   ; break;
    case JasonWalkState::WalkLeft : SetAnimation("Jason-Walk-Left") ; break;
    case JasonWalkState::WalkDown : SetAnimation("Jason-Walk-Down") ; break;
    case JasonWalkState::WalkRight: SetAnimation("Jason-Walk-Right"); break;
    }
  }
}

JasonKeyboard::JasonKeyboard(Jason* jason)
{
  m_Jason = jason;
}

void JasonKeyboard::KeyState(BYTE* keyboard)
{
  Vector2F velocity;
  if (IS_KEYDOWN(keyboard, KUp)) velocity.SetY(1.f);
  else if (IS_KEYDOWN(keyboard, KDown)) velocity.SetY(-1.f);
  if (IS_KEYDOWN(keyboard, KLeft)) velocity.SetX(-1.f);
  else if (IS_KEYDOWN(keyboard, KRight)) velocity.SetX(1.f);
  
  if (velocity.Abs() != 0)
    velocity = velocity / velocity.Abs();
  m_Jason->SetVelocity(velocity * JASON_SPEED);

  if (velocity.GetY() > 0) m_Jason->SetWalkState(JasonWalkState::WalkUp);
  else if (velocity.GetY() < 0) m_Jason->SetWalkState(JasonWalkState::WalkDown);
  else if (velocity.GetX() < 0) m_Jason->SetWalkState(JasonWalkState::WalkLeft);
  else if (velocity.GetX() > 0) m_Jason->SetWalkState(JasonWalkState::WalkRight);
  else
  {
    switch (m_Jason->GetWalkState())
    {
    case JasonWalkState::WalkUp   : m_Jason->SetWalkState(JasonWalkState::IdleUp)   ; break;
    case JasonWalkState::WalkLeft : m_Jason->SetWalkState(JasonWalkState::IdleLeft) ; break;
    case JasonWalkState::WalkDown : m_Jason->SetWalkState(JasonWalkState::IdleDown) ; break;
    case JasonWalkState::WalkRight: m_Jason->SetWalkState(JasonWalkState::IdleRight); break;
    }
  }
}
