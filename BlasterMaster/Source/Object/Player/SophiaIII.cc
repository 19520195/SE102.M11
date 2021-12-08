#include "SophiaIII.hh"
#include "Engine/Renderer/Animation.hh"

std::vector<bool> DEBUG_Collision;

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

  m_Width = 24;
  m_Height = 18;

  SM_SET_IDLE(m_State);
  SD_SET_LEFT(m_State);
}

void SophiaIII::SetState(int state)
{
  Object::SetState(state);

  if (SM_IS_IDLE(m_State)) m_SpeedX = 0; 
  else
  {
    // MOVE: left / right
    if (SD_IS_LEFT(m_State)) m_SpeedX = -SOPHIAIII_SPEEDX;
    if (SD_IS_RIGHT(m_State)) m_SpeedX = SOPHIAIII_SPEEDX;
  }
  
  if (SM_IS_JUMP(m_State))
  {
    m_SpeedY = SOPHIAIII_SPEEDY;
    SM_SET_FALL(m_State); 
  }
}

void SophiaIII::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  m_SpeedY -= SOPHIAIII_GRAVITY * elapsed;
  float deltaTimeX = static_cast<float>(elapsed);
  float deltaTimeY = static_cast<float>(elapsed);
  
  DEBUG_Collision = std::vector<bool>(objects.size()); 
  for (size_t i = 0; i < objects.size(); ++i) if (static_cast<Brick*>(objects[i]))
  {
    auto object = objects[i];
    float deltaTime = Collision::SweptAABB(*this, *object);
    if (0 <= deltaTime && deltaTime <= elapsed)
    {
      DEBUG_Collision[i] = true;
      DEBUG_MSG(L"ObjectID = %d Delta Time = %f\n", i, deltaTime);
      float remainTime = (float)elapsed - deltaTime;
      float deltaY = deltaTime * this->GetSpeedY();

      Movable movedThis(this->m_SpeedX, this->m_SpeedY, this->m_X, this->m_Y, this->m_Width, this->m_Height);
      movedThis.Move(deltaTime); 

      if (Collision::IsCollideY(movedThis, *object))
      {
        deltaTimeX = std::min(deltaTimeX, deltaTime + remainTime);
        deltaTimeY = std::min(deltaTimeY, deltaTime);
      }

      if (Collision::IsCollideX(movedThis, *object))
      {
        deltaTimeX = std::min(deltaTimeX, deltaTime);
        deltaTimeY = std::min(deltaTimeY, deltaTime + remainTime);
      }
    }
  }

  m_X += m_SpeedX * std::max(0.f, deltaTimeX);
  m_Y += m_SpeedY * std::max(0.f, deltaTimeY);
  
  if (deltaTimeX < elapsed) m_SpeedX = 0;
  if (deltaTimeY < elapsed) m_SpeedY = 0;
}

void SophiaIII::Render(TimeStep step)
{
  m_LWheel->SetXY(m_X     , m_Y     ); 
  m_RWheel->SetXY(m_X + 16, m_Y     );

  // Assemble Sophia III
  if (SD_IS_LEFT(m_State))
  {
    m_Barrel->SetXY(m_X    , m_Y + 10);
    m_Hammer->SetXY(m_X + 8, m_Y + 10);
    m_Grip  ->SetXY(m_X + 8, m_Y +  2);
    m_Barrel->SetID(10101);
    m_Hammer->SetID(10401);
  }

  if (SD_IS_RIGHT(m_State))
  {
    m_Barrel->SetXY(m_X + 16, m_Y + 10);
    m_Hammer->SetXY(m_X     , m_Y + 10);
    m_Grip  ->SetXY(m_X +  8, m_Y +  2);
    m_Barrel->SetID(10105);
    m_Hammer->SetID(10402);
  }

  if (SM_IS_IDLE(m_State)) step = 0;
  else
  {
    if (SD_IS_LEFT(m_State))
      step = -step;
  }

  m_Barrel->Render(step);
  m_Hammer->Render(step);
  m_Grip  ->Render(step);
  m_LWheel->Render(step);
  m_RWheel->Render(step);
}

/// DEBUG /// 
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

void SophiaIIIKeyboardEvent::KeyState(BYTE* keyboard)
{
  int currentState = m_SophiaIII->GetState(); 

  if (IS_KEYDOWN(keyboard, DIK_C))
  {
    TimeStep currentBulletTime = GetTickCount64();
    if (currentBulletTime - m_LastBulletTime >= SOPHIAIII_BULLET_TIMEOUT)
    {
      // Update bullet frame time
      m_LastBulletTime = currentBulletTime;

      // Handle shoot event
      bool isVertical = false; 
      SophiaIIIBullet* bullet = new SophiaIIIBullet(isVertical);
      if (isVertical)
      {
        // 
      }
      else
      {
        bullet->SetX(m_SophiaIII->GetX() + m_SophiaIII->GetWidth());
        bullet->SetY(m_SophiaIII->GetY() + (m_SophiaIII->GetHeight() - bullet->GetHeight()) / 2);
        if (SD_IS_LEFT(m_SophiaIII->GetState()))
        {
          bullet->SetX(m_SophiaIII->GetX() - bullet->GetWidth());
          bullet->SetSpeed(-bullet->GetSpeedX(), 0);
        }

        PlayScene* scene = dynamic_cast<PlayScene*>(Game::GetInstance()->GetScene());
        scene->AddObject(bullet); 
      }
    }
  }

  // MOVE: Jump
  if (IS_KEYDOWN(keyboard, DIK_X) && SM_IS_FALL(m_SophiaIII->GetState()))
    if (!m_SophiaIII->GetSpeedY())
      SM_SET_JUMP(currentState); 

  // MOVE: Left / Right / Idle
  if (IS_KEYDOWN(keyboard, DIK_RIGHT) || IS_KEYDOWN(keyboard, DIK_LEFT))
  {
    SM_SET_WALK(currentState);
    IS_KEYDOWN(keyboard, DIK_LEFT) ?
      SD_SET_LEFT(currentState) : SD_SET_RIGHT(currentState);
  }
  else
  {
    SM_SET_IDLE(currentState);
  }

  // Set state
  m_SophiaIII->SetState(currentState);
}

void SophiaIIIKeyboardEvent::OnKeyUp(int code) 
{
  // 
}

void SophiaIIIKeyboardEvent::OnKeyDown(int code) 
{
  //
}
