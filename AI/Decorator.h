#pragma once
#include "BTnode.h"

class Decorator : public BTNode
{
public:
	void SetChild(std::shared_ptr<BTNode> child)
	{
		m_Children = child;
	}

protected:
	std::shared_ptr<BTNode> m_Children;
};

