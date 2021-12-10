#include "SophiaIII.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Animation.hh"

std::vector<bool> DEBUG_COLLISION;

SophiaIII::SophiaIII()
{
  m_Barrel = std::make_unique<SophiaIIIBodyPart>();
  m_Hammer = std::make_unique<SophiaIIIBodyPart>();
  m_Grip   = std::make_unique<SophiaIIIBodyPart>();
  m_LWheel = std::make_unique<SophiaIIIWheel>();
  m_RWheel = std::make_unique<SophiaIIIWheel>();

  m_Grip  ->SetID(SPRID_S3_GRIP_HRZ);
  m_LWheel->SetID(ANMID_S3_LEFT_WHEEL);
  m_RWheel->SetID(ANMID_S3_RIGHT_WHEEL);

  m_Width = SOPHIAIII_WIDTH;
  m_Height = SOPHIAIII_HEIGHT;

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
    if (SD_IS_LEFT(m_State)) m_SpeedX = -SOPHIAIII_SPEED;
    if (SD_IS_RIGHT(m_State)) m_SpeedX = SOPHIAIII_SPEED;
  }
  
  if (SM_IS_JUMP(m_State))
  {
    m_SpeedY = SOPHIAIII_JUMPSPEED;
    SM_SET_FALL(m_State); 
  }
}

void SophiaIII::AddBullet(SophiaIIIBullet* bullet)
{
  m_Bullets.emplace_back(bullet);
}

SophiaIIIBullet* SophiaIII::CreateBullet()
{
  TimeStep lastFrameTime = Game::GetInstance()->GetLastFrameTime();
  TimeStep lastBulletTime = this->GetLastBulletTime();
  TimeStep elapsed = lastFrameTime - lastBulletTime;

  if (elapsed < S3_BULLET_DELTA || this->GetBullets().size() >= S3_BULLET_MAX)
    return nullptr;
  
  SophiaIIIBullet* bullet = new SophiaIIIBullet(SD_IS_UP(m_State));
  bullet->SetArriveTime(lastFrameTime);
  this->AddBullet(bullet);

  if (SD_IS_UP(m_State))
  {
    bullet->SetX(this->GetLeft() + (this->GetWidth() - bullet->GetWidth()) / 2);
    bullet->SetY(this->GetTop() - bullet->GetHeight() / 2);
    bullet->SetSpeed(0, S3BULLET_SPEED);
  }
  else
  {
    bullet->SetY(this->GetY() + (this->GetHeight() - bullet->GetHeight()));
    if (SD_IS_RIGHT(GetState()))
    {
      bullet->SetX(GetLeft() + bullet->GetWidth() / 2);
      bullet->SetSpeed(S3BULLET_SPEED, 0);
    }
    else
    {
      bullet->SetX(GetLeft() - bullet->GetWidth() / 2);
      bullet->SetSpeed(-S3BULLET_SPEED, 0);
    }
  }

  return bullet;
}

void SophiaIII::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  m_SpeedY -= SOPHIAIII_GRAVITY * elapsed;
  float deltaTimeX = static_cast<float>(elapsed);
  float deltaTimeY = static_cast<float>(elapsed);
  
  DEBUG_COLLISION = std::vector<bool>(objects.size()); 
  for (size_t i = 0; i < objects.size(); ++i)
  {
    if (dynamic_cast<Brick*>(objects[i]))
    {
      auto object = objects[i];
      float deltaTime = Collision::SweptAABB(*this, *object);
      if (0 <= deltaTime && deltaTime <= elapsed)
      {
        DEBUG_COLLISION[i] = true;
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

  m_X += m_SpeedX * deltaTimeX;
  m_Y += m_SpeedY * deltaTimeY;
  
  if (deltaTimeX < elapsed) m_SpeedX = 0;
  if (deltaTimeY < elapsed) m_SpeedY = 0;

  DEBUG_MSG(L"Sophia III X = %.2f, Y = %.2f\n", m_X, m_Y);
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
    m_Barrel->SetID(SPRID_S3_LEFT_BARREL);
    m_Hammer->SetID(SPRID_S3_LEFT_HAMMER);
  }

  if (SD_IS_RIGHT(m_State))
  {
    m_Barrel->SetXY(m_X + 16, m_Y + 10);
    m_Hammer->SetXY(m_X     , m_Y + 10);
    m_Grip  ->SetXY(m_X +  8, m_Y +  2);
    m_Barrel->SetID(SPRID_S3_RIGHT_BARREL);
    m_Hammer->SetID(SPRID_S3_RIGHT_HAMMER);
  }

  if (SD_IS_UP(m_State))
  {
    m_Barrel->SetID(SPRID_S3_UP_BARREL);
    m_Barrel->SetXY(m_X + (m_Width - 8) / 2, m_Y + m_Height + 4);
    m_Hammer->SetID(SD_IS_LEFT(m_State) ? SPRID_S3_UPLEFT_HAMMER : SPRID_S3_UPRIGHT_HAMMER);
    m_Hammer->SetXY(SD_IS_LEFT(m_State) ? m_X + 9 : m_X, m_Y + 6);
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

void SophiaIIIKeyboardEvent::KeyState(BYTE* keyboard)
{
  SophiaIII* pS3 = static_cast<SophiaIII*>(m_Player);
  int currentState = pS3->GetState(); 

  // MOVE: Jump
  if (IS_KEYDOWN(keyboard, DIK_X) && SM_IS_FALL(pS3->GetState()))
    if (!pS3->GetSpeedY())
      SM_SET_JUMP(currentState); 

  // MOVE: Left / Right / Idle
  if (IS_KEYDOWN(keyboard, DIK_RIGHT) || IS_KEYDOWN(keyboard, DIK_LEFT))
  {
    SM_SET_WALK(currentState);
    if (IS_KEYDOWN(keyboard, DIK_LEFT))
      SD_SET_LEFT(currentState);
    else SD_SET_RIGHT(currentState);
  }
  else SM_SET_IDLE(currentState);

  if (IS_KEYDOWN(keyboard, DIK_UP))
    SD_SET_UP(currentState);
  else SD_SET_DOWN(currentState); 

  // Set state
  pS3->SetState(currentState);

  if (IS_KEYDOWN(keyboard, DIK_C))
    pS3->CreateBullet();
}

void SophiaIIIKeyboardEvent::OnKeyUp(int code) 
{
  // 
}

void SophiaIIIKeyboardEvent::OnKeyDown(int code) 
{
  //
}
