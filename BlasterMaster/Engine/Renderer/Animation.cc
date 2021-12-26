#include "Animation.hh"
#include "Renderer.hh"
#include "Engine/Core/Game.hh"

Frame::Frame(Ref<Sprite> sprite, TimeStep time)
{
  m_Sprite = sprite;
  m_Time = time;
}

Ref<Sprite> Frame::GetSprite()
{
	return m_Sprite;
}

TimeStep Frame::GetTime()
{
	return m_Time;
}

Animation::Animation(TimeStep defaultTime)
{
  m_DefaultTime = defaultTime;
  m_CurrentFrame = -1;
  m_LastFrameTime = -1;
	m_TimeStep = 0;
}

void Animation::Add(const std::string& name, TimeStep time)
{
	if (time == 0) time = this->m_DefaultTime;
	Ref<Sprite> sprite = SpriteBase::GetInstance()->Get(name);
	m_Frames.push_back(std::make_shared<Frame>(sprite, time));
}

void Animation::Render(float X, float Y, TimeStep elapsed)
{
	TimeStep offset = m_Frames.size() * m_DefaultTime;
	m_TimeStep = (m_TimeStep + offset + elapsed) / (offset);
	m_TimeStep = (m_TimeStep - std::floor(m_TimeStep)) * offset;

	size_t frameID = static_cast<size_t>(m_TimeStep / m_DefaultTime);
	m_Frames[frameID]->GetSprite()->Render(X, Y);
}


Ref<AnimationBase> AnimationBase::s_Instance = CreateRef<AnimationBase>();
Ref<AnimationBase> AnimationBase::GetInstance() { return s_Instance; }

Ref<Animation> AnimationBase::Add(const std::string& name, Ref<Animation> animation)
{
	Ref<Animation>& refer = m_Animations[name];
	return refer = animation;
}

Ref<Animation> AnimationBase::Get(const std::string& name)
{
	return m_Animations[name];
}
