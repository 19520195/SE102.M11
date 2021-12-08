#include "Animation.hh"
#include "Renderer.hh"

std::shared_ptr<AnimationBase> AnimationBase::s_Instance = std::make_shared<AnimationBase>();

Frame::Frame(Sprite* sprite, TimeStep time)
{
  m_Sprite = sprite;
  m_Time = time;
}

Sprite* Frame::GetSprite()
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

void Animation::Add(int spriteID, TimeStep time)
{
  if (time == 0) time = this->m_DefaultTime;
  Sprite* sprite = SpriteBase::GetInstance()->Get(spriteID);
  m_Frames.push_back(std::make_shared<Frame>(sprite, time));
}

void Animation::Render(float X, float Y)
{
	TimeStep currentFrameTime = GetTickCount64();
	if (m_CurrentFrame == -1)
	{
		m_CurrentFrame = 0;
		m_LastFrameTime = currentFrameTime;
	}
	else
	{
		TimeStep t = m_Frames[m_CurrentFrame]->GetTime(); 
		if (currentFrameTime - m_LastFrameTime > t)
		{
			m_CurrentFrame++;
			m_LastFrameTime = currentFrameTime;
			if (m_CurrentFrame == m_Frames.size()) m_CurrentFrame = 0;
		}
	}

	m_Frames[m_CurrentFrame]->GetSprite()->Render(X, Y);
}

void Animation::Render(float X, float Y, TimeStep elapsed)
{
	TimeStep offset = m_Frames.size() * m_DefaultTime;
	m_TimeStep = (m_TimeStep + offset + elapsed) % (offset);

	size_t frameID = (size_t)(m_TimeStep / m_DefaultTime);
	m_Frames[frameID]->GetSprite()->Render(X, Y);
}

Animation* AnimationBase::Add(size_t ID, Animation* animation)
{
	std::shared_ptr<Animation>& pAnimation = m_Animations[ID];
	pAnimation.reset(animation);
	return pAnimation.get();
}

Animation* AnimationBase::Get(size_t ID)
{
	return m_Animations[ID].get(); 
}

AnimationBase* AnimationBase::GetInstance()
{
	return s_Instance.get();
}
