#include "Collider2D.hh"

// Collider2D::Collider2D(Ref<Object> refer, Vector2F scale) :
//   m_Refer(refer), m_Scale(scale)
// {
// }

Collider2D::Collider2D(Object* refer) : m_Refer(refer)
{
}

Box2F Collider2D::GetBoundingBox() const
{
  return static_cast<Box2F>(*this->m_Refer);
  // Vector2F center = m_Refer->GetCenter();
  // Vector2F scaledSize = m_Refer->GetSize() * m_Scale;
  // Vector2F scaledLocation = center - (scaledSize / 2);
  // return Box2F(scaledLocation, scaledSize.GetX(), scaledSize.GetY());
}
