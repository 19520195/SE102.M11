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

  m_Width = 24;
  m_Height = 18;
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

void SophiaIII::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  m_SpeedY -= SOPHIAIII_GRAVITY * elapsed;

  float deltaX = m_SpeedX * elapsed;
  float deltaY = m_SpeedY * elapsed; 
  
  for (size_t i = 0; i < objects.size(); ++i)
  {
    float deltaT = Collision::SweptAABB(*this, *objects[i]);
    if (deltaT >= 0 && deltaT <= elapsed)
    {
      deltaY = m_SpeedY * deltaT;
      m_SpeedY = 0;
    }
  }

  m_X += deltaX;
  m_Y += deltaY;
  DEBUG_MSG(L"deltaY = %d\n", deltaY);
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
    m_Barrel->SetXY(m_X     , m_Y + 10);
    m_Hammer->SetXY(m_X +  8, m_Y + 10);
    m_Grip  ->SetXY(m_X +  8, m_Y +  2);
    m_Barrel->SetID(10101);
    m_Hammer->SetID(10401);
    break;

  case SOPHIAIII_IDLE_RIGHT:
  case SOPHIAIII_WALK_RIGHT:
    m_Barrel->SetXY(m_X + 16, m_Y + 10);
    m_Hammer->SetXY(m_X     , m_Y + 10);
    m_Grip  ->SetXY(m_X +  8, m_Y +  2);
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

#include "Engine/Core/Game.hh"

void SophiaIIIKeyboardEvent::KeyState(BYTE* state)
{
  if (IS_KEYDOWN(state, DIK_RIGHT))
    m_SophiaIII->SetState(SOPHIAIII_WALK_RIGHT);
  else if (IS_KEYDOWN(state, DIK_LEFT))
    m_SophiaIII->SetState(SOPHIAIII_WALK_LEFT);
  else
  {
    if (m_SophiaIII->GetState() == SOPHIAIII_WALK_LEFT)
      m_SophiaIII->SetState(SOPHIAIII_IDLE_LEFT);
    else if (m_SophiaIII->GetState() == SOPHIAIII_WALK_RIGHT)
      m_SophiaIII->SetState(SOPHIAIII_IDLE_RIGHT);
  }

  /// DEBUG /// 
  static float cameraMovement = 8.f;
  Camera camera = Game::GetInstance()->GetScene()->GetCamera();
  if (IS_KEYDOWN(state, DIK_A))
  {
    camera.SetXY(camera.GetX() - cameraMovement, camera.GetY());
    Game::GetInstance()->GetScene()->SetCamera(camera);
  }
  else if (IS_KEYDOWN(state, DIK_D))
  {
    camera.SetXY(camera.GetX() + cameraMovement, camera.GetY());
    Game::GetInstance()->GetScene()->SetCamera(camera);
  }
  else if (IS_KEYDOWN(state, DIK_S))
  {
    camera.SetXY(camera.GetX(), camera.GetY() - cameraMovement);
    Game::GetInstance()->GetScene()->SetCamera(camera);
  }
  else if (IS_KEYDOWN(state, DIK_W))
  {
    camera.SetXY(camera.GetX(), camera.GetY() + cameraMovement);
    Game::GetInstance()->GetScene()->SetCamera(camera);
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
