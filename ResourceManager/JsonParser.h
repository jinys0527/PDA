#pragma once

#include <filesystem>
#include "AnimationClip.h"

using AnimationClips = std::vector<std::pair<std::string, AnimationClip>>;
class JsonParser
{
public:
	JsonParser() = default;
	~JsonParser() = default;

	static AnimationClips LoadAnimation(const std::filesystem::path& jsonPath);
};

