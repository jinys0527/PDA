#include "BossBehaviorTree.h"
#include "Selector.h"
#include "SkillCondition.h"
#include "PhaseChecker.h"
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
	auto P1_PhaseChecker = std::make_shared<PhaseChecker>("PhaseChecker_1");
	//auto P2_PhaseChecker = std::make_shared<PhaseChecker>("PhaseChecker_2");


	auto P1_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown");
	//auto P2_BossCoolDown = std::make_shared<BossCoolDown>("BossCoolDown");

	// 1페이즈 스킬 사용 가능 판정 노드
	auto P1_Skill_1_Con = std::make_shared<SkillCondition>("Skill_1_Con");
	auto P1_Skill_2_Con = std::make_shared<SkillCondition>("Skill_2_Con");
	auto P1_Skill_3_Con = std::make_shared<SkillCondition>("Skill_3_Con");
	auto P1_Skill_4_Con = std::make_shared<SkillCondition>("Skill_4_Con");
	auto P1_Skill_5_Con = std::make_shared<SkillCondition>("Skill_5_Con");


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
	// 1-1 끝














	// 3-1스킬  근데 고쳐야함
	//auto P1_Skill_1_Parallel = std::make_shared<ParallelNode>("P1_Skill_1_Parallel");
	//auto P1_Skill_1_Pick = std::make_shared<Pick>("Pick_5");
	//auto P1_Skill_1_ArmSmash_1 = std::make_shared<ArmSmash>("ArmSmash_1");
	//auto P1_Skill_1_ArmSmash_2 = std::make_shared<ArmSmash>("ArmSmash_3");
	//P1_Skill_1_Parallel->AddChild(P1_Skill_1_Pick);
	//P1_Skill_1_Parallel->AddChild(P1_Skill_1_ArmSmash_1);
	//P1_Skill_1_Parallel->AddChild(P1_Skill_1_ArmSmash_2);

	//auto P1_Skill_1 = std::make_shared<Sequence>("P1_Skill_1");
	//P1_Skill_1->AddChild(P1_Skill_1_Con);
	//P1_Skill_1->AddChild(P1_Skill_1_Parallel);
	// 3-1 끝












	
	// 딜레이 있는거 연습?
	//auto P1_SKill_1_Sequence_3 = std::make_shared<Sequence>("P1_SKill_1_Sequence_3");
	//auto P1_SKill_1_Wait_3 = std::make_shared<WaitNode>("P1_SKill_1_Wait_3");
	//auto P1_Skill_1_ArmSmash_3 = std::make_shared<ArmSmash>("P1_Skill_1_ArmSmash_3");
	//P1_SKill_1_Sequence_3->AddChild(P1_SKill_1_Wait_3);
	//P1_SKill_1_Sequence_3->AddChild(P1_Skill_1_ArmSmash_3);

	//auto P1_SKill_1_Parallel_2 = std::make_shared<ParallelNode>("P1_SKill_1_Parallel_2");
	//auto P1_SKill_1_ArmSmash_2 = std::make_shared<ArmSmash>("P1_SKill_1_ArmSmash_2");
	//P1_SKill_1_Parallel_2->AddChild(P1_SKill_1_ArmSmash_2);
	//P1_SKill_1_Parallel_2->AddChild(P1_SKill_1_Sequence_3);

	//auto P1_SKill_1_Sequence_2 = std::make_shared<Sequence>("P1_SKill_1_Sequence_2");
	//auto P1_SKill_1_Wait_2 = std::make_shared<WaitNode>("P1_SKill_1_Wait_2");







	// 연속 공격 테스트=======
	//auto secondAttackSequence = std::make_shared<Sequence>("SecondAttackSequence");
	//auto Wait = std::make_shared<WaitNode>("Wait", 1.f); // 0.5초 대기
	//auto Second_Attack = std::make_shared<ArmSmash>("Skill_2_ArmSmash");
	//secondAttackSequence->AddChild(Wait);
	//secondAttackSequence->AddChild(Second_Attack);

	//auto parallelAttacks = std::make_shared<ParallelNode>("parel");
	//parallelAttacks->AddChild(P1_Skill_1_ArmSmash); // 첫 번째 공격은 바로 시작
	//parallelAttacks->AddChild(secondAttackSequence); // 두 번째 공격은 0.5초 뒤 시작

	//auto P1_Skill_1 = std::make_shared<Sequence>("Skill_1");
	//P1_Skill_1->AddChild(P1_Skill_1_Con);
	//P1_Skill_1->AddChild(parallelAttacks);

	//연속 공격 완======



	auto P1_Skill_ArmSwip_Test = std::make_shared<ArmSwip>("Swip_L");
	auto P1_Skill_2 = std::make_shared<Sequence>("P1_Skill_2");
	P1_Skill_2->AddChild(P1_Skill_2_Con);
	P1_Skill_2->AddChild(P1_Skill_ArmSwip_Test);


	auto P1_Skill_3 = std::make_shared<Sequence>("P1_Skill_3");
	P1_Skill_3->AddChild(P1_Skill_3_Con);



	auto Phase_1 = std::make_shared<Selector>("Phase_1");



	Phase_1->AddChild(P1_PhaseChecker);
	Phase_1->AddChild(P1_BossCoolDown);
	Phase_1->AddChild(P1_Skill_1);
	Phase_1->AddChild(P1_Skill_2);
	Phase_1->AddChild(P1_Skill_3);







	auto Root = std::make_shared<Selector>("Root");
	Root->AddChild(Phase_1);
	//Root->AddChild(Phase_2);


	m_BehaviorTree = Root;
}

void BossBehaviorTree::Tick(float deltaTime)
{
	if (m_BehaviorTree)
		m_BehaviorTree->Tick(m_BlackBoard, deltaTime);
}
