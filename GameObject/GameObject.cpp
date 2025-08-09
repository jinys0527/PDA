#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"
#include "GraffitiComponent.h"
#include "CameraObject.h"
#include "CameraComponent.h"

GameObject::GameObject(EventDispatcher& eventDispatcher) : Object(eventDispatcher)
{
	m_Transform = AddComponent<TransformComponent>();
}

bool GameObject::IsInView(CameraObject* camera) const
{
	// ī�޶� �� ���� ũ��, ��ġ ��������
	// ī�޶� ��ġ (World)
	auto cameraComp = camera->GetComponent<CameraComponent>();
	auto cameraPos = camera->GetComponent<TransformComponent>()->GetPosition();

	float cameraWidth = cameraComp->GetWidth() / cameraComp->GetZoom();
	float cameraHeight = cameraComp->GetHeight() / cameraComp->GetZoom();

	// ī�޶� ���� Rect
	float cameraLeft = cameraPos.x - cameraWidth * 0.5f;
	float cameraTop = cameraPos.y - cameraHeight * 0.5f;
	float cameraRight = cameraLeft + cameraWidth;
	float cameraBottom = cameraTop + cameraHeight;

	// ������Ʈ ��ġ �� ũ�� ��������
	auto trans = GetComponent<TransformComponent>();

	if (!trans)
		return true;

	auto spriteRenderer = GetComponent<SpriteRenderer>();

	if (!spriteRenderer)
		return false;

	auto objPos = trans->GetPosition();
	auto objSize = spriteRenderer->GetTexture()->GetSize();
	auto objPivot = spriteRenderer->GetPivot();

	// ������Ʈ �»�� ��ǥ ��� (pivot ����)
	float objLeft = objPos.x - objSize.width * objPivot.x;
	float objTop = objPos.y - objSize.height * objPivot.y;
	float objRight = objLeft + objSize.width;
	float objBottom = objTop + objSize.height;

	// AABB �浹 �˻�
	bool isVisible = !(objRight < cameraLeft || objLeft > cameraRight ||
		objBottom < cameraTop || objTop > cameraBottom);

	return isVisible;
}

void GameObject::Render(std::vector<RenderInfo>& renderInfo)
{
	for(auto& spriteRenderer : GetComponents<SpriteRenderer>())
	{
		RenderInfo info;
		info.bitmap = spriteRenderer->GetTexture();
		info.worldMatrix = m_Transform->GetWorldMatrix();
		info.pivot = spriteRenderer->GetPivot();
		// Opacity ����
		info.opacity = spriteRenderer->GetOpacity();
		// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
		info.useSrcRect = spriteRenderer->GetUseSrcRect();
		info.srcRect = spriteRenderer->GetSrcRect();
		renderInfo.emplace_back(info);
	}
}

void GameObject::Serialize(nlohmann::json& j) const
{
	j["name"] = m_Name;
	j["components"] = nlohmann::json::array();
	for (const auto& component : m_Components)
	{
		for (const auto& comp : component.second)
		{
			const char* typeName = comp->GetTypeName();
			if (strcmp(typeName, "TransformComponent") == 0 || strcmp(typeName, "SpriteRenderer") == 0)
			{
				nlohmann::json compJson;
				compJson["type"] = typeName;
				comp->Serialize(compJson["data"]);
				j["components"].push_back(compJson);
			}
		}
	}
}

void GameObject::Deserialize(const nlohmann::json& j)
{
	m_Name = j.at("name");

	for (const auto& compJson : j.at("components"))
	{
		std::string typeName = compJson.at("type");

		// ���� ������Ʈ�� ������ ã�Ƽ� ����
		auto it = m_Components.find(typeName);
		if (it != m_Components.end() && !it->second.empty())
		{
			// �ش� Ÿ���� ��� ������Ʈ�� ���� Deserialize �õ�
			for (auto& comp : it->second)
			{
				comp->Deserialize(compJson.at("data"));
			}
		}
		else
		{
			// ������ ���� ���� �� �߰�
			auto comp = ComponentFactory::Instance().Create(typeName);
			if (comp)
			{
				comp->Deserialize(compJson.at("data"));
				AddComponent(std::move(comp));
			}
		}
	}
}