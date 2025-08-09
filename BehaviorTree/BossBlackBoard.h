#pragma once
#include "BlackBoard.h"

class Telegraph;
class GameObject;

class BossBlackBoard : public BlackBoard
{
public:
	BossBlackBoard() = delete;
	BossBlackBoard(std::vector<std::shared_ptr<Telegraph>>& telegraphs, std::vector<std::shared_ptr<GameObject>>& anim);

private:
};

