#include "SophiaIII.hh"
#include "Engine/Renderer/Animation.hh"

SophiaIII::SophiaIII()
{
  m_Barrel = std::make_unique<SophiaIIIBodyPart>();
  m_Hammer = std::make_unique<SophiaIIIBodyPart>();
  m_Grip   = std::make_unique<SophiaIIIBodyPart>();
  m_LWheel = std::make_unique<SophiaIIIWheel>();
  m_RWheel = std::make_unique<SophiaIIIWheel>();
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

void SophiaIII::Render()
{
  m_Barrel->SetXY(m_X + 8 , m_Y + 12);
  m_Hammer->SetXY(m_X     , m_Y + 12);
  m_Grip  ->SetXY(m_X + 8 , m_Y + 4 );
  m_LWheel->SetXY(m_X     , m_Y     ); 
  m_RWheel->SetXY(m_X + 16, m_Y     );

  m_Barrel->Render();
  m_Hammer->Render();
  m_Grip  ->Render();
  m_LWheel->Render();
  m_RWheel->Render();
}
