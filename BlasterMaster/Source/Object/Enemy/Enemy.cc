#include "Enemy.hh"
#include "Utility/Strings.hh"

Enemy::Enemy() : m_IsActivated(true), m_IsTriggered(false)
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

Ref<Enemy> Enemy::Create(const std::string& name)
{
  auto tokens = Strings::Split(name, ".");
  std::string enemyType = tokens[0];

  Ref<Enemy> enemy;
       if (enemyType == "Interrupt" ) enemy = CreateRef<Interrupt>();
  else if (enemyType == "Ballbot"   ) enemy = CreateRef<Ballbot>();
  else if (enemyType == "Stuka"     ) enemy = CreateRef<Stuka>();
  else if (enemyType == "Eyelet"    ) enemy = CreateRef<Eyelet>();
  else if (enemyType == "Ball-Carry") enemy = CreateRef<BallCarry>();
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
