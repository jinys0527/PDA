#include "pch.h"
#include "D2DRenderer.h"
#include "JsonParser.h"
#include "AssetManager.h"

ID2D1Bitmap1* AssetManager::LoadTexture(std::wstring keyWide, std::filesystem::path fullPath)
{
	auto it = m_Textures.find(keyWide);

	if (it != m_Textures.end()) return it->second.Get();

	m_Renderer.CreateBitmapFromFile(fullPath.c_str(), *m_Textures[keyWide].GetAddressOf());
	
	return m_Textures[keyWide].Get();
}

const AnimationClips& AssetManager::LoadAnimation(std::wstring keyWide, std::filesystem::path fullPath)
{
	auto it = m_Animations.find(keyWide);
	if (it != m_Animations.end())
	{
		return it->second;
	}

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet = GetTexture(keyWide);
	std::wstring keyW = keyWide + L".png";

	m_Renderer.CreateBitmapFromFile(keyW.c_str(), *sheet.GetAddressOf());

	auto tempMap = JsonParser::LoadAnimation(fullPath);

	AnimationClips clips;
	clips.reserve(tempMap.size());
	for (auto& [name, clip] : tempMap)
	{
		clip.SetTextureKey(keyW);
		clips.emplace_back(std::move(name), std::move(clip));
	}

	auto res = m_Animations.emplace(keyWide, std::move(clips));

	return res.first->second;
}

const Microsoft::WRL::ComPtr<ID2D1Bitmap1> AssetManager::GetTexture(const std::wstring& key) const
{
	auto it = m_Textures.find(key);
	if (it != m_Textures.end())
	{
		return it->second.Get();
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
