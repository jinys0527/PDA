#include "BulletUIComponent.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "UITextComponent.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "UIGridComponent.h"
#include "UIObject.h"
#include "UIImageComponent.h"

BulletUIComponent::~BulletUIComponent()
{
	m_Owner->GetEventDispatcher().RemoveListener(EventType::OnPlayerReinforcedBulletChanged, this);
}

void BulletUIComponent::Start()
{
	m_Owner->GetEventDispatcher().AddListener(EventType::OnPlayerReinforcedBulletChanged, this);
}

void BulletUIComponent::SetNumbers(AssetManager* assetManager)
{
	m_NumberBitmaps.assign(10, nullptr);
	m_NumberBitmaps[0] = assetManager->LoadTexture(L"bullet_count_0", L"../Resource/UI/Sour/InGame/bullet_count_0.png");
	m_NumberBitmaps[1] = assetManager->LoadTexture(L"bullet_count_1", L"../Resource/UI/Sour/InGame/bullet_count_1.png");
	m_NumberBitmaps[2] = assetManager->LoadTexture(L"bullet_count_2", L"../Resource/UI/Sour/InGame/bullet_count_2.png");
	m_NumberBitmaps[3] = assetManager->LoadTexture(L"bullet_count_3", L"../Resource/UI/Sour/InGame/bullet_count_3.png");
	m_NumberBitmaps[4] = assetManager->LoadTexture(L"bullet_count_4", L"../Resource/UI/Sour/InGame/bullet_count_4.png");
	m_NumberBitmaps[5] = assetManager->LoadTexture(L"bullet_count_5", L"../Resource/UI/Sour/InGame/bullet_count_5.png");
	m_NumberBitmaps[6] = assetManager->LoadTexture(L"bullet_count_6", L"../Resource/UI/Sour/InGame/bullet_count_6.png");
	m_NumberBitmaps[7] = assetManager->LoadTexture(L"bullet_count_7", L"../Resource/UI/Sour/InGame/bullet_count_7.png");
	m_NumberBitmaps[8] = assetManager->LoadTexture(L"bullet_count_8", L"../Resource/UI/Sour/InGame/bullet_count_8.png");
	m_NumberBitmaps[9] = assetManager->LoadTexture(L"bullet_count_9", L"../Resource/UI/Sour/InGame/bullet_count_9.png");
}

void BulletUIComponent::Update(float deltaTime)
{
}

void BulletUIComponent::OnEvent(EventType type, const void* data)
{
	if (type == EventType::OnPlayerReinforcedBulletChanged)
	{
		auto grid = m_Owner->GetComponent<UIGridComponent>();
		auto items = grid->GetItems();

		int count = (int)data;
		if ((int)data >= 10)
		{
			items[0]->GetComponent<UIImageComponent>()->SetBitmap(m_NumberBitmaps[count / 10]);
			items[1]->GetComponent<UIImageComponent>()->SetBitmap(m_NumberBitmaps[count % 10]);
			items[1]->SetIsVisible(true);
		}
		else
		{
			items[0]->GetComponent<UIImageComponent>()->SetBitmap(m_NumberBitmaps[count % 10]);
			items[1]->SetIsVisible(false);
		}
	}
}

void BulletUIComponent::Serialize(nlohmann::json& j) const
{
}

void BulletUIComponent::Deserialize(const nlohmann::json& j)
{
}
