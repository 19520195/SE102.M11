#pragma once
#include "Sprite.hh"
#include "Engine/Core/TimeStep.hh"
#include <vector>

class Frame
{
public:
  Frame(Ref<Sprite> sprite, TimeStep time);

  TimeStep GetTime();
  Ref<Sprite> GetSprite();

private:
  TimeStep    m_Time;
  Ref<Sprite> m_Sprite;
};

class Animation : public IRender2D
{
public:
  Animation(TimeStep defaultTime);

  void Add(const std::string& name, TimeStep time = 0);
  void Render(float X, float Y, TimeStep elapsed);

private:
  TimeStep m_DefaultTime;
  size_t   m_CurrentFrame;
  TimeStep m_TimeStep; 

  TimeStep m_LastFrameTime;
  std::vector<Ref<Frame>> m_Frames;
};

class AnimationBase
{
public:
  static Ref<AnimationBase> GetInstance();

  Ref<Animation> Add(const std::string& name, Ref<Animation> animation);
  Ref<Animation> Get(const std::string& name);
 
private:
  static Ref<AnimationBase> s_Instance;
  HashTable<std::string, Ref<Animation>> m_Animations;
};
