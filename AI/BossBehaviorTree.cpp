#include "BossBehaviorTree.h"
#include "Selector.h"

void BossBehaviorTree::Initialize()
{
	auto Phase_1 = std::make_shared<Selector>("Phase_1");
	auto Phase_2 = std::make_shared<Selector>("Phase_2");
	auto Phase_3 = std::make_shared<Selector>("Phase_3");


	auto Root = std::make_shared<Selector>("Root");
	Root->AddChild(Phase_1);
	Root->AddChild(Phase_2);
	Root->AddChild(Phase_3);


	m_BehaviorTree = Root;
}
