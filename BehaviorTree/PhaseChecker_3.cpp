#include "PhaseChecker_3.h"
#include "BlackBoard.h"
#include "SpriteRenderer.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"

NodeState PhaseChecker_3::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();
    bool isPhase3 = bb.GetValue<bool>("3Phase").value();

    if (m_PhaseChange)
    {
        auto trans = m_Boss_Phase_2_Arm->GetComponent<TransformComponent>();

        auto pos = trans->GetPosition();

        if (pos.x > m_targetX)
        {
            pos.x -= m_moveSpeed * deltaTime;
            if (pos.x < m_targetX)
            {
                pos.x = m_targetX; // 목표 도착 시 보정
            }
            trans->SetPosition(pos);
            return NodeState::Running;
        }


        bool allFinished = true;
        const float fadeSpeed = 0.5f; // 초당 1.0씩 증가 (0~1 사이)

        auto fadeObj = [&](std::shared_ptr<GameObject> obj) {
            auto anim = obj->GetComponent<AnimationComponent>();
            anim->SetIsActive(true);
            auto sprite = obj->GetComponent<SpriteRenderer>();
            sprite->SetIsActive(true);
            float current = sprite->GetOpacity();
            current += fadeSpeed * deltaTime;
            if (current >= 1.0f)
                current = 1.0f;
            sprite->SetOpacity(current);
            return current >= 1.0f; // true면 완전 불투명
            };

        if (!fadeObj(m_Boss_Main)) allFinished = false;
        if (!fadeObj(m_Boss_Arm_L)) allFinished = false;
        if (!fadeObj(m_Boss_Arm_R)) allFinished = false;

        // 세 개 다 완전히 나타나면 PhaseChange 종료
        if (allFinished)
        {
            m_PhaseChange = false;
            return NodeState::Success;
        }

        return NodeState::Running;
    }

    if (currPhase == 3)
        return NodeState::Success;

    if (hp < 50.f && isPhase3)
    {
        bb.SetValue("CurrPhase", 3);
        m_PhaseChange = true;

        m_Boss_Main = GetAnim(bb, "Boss_3Phase_IDLE_ani");
        m_Boss_Arm_L = GetAnim(bb, "Boss_Anim_Arm_L");
        m_Boss_Arm_R = GetAnim(bb, "Boss_Anim_Arm_R");
        m_Boss_Phase_2_Arm = GetAnim(bb, "Boss_Anim_Phase2_Arm");

        m_targetX += m_Boss_Phase_2_Arm->GetComponent<TransformComponent>()->GetPosition().x;

        return NodeState::Running;
    }

    return NodeState::Failure;
}