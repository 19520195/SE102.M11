#pragma once

#include "Engine/Scene/Scene.hh"
#include "Object/Object.hh"
#include "Utility/QuadTree.hh"

class PlayScene : public Scene
{
public:
  PlayScene();
  PlayScene(const std::string& rFile, const std::string& oFile);

  Player* GetPlayer() const;
  std::vector<Object*> GetObjects() const;

  void SetPlayer(Ref<Player> player);
  void SetKeyboardHandler(Ref<KeyboardEvent> handler);

  void AddObject(Object* object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Ref<Player>               m_Player;
  std::vector<Object*>      m_Objects;
  std::unique_ptr<QuadTree> m_QuadTree;
};
