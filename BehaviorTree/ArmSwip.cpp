#include "ArmSwip.h"
#include "BlackBoard.h"

NodeState ArmSwip::Tick(BlackBoard& bb, float deltaTime)
{
#pragma region Initialize
    if (!m_Initialized)
    {
        if (!m_Initialized)
        {
            m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
            m_Anims = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims").value();
        }
        //m_MoveDuration = m_Anims[0]->GetComponent<AnimationComponent>()->GetTotalDuration("attack");

        m_AttackRange = bb.GetValue<std::vector<int>>(m_Name).value();



        m_Initialized = true;
    }
#pragma endregion

    return NodeState();
}

void ArmSwip::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " °æ°í" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            telegraph->SetActive();
        }
    }
}

