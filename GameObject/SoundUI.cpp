#include "SoundUI.h"

SoundUI::SoundUI(SoundManager& soundManager, EventDispatcher& eventDispatcher) : UIObject(eventDispatcher), m_SoundManager(soundManager)
{
	m_Master = std::make_unique<UISliderComponent>();
	m_BGM = std::make_unique<UISliderComponent>();
	m_SFX = std::make_unique<UISliderComponent>();
	m_UI = std::make_unique<UISliderComponent>();
}

void SoundUI::SetSlider()
{
	m_Master->SetOnValueChanged([this](float value) { m_SoundManager.SetVolume_Master(value); });
	m_BGM->SetOnValueChanged([this](float value) { m_SoundManager.SetVolume_BGM(value); });
	m_SFX->SetOnValueChanged([this](float value) { m_SoundManager.SetVolume_SFX(value); });
	m_UI->SetOnValueChanged([this](float value) { m_SoundManager.SetVolume_UI(value); });
}
