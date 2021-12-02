#pragma once

#include "../Object/Object.hh"
#include "Engine/Scene/Scene.hh"

class PlayScene : public Scene
{
public:
  PlayScene() = default; 

  /// GETTER /// 
  Player* GetPlayer() const;

  /// SETTER /// 
  void SetPlayer(Player* player);
  void SetKeyboardHandler(KeyboardEvent* handler);

  void AddRenderableObject(RenderableObject* object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Player*                        m_Player;
  std::vector<Object*>           m_Objects;
  std::vector<RenderableObject*> m_RenderableObjects;
};
