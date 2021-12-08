#include "Bullet.hh"
#include "Object/Object.hh"
#include <algorithm>

void Bullet::Update(TimeStep elapsed)
{
  m_X += m_SpeedX * elapsed;
  m_Y += m_SpeedY * elapsed;
}

void Bullet::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  std::sort(objects.begin(), objects.end(), [](Object* shl, Object* shr) {
    return shl->GetX() < shr->GetX();
  });

  for (size_t i = 0; i < objects.size(); ++i)
  {
    auto& object = objects[i];
    if (dynamic_cast<Enemy*>(object) && !object->IsDied())
    {
      bool killed = Collision::AABB(*this, *object);
      if (!killed)
      {
        float deltaTime = Collision::SweptAABB(*this, *object);
        killed = (0 <= deltaTime && deltaTime <= elapsed);
      }

      if (killed)
      {
        this->Die();
        object->Die();
        return;
      }
    }
  }

  Update(elapsed);
}
