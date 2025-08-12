#include "PhaseChecker_2.h"
#include "BlackBoard.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"


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
        return NodeState::Success;
    }

    if (hp < 50.f && !isPhase3)
    {
        m_Lazer_CCTV = GetAnim(bb, "Boss_Phase_1_Main");

        m_targetX += m_Lazer_CCTV->GetComponent<TransformComponent>()->GetPosition().x;

        m_PhaseChange = true;
        bb.SetValue("CurrPhase", 2);
        return NodeState::Running;
    }

    return NodeState::Failure;
}