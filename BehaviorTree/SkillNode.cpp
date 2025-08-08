#include "SkillNode.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"

NodeState SkillNode::Tick(BlackBoard& bb, float deltaTime)
{
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
        m_Anims = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims").value();

        if (m_Name == "Skill_1_Warning")
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_1").value();
        else if (m_Name == "Skill_2_Warning")
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_2").value();
        else if (m_Name == "Skill_3_Warning")
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_3").value();

        m_Initialized = true;
    }

    if (!m_HasStarted)
    {
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    // �ִϸ��̼� ��Ȱ��ȭ Ÿ�̸� (�̰� ���� �;� Success ���� �����)
    if (m_AnimPlaying)
    {
        if (m_Anims[0]->GetComponent<AnimationComponent>()->IsAnimationFinished())
            std::cout << "adfasdfasdf" << std::endl;

        m_AnimTimer += deltaTime;
        if (m_AnimTimer >= 1.0f)
        {

            m_Anims[0]->GetComponent<AnimationComponent>()->SetIsActive(false);
            auto sprite = m_Anims[0]->GetComponent<SpriteRenderer>();
            sprite->SetIsActive(0);
            sprite->SetOpacity(0);
            m_AnimPlaying = false;
            m_AnimTimer = 0.0f;
        }
    }

    if (m_ElapsedTime >= m_WarningTime)
    {
        if (!m_AttackStarted)
        {
            EndWarning(bb);  // ���� ����
            m_AttackStarted = true;
        }

        // �ִϸ��̼��� ������ ������ Success �� ��
        if (!m_AnimPlaying)
        {
            Reset();
            return NodeState::Success;
        }

        return NodeState::Running;
    }

    return NodeState::Running;
}


void SkillNode::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ���" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            telegraph->SetActive();
        }
    }
}

//�ӽ÷� ��Ÿ Ÿ�� ����
void SkillNode::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ����" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
        {
            telegraph->SetInactive();
            telegraph->SetColliderActive();
        }
    }

    // �ִϸ��̼� ���
    m_Anims[0]->GetComponent<AnimationComponent>()->SetIsActive(true);
    auto sprite = m_Anims[0]->GetComponent<SpriteRenderer>();
    sprite->SetIsActive(1);
    sprite->SetOpacity(1);
    

    m_AnimPlaying = true;
    m_AnimTimer = 0.0f;
}

void SkillNode::Reset()
{
    m_ElapsedTime = 0.0f;
    m_HasStarted = false;
    m_AttackStarted = false;
    // �ִϸ��̼� Ÿ�̸ӵ� �ʱ�ȭ
    //m_AnimPlaying = false;
    //m_AnimTimer = 0.0f;
}

