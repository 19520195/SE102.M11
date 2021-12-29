#include "GX680.hh"

GX680::GX680()
{ 
  m_Render = CreateRef<Sprite>(0.f, 0.f, 16.f, 16.f, TextureBase::GetInstance()->Get("RBB"));
}

GX680S::GX680S()
{
  m_Render = CreateRef<Sprite>(0.f, 0.f, 16.f, 16.f, TextureBase::GetInstance()->Get("RBB"));
}
