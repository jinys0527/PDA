#pragma once
#include <unordered_map>
#include <filesystem>

class SoundAssetManager
{
public:
	SoundAssetManager() = default;
	~SoundAssetManager() = default;
	using Sounds = std::unordered_map<std::wstring, std::filesystem::path>;
	const Sounds& GetBGMPaths() const { return m_BGMs; }
	const Sounds& GetSFXPaths() const { return m_SFXs; }
	const Sounds& GetUISoundPaths() const { return m_UISounds; }
	
	void Init(const std::filesystem::path& rootPath);

private:
	std::unordered_map<std::wstring, std::filesystem::path> m_BGMs;
	std::unordered_map<std::wstring, std::filesystem::path> m_SFXs;
	std::unordered_map<std::wstring, std::filesystem::path> m_UISounds;
};

