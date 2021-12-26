#include "SophiaIII.hh"
#include "Scene/PlayScene.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Animation.hh"

std::vector<bool> DEBUG_COLLISION;

SophiaIII::SophiaIII()
{
  m_Barrel = std::make_unique<Object>();
  m_Hammer = std::make_unique<Object>();
  m_Grip   = std::make_unique<Object>();
  m_LWheel = std::make_unique<Object>();
  m_RWheel = std::make_unique<Object>();

  m_LWheel->SetAnimation("S3-Left-Wheel");
  m_RWheel->SetAnimation("S3-Right-Wheel");

  m_Width = SOPHIAIII_WIDTH;
  m_Height = SOPHIAIII_HEIGHT;

  m_Keyboard = CreateRef<SophiaIIIKeyboardEvent>(this);

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

  if (SM_IS_IDLE(m_State)) m_Velocity.SetX(0); 
  else
  {
    // MOVE: left / right
    if (SD_IS_LEFT(m_State)) m_Velocity.SetX(-SOPHIAIII_SPEED);
    if (SD_IS_RIGHT(m_State)) m_Velocity.SetX(SOPHIAIII_SPEED);
  }
  
  if (SM_IS_JUMP(m_State))
  {
    m_Velocity.SetY(SOPHIAIII_JUMPSPEED);
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

Scope<JasonS> SophiaIII::CreateJason()
{
  Scope<JasonS> jason = CreateScope<JasonS>();
  jason->SetLocation(m_X, m_Y);
  return jason;
}

void SophiaIII::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  DEBUG_COLLISION = std::vector<bool>(objects.size());

  m_Velocity.SetY(m_Velocity.GetY() - SOPHIAIII_GRAVITY * elapsed);
  Vector2F deltaTime(static_cast<float>(elapsed), static_cast<float>(elapsed));
  for (size_t i = 0; i < objects.size(); ++i)
  {
    Vector2F deltaMove = Vector2F::Infinity();
    float deltaCollide = Collision::SweptAABB(*this, *objects[i]);

    if (Trigger* trigger = dynamic_cast<Trigger*>(objects[i]))
      if (0 <= deltaCollide && deltaCollide <= elapsed)
        trigger->Start();

    if (Brick* brick = dynamic_cast<Brick*>(objects[i]))
    {
      if (0 <= deltaCollide && deltaCollide <= elapsed)
      {
        DEBUG_COLLISION[i] = true;
        deltaMove = CollideWithBrick(brick, deltaCollide);
      }
    }
    else if (Enemy* enemy = dynamic_cast<Enemy*>(objects[i]))
    {
      if (enemy->IsActivated())
      {
        if ((0 <= deltaCollide && deltaCollide <= elapsed) || Collision::AABB(*this, *objects[i]))
        {
          DEBUG_COLLISION[i] = true;
        }
      }
    }

    deltaTime.SetX(std::min(deltaTime.GetX(), deltaMove.GetX()));
    deltaTime.SetY(std::min(deltaTime.GetY(), deltaMove.GetY()));
  }

  m_X += m_Velocity.GetX() * deltaTime.GetX();
  m_Y += m_Velocity.GetY() * deltaTime.GetY();
  if (deltaTime.GetX() < elapsed) m_Velocity.SetX(0);
  if (deltaTime.GetY() < elapsed) m_Velocity.SetY(0);
}

void SophiaIII::Render(TimeStep elapsed)
{
  m_LWheel->SetXY(m_X     , m_Y); 
  m_RWheel->SetXY(m_X + 16, m_Y);
  m_Grip  ->SetXY(m_X +  8, m_Y);

  // Assemble Sophia III
  if (SD_IS_LEFT(m_State))
  {
    m_Barrel->SetXY(m_X    , m_Y + 8);
    m_Hammer->SetXY(m_X + 8, m_Y + 8);
    m_Grip  ->SetSprite("S3-Grip-Left");
    m_Barrel->SetSprite("S3-Barrel-Left");
    m_Hammer->SetSprite("S3-Left-Hammer");
  }

  if (SD_IS_RIGHT(m_State))
  {
    m_Barrel->SetXY(m_X + 16, m_Y + 8);
    m_Hammer->SetXY(m_X     , m_Y + 8);
    m_Grip  ->SetSprite("S3-Grip-Right");
    m_Barrel->SetSprite("S3-Barrel-Right");
    m_Hammer->SetSprite("S3-Right-Hammer");
  }

  if (SD_IS_UP(m_State))
  {
    m_Barrel->SetXY(m_X + (m_Width - 8) / 2, m_Y + m_Height + 4);
    m_Hammer->SetSprite(SD_IS_LEFT(m_State) ? "S3-UpLeft-Hammer" : "S3-UpRight-Hammer");
    m_Hammer->SetXY(SD_IS_LEFT(m_State) ? m_X + 9 : m_X, m_Y + 6);
  }

  if (SM_IS_IDLE(m_State)) elapsed = 0;
  else
  {
    if (SD_IS_LEFT(m_State))
      elapsed = -elapsed;
  }

  if (SD_IS_UP(m_State))
  {
    // m_Width = 26;
    // m_Height = 32;
    m_Barrel->SetXY(m_X + 9, m_Y + 24);
    if (SD_IS_LEFT(m_State))
    {
      m_Barrel->SetSprite("S3-Barrel-Left-90deg");
      m_LWheel->SetXY(m_X     , m_Y     );
      m_RWheel->SetXY(m_X + 12, m_Y     );
      m_Grip  ->SetXY(m_X +  6, m_Y +  7);
      m_Hammer->SetXY(m_X + 10, m_Y +  9);
    }
    else
    {
      m_Barrel->SetSprite("S3-Barrel-Right-90deg");
      m_LWheel->SetXY(m_X +  6, m_Y     );
      m_RWheel->SetXY(m_X + 18, m_Y     );
      m_Grip  ->SetXY(m_X + 12, m_Y +  7);
      m_Hammer->SetXY(m_X     , m_Y +  9);
    }
  }
  else
  {
    m_Width  = SOPHIAIII_WIDTH;
    m_Height = SOPHIAIII_HEIGHT;
  }

  m_Barrel->Render(elapsed);
  m_Hammer->Render(elapsed);
  m_Grip  ->Render(elapsed);
  m_LWheel->Render(elapsed);
  m_RWheel->Render(elapsed);
}

Vector2F SophiaIII::CollideWithBrick(Brick* brick, float deltaCollide)
{
  Movable movedThis(
    this->m_Velocity.GetX(), this->m_Velocity.GetY(),
    this->m_X, this->m_Y,
    this->m_Width, this->m_Height);
  movedThis.Move(deltaCollide);

  Vector2F delta(
    std::numeric_limits<float>::infinity(),
    std::numeric_limits<float>::infinity());
  deltaCollide = std::max(deltaCollide, deltaCollide - 0.1f);
  if (Collision::IsCollideX(movedThis, *brick)) delta.SetX(deltaCollide);
  if (Collision::IsCollideY(movedThis, *brick)) delta.SetY(deltaCollide);
  return delta;
}

SophiaIIIKeyboardEvent::SophiaIIIKeyboardEvent(SophiaIII* player)
{
  m_Player = player;
}

void SophiaIIIKeyboardEvent::KeyState(BYTE* keyboard)
{
  SophiaIII* pS3 = static_cast<SophiaIII*>(m_Player);
  int currentState = pS3->GetState();

  // MOVE: Jump
  if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Jump) && SM_IS_FALL(pS3->GetState()))
    if (!pS3->GetSpeedY())
      SM_SET_JUMP(currentState); 

  // MOVE: Left / Right / Idle
  if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Right) || IS_KEYDOWN(keyboard, SophiaIIIKBS::Left))
  {
    SM_SET_WALK(currentState);
    if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Left))
      SD_SET_LEFT(currentState);
    else SD_SET_RIGHT(currentState);
  }
  else SM_SET_IDLE(currentState);

  if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Up))
    SD_SET_UP(currentState);
  else SD_SET_DOWN(currentState); 

  // Set state
  pS3->SetState(currentState);

  // if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Shoot))
  //   if (auto bullet = pS3->CreateBullet())
  //     std::static_pointer_cast<PlayScene>(
  //       Game::GetInstance()->GetScene())->AddObject(bullet);

  if (IS_KEYDOWN(keyboard, SophiaIIIKBS::Open))
  {
    auto jason = pS3->CreateJason();
    auto scene = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene());
    scene->SetPlayer(std::move(jason));
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
