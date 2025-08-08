#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>
#include "AnimationController.h"

class AnimationClip;
class AssetManager;

class AnimationComponent : public Component
{
public:
	static constexpr const char* StaticTypeName = "AnimationComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void AddClip(const std::string& name, const AnimationClip* clip)
	{
		m_Clips[name] = clip;
	}

	bool IsAnimationFinished()
	{
		return m_AnimationController.IsEnd();
	}

	void Play(const std::string& name, bool loop = true);

	void Update(float deltaTime) override;

	void OnEvent(EventType type, const void* data) override;

	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json & j) override;

private:
	using AnimationMap = std::unordered_map<std::string, const AnimationClip*>;

	AnimationMap m_Clips;
	AnimationController m_AnimationController;
	std::string m_CurrentClipName;
	AssetManager* m_AssetManager;
};

REGISTER_COMPONENT(AnimationComponent);