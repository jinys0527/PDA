#include "CompositeNode.h"

void CompositeNode::AddChild(std::shared_ptr<BTNode> child)
{
	children.push_back(child);
}
