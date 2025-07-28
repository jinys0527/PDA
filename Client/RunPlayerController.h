#pragma once

#include "Component.h"
#include "GameObject.h"

// 뛰는 씬의 플레이어를 조종할 컴포넌트
class RunPlayerController : public Component, public IEventListener
{
public:
	RunPlayerController() : Component() 
	{
		// 아직 없음
	}

	virtual ~RunPlayerController()
	{
		// 아직 없음
	}

	virtual void OnEvent(EventType type, const void* data) override;// 입력 받을 곳

	virtual void Update(float deltaTime) override;// 추후 더 추가할 업데이트
	virtual std::string GetTypeName() override;

	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

private:
	// 입력 처리
	bool m_IsWPressed = false;
	bool m_IsAPressed = false;
	bool m_IsSPressed = false;
	bool m_IsDPressed = false;

};

