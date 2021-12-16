#include "Trigger.hh"

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
