#pragma once
#include "BTNode.h"
#include "Telegraph.h"
#include "GameObject.h"

//�� �������
class SkillNode : public BTNode
{
public:
	SkillNode(std::string name) : BTNode(name) {}

	virtual NodeState Tick(BlackBoard& bb, float deltaTime) override = 0;

protected:
	virtual void StartWarning(BlackBoard& bb) {}
	virtual void EndWarning(BlackBoard& bb) {}
	virtual void Reset() {}
};

