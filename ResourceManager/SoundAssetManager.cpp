#include "pch.h"
#include "SoundAssetManager.h"

void SoundAssetManager::Init(const std::filesystem::path& rootPath)
{
	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(rootPath))
	{
		if (!dirEntry.is_regular_file())
			continue;

		const auto& path = dirEntry.path();
		const auto& parent = path.parent_path().filename().wstring();

		if (parent == L"BGM")
		{
			m_BGMs[path.stem().wstring()] = path;
		}
		else if (parent == L"SFX")
		{
			m_SFXs[path.stem().wstring()] = path;
		}
		else if (parent == L"UI")
		{
			m_UISounds[path.stem().wstring()] = path;
		}
	}
}
