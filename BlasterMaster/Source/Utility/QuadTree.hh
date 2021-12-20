#pragma once
#include "Engine/Core/Object.hh"
#include <vector>

class QuadNode
{
public:
  using Container = std::vector<Object*>;

public:
  QuadNode() = default;
  void Insert(Object* object);
  void Retrieve(Box2F, Container& container);
  Container Retrieve(Box2F);

protected:
  Container             m_Objects;
  std::vector<QuadNode> m_Children;
};

class QuadTree : public QuadNode
{
public:
  // 

private:
  // 
};
