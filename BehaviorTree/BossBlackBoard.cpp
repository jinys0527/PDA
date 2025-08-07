#include "BossBlackBoard.h"

BossBlackBoard::BossBlackBoard(std::vector<std::shared_ptr<Telegraph>>& telegraphs, std::vector<std::shared_ptr<GameObject>>& anim)
{
	SetValue("BossMaxHP", 100.0f);
	SetValue("BossCurrHP", GetValue<float>("BossMaxHP").value());
	SetValue("IdleCoolDown", 1.0f);

	//���� ���� ���� ��ü
	SetValue("BossTelegraph", telegraphs);
	SetValue("BossAnims", anim);

	//���� ���� Ȱ��ȭ ����?
	// ���߿� ���� �̸������� ���⿡ Skill_1 ��� �Է�
	SetValue("Skill_1", std::vector<int>{0, 1, 2, 3});
	SetValue("Skill_2", std::vector<int>{4, 5, 6, 7});
	SetValue("Skill_3", std::vector<int>{8, 9, 10, 11});



	//��ٿ� ��� �ð�
	SetValue("ElapsedIdleTime", 0.0f);
	SetValue("WarningTime", 3.0f);


	SetValue("3Phase", false);
	SetValue("RandomValue", 0.0f);

	SetValue("SkillWeight_1", 1.0f);
	SetValue("SkillWeight_2", 1.0f);
	SetValue("SkillWeight_3", 1.0f);

	SetValue("SkillChance_1", 0.f);
	SetValue("SkillChance_2", 0.f);
	SetValue("SkillChance_3", 0.f);

	SetValue("CurrPhase", 0);
}


