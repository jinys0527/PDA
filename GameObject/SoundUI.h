#pragma once
#include "UISliderComponent.h"
#include "memory"
#include "SoundManager.h"
class SoundUI
{
public:
	SoundUI(SoundManager& soundManager);
	~SoundUI() = default;

	UISliderComponent* GetMaster() { return m_Master.get(); }
	UISliderComponent* GetBGM() { return m_BGM.get(); }
	UISliderComponent* GetSFX() { return m_SFX.get(); }
	UISliderComponent* GetUI() { return m_UI.get(); }

	void SetSlider();

private:
	SoundManager& m_SoundManager;

	std::unique_ptr<UISliderComponent> m_Master;
	std::unique_ptr<UISliderComponent> m_BGM;
	std::unique_ptr<UISliderComponent> m_SFX;
	std::unique_ptr<UISliderComponent> m_UI;
};

