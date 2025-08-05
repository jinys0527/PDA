#pragma once
#include <memory>

class BlackBoard;
class BTNode;

class BossBehaviorTree
{
	BossBehaviorTree(BlackBoard& blackBoard) : m_BlackBoard(blackBoard) {}

	void Initialize();
private:
	BlackBoard& m_BlackBoard;
	std::shared_ptr<BTNode> m_BehaviorTree;
};

