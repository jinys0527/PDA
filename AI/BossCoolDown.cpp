#include "BossCoolDown.h"
#include "BlackBoard.h"
#include <random>

NodeState BossCoolDown::Tick(BlackBoard& bb, float deltaTime)
{
	float coolDown = bb.GetValue<float>("IdleCoolDown").value();
	float elapsedTime = bb.GetValue<float>("ElapsedIdleTime").value();

	elapsedTime += deltaTime;
	

	if (elapsedTime < coolDown)
	{
		//std::cout << "ÄðÅ¸ÀÓ: " << elapsedTime << std::endl;

		bb.SetValue("ElapsedIdleTime", elapsedTime);
		return NodeState::Running;
	}


	float skillWeight_1 = bb.GetValue<float>("SkillWeight_1").value();
	float skillWeight_2 = bb.GetValue<float>("SkillWeight_2").value();
	float skillWeight_3 = bb.GetValue<float>("SkillWeight_3").value();

	float sum = skillWeight_1 + skillWeight_2 + skillWeight_3;

	float chance1 = skillWeight_1 / sum;
	float chance2 = (skillWeight_1 + skillWeight_2) / sum;
	float chance3 = (skillWeight_1 + skillWeight_2 + skillWeight_3) / sum;

	bb.SetValue("SkillChance_1", chance1);
	bb.SetValue("SkillChance_2", chance2);
	bb.SetValue("SkillChance_3", chance3);

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	float randVal = dist(gen);
	bb.SetValue("RandomValue", randVal);

	bb.SetValue("ElapsedIdleTime", 0.f);

	return NodeState::Failure;
}
