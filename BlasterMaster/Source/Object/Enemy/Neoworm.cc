#include "Neoworm.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Neoworm::Neoworm(Vector2F p)
{
  m_X = p.GetX();
  m_Y = p.GetY();

  m_Width = NEOWORMFALL_WIDTH;
  m_Height = NEOWORMFALL_HEIGHT;
  m_SpriteID = SPRID_NEOWORM_FALL;
}

void Neoworm::SetState(int state)
{
  Enemy::SetState(state);
  float velocity = 0;
  switch ((bool)SD_IS_LEFT(state))
  {
  case true: // LEFT
    velocity = -NEOWORMFALL_SPEED;
    m_SpriteID = ANMID_NEOWORM_WALK_LEFT;
    break;

  case false: // RIGHT
    velocity = NEOWORMFALL_SPEED;
    m_SpriteID = ANMID_NEOWORM_WALK_RIGHT;
    break;
  }

  SetSpeed(velocity, GetSpeedY());
}

void Neoworm::Activate()
{
  if (m_IsTriggered)
    return;
  Enemy::Activate();

  SetSpeed(GetSpeedX(), NEOWORMFALL_JUMPSPEED);
  SetState(m_State = SD_SET_RIGHT(m_State));

  m_Width = NEOWORM_WIDTH;
  m_Height = NEOWORM_HEIGHT;
}

void Neoworm::Update(TimeStep elapsed)
{
  Vector2F deltaTime(
    static_cast<float>(elapsed),
    static_cast<float>(elapsed));
  SetSpeed(GetSpeedX(), GetSpeedY() - NEOWORMFALL_GRAVITY * elapsed);

  Ref<PlayScene> scene = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene());
  std::vector<Object*> objects = scene->GetObjects();
  for (const auto& object : objects)
    CollideWithBrick(dynamic_cast<Brick*>(object), elapsed, deltaTime);

  m_X += GetSpeedX() * deltaTime.GetX();
  m_Y += GetSpeedY() * deltaTime.GetY();
  if (deltaTime.GetY() == 0) SetSpeed(GetSpeedX(), 0);
}

void Neoworm::Render(TimeStep elapsed)
{
  if (!m_IsTriggered)
    return SpriteBase::GetInstance()->Get(m_SpriteID)->Render(m_X, m_Y);
  AnimationBase::GetInstance()->Get(m_SpriteID)->Render(m_X, m_Y, elapsed);
}

void Neoworm::CollideWithBrick(Brick* brick, TimeStep elapsed, Vector2F& deltaTime)
{
  if (brick == nullptr) return;
  float collideTime = Collision::SweptAABB(*this, *brick);
  if (0 <= collideTime && collideTime <= elapsed)
  {
    Movable _o = this->GetMove(collideTime);
    if (Collision::IsCollideX(_o, *brick))
    {
      deltaTime.SetX(std::min(deltaTime.GetX(), collideTime));

      auto currentState = this->GetState();
      if (_o.GetRight() == brick->GetLeft())
        SD_SET_LEFT(currentState);
      else SD_SET_RIGHT(currentState);
      this->SetState(currentState);
    }

    if (Collision::IsCollideY(_o, *brick))
      deltaTime.SetY(std::min(deltaTime.GetY(), collideTime));
    this->Activate();
  }
}
