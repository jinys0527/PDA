#pragma once
#include "BTNode.h"

class CompositeNode : public BTNode
{
public:
	CompositeNode(std::string name) : BTNode(name) {}
	void AddChild(std::shared_ptr<BTNode> child);

protected:
	std::vector<std::shared_ptr<BTNode>> m_Children;
};

