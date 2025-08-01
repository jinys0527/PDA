#include "pch.h"
#include <filesystem>
#include "SoundManager.h"
#include "Fmod_Error.h"
#include <unordered_map>

constexpr int ChannelCount = 128;

bool SoundManager::Init()
{
	FMOD_RESULT result = FMOD::System_Create(&m_CoreSystem);
	if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }

	//3D Sound 추가시 수정
	result = m_CoreSystem->init(ChannelCount, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }
	 
	m_CoreSystem->getMasterChannelGroup(&m_MasterGroup);
	m_CoreSystem->createChannelGroup("BGM", &m_BGMGroup);
	m_CoreSystem->createChannelGroup("SFX", &m_SFXGroup);
	m_CoreSystem->createChannelGroup("UI", &m_UIGroup);

	m_MasterGroup->addGroup(m_BGMGroup);
	m_MasterGroup->addGroup(m_SFXGroup);
	m_MasterGroup->addGroup(m_UIGroup);

	CreateBGMSource(m_AssetManager.GetBGMPaths());
	CreateSFXSource(m_AssetManager.GetSFXPaths());
	CreateUISource(m_AssetManager.GetUISoundPaths());

	return true;
}

SoundManager::~SoundManager()
{
	m_CoreSystem->release();
	m_BGMGroup->release();
	m_SFXGroup->release();
	m_UIGroup->release();
	m_MasterGroup->release();
}

void SoundManager::SetDirty()
{
	m_SoundDirty = true;
	m_Dirty_BGM = true;
	m_Dirty_SFX = true;
	m_Dirty_UI = true;
}

//3D 설정시 변경 //FMOD_3D
void SoundManager::CreateBGMSource(const std::unordered_map<std::wstring, std::filesystem::path>& bgms)
{
	for (auto& bgm : bgms)
	{
		FMOD::Sound* temp;
		m_CoreSystem->createSound(bgm.second.string().c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &temp);

		m_BGMs.emplace(bgm.first, temp);
	}
}

void SoundManager::CreateSFXSource(const std::unordered_map<std::wstring, std::filesystem::path>& sfxs)
{
	for (auto& sfx : sfxs)
	{
		FMOD::Sound* temp;
		m_CoreSystem->createSound(sfx.second.string().c_str(), FMOD_DEFAULT | FMOD_2D, nullptr, &temp);

		m_SFXs.emplace(sfx.first, temp);
	}
}

void SoundManager::CreateUISource(const std::unordered_map<std::wstring, std::filesystem::path>& uis)
{
	for (auto& ui : uis)
	{
		FMOD::Sound* temp;
		m_CoreSystem->createSound(ui.second.string().c_str(), FMOD_DEFAULT | FMOD_2D, nullptr, &temp);

		m_UIs.emplace(ui.first, temp);
	}
}



void SoundManager::Update() //매 프레임 마다 필수 호출
{
	m_CoreSystem->update();
}

void SoundManager::Shutdown()
{
	for (auto& bgm : m_BGMs) { bgm.second->release(); }
	for (auto& sfx : m_SFXs) { sfx.second->release(); }
	for (auto& ui : m_UIs) { ui.second->release(); }
	m_CoreSystem->release();
}

void SoundManager::BGM_Shot(const std::wstring& fileName)
{
	//std::cout << fileName << std::endl;

	bool isBGMPlaying = false;
	if (m_BGMGroup->isPlaying(&isBGMPlaying))
	{
		m_BGMGroup->stop();
	}
	//fade in,out 만들거여?

	FMOD::Channel* channel = nullptr;
	auto it = m_BGMs.find(fileName);

	//std::cout << "it 찾음?: " << it->first << std::endl;

	if (it != m_BGMs.end())
	{
		m_CoreSystem->playSound(it->second, m_BGMGroup, false, &channel);
	}

}

void SoundManager::SFX_Shot(const std::wstring& fileName)
{
	FMOD::Channel* channel = nullptr;
	auto it = m_SFXs.find(fileName);

	if (it != m_SFXs.end())
	{
		m_CoreSystem->playSound(it->second, m_SFXGroup, false, &channel);
	}
}

void SoundManager::UI_Shot(const std::wstring& fileName)
{
	FMOD::Channel* channel = nullptr;
	auto it = m_UIs.find(fileName);

	if (it != m_UIs.end())
	{
		m_CoreSystem->playSound(it->second, m_UIGroup, false, &channel);
	}
}


void SoundManager::SetVolume_Main(float volume)
{
	if (m_SoundDirty == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_Master = volume;

	m_MasterGroup->setVolume(m_Volume_Master);

	m_SoundDirty = false;
}

void SoundManager::SetVolume_BGM(float volume)
{
	if (m_Dirty_BGM == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_BGM = m_Volume_Master * volume;

	m_BGMGroup->setVolume(m_Volume_BGM);

	m_Dirty_BGM = false;
}

void SoundManager::SetVolume_SFX(float volume)
{
	if (m_Dirty_SFX == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_SFX = m_Volume_Master * volume;

	m_SFXGroup->setVolume(m_Volume_SFX);

	m_Dirty_SFX = false;
}

void SoundManager::SetVolume_UI(float volume)
{
	if (m_Dirty_UI == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_UI = m_Volume_Master * volume;

	m_UIGroup->setVolume(m_Volume_UI);

	m_Dirty_UI = false;
}

