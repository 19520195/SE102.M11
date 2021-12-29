#include "LazerGuard.hh"

LazerGuard::LazerGuard()
{
  m_Render = CreateRef<Sprite>(0.f, 0.f, 16.f, 16.f, TextureBase::GetInstance()->Get("RBB"));
}
