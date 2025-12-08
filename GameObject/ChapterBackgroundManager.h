#pragma once
#include "GameObject.h"
#include "EventDispatcher.h"

class Background;
class AssetManager;

class ChapterBackgroundManager : public GameObject
{
public:
	ChapterBackgroundManager(AssetManager* assetManager, EventDispatcher& eventDispatcher);
	void LoadBackgroundSet(int chapter);
	void Update(float deltaTime, const CameraObject* camera);

	std::vector<std::shared_ptr<Background>> GetAllBackgrounds() const;
private:
	AssetManager* m_AssetManager;

	std::vector<std::shared_ptr<Background>> m_FarLayers;
	std::vector<std::shared_ptr<Background>> m_NearLayers;
	std::vector<std::shared_ptr<Background>> m_ForeLayers;
	std::vector<std::shared_ptr<Background>> m_Backgrounds;
	std::vector<std::shared_ptr<Background>> m_Tiles;
	std::vector<std::shared_ptr<Background>> m_TileEdges;

	void CreateLayerSet(std::vector<std::shared_ptr<Background>>& layerVec, 
		const std::vector<std::wstring>& texturePaths,
		float moveSpeed,
		int zOrder);
};

