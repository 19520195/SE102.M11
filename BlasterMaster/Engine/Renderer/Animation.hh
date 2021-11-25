#pragma once

#include <vector>

#include "Sprite.hh"
#include "Engine/Core/TimeStep.hh"

class Frame
{
public:
  Frame(Sprite* sprite, TimeStep time);

  Sprite* GetSprite();
  TimeStep GetTime();

private:
  Sprite*  m_Sprite;
  TimeStep m_Time;
};

class Animation
{
public:
  Animation(TimeStep defaultTime);

  void Add(int spriteID, TimeStep time = 0);
  void Render(float X, float Y);

private:
  TimeStep m_DefaultTime;
  size_t   m_CurrentFrame;

  TimeStep m_LastFrameTime;
  std::vector<std::shared_ptr<Frame>> m_Frames;
};

class AnimationBase
{
public:
  void Add(size_t ID, Animation* animation);

  Animation* Get(size_t ID); 
  
  static AnimationBase* Get(); 

private:
  std::unordered_map<size_t, std::shared_ptr<Animation>> m_Animations;

private:
  static std::shared_ptr<AnimationBase> s_Instance;
};
