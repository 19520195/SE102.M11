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

  void SetForeground(uint32_t ID);
  void SetBackground(uint32_t ID);
  void SetPlayer(Ref<Player> player);
  void SetKeyboardHandler(Ref<KeyboardEvent> handler);

  void AddObject(Object* object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Ref<Player>               m_Player;
  std::vector<Object*>      m_Objects;
  std::unique_ptr<QuadTree> m_QuadTree;

  uint32_t m_ForegroundID;
  uint32_t m_BackgroundID;
};
