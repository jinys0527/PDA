#include "BossBehaviorTree.h"
#include "Selector.h"
#include "SkillCondition.h"
#include "PhaseChecker_1.h"
#include "PhaseChecker_3.h"
#include "BossCoolDown.h"
#include "Sequence.h"
#include "ArmSmash.h"
#include "WaitNode.h"
#include "ParallelNode.h"
#include "Pick.h"
#include "Lazer.h"
#include "ArmSwip.h"

void BossBehaviorTree::Initialize()
{
#pragma region PhaseCheckers_and_CoolDown
	auto P1_PhaseChecker = std::make_shared<PhaseChecker_1>("PhaseChecker_1");
	//auto P2_PhaseChecker = std::make_shared<PhaseChecker>("PhaseChecker_2");
	auto P3_PhaseChecker = std::make_shared<PhaseChecker_3>("PhaseChecker_3");

	auto P1_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown_1");
	//auto P2_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown");
	auto P3_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown_3");

#pragma endregion

#pragma region SkillConditions
	// 1페이즈 스킬 사용 가능 판정 노드
	auto P1_Skill_1_Con = std::make_shared<SkillCondition>("Skill_1_Con");
	auto P1_Skill_2_Con = std::make_shared<SkillCondition>("Skill_2_Con");
	auto P1_Skill_3_Con = std::make_shared<SkillCondition>("Skill_3_Con");
	auto P1_Skill_4_Con = std::make_shared<SkillCondition>("Skill_4_Con");
	auto P1_Skill_5_Con = std::make_shared<SkillCondition>("Skill_5_Con");

	// 3페이즈 스킬 사용 가능 판정 노드
	auto P3_Skill_1_Con = std::make_shared<SkillCondition>("Skill_1_Con");
	auto P3_Skill_2_Con = std::make_shared<SkillCondition>("Skill_2_Con");
	auto P3_Skill_3_Con = std::make_shared<SkillCondition>("Skill_3_Con");
	auto P3_Skill_4_Con = std::make_shared<SkillCondition>("Skill_4_Con");
	auto P3_Skill_5_Con = std::make_shared<SkillCondition>("Skill_5_Con");
#pragma endregion

#pragma region 1-1
	// 1-1 스킬
	auto P1_Skill_1_6_Pick_0 = std::make_shared<Pick>("Pick_0");
	auto P1_Skill_1_6_Pick_10 = std::make_shared<Pick>("Pick_10");

	auto P1_Skill_1_5_Pick_4 = std::make_shared<Pick>("Pick_4");
	auto P1_Skill_1_5_Pick_14 = std::make_shared<Pick>("Pick_14");
	auto P1_Skill_1_5_Wait = std::make_shared<WaitNode>("P1_Skill_1_5_Wait", 0.17f);
	auto P1_Skill_1_5_Parallel = std::make_shared<ParallelNode>("P1_Skill_1_5_Parallel");
	P1_Skill_1_5_Parallel->AddChild(P1_Skill_1_6_Pick_0);
	P1_Skill_1_5_Parallel->AddChild(P1_Skill_1_6_Pick_10);

	auto P1_Skill_1_4_Parallel = std::make_shared<ParallelNode>("P1_Skill_1_4_Parallel");
	P1_Skill_1_4_Parallel->AddChild(P1_Skill_1_5_Pick_4);
	P1_Skill_1_4_Parallel->AddChild(P1_Skill_1_5_Pick_14);
	auto P1_Skill_1_4_Sequence = std::make_shared<Sequence>("P1_Skill_1_4_Sequence");
	P1_Skill_1_4_Sequence->AddChild(P1_Skill_1_5_Wait);
	P1_Skill_1_4_Sequence->AddChild(P1_Skill_1_5_Parallel);

	auto P1_Skill_1_3_Wait = std::make_shared<WaitNode>("P1_Skill_1_3_Wait", 0.67f);
	auto P1_Skill_1_3_Parallel = std::make_shared<ParallelNode>("P1_Skill_1_3_Parallel");
	P1_Skill_1_3_Parallel->AddChild(P1_Skill_1_4_Parallel);
	P1_Skill_1_3_Parallel->AddChild(P1_Skill_1_4_Sequence);

	auto P1_Skill_1_2_Pick_5 = std::make_shared<Pick>("Pick_5");
	auto P1_Skill_1_2_Sequence = std::make_shared<Sequence>("P1_Skill_1_2_Sequence");
	P1_Skill_1_2_Sequence->AddChild(P1_Skill_1_3_Wait);
	P1_Skill_1_2_Sequence->AddChild(P1_Skill_1_3_Parallel);

	auto P1_Skill_1_1_Parallel = std::make_shared<ParallelNode>("P1_Skill_1_1_Parallel");
	P1_Skill_1_1_Parallel->AddChild(P1_Skill_1_2_Pick_5);
	P1_Skill_1_1_Parallel->AddChild(P1_Skill_1_2_Sequence);

	auto P1_Skill_1 = std::make_shared<Sequence>("P1_Skill_1");
	P1_Skill_1->AddChild(P1_Skill_1_Con);
	P1_Skill_1->AddChild(P1_Skill_1_1_Parallel);
#pragma endregion

#pragma region 1-2
	// 1-2
	auto P1_Skill_2_5_Wait = std::make_shared<WaitNode>("P1_Skill_2_5_Wait", 0.5f);
	auto P1_Skill_2_5_Lazer_3 = std::make_shared<Lazer>("Row_3");

	auto P1_Skill_2_4_ArmSmash_1 = std::make_shared<ArmSmash>("Row_1");
	auto P1_Skill_2_4_Sequence = std::make_shared<Sequence>("P1_Skill_2_4_Sequence");
	P1_Skill_2_4_Sequence->AddChild(P1_Skill_2_5_Wait);
	P1_Skill_2_4_Sequence->AddChild(P1_Skill_2_5_Lazer_3);

	auto P1_Skill_2_3_Wait = std::make_shared<WaitNode>("P1_Skill_2_3_Wait", 0.5f);
	auto P1_Skill_2_3_Parallel = std::make_shared<ParallelNode>("P1_Skill_2_3_Parallel");
	P1_Skill_2_3_Parallel->AddChild(P1_Skill_2_4_ArmSmash_1);
	P1_Skill_2_3_Parallel->AddChild(P1_Skill_2_4_Sequence);

	auto P1_Skill_2_2_Pick_5 = std::make_shared<Pick>("Pick_5");
	auto P1_Skill_2_2_Sequence = std::make_shared<Sequence>("P1_Skill_2_2_Sequence");
	P1_Skill_2_2_Sequence->AddChild(P1_Skill_2_3_Wait);
	P1_Skill_2_2_Sequence->AddChild(P1_Skill_2_3_Parallel);

	auto P1_Skill_2_1_Parallel = std::make_shared<ParallelNode>("P1_Skill_2_1_Parallel");
	P1_Skill_2_1_Parallel->AddChild(P1_Skill_2_2_Pick_5);
	P1_Skill_2_1_Parallel->AddChild(P1_Skill_2_2_Sequence);

	auto P1_Skill_2 = std::make_shared<Sequence>("P1_Skill_2");
	P1_Skill_2->AddChild(P1_Skill_2_Con);
	P1_Skill_2->AddChild(P1_Skill_2_1_Parallel);
#pragma endregion

#pragma region 1-3
	// 1-3
	auto P1_Skill_3_5_Wait = std::make_shared<WaitNode>("P1_Skill_3_5_Wait", 0.5f);
	auto P1_Skill_3_5_Pick_7 = std::make_shared<Pick>("Pick_7");

	auto P1_Skill_3_4_ArmSmash_3 = std::make_shared<ArmSmash>("Row_3");
	auto P1_Skill_3_4_Sequence = std::make_shared<Sequence>("P1_Skill_3_4_Sequence");
	P1_Skill_3_4_Sequence->AddChild(P1_Skill_3_5_Wait);
	P1_Skill_3_4_Sequence->AddChild(P1_Skill_3_5_Pick_7);

	auto P1_Skill_3_3_Wait = std::make_shared<WaitNode>("P1_Skill_3_3_Wait", 0.5f);
	auto P1_Skill_3_3_Parallel = std::make_shared<ParallelNode>("P1_Skill_3_3_Parallel");
	P1_Skill_3_3_Parallel->AddChild(P1_Skill_3_4_ArmSmash_3);
	P1_Skill_3_3_Parallel->AddChild(P1_Skill_3_4_Sequence);

	auto P1_Skill_3_2_Lazer_1 = std::make_shared<Lazer>("Row_1");
	auto P1_Skill_3_2_Sequence = std::make_shared<Sequence>("P1_Skill_3_2_Sequence");
	P1_Skill_3_2_Sequence->AddChild(P1_Skill_3_3_Wait);
	P1_Skill_3_2_Sequence->AddChild(P1_Skill_3_3_Parallel);

	auto P1_Skill_3_1_Parallel = std::make_shared<ParallelNode>("P1_Skill_3_1_Parallel");
	P1_Skill_3_1_Parallel->AddChild(P1_Skill_3_2_Lazer_1);
	P1_Skill_3_1_Parallel->AddChild(P1_Skill_3_2_Sequence);

	auto P1_Skill_3 = std::make_shared<Sequence>("P1_Skill_3");
	P1_Skill_3->AddChild(P1_Skill_3_Con);
	P1_Skill_3->AddChild(P1_Skill_3_1_Parallel);
#pragma endregion

#pragma region 1-4
	// 1-4
	auto P1_Skill_4_5_Wait = std::make_shared<WaitNode>("P1_Skill_4_5_Wait", 0.25f);
	auto P1_Skill_4_5_ArmSmash_3 = std::make_shared<ArmSmash>("Row_3");

	auto P1_Skill_4_4_ArmSmash_2 = std::make_shared<ArmSmash>("Row_2");
	auto P1_Skill_4_4_Sequence = std::make_shared<Sequence>("P1_Skill_4_4_Sequence");
	P1_Skill_4_4_Sequence->AddChild(P1_Skill_4_5_Wait);
	P1_Skill_4_4_Sequence->AddChild(P1_Skill_4_5_ArmSmash_3);

	auto P1_Skill_4_3_Wait = std::make_shared<WaitNode>("P1_Skill_4_3_Wait", 0.25f);
	auto P1_Skill_4_3_Parallel = std::make_shared<ParallelNode>("P1_Skill_4_3_Parallel");
	P1_Skill_4_3_Parallel->AddChild(P1_Skill_4_4_ArmSmash_2);
	P1_Skill_4_3_Parallel->AddChild(P1_Skill_4_4_Sequence);

	auto P1_Skill_4_2_ArmSmash_1 = std::make_shared<ArmSmash>("Row_1");
	auto P1_Skill_4_2_Sequence = std::make_shared<Sequence>("P1_Skill_4_2_Sequence");
	P1_Skill_4_2_Sequence->AddChild(P1_Skill_4_3_Wait);
	P1_Skill_4_2_Sequence->AddChild(P1_Skill_4_3_Parallel);

	auto P1_Skill_4_1_Parallel = std::make_shared<ParallelNode>("P1_Skill_4_1_Parallel");
	P1_Skill_4_1_Parallel->AddChild(P1_Skill_4_2_ArmSmash_1);
	P1_Skill_4_1_Parallel->AddChild(P1_Skill_4_2_Sequence);

	auto P1_Skill_4 = std::make_shared<Sequence>("P1_Skill_4");
	P1_Skill_4->AddChild(P1_Skill_4_Con);
	P1_Skill_4->AddChild(P1_Skill_4_1_Parallel);

#pragma endregion


#pragma region 3-1
	// 3-1 
	auto P3_Skill_1_5_Wait = std::make_shared<WaitNode>("P3_Skill_1_5_Wait", 0.33f);
	auto P3_Skill_1_5_ArmSwip_L = std::make_shared<ArmSwip>("Swip_L");

	auto P3_Skill_1_4_Pick_5 = std::make_shared<Pick>("Pick_5");
	auto P3_Skill_1_4_Sequence = std::make_shared<Sequence>("P3_Skill_1_4_Sequence");
	P3_Skill_1_4_Sequence->AddChild(P3_Skill_1_5_Wait);
	P3_Skill_1_4_Sequence->AddChild(P3_Skill_1_5_ArmSwip_L);

	auto P3_Skill_1_3_Wait = std::make_shared<WaitNode>("P3_Skill_1_3_Wait", 0.33f);
	auto P3_Skill_1_3_Parallel = std::make_shared<ParallelNode>("P3_Skill_1_3_Parallel");
	P3_Skill_1_3_Parallel->AddChild(P3_Skill_1_4_Pick_5);
	P3_Skill_1_3_Parallel->AddChild(P3_Skill_1_4_Sequence);

	auto P3_Skill_1_2_ArmSmash_1 = std::make_shared<ArmSmash>("Row_1");
	auto P3_Skill_1_2_Sequence = std::make_shared<Sequence>("P3_Skill_1_2_Sequence");
	P3_Skill_1_2_Sequence->AddChild(P3_Skill_1_3_Wait);
	P3_Skill_1_2_Sequence->AddChild(P3_Skill_1_3_Parallel);

	auto P3_Skill_1_1_Parallel = std::make_shared<ParallelNode>("P3_Skill_1_1_Parallel");
	P3_Skill_1_1_Parallel->AddChild(P3_Skill_1_2_ArmSmash_1);
	P3_Skill_1_1_Parallel->AddChild(P3_Skill_1_2_Sequence);

	auto P3_Skill_1 = std::make_shared<Sequence>("P3_Skill_1");
	P3_Skill_1->AddChild(P3_Skill_1_Con);
	P3_Skill_1->AddChild(P3_Skill_1_1_Parallel);
#pragma endregion

#pragma region 3-2
	// 1-5
	auto P3_Skill_2_5_Wait = std::make_shared<WaitNode>("P3_Skill_2_5_Wait", 0.33f);
	auto P3_Skill_2_5_Pick_4 = std::make_shared<Pick>("Pick_4");

	auto P3_Skill_2_4_Lazer_2 = std::make_shared<Lazer>("Row_2");
	auto P3_Skill_2_4_Sequence = std::make_shared<Sequence>("P3_Skill_2_4_Sequence");
	P3_Skill_2_4_Sequence->AddChild(P3_Skill_2_5_Wait);
	P3_Skill_2_4_Sequence->AddChild(P3_Skill_2_5_Pick_4);

	auto P3_Skill_2_3_Wait = std::make_shared<WaitNode>("P3_Skill_2_3_Wait", 0.33f);
	auto P3_Skill_2_3_Parallel = std::make_shared<ParallelNode>("P3_Skill_2_3_Parallel");
	P3_Skill_2_3_Parallel->AddChild(P3_Skill_2_4_Lazer_2);
	P3_Skill_2_3_Parallel->AddChild(P3_Skill_2_4_Sequence);

	auto P3_Skill_2_2_ArmSwip_L = std::make_shared<ArmSwip>("Swip_L");
	auto P3_Skill_2_2_Sequence = std::make_shared<Sequence>("P3_Skill_2_2_Sequence");
	P3_Skill_2_2_Sequence->AddChild(P3_Skill_2_3_Wait);
	P3_Skill_2_2_Sequence->AddChild(P3_Skill_2_3_Parallel);

	auto P3_Skill_2_1_Parallel = std::make_shared<ParallelNode>("P3_Skill_2_1_Parallel");
	P3_Skill_2_1_Parallel->AddChild(P3_Skill_2_2_ArmSwip_L);
	P3_Skill_2_1_Parallel->AddChild(P3_Skill_2_2_Sequence);

	auto P3_Skill_2 = std::make_shared<Sequence>("P3_Skill_2");
	P3_Skill_2->AddChild(P3_Skill_2_Con);
	P3_Skill_2->AddChild(P3_Skill_2_1_Parallel);
#pragma endregion

#pragma region Phase_1
	auto Phase_1_Skills = std::make_shared<Selector>("Phase_1_Skills");
	Phase_1_Skills->AddChild(P1_Skill_1);
	Phase_1_Skills->AddChild(P1_Skill_2);
	Phase_1_Skills->AddChild(P1_Skill_3);
	Phase_1_Skills->AddChild(P1_Skill_4);
	Phase_1_Skills->AddChild(P1_Skill_5);
#pragma endregion



#pragma region Phase_3
	auto Phase_3_Skills = std::make_shared<Selector>("Phase_3_Skills");

#pragma endregion


#pragma region PhaseSelectors_and_Root
	//원본임
	auto Phase_1 = std::make_shared<Sequence>("Phase_1");
	auto Phase_3 = std::make_shared<Sequence>("Phase_3");

	Phase_1->AddChild(P1_PhaseChecker);
	Phase_1->AddChild(P1_BossCoolDown);
	Phase_1->AddChild(Phase_1_Skills);

	Phase_3->AddChild(P3_PhaseChecker);
	Phase_3->AddChild(P3_BossCoolDown);
	Phase_3->AddChild(Phase_3_Skills);


	auto Root = std::make_shared<Selector>("Root");
	Root->AddChild(Phase_1);
	Root->AddChild(Phase_3);

	m_BehaviorTree = Root;
#pragma endregion
}

void BossBehaviorTree::Tick(float deltaTime)
{
	if (m_BehaviorTree)
		m_BehaviorTree->Tick(m_BlackBoard, deltaTime);
}
