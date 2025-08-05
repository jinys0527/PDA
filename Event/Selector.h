#pragma once
#include "CompositeNode.h"

class Selector : public CompositeNode
{
public:
	NodeState Tick() override;

private:
	int m_CurrIndex = 0;
};

