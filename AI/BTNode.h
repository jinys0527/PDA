#pragma once
#include <vector>
#include <memory>
#include <iostream>



class BlackBoard;


enum class NodeState
{
	Success,
	Failure,
	Running,
};

class BTNode
{
public :
	BTNode(std::string name) : m_name(name) {}

	virtual ~BTNode() = default;
	virtual NodeState Tick(BlackBoard& bb) = 0;

protected:
	std::string m_name;

};

