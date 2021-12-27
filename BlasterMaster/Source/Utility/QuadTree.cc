#include "QuadTree.hh"

constexpr size_t NUMBER_PARTITIONS = 4;

QuadNode::QuadNode(float width, float height) : 
  m_Level(0), Box2F(0, 0, width, height)
{
}

void QuadNode::Insert(Ref<Object> object)
{
  Insert(std::vector<Ref<Object>>{ object });
}

void QuadNode::Insert(const std::vector<Ref<Object>>& objects)
{
  m_Objects.insert(objects.begin(), objects.end());
  if (0 <= m_Level || (m_Objects.empty() && m_Children.empty()))
    return;

  if (m_Children.empty())
    m_Children = CreateChildren();

  // Partitioning objects to partitions
  std::vector<std::vector<Ref<Object>>> m_Part(NUMBER_PARTITIONS);
  for (const auto& object : m_Objects)
    for (size_t i = 0; i < NUMBER_PARTITIONS; ++i)
      if (Collision::AABB(m_Children[i], *object))
        m_Part[i].emplace_back(object);

  // Migrate object from this node to children
  m_Objects.clear();
  for (size_t i = 0; i < NUMBER_PARTITIONS; ++i)
    if (m_Part[i].size() != 0)
      m_Children[i].Insert(m_Part[i]);
}

void QuadNode::Remove(const Ref<Object>& object)
{
  // Leaf node
  if (m_Objects.size())
    if (auto iter = m_Objects.find(object); iter != m_Objects.end())
      m_Objects.erase(iter);

  // Children traversal
  for (size_t i = 0; i < m_Children.size(); ++i)
    if (Collision::AABB(m_Children[i], *object))
      m_Children[i].Remove(object);
}

void QuadNode::Retrieve(const Box2F& box, std::set<Ref<Object>>& container) const
{
  if (m_Children.empty())
    return container.insert(m_Objects.begin(), m_Objects.end());

  for (const auto& child : m_Children)
    if (Collision::AABB(box, child))
      child.Retrieve(box, container);
}

std::vector<Ref<Object>> QuadNode::Retrieve(const Box2F& box) const
{
  std::set<Ref<Object>> container;
  this->Retrieve(box, container);
  return std::vector<Ref<Object>>(container.begin(), container.end());
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
