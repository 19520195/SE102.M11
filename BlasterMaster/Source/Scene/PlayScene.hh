#pragma once

#include "Engine/Scene/Scene.hh"
#include "Object/Object.hh"
#include "Utility/QuadTree.hh"

class BoundingBox
{
public:
  BoundingBox(Box2F box)
  {
    m_Location = box.GetLocation();
    m_Box = CreateRef<Sprite>(
      0.f, 0.f, box.GetHeight(), box.GetWidth(),
      TextureBase::GetInstance()->Get("Blue-BBox"));
  }

  void Render()
  {
    m_Box->Render(m_Location.GetX(), m_Location.GetY());
  }

private:
  Vector2F m_Location;
  Ref<Sprite> m_Box;
};

class PlayScene : public Scene
{
public:
  PlayScene();
  PlayScene(const std::string& rFile, const std::string& oFile);

  Player* GetPlayer() const;
  std::vector<Ref<Object>> GetObjects();

  void SetPlayer(Ref<Player> player);
  void SetKeyboardHandler(Ref<KeyboardEvent> handler);

  Ref<Object> FindRef(Object* object) const;

  void AddObject(Ref<Object> object); 
  void AddBounding(Ref<BoundingBox> box);

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Ref<Sprite> m_Foreground;
  Ref<Sprite> m_Background;
  List<Ref<BoundingBox>> m_Boxes;
 
  float m_ScreenWidth;
  float m_ScreenHeight;

  Ref<Player>     m_Player;
  Scope<QuadTree> m_QuadTree;

  TimeStep m_LastGetObject;
  List<Ref<Object>>  m_Objects;
};
