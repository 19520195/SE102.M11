#pragma once
#include "Engine/Core/Base.hh"
#include "Engine/Core/Object.hh"
#include <vector>
#include <set>
#include <unordered_set>

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

public:
  QuadNode() = default;
  QuadNode(float width, float height);

  void Insert(Ref<Object> object);
  void Insert(const std::vector<Ref<Object>>& objects);
  void Remove(const Ref<Object>& object);

  void Retrieve(const Box2F& box, std::set<Ref<Object>>& container) const;
  std::vector<Ref<Object>> Retrieve(const Box2F& box) const;

protected:
  std::vector<QuadNode> CreateChildren() const;

protected:
  uint32_t                        m_Level;
  std::vector<QuadNode>           m_Children;
  std::unordered_set<Ref<Object>> m_Objects;
};

typedef QuadNode QuadTree;
