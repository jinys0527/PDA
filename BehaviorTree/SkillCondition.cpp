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
    else if (m_Name == "Skill_4_Con")
    {
        skillchance = bb.GetValue<float>("SkillChance_4").value();
        skillName = "SkillWeight_4";
        skillIndex = 4;
    }
    else if (m_Name == "Skill_5_Con")
    {
        skillchance = bb.GetValue<float>("SkillChance_5").value();
        skillName = "SkillWeight_5";
        skillIndex = 5;
    }

    float randomValue = bb.GetValue<float>("RandomValue").value();

    if (randomValue < skillchance)
    {
        // ����� ��ų: ����ġ ����
        float weight = bb.GetValue<float>(skillName).value();
        bb.SetValue(skillName, 1.0f); // 1�� �ʱ�ȭ

        int n = 0;
        // ������� ���� ��ų��: ����ġ ����
        if (bb.GetValue<int>("CurrPhase").value() == 2)
        {
            n = 3;
            bb.SetValue("SkillChance_4", 0.f);
            bb.SetValue("SkillChance_5", 0.f);

        }
        else
        {
            n = 5;
        }

        //����ġ �ڵ�
        std::cout << "[SkillCondition] ���� ��ų ����ġ ����:" << std::endl;
        for (int i = 1; i <= n; ++i)
        {
            std::string skillKey = "SkillWeight_" + std::to_string(i);
            auto valOpt = bb.GetValue<float>(skillKey);
            if (valOpt.has_value())
            {
                std::cout << "  " << skillKey << ": " << valOpt.value() << std::endl;
            }
            else
            {
                std::cout << "  " << skillKey << ": (�� ����)" << std::endl;
            }
        }

        for (int i = 1; i <= n; ++i)
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

