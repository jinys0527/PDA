#include "BossBehaviorTree.h"
#include "Selector.h"
#include "SkillCondition.h"
#include "PhaseChecker.h"
#include "BossCoolDown.h"
#include "Sequence.h"
#include "ArmSmash.h"


void BossBehaviorTree::Initialize()
{
	auto P1_PhaseChecker = std::make_shared<PhaseChecker>("PhaseChecker_1");
	auto P2_PhaseChecker = std::make_shared<PhaseChecker>("PhaseChecker_2");


	auto P1_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown");
	auto P2_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown");


	auto P1_Skill_1_Con = std::make_shared<SkillCondition>("Skill_1_Con");
	auto P1_Skill_2_Con = std::make_shared<SkillCondition>("Skill_2_Con");
	auto P1_Skill_3_Con = std::make_shared<SkillCondition>("Skill_3_Con");

	auto P2_Skill_1_Con = std::make_shared<SkillCondition>("Skill_1_Con");
	auto P2_Skill_2_Con = std::make_shared<SkillCondition>("Skill_2_Con");
	auto P2_Skill_3_Con = std::make_shared<SkillCondition>("Skill_3_Con");

	auto P1_Skill_1_ArmSmash = std::make_shared<ArmSmash>("Skill_1_ArmSmash");
	auto P1_Skill_2_ArmSmash = std::make_shared<ArmSmash>("Skill_2_ArmSmash");
	auto P1_Skill_3_ArmSmash = std::make_shared<ArmSmash>("Skill_3_ArmSmash");

	auto P2_Skill_1_ArmSmash = std::make_shared<ArmSmash>("Skill_1_ArmSmash");
	auto P2_Skill_2_ArmSmash = std::make_shared<ArmSmash>("Skill_2_ArmSmash");
	auto P2_Skill_3_ArmSmash = std::make_shared<ArmSmash>("Skill_3_ArmSmash");


	auto P1_Skill_1 = std::make_shared<Sequence>("Skill_1");
	P1_Skill_1->AddChild(P1_Skill_1_Con);
	P1_Skill_1->AddChild(P1_Skill_1_ArmSmash);

	auto P1_Skill_2 = std::make_shared<Sequence>("Skill_2");
	P1_Skill_2->AddChild(P1_Skill_2_Con);
	P1_Skill_2->AddChild(P1_Skill_2_ArmSmash);

	auto P1_Skill_3 = std::make_shared<Sequence>("Skill_3");
	P1_Skill_3->AddChild(P1_Skill_3_Con);
	P1_Skill_3->AddChild(P1_Skill_3_ArmSmash);


	auto P2_Skill_1 = std::make_shared<Sequence>("Skill_1");
	P2_Skill_1->AddChild(P2_Skill_1_Con);
	P2_Skill_1->AddChild(P2_Skill_1_ArmSmash);

	auto P2_Skill_2 = std::make_shared<Sequence>("Skill_2");
	P2_Skill_2->AddChild(P2_Skill_2_Con);
	P2_Skill_2->AddChild(P2_Skill_2_ArmSmash);

	auto P2_Skill_3 = std::make_shared<Sequence>("Skill_3");
	P2_Skill_3->AddChild(P2_Skill_3_Con);
	P2_Skill_3->AddChild(P2_Skill_3_ArmSmash);




	auto Phase_1 = std::make_shared<Selector>("Phase_1");
	auto Phase_2 = std::make_shared<Selector>("Phase_2");



	Phase_1->AddChild(P1_PhaseChecker);
	Phase_1->AddChild(P1_BossCoolDown);
	Phase_1->AddChild(P1_Skill_1);
	Phase_1->AddChild(P1_Skill_2);
	Phase_1->AddChild(P1_Skill_3);



	Phase_2->AddChild(P2_PhaseChecker);
	Phase_2->AddChild(P2_BossCoolDown);
	Phase_2->AddChild(P2_Skill_1);
	Phase_2->AddChild(P2_Skill_2);
	Phase_2->AddChild(P2_Skill_3);




	auto Root = std::make_shared<Selector>("Root");
	Root->AddChild(Phase_1);
	Root->AddChild(Phase_2);


	m_BehaviorTree = Root;
}

void BossBehaviorTree::Tick(float deltaTime)
{
	if (m_BehaviorTree)
		m_BehaviorTree->Tick(m_BlackBoard, deltaTime);
}
