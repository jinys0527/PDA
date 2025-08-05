#pragma once
#include "BTNode.h"
#include <vector>
#include <memory>

class CompositeNode : public BTNode
{
public:
	void AddChild(std::shared_ptr<BTNode> child);

protected:
	std::vector<std::shared_ptr<BTNode>> m_Children;
};

