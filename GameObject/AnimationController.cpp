#include "AnimationController.h"

void AnimationController::SetClip(const AnimationClip* clip)
{
	m_Clip = clip;
	m_Elapsed = 0.f;
}

void AnimationController::SetLooping(bool loop)
{
	m_Loop = loop;
}

void AnimationController::SetElapsed(float elapsedTime)
{
	m_Elapsed = elapsedTime;
}

const Frame& AnimationController::GetCurrentFrame() const
{
	static Frame dummy{ {0, 0, 0, 0}, 0.f };

	if (!m_Clip || m_Clip->GetFrames().empty())
	{
		return dummy;
	}

	float accum = 0.f;
	for (auto& frame : m_Clip->GetFrames())
	{
		accum += frame.m_Duration;

		if (m_Elapsed < accum)
			return frame;
	}

	return m_Clip->GetFrames().back();
}

void AnimationController::Update(float deltaTime)
{
	if (!m_Clip) return;
	m_Elapsed += deltaTime;

	float total = m_Clip->GetTotalDuration();

	if (m_Loop)
	{
		if (m_Elapsed >= total)
		{
			m_Elapsed = std::fmod(m_Elapsed, total);
		}
	}
	else
	{
		if (m_Elapsed > total)
		{
			m_Elapsed = total;
		}
	}
}

void AnimationController::OnEvent(EventType type, const void* data)
{

}

void AnimationController::Serialize(nlohmann::json& j) const
{
}

void AnimationController::Deserialize(const nlohmann::json& j)
{
}
