#pragma once

#include "Component.h"
#include "GameObject.h"

// �ٴ� ���� �÷��̾ ������ ������Ʈ
class RunPlayerController : public Component, public IEventListener
{
public:
	RunPlayerController() : Component() 
	{
		// ���� ����
	}

	virtual ~RunPlayerController()
	{
		// ���� ����
	}

	virtual void OnEvent(EventType type, const void* data) override;// �Է� ���� ��

	virtual void Update(float deltaTime) override;// ���� �� �߰��� ������Ʈ
	virtual std::string GetTypeName() override;

	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

private:
	// �Է� ó��
	bool m_IsWPressed = false;
	bool m_IsAPressed = false;
	bool m_IsSPressed = false;
	bool m_IsDPressed = false;

};

