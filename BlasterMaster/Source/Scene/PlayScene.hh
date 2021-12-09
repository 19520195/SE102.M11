#pragma once

#include "Object/Object.hh"
#include "Engine/Scene/Scene.hh"

class PlayScene : public Scene
{
public:
  PlayScene();

  Player* GetPlayer() const;

  void SetBackground(size_t ID); 
  void SetPlayer(Player* player);
  void SetKeyboardHandler(KeyboardEvent* handler);

  void AddObject(Object* object); 

  virtual void Update(TimeStep elapsed);
  virtual void Render(TimeStep elapsed);

private:
  Player*              m_Player;
  std::vector<Object*> m_Objects;

  size_t m_BackgroundID;
};
