#include "BossBlackBoard.h"

BossBlackBoard::BossBlackBoard(
	float scrollspeed,
	std::vector<std::shared_ptr<Telegraph>>& telegraphs, 
	std::vector<std::shared_ptr<GameObject>>& anims, 
	std::vector<std::shared_ptr<GameObject>>& fires,

	std::unordered_map<std::string, std::vector<int>>& animIndexMap,
	SoundManager& soundmanager)
	: BlackBoard(soundmanager)
{
	SetValue("ScrollSpeed", scrollspeed);

	SetValue("BossMaxHP", 149.0f);
	SetValue("BossCurrHP", GetValue<float>("BossMaxHP").value());
	SetValue("IdleCoolDown", 1.0f);

	//���� ���� ���� ��ü
	SetValue("BossTelegraph", telegraphs);

	//���� �ִϸ��̼� ����
	SetValue("LazerFire", fires);

	SetValue("BossAnims", anims);
	SetValue("BossAnimIndexMap", animIndexMap);

	//���� ���� Ȱ��ȭ ����?
	// ���߿� ���� �̸������� ���⿡ Skill_1 ��� �Է�
	SetValue("Row_1", std::vector<int>{0, 1, 2, 3, 4});
	SetValue("Row_2", std::vector<int>{5, 6, 7, 8, 9});
	SetValue("Row_3", std::vector<int>{10, 11, 12, 13, 14});

	SetValue("Pick_0", std::vector<int>{0});
	SetValue("Pick_1", std::vector<int>{1});
	SetValue("Pick_3", std::vector<int>{3});
	SetValue("Pick_4", std::vector<int>{4});
	SetValue("Pick_5", std::vector<int>{5});
	SetValue("Pick_6", std::vector<int>{6});
	SetValue("Pick_7", std::vector<int>{7});
	SetValue("Pick_8", std::vector<int>{8});
	SetValue("Pick_9", std::vector<int>{9});
	SetValue("Pick_10", std::vector<int>{10});
	SetValue("Pick_14", std::vector<int>{14});

	SetValue("Swip_L", std::vector<int>{0, 1, 2, 5, 6, 7, 10, 11, 12});
	SetValue("Swip_R", std::vector<int>{2, 3, 4, 7, 8, 9, 12, 13, 14});


	//��ٿ� ��� �ð�
	SetValue("ElapsedIdleTime", 0.0f);
	SetValue("WarningTime", 3.0f);


	SetValue("3Phase", false);
	SetValue("RandomValue", 0.0f);

	SetValue("SkillWeight_1", 1.0f);
	SetValue("SkillWeight_2", 5001.0f);
	SetValue("SkillWeight_3", 1.0f);
	SetValue("SkillWeight_4", 1.0f);
	SetValue("SkillWeight_5", 1.0f);

	SetValue("SkillChance_1", 0.f);
	SetValue("SkillChance_2", 0.f);
	SetValue("SkillChance_3", 0.f);
	SetValue("SkillChance_4", 0.f);
	SetValue("SkillChance_5", 0.f);

	SetValue("CurrPhase", 0);
}


