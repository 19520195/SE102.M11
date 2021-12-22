#pragma once
#include "Engine/Core/Base.hh"
#include "Engine/Core/Object.hh"
#include <vector>
#include <set>

class QuadNode : public Box2F
{
public:
  enum Quarter : size_t 
  { 
    NorthWest,
    NorthEast,
    SouthWest,
    SouthEast,
  };

  using Container = std::vector<Object*>;

public:
  QuadNode() = default;
  QuadNode(float width, float height);

  void Insert(Object* object);
  void Retrieve(const Box2F& box, std::set<Object*>& container) const;
  Container Retrieve(const Box2F& box) const;

protected:
  std::vector<QuadNode> CreateChildren() const;

protected:
  uint32_t              m_Level;
  Container             m_Objects;
  std::vector<QuadNode> m_Children;
};

typedef QuadNode QuadTree;
