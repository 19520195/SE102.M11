#include "SophiaIII.hh"
#include "Engine/Renderer/Animation.hh"

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

#include <string>
void SophiaIII::Render()
{
  OutputDebugString((L"X = " + std::to_wstring(m_X) + L", ").c_str());
  OutputDebugString((L"Y = " + std::to_wstring(m_Y) + L"\n").c_str());

  if (m_Barrel) m_Barrel->Render();
  if (m_Hammer) m_Hammer->Render();
  if (m_Grip)   m_Grip  ->Render();
  if (m_LWheel) m_LWheel->Render();
  if (m_RWheel) m_RWheel->Render();
}