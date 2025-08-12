#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>
#include "AnimationController.h"
#include <iostream>

class AnimationClip;
class AssetManager;

class AnimationComponent : public Component
{
public:
	static constexpr const char* StaticTypeName = "AnimationComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	const AnimationClip* GetClip() const;


	void AddClip(const std::string& name, const AnimationClip* clip)
	{
		m_Clips[name] = clip;
	}

	bool IsAnimationFinished()
	{
		if (!m_AnimationController.IsValid())
			return true;

		if (m_AnimationController.IsLooping())
			return false;

		return m_AnimationController.IsLastFrameFinished();
	}

	void SetLoop(bool loop)
	{
		m_AnimationController.SetLooping(loop);
	}

	float GetTotalDuration(const std::string& name)
	{
		return m_Clips[name]->GetTotalDuration();
	}

	void Play();
	void Play(const std::string& name, bool loop = true);

	void Finish();

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