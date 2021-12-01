#pragma once

#include "../Object/Object.hh"
#include "Engine/Scene/Scene.hh"

class PlayScene : public Scene
{
public:
  Player* GetPlayer() const;

  void SetPlayer(Player* player);
  void SetKeyboardHandler(KeyboardEvent* handler); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Player*              m_Player;
  std::vector<Object*> m_Objects;
};
