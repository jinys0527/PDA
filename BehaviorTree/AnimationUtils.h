#pragma once
#include <memory>
#include <string>
#include "BlackBoard.h"
#include "GameObject.h"

std::shared_ptr<GameObject> GetAvailableAnim(BlackBoard& bb, const std::string& animName);
bool IsAnimationAvailable(const std::shared_ptr<GameObject>& animObj);
