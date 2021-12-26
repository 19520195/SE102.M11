#include "JasonS.hh"
#include "Object/State.hh"
#include "Resources/Resources.hh"

JasonS::JasonS()
{
  m_Width = JASONS_WIDTH;
  m_Height = JASONS_HEGIHT;  
  m_Keyboard = std::make_unique<JasonSKeyboard>(this);
}

void JasonS::SetState(int state)
{
  Object::SetState(state);
  if (SM_IS_WALK(state))
    m_Velocity.SetX((SD_IS_LEFT(m_State) ? -1 : 1) * JASONS_SPEED);
  else m_Velocity.SetX(0); 
}

void JasonS::Render(TimeStep elapsed)
{
  if (SM_IS_IDLE(m_State))
  {
    size_t ID = (SD_IS_LEFT(m_State) ? SPRID_JASON_IDLE_LEFT : SPRID_JASON_IDLE_RIGHT);
    SpriteBase::GetInstance()->Get(ID)->Render(m_X, m_Y);
  }
  else
  {
    size_t ID = (SD_IS_LEFT(m_State) ? ANMID_JASON_WALK_LEFT : ANMID_JASON_WALK_RIGHT);
    AnimationBase::GetInstance()->Get(ID)->Render(m_X, m_Y, elapsed);
  }
}

JasonSKeyboard::JasonSKeyboard(JasonS* player)
{
  m_JasonS = player;
}

void JasonSKeyboard::KeyState(BYTE* state)
{
  auto currentState = m_JasonS->GetState(); 
  if (IS_KEYDOWN(state, DIK_LEFT) || IS_KEYDOWN(state, DIK_RIGHT))
  {
    SM_SET_WALK(currentState);
    if (IS_KEYDOWN(state, DIK_LEFT))
      SD_SET_LEFT(currentState);
    else SD_SET_RIGHT(currentState);
  }
  else SM_SET_IDLE(currentState);
  m_JasonS->SetState(currentState);
}

void JasonSKeyboard::OnKeyDown(int code)
{
  //
}

void JasonSKeyboard::OnKeyUp(int code)
{
  //
}
