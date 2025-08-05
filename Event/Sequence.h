#pragma once
#include "CompositeNode.h"

class Sequence : public CompositeNode
{
public:
	NodeState Tick() override;

private: 
	int m_CurrIndex = 0;
};

