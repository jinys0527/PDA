#include "PhaseChecker_2.h"
#include "BlackBoard.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include <algorithm>

NodeState PhaseChecker_2::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();
    bool isPhase3 = bb.GetValue<bool>("3Phase").value();

    if (m_PhaseChange)
    {
        auto trans = m_Lazer_CCTV->GetComponent<TransformComponent>();

        auto pos = trans->GetPosition();

        if (pos.x < m_targetX)
        {
            pos.x += m_moveSpeed * deltaTime;
            if (pos.x > m_targetX)
            {
                pos.x = m_targetX; // 목표 도착 시 보정
            }
            trans->SetPosition(pos);
            return NodeState::Running;
        }

        m_PhaseChange = false;
        return NodeState::Success;
    }

    if (currPhase == 2)
    {
        //m_Back_2->GetComponent<SpriteRenderer>()->SetOpacity(0);
        //// 3과 4 반복 출력
        //if (m_PrintState == 3)
        //{
        //    m_Back_3->GetComponent<SpriteRenderer>()->SetOpacity(1);
        //    m_Back_4->GetComponent<SpriteRenderer>()->SetOpacity(0);
        //    m_PrintState = 4;
        //}
        //else
        //{
        //    m_Back_4->GetComponent<SpriteRenderer>()->SetOpacity(1);
        //    m_Back_3->GetComponent<SpriteRenderer>()->SetOpacity(0);
        //    m_PrintState = 3;
        //}

        if (hp < 45.f)
        {
            bb.SetValue("3Phase", true);
        }
        return NodeState::Success;
    }

    if (hp < 50.f && !isPhase3)
    {
       auto map = bb.GetValue<std::unordered_map<std::string, std::shared_ptr<GameObject>>>("Backgrounds");

       auto& backgrounds = map.value();

        m_Back_0 = backgrounds["Phase_1_Monitor"];
        m_Back_1 = backgrounds["Phase_2_Monitor_1"];
        m_Back_2 = backgrounds["Phase_2_Monitor_2"];
        m_Back_3 = backgrounds["Phase_2_Monitor_3"];
        m_Back_4 = backgrounds["Phase_2_Monitor_4"];


        m_Lazer_CCTV = GetAnim(bb, "Boss_Phase_1_Main");

        m_targetX += m_Lazer_CCTV->GetComponent<TransformComponent>()->GetPosition().x;

        m_PhaseChange = true;
        bb.SetValue("CurrPhase", 2);
        return NodeState::Running;
    }

    return NodeState::Failure;
}