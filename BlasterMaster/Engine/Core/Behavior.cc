#include "Behavior.hh"

Behavior::Behavior(const Direct& direct)
{
  m_Direct = direct;
}

Behavior::Direct Behavior::GetDirect() const
{
  return m_Direct;
}

void Behavior::SetDirect(const Direct& direct)
{
  m_Direct = direct;
}
