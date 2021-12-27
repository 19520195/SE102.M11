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
  std::vector<Ref<Object>> GetObjects();

  void SetPlayer(Ref<Player> player);
  void SetKeyboardHandler(Ref<KeyboardEvent> handler);

  void AddObject(Ref<Object> object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Ref<Sprite> m_Foreground;
  Ref<Sprite> m_Background;

  Ref<Player>               m_Player;
  std::unique_ptr<QuadTree> m_QuadTree;

  TimeStep m_LastGetObject;
  std::vector<Ref<Object>>  m_Objects;
};
