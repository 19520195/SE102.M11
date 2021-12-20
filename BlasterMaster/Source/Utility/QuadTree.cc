#include "QuadTree.hh"

void QuadNode::Insert(Object* object)
{
  m_Objects.emplace_back(object);
  // HANDLE QUADNODE LATER //
}

void QuadNode::Retrieve(Box2F, Container& container)
{
  container = m_Objects;
}

QuadNode::Container QuadNode::Retrieve(Box2F box)
{
  Container container;
  this->Retrieve(box, container);
  return container;
}
