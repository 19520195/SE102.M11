#pragma once

#include "Engine/Scene/Scene.hh"
#include "Object/Object.hh"
#include "Utility/QuadTree.hh"

class PlayScene : public Scene
{
public:
  PlayScene();
  PlayScene(const std::string& conf);

  Player* GetPlayer() const;
  std::vector<Object*> GetObjects() const;

  void SetBackground(size_t ID); 
  void SetPlayer(Player* player);
  void SetKeyboardHandler(KeyboardEvent* handler);

  void AddObject(Object* object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Player*                   m_Player;
  std::vector<Object*>      m_Objects;
  std::unique_ptr<QuadTree> m_QuadTree;

  size_t m_BackgroundID;
};
