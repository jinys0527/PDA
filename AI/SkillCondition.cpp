#include "SkillCondition.h"
#include "BlackBoard.h"

NodeState SkillCondition::Tick(BlackBoard& bb, float deltaTime)
{
    float skillchance = 0.f;

    std::string skillName;
    int skillIndex = 0;

    if (m_Name == "Skill_1_Con")
    {
        skillchance = bb.GetValue<float>("SkillChance_1").value();
        skillName = "SkillWeight_1";
        skillIndex = 1;
    }
    else if (m_Name == "Skill_2_Con")
    {
        skillchance = bb.GetValue<float>("SkillChance_2").value();
        skillName = "SkillWeight_2";
        skillIndex = 2;
    }
    else if (m_Name == "Skill_3_Con")
    {
        skillchance = bb.GetValue<float>("SkillChance_3").value();
        skillName = "SkillWeight_3";
        skillIndex = 3;
    }

    float randomValue = bb.GetValue<float>("RandomValue").value();

    if (randomValue < skillchance)
    {
        //std::cout << m_Name << " ���� \n";

        // ����� ��ų: ����ġ ����
        float weight = bb.GetValue<float>(skillName).value();
        bb.SetValue(skillName, 1.0f); // ���� ����

        // ������� ���� ��ų��: ����ġ ����
        for (int i = 1; i <= 3; ++i)
        {
            if (i == skillIndex) continue; // ����� ��ų�� �ǳʶ�

            std::string otherSkill = "SkillWeight_" + std::to_string(i);
            float otherWeight = bb.GetValue<float>(otherSkill).value();
            bb.SetValue(otherSkill, otherWeight + 1.0f);
        }

        return NodeState::Success;
    }

    return NodeState::Failure;
}
