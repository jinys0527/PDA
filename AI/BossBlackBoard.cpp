#include "BossBlackBoard.h"

BossBlackBoard::BossBlackBoard()
{
	SetValue("BossMaxHP", 100.0f);
	SetValue("BossCurrHP", GetValue<float>("BossMaxHP").value());
	SetValue("IdleCoolDown", 1.0f);

	//쿨다운 경과 시간
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