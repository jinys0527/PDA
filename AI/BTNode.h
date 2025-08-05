#pragma once






enum class NodeState
{
	Success,
	Failure,
	Running,
};

class BTNode
{
public :
	virtual ~BTNode() = default;
	virtual NodeState Tick() = 0;
};

