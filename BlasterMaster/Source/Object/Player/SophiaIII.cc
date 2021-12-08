#include "SophiaIII.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Animation.hh"

std::vector<bool> DEBUG_Collision;

SophiaIII::SophiaIII()
{
  m_Barrel = std::make_unique<SophiaIIIBodyPart>();
  m_Hammer = std::make_unique<SophiaIIIBodyPart>();
  m_Grip   = std::make_unique<SophiaIIIBodyPart>();
  m_LWheel = std::make_unique<SophiaIIIWheel>();
  m_RWheel = std::make_unique<SophiaIIIWheel>();

  m_Barrel->SetID(2);
  m_Hammer->SetID(7);
  m_Grip  ->SetID(10);
  m_LWheel->SetID(1);
  m_RWheel->SetID(2);

  m_Width = 24;
  m_Height = 18;

  SM_SET_IDLE(m_State);
  SD_SET_LEFT(m_State);
}

TimeStep SophiaIII::GetLastBulletTime() const
{
  if (m_Bullets.empty()) return 0;
  return m_Bullets.back()->GetArriveTime();
}

std::vector<SophiaIIIBullet*> SophiaIII::GetBullets()
{
  while (m_Bullets.size())
  {
    TimeStep lastFrameTime = Game::GetInstance()->GetLastFrameTime();
    if ((lastFrameTime - m_Bullets.front()->GetArriveTime()) < S3_BULLET_TIMEOUT) break;
    m_Bullets.pop_front();
  }

  std::vector<SophiaIIIBullet*> bullets;
  for (const auto& bullet : m_Bullets)
    bullets.emplace_back(bullet.get());
  return bullets;
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

void SophiaIII::AddBullet(SophiaIIIBullet* bullet)
{
  m_Bullets.emplace_back(bullet);
}

void SophiaIII::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  m_SpeedY -= SOPHIAIII_GRAVITY * elapsed;
  float deltaTimeX = static_cast<float>(elapsed);
  float deltaTimeY = static_cast<float>(elapsed);
  
  DEBUG_Collision = std::vector<bool>(objects.size()); 
  for (size_t i = 0; i < objects.size(); ++i)
  {
    if (dynamic_cast<Brick*>(objects[i]))
    {
      auto object = objects[i];
      float deltaTime = Collision::SweptAABB(*this, *object);
      if (0 <= deltaTime && deltaTime <= elapsed)
      {
        DEBUG_Collision[i] = true;
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
  }

  m_X += m_SpeedX * std::max(0.f, deltaTimeX);
  m_Y += m_SpeedY * std::max(0.f, deltaTimeY);
  
  if (deltaTimeX < elapsed) m_SpeedX = 0;
  if (deltaTimeY < elapsed) m_SpeedY = 0;
}

void SophiaIII::Render(TimeStep elapsed)
{
  m_LWheel->SetXY(m_X     , m_Y     ); 
  m_RWheel->SetXY(m_X + 16, m_Y     );

  // Assemble Sophia III
  if (SD_IS_LEFT(m_State))
  {
    m_Barrel->SetXY(m_X    , m_Y + 10);
    m_Hammer->SetXY(m_X + 8, m_Y + 10);
    m_Grip  ->SetXY(m_X + 8, m_Y +  2);
    m_Barrel->SetID(2);
    m_Hammer->SetID(7);
  }

  if (SD_IS_RIGHT(m_State))
  {
    m_Barrel->SetXY(m_X + 16, m_Y + 10);
    m_Hammer->SetXY(m_X     , m_Y + 10);
    m_Grip  ->SetXY(m_X +  8, m_Y +  2);
    m_Barrel->SetID(6);
    m_Hammer->SetID(8);
  }

  if (SM_IS_IDLE(m_State)) elapsed = 0;
  else
  {
    if (SD_IS_LEFT(m_State))
      elapsed = -elapsed;
  }

  m_Barrel->Render(elapsed);
  m_Hammer->Render(elapsed);
  m_Grip  ->Render(elapsed);
  m_LWheel->Render(elapsed);
  m_RWheel->Render(elapsed);
}

/// DEBUG /// 
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

void SophiaIIIKeyboardEvent::KeyState(BYTE* keyboard)
{
  int currentState = m_SophiaIII->GetState(); 

  if (IS_KEYDOWN(keyboard, DIK_C))
  {
    TimeStep currentTime = GetTickCount64();
    m_LastBulletTime = m_SophiaIII->GetLastBulletTime();
    if (currentTime - m_LastBulletTime >= S3_BULLET_T3MP)
    {
      // Handle shoot event
      bool isVertical = false; 
      SophiaIIIBullet* bullet = new SophiaIIIBullet(isVertical);
      bullet->SetArriveTime(currentTime);
      m_SophiaIII->AddBullet(bullet);
      if (isVertical)
      {
        // 
      }
      else
      {
        bullet->SetX(m_SophiaIII->GetX() + m_SophiaIII->GetWidth());
        bullet->SetY(m_SophiaIII->GetY() + (m_SophiaIII->GetHeight() - bullet->GetHeight()));
        if (SD_IS_LEFT(m_SophiaIII->GetState()))
        {
          bullet->SetX(m_SophiaIII->GetX() - bullet->GetWidth());
          bullet->SetSpeed(-bullet->GetSpeedX(), 0);
        }
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
