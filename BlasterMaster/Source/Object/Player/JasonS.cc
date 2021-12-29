#include "JasonS.hh"
#include "Scene/PlayScene.hh"
#include "Engine/Core/Game.hh"

JasonS::JasonS(Player* owner) : m_Owner(owner)
{
  m_Width = JASONS_WIDTH;
  m_Height = JASONS_HEGIHT;

  m_Acceleration = Vector2F(0, JASONS_GRAVITY);
  m_Velocity = JASONS_JUMP * m_Acceleration;

  m_Keyboard = std::make_unique<JasonSKeyboard>(this);
  SetWalkState(JasonSWalkState::IdleLeft);
}

Player* JasonS::GetOwner()
{
  return m_Owner;
}

JasonSWalkState JasonS::GetCustomState() const
{
  return m_WalkState;
}

void JasonS::SetWalkState(JasonSWalkState s)
{
  switch (m_WalkState = s)
  {
  case JasonSWalkState::IdleLeft:
    m_Velocity.SetX(0);
    SetSprite("Jason-Idle-Left");
    break;

  case JasonSWalkState::IdleRight:
    m_Velocity.SetX(0);
    SetSprite("Jason-Idle-Right");
    break;

  case JasonSWalkState::WalkLeft:
    m_Velocity.SetX(-JASONS_WALK);
    SetAnimation("Jason-Walk-Left");
    break;

  case JasonSWalkState::WalkRight:
    m_Velocity.SetX(JASONS_WALK);
    SetAnimation("Jason-Walk-Right");
    break;
  }
}

void JasonS::OnCollide(const Ref<Collision2D>& collision)
{
  auto refer = collision->GetCollider()->GetRefer();
  if (auto portal = dynamic_cast<ScenePortal*>(refer))
    portal->Activate();
}

JasonSKeyboard::JasonSKeyboard(JasonS* jason) : m_JasonS(jason)
{
}

void JasonSKeyboard::KeyState(BYTE* keyboard)
{
  HandleWalk(keyboard);
  HandleJump(keyboard);
}

void JasonSKeyboard::OnKeyDown(int keycode)
{
  HandleEnter(keycode);
}

void JasonSKeyboard::HandleWalk(BYTE* keyboard)
{
  // Walk
  if (IS_KEYDOWN(keyboard, KLeft))
    return m_JasonS->SetWalkState(JasonSWalkState::WalkLeft);
  if (IS_KEYDOWN(keyboard, KRight))
    return m_JasonS->SetWalkState(JasonSWalkState::WalkRight);

  // Idle
  switch (m_JasonS->GetCustomState())
  {
  case JasonSWalkState::WalkLeft:
    m_JasonS->SetWalkState(JasonSWalkState::IdleLeft);
    break;

  case JasonSWalkState::WalkRight:
    m_JasonS->SetWalkState(JasonSWalkState::IdleRight);
    break;
  }
}

void JasonSKeyboard::HandleJump(BYTE* keyboard)
{
  Vector2F velocity = m_JasonS->GetVelocity();
  if (velocity.GetY()) return;
  
  if (IS_KEYDOWN(keyboard, KJump))
    velocity.SetY(JASONS_JUMP * JASONS_GRAVITY);
  m_JasonS->SetVelocity(velocity);
}

void JasonSKeyboard::HandleEnter(int keycode)
{
  if (keycode == KEnter)
  {
    if (Collision2D::AABB(*m_JasonS, *m_JasonS->GetOwner()))
    {
      auto scene = std::static_pointer_cast<PlayScene>(
        Game::GetInstance()->GetScene());
      scene->SetPlayer(
        std::static_pointer_cast<Player>(
          scene->FindRef(m_JasonS->GetOwner())));
      m_JasonS->Die();
    }
  }
}
