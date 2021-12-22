#include "QuadTree.hh"

QuadNode::QuadNode(float width, float height) : 
  m_Level(0), Box2F(0, 0, width, height)
{
}

void QuadNode::Insert(Object* object)
{
  if (0 <= m_Level || (m_Objects.empty() && m_Children.empty()))
    return (void)m_Objects.emplace_back(object);
  
  if (m_Children.empty())
    m_Children = CreateChildren();

  m_Objects.emplace_back(object);
  for (const auto& object : m_Objects)
    for (auto& child : m_Children)
      if (Collision::AABB(child, *object))
        child.Insert(object);
  m_Objects.clear();
}

void QuadNode::Retrieve(const Box2F& box, std::set<Object*>& container) const
{
  if (m_Children.empty())
    return container.insert(m_Objects.begin(), m_Objects.end());

  for (const auto& child : m_Children)
    if (Collision::AABB(box, child))
      child.Retrieve(box, container);
}

QuadNode::Container QuadNode::Retrieve(const Box2F& box) const
{
  std::set<Object*> container;
  // Container container;
  this->Retrieve(box, container);
  // std::sort(container.begin(), container.end());
  // container.resize(std::unique(container.begin(), container.end()) - container.begin());
  return Container(container.begin(), container.end());
}

std::vector<QuadNode> QuadNode::CreateChildren() const
{
  float halfWidth = m_Width / 2;
  float halfHeight = m_Height / 2;
  float middleX = m_X + halfWidth;
  float middleY = m_Y + halfHeight;

  auto children = std::vector<QuadNode>(4, QuadNode(halfWidth, halfHeight));
  children[SouthWest].SetLocation(m_X, m_Y);
  children[SouthEast].SetLocation(middleX, m_Y);
  children[NorthWest].SetLocation(m_X, middleY);
  children[NorthEast].SetLocation(middleX, middleY);

  for (auto& child : children)
    child.m_Level = m_Level + 1;
  return children;
}
