#pragma once
#include "Component.h"
#include "AnimationClip.h"

class AnimationController : public Component
{
public:
	virtual ~AnimationController() = default;

	bool IsValid() const { return m_Clip != nullptr; }

	void SetClip(const AnimationClip* clip);
	const AnimationClip* GetClip() const { return m_Clip; }

	void SetLooping(bool loop);

	float GetElapsed() const { return m_Elapsed; }
	void SetElapsed(float elapsedTime);

	const Frame& GetCurrentFrame() const;

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	std::string GetTypeName() override { return "AnimationController"; }
	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	const AnimationClip* m_Clip = nullptr;
	float m_Elapsed = 0.f;
	bool m_Loop = true;
};