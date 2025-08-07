#pragma once
#include "BlackBoard.h"

class Telegraph;

class BossBlackBoard : public BlackBoard
{
public:
	BossBlackBoard() = delete;
	BossBlackBoard(std::vector<std::shared_ptr<Telegraph>>& telegraphs);

private:
};

