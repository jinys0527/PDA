#include "PhaseChecker_2.h"
#include "BlackBoard.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include <algorithm>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

NodeState PhaseChecker_2::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();
    bool isPhase3 = bb.GetValue<bool>("3Phase").value();

    if (m_PhaseChange)
    {
        {
            auto sr = m_Back_0->GetComponent<SpriteRenderer>();
            float curOpacity = sr->GetOpacity();
            float newOpacity = std::max(0.f, curOpacity - m_fadeSpeed * deltaTime);
            sr->SetOpacity(newOpacity);
        }

        // ��� 1: ���� ���������� (����)
        {
            auto sr = m_Back_1->GetComponent<SpriteRenderer>();
            float curOpacity = sr->GetOpacity();
            float newOpacity = std::min(1.f, curOpacity + m_fadeSpeed * deltaTime);
            sr->SetOpacity(newOpacity);
        }

        // ��� 2: ���������ٰ� ��������� ȿ�� (�ݺ�)
        {
            auto sr = m_Back_2->GetComponent<SpriteRenderer>();
            float curOpacity = sr->GetOpacity();

            // m_Back2FadeDirection: +1�̸� ����, -1�̸� ���� (��� ������ bool �Ǵ� int ���� �ʿ�)
            if (m_Back2FadeDirection > 0)
            {
                float newOpacity = curOpacity + m_fadeSpeed * deltaTime;
                if (newOpacity >= 1.f)
                {
                    newOpacity = 1.f;
                    m_Back2FadeDirection = -1; // ���ҷ� ��ȯ
                }
                sr->SetOpacity(newOpacity);
            }
            else
            {
                float newOpacity = curOpacity - m_fadeSpeed * deltaTime;
                if (newOpacity <= 0.f)
                {
                    newOpacity = 0.f;
                    m_Back2FadeDirection = 1; // ������ ��ȯ
                }
                sr->SetOpacity(newOpacity);
            }
        }

        auto trans = m_Lazer_CCTV->GetComponent<TransformComponent>();

        auto pos = trans->GetPosition();

        if (pos.x < m_targetX)
        {
            pos.x += m_moveSpeed * deltaTime;
            if (pos.x > m_targetX)
            {
                pos.x = m_targetX; // ��ǥ ���� �� ����
            }
            trans->SetPosition(pos);
            return NodeState::Running;
        }

        m_PhaseChange = false;
        return NodeState::Success;
    }

    if (currPhase == 2)
    {
        m_Back_2->GetComponent<SpriteRenderer>()->SetOpacity(0);
        // 3�� 4 �ݺ� ���
        if (m_PrintState == 3)
        {
            m_Back_3->GetComponent<SpriteRenderer>()->SetOpacity(1);
            m_Back_4->GetComponent<SpriteRenderer>()->SetOpacity(0);
            m_PrintState = 4;
        }
        else
        {
            m_Back_4->GetComponent<SpriteRenderer>()->SetOpacity(1);
            m_Back_3->GetComponent<SpriteRenderer>()->SetOpacity(0);
            m_PrintState = 3;
        }

        //if (hp < 45.f)
        //{
        //    bb.SetValue("3Phase", true);
        //}
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