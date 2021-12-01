#include "SophiaIII.hh"
#include "Engine/Renderer/Animation.hh"

SophiaIII::SophiaIII()
{
  m_Barrel = std::make_unique<SophiaIIIBodyPart>();
  m_Hammer = std::make_unique<SophiaIIIBodyPart>();
  m_Grip   = std::make_unique<SophiaIIIBodyPart>();
  m_LWheel = std::make_unique<SophiaIIIWheel>();
  m_RWheel = std::make_unique<SophiaIIIWheel>();

  m_Barrel->SetID(10101);
  m_Hammer->SetID(10401);
  m_Grip  ->SetID(10201);
  m_LWheel->SetID(10301);
  m_RWheel->SetID(10302);
}

void SophiaIII::SetState(int state)
{
  Object::SetState(state);

  switch (state)
  {
  case SOPHIAIII_IDLE_LEFT:
  case SOPHIAIII_IDLE_RIGHT:
    m_SpeedX = 0;
    break;

  case SOPHIAIII_WALK_LEFT:
    m_SpeedX = -SOPHIAIII_SPEED;
    break;

  case SOPHIAIII_WALK_RIGHT:
    m_SpeedX = SOPHIAIII_SPEED;
    break;
  }
}

void SophiaIII::Update(TimeStep step)
{
  Object::Update(step); 

  m_SpeedY -= SOPHIAIII_GRAVITY * step; 
}

void SophiaIII::Render(TimeStep step)
{
  m_LWheel->SetXY(m_X     , m_Y     ); 
  m_RWheel->SetXY(m_X + 16, m_Y     );

  // Assemble Sophia III
  switch (m_State)
  {
  case SOPHIAIII_IDLE_LEFT:
  case SOPHIAIII_WALK_LEFT:
    m_Barrel->SetXY(m_X     , m_Y + 12);
    m_Hammer->SetXY(m_X +  8, m_Y + 12);
    m_Grip  ->SetXY(m_X +  8, m_Y +  4);
    m_Barrel->SetID(10101);
    m_Hammer->SetID(10401);
    break;

  case SOPHIAIII_IDLE_RIGHT:
  case SOPHIAIII_WALK_RIGHT:
    m_Barrel->SetXY(m_X + 16, m_Y + 12);
    m_Hammer->SetXY(m_X     , m_Y + 12);
    m_Grip  ->SetXY(m_X +  8, m_Y +  4);
    m_Barrel->SetID(10105);
    m_Hammer->SetID(10402);
    break;
  }

  // Movement
  switch (m_State)
  {
  case SOPHIAIII_IDLE_LEFT:
  case SOPHIAIII_IDLE_RIGHT:
    step = 0;
    break;

  case SOPHIAIII_WALK_LEFT:
    step = -step;
    break;
  }

  m_Barrel->Render(step);
  m_Hammer->Render(step);
  m_Grip  ->Render(step);
  m_LWheel->Render(step);
  m_RWheel->Render(step);
}

void SophiaIIIKeyboardEvent::KeyState(BYTE* state)
{
  if (Input::GetInstance()->IsKeyDown(DIK_RIGHT))
    m_SophiaIII->SetState(SOPHIAIII_WALK_RIGHT);
  else if (Input::GetInstance()->IsKeyDown(DIK_LEFT))
    m_SophiaIII->SetState(SOPHIAIII_WALK_LEFT);
  else
  {
    if (m_SophiaIII->GetState() == SOPHIAIII_WALK_LEFT)
      m_SophiaIII->SetState(SOPHIAIII_IDLE_LEFT);
    else if (m_SophiaIII->GetState() == SOPHIAIII_WALK_RIGHT)
      m_SophiaIII->SetState(SOPHIAIII_IDLE_RIGHT);
  }
}

void SophiaIIIKeyboardEvent::OnKeyUp(int code) 
{
  // 
}

void SophiaIIIKeyboardEvent::OnKeyDown(int code) 
{
  //
}
