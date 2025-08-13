#include "ChapterBackgroundManager.h"
#include "Background.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "AssetManager.h"
#include <iostream>

ChapterBackgroundManager::ChapterBackgroundManager(AssetManager* assetManager, EventDispatcher& eventDispatcher) : m_AssetManager(assetManager), GameObject(eventDispatcher)
{
}

void ChapterBackgroundManager::LoadBackgroundSet(int chapter)
{
	m_FarLayers.clear();
	m_NearLayers.clear();
	m_ForeLayers.clear();
	m_Backgrounds.clear();
	m_Tiles.clear(); 
	m_TileEdges.clear();

	// é�ͺ� �̹��� ���
	std::vector<std::wstring> farTextures;
	std::vector<std::wstring> nearTextures;
	std::vector<std::wstring> foreTextures;
	std::vector<std::wstring> backgroundTextures;
	std::vector<std::wstring> tileTextures;
	std::vector<std::wstring> tileEdgesTextures;

	nearTextures = { L"../Resource/Background/Near_sight1.png",
					L"../Resource/Background/Near_sight2.png" };
	if (chapter == 1)
	{
		farTextures = { L"../Resource/Background/Chapter1/Background.png" };
		foreTextures = { L"../Resource/Background/Chapter1/Foreground.png" };
		backgroundTextures = { L"../Resource/Background/Chapter1/Building1.png",
		L"../Resource/Background/Chapter1/Building2.png", 
		L"../Resource/Background/Chapter1/Building3.png", 
		L"../Resource/Background/Chapter1/Building4.png", 
		L"../Resource/Background/Chapter1/Building5.png" };
		tileTextures = { L"../Resource/Background/Chapter1/Tile_1.png" };
		tileEdgesTextures = { L"../Resource/Background/Chapter1/Tile_1_1.png" };
	}
	else if (chapter == 2)
	{
		farTextures = { L"../Resource/Background/Chapter2/Background_Sky.png" };
		foreTextures = { L"../Resource/Background/Chapter2/Foreground.png" };
		backgroundTextures = { L"../Resource/Background/Chapter2/Background1.png",
		L"../Resource/Background/Chapter2/Background2.png"};
		tileTextures = { L"../Resource/Background/Chapter2/Tile_2.png" };
		tileEdgesTextures = { L"../Resource/Background/Chapter2/Tile_2_1.png" };
	}
	else if (chapter == 3)
	{

	}

	// ���̾ ����
	CreateLayerSet(m_NearLayers, nearTextures, 40.0f, 6);		  // �ٰ�
	CreateLayerSet(m_Tiles, tileTextures, 0.0f, -1);			  // Ÿ��
	CreateLayerSet(m_TileEdges, tileEdgesTextures, 0.0f, -2);     // Ÿ�� �׵θ�
	CreateLayerSet(m_Backgrounds, backgroundTextures, 0.0f, -3);  // ���
	CreateLayerSet(m_ForeLayers, foreTextures, 80.0f, -4);		  // ����
	CreateLayerSet(m_FarLayers, farTextures, 20.0f, -5);		  // ����
}

void ChapterBackgroundManager::Update(float deltaTime, const CameraObject* camera)
{
	for (auto& bg : m_FarLayers)  bg->Update(deltaTime);
	for (auto& bg : m_NearLayers)  bg->Update(deltaTime);
	for (auto& bg : m_ForeLayers) bg->Update(deltaTime);
	for (auto& bg : m_Backgrounds) bg->Update(deltaTime, camera);
	for (auto& tile : m_Tiles) tile->Update(deltaTime, camera);
	for (auto& tileEdge : m_TileEdges) tileEdge->Update(deltaTime, camera);
}

std::vector<std::shared_ptr<Background>> ChapterBackgroundManager::GetAllBackgrounds() const
{
	std::vector<std::shared_ptr<Background>> allBackgrounds;

	auto appendVec = [&](const std::vector<std::shared_ptr<Background>>& vec)
		{
			allBackgrounds.insert(allBackgrounds.end(), vec.begin(), vec.end());
		};

	appendVec(m_FarLayers);
	appendVec(m_NearLayers);
	appendVec(m_ForeLayers);
	appendVec(m_Backgrounds);
	appendVec(m_Tiles);
	appendVec(m_TileEdges);

	return allBackgrounds;
}

void ChapterBackgroundManager::CreateLayerSet(
	std::vector<std::shared_ptr<Background>>& layerVec, 
	const std::vector<std::wstring>& texturePaths, 
	float moveSpeed,
	int zOrder)
{
	float startX = 0.0f;

	for (auto& texPath : texturePaths)
	{
		// Ȯ���� ����
		std::wstring key = std::filesystem::path(texPath).stem();
		auto tex = m_AssetManager->LoadTexture(key, texPath);
		int width = tex->GetSize().width;

		// 2��Ʈ ����
		for (int i = 0; i < 2; i++)
		{
			auto bg = std::make_shared<Background>(m_EventDispatcher);
			std::string name = std::string(key.begin(), key.end()) + std::to_string(i);
			bg->SetName(name);
			auto bgSr = bg->AddComponent<SpriteRenderer>();
			bgSr->SetTexture(tex);
			bgSr->SetPivotPreset(SpritePivotPreset::BottomCenter, bgSr->GetTexture()->GetSize());

			auto trans = bg->GetComponent<TransformComponent>();

			// m_Backgrounds�� �ش��ϴ� ������ ���� ������ ����
			if (&layerVec == &m_Backgrounds)
			{
				trans->SetScale({ 0.98f, 0.98f });
				// pivot�� BottomCenter�̹Ƿ� ���� �� ������ ���� ���ݸ�ŭ ����
				int width = tex->GetSize().width;
				float adjustedStartX = startX + width * 0.5f;
				trans->SetPosition({ adjustedStartX + width * i, 0 });
			}
			else
			{
				trans->SetPosition({ startX + width * i, 0 });
			}
			
			trans->SetZOrder(zOrder);  // ���⼭ ZOrder ����

			bg->SetMoveSpeed(moveSpeed);
			bg->ToggleScroll();
			layerVec.push_back(bg);
		}
		startX += width * 2; // ���� ��Ʈ ��ġ��
	}
}
