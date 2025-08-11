#include "AnimationUtils.h"
#include "AnimationComponent.h"

std::shared_ptr<GameObject> GetAvailableAnim(BlackBoard& bb, const std::string& animName)
{
    auto animsOpt = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims");
    auto mapOpt = bb.GetValue<std::unordered_map<std::string, std::vector<int>>>("BossAnimIndexMap");

    if (!animsOpt.has_value() || !mapOpt.has_value())
        return nullptr;

    auto& anims = animsOpt.value();
    auto& animMap = mapOpt.value();

    auto it = animMap.find(animName);
    if (it == animMap.end())
        return nullptr;

    for (int idx : it->second)
    {
        auto animObj = anims[idx];
        if (IsAnimationAvailable(animObj))  // ����: ��ƿ �Լ��� üũ
        {
            return animObj;
        }
    }
    return nullptr;
}

bool IsAnimationAvailable(const std::shared_ptr<GameObject>& animObj)
{
    if (!animObj) return false;

    auto animComp = animObj->GetComponent<AnimationComponent>();
    if (!animComp) return false;

    return !animComp->GetIsActive();
}
