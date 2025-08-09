#include "pch.h"
#include "D2DRenderer.h"
#include "JsonParser.h"
#include "AssetManager.h"

void AssetManager::Init(const std::filesystem::path& rootPath)	// 폴더 자동 로드
{
	for (const auto& entry : std::filesystem::recursive_directory_iterator(rootPath))
	{
		if (!entry.is_regular_file())
			continue;

		const auto& path = entry.path();
		const auto& ext = path.extension().wstring();
		const auto key = path.stem().wstring();
		
		if (ext == L".json")
		{
			LoadAnimation(key, path);
		}
		else if (ext == L".png" || ext == L".jpg" || ext == L".bmp")
		{
			LoadTexture(key, path);
		}
	}
}


Microsoft::WRL::ComPtr<ID2D1Bitmap1> AssetManager::LoadTexture(std::wstring keyWide, std::filesystem::path fullPath)
{
	auto it = m_Textures.find(keyWide);
	if (it != m_Textures.end())
		return it->second;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture;
	m_Renderer.CreateBitmapFromFile(fullPath.c_str(), *texture.GetAddressOf()); // 아래 방식으로 오버로드 바꿔야 함

	m_Textures.emplace(keyWide, texture);
	return texture;
}

const AnimationClips& AssetManager::LoadAnimation(std::wstring keyWide, std::filesystem::path fullPath)
{
	auto it = m_Animations.find(keyWide);
	if (it != m_Animations.end())
	{
		return it->second;
	}

	std::filesystem::path texPath = fullPath;
	texPath.replace_extension(L".png");
	LoadTexture(keyWide, texPath);

	auto tempMap = JsonParser::LoadAnimation(fullPath);

	AnimationClips clips;
	clips.reserve(tempMap.size());
	for (auto& [name, clip] : tempMap)
	{
		clip.SetTextureKey(keyWide);
		clips.emplace_back(std::move(name), std::move(clip));
	}

	auto res = m_Animations.emplace(keyWide, std::move(clips));

	return res.first->second;
}

Microsoft::WRL::ComPtr<ID2D1Bitmap1> AssetManager::GetTexture(const std::wstring& key) const
{
	auto it = m_Textures.find(key);
	if (it != m_Textures.end())
	{
		return it->second;
	}

	return nullptr;
}

const AssetManager::AnimationClips& AssetManager::GetClips(const std::wstring& key) const
{
	auto it = m_Animations.find(key);
	if (it != m_Animations.end())
	{
		return it->second;
	}

	static const AnimationClips empty;
	return empty;
}

const UIData& AssetManager::GetUI(const std::wstring& key) const
{
	auto it = m_UIs.find(key);
	if (it != m_UIs.end())
	{
		return it->second;
	}

	static const UIData empty;
	return empty;
}

const MapData& AssetManager::GetMap(const std::wstring& key) const
{
	auto it = m_Maps.find(key);
	if (it != m_Maps.end())
	{
		return it->second;
	}

	static const MapData empty;
	return empty;
}