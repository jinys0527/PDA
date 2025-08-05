#include "BossBlackBoard.h"

BossBlackBoard::BossBlackBoard()
{
	SetValue("BossMaxHP", 100.0f);
	SetValue("BossCurrHP", GetValue<float>("m_BossMaxHP").value());
	SetValue("IdleCoolDown", 1.0f);
	SetValue("3Phase", 1.0f);
	SetValue("RandomValue", 0.0f);

	SetValue("SkillWeight_1", 1.0f);
	SetValue("SkillWeight_2", 1.0f);
	SetValue("SkillWeight_3", 1.0f);

	SetValue("SkillChance_1", 0.f);
	SetValue("SkillChance_2", 0.f);
	SetValue("SkillChance_3", 0.f);

}