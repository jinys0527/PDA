#pragma once
#include "Decorator.h"

class Repeater : public Decorator
{
public:
	Repeater(int repeat) : m_TimeToRepeat(repeat) {}

	NodeState Tick() override;

private:
	int m_TimeToRepeat;
	int m_TimesDone = 0;
};

