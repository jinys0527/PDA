#pragma once
#include "BlackBoard.h"

class Telegraph;
class GameObject;

class BossBlackBoard : public BlackBoard
{
public:
	BossBlackBoard() = delete;
	BossBlackBoard(
		std::vector<std::shared_ptr<Telegraph>>& telegraphs,
		std::vector<std::shared_ptr<GameObject>>& anims, 
		std::vector<std::shared_ptr<GameObject>>& fires,

		std::unordered_map<std::string, std::vector<int>>& animIndexMap,
		SoundManager& soundmanager);

};

