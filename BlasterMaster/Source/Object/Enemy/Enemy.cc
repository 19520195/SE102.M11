#include "Enemy.hh"
#include "Utility/Strings.hh"

Enemy::Enemy() : m_IsActivated(true), m_IsTriggered(false), m_StartPoint(0, 0)
{
  // 
}

bool Enemy::IsActivated() const
{
  return m_IsActivated;
}

bool Enemy::IsTriggered() const
{
  return m_IsTriggered;
}

void Enemy::SetStartPoint(const Vector2F& point)
{
  m_StartPoint = point;
  m_X = point.GetX();
  m_Y = point.GetY();
}

Trigger* Enemy::CreateTrigger()
{
  return nullptr;
}

void Enemy::Activate()
{
  m_IsTriggered = true;
  m_IsActivated = true;
}

void Enemy::ResetTrigger()
{
  m_IsTriggered = false;
}

Enemy* Enemy::Create(const std::string& name)
{
  auto tokens = Strings::Split(name, ".");
  std::string enemyType = tokens[0];

  Enemy* enemy = nullptr;
       if (enemyType == "Interrupt" ) enemy = new Interrupt();
  else if (enemyType == "Ballbot"   ) enemy = new Ballbot();
  else if (enemyType == "Stuka"     ) enemy = new Stuka();
  else if (enemyType == "Eyelet"    ) enemy = new Eyelet();
  else if (enemyType == "Ball-Carry") enemy = new BallCarry();
  else return nullptr;

  if (tokens.size() >= 2)
  {
    std::string enemyDirection = tokens[1];
    int startState = 0;
    if (enemyDirection == "Left")
      SD_SET_LEFT(startState);
    else SD_SET_RIGHT(startState);
    enemy->SetState(startState);
  }

  return enemy;
}

Trigger::Trigger(Enemy* refer) : m_Refer(refer)
{
  // 
}

void Trigger::Start()
{
  if (this->IsDied())
    return;

  this->Die();
  m_Refer->Activate();
}
