#pragma once

#include "Engine/Core/Object.hh"

class Brick : public Object 
{
public:
  Brick()
  {
    m_Collider->SetMaterial(CreateRef<Material>());
  }

  void Die() override
  {
    //
  }
};
