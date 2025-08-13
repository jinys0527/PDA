#include "AnimationController.h"

bool AnimationController::IsLastFrameFinished() const
{
	if (!m_Clip || m_Clip->GetFrames().empty())
		return true; // 재생할 게 없음 = 끝난 상태

	const auto& frames = m_Clip->GetFrames();

	// 마지막 프레임의 시작 시간 계산
	float lastFrameStart = 0.f;
	for (size_t i = 0; i < frames.size() - 1; ++i)
	{
		lastFrameStart += frames[i].m_Duration;
	}

	// 마지막 프레임의 전체 재생 시간
	float lastFrameEnd = lastFrameStart + frames.back().m_Duration;

	// m_Elapsed가 마지막 프레임 끝나는 시각을 넘어섰는지 확인
	return m_Elapsed >= lastFrameEnd;
}

void AnimationController::FinishFrame()
{
	m_Elapsed = m_Clip->GetTotalDuration();
}

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
