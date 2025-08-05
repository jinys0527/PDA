#pragma once
#include "Decorator.h"

class Inverter : public Decorator
{
public:
	NodeState Tick() override;
};

