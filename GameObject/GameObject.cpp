#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

GameObject::GameObject(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher)
{
	m_Transform = AddComponent<TransformComponent>();
}

void GameObject::Update(float deltaTime)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Update(deltaTime);
	}
}

void GameObject::FixedUpdate()
{
}

void GameObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto spriteRenderer = GetComponent<SpriteRenderer>();
	auto uiImage = GetComponent<UIImageComponent>();

	if (spriteRenderer)
	{
		RenderInfo info;
		info.bitmap = spriteRenderer->GetTexture();
		info.worldMatrix = m_Transform->GetWorldMatrix();
		info.pivot = spriteRenderer->GetPivot();
		// Opacity 적용
		info.opacity = spriteRenderer->GetOpacity();
		// UI가 아닌 일반 오브젝트 위치로 설정
		info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
		info.anchoredPosition = m_Transform->GetPosition();
		info.sizeDelta = { 0, 0 };
		info.parentSize = { 0, 0 };
		info.useSrcRect = spriteRenderer->GetUseSrcRect();
		info.srcRect = spriteRenderer->GetSrcRect();
		renderInfo.push_back(info);
	}
	if (uiImage)
	{
		RenderInfo info;
		renderInfo.push_back(info);
	}
	else
	{
		return;
	}
}

void GameObject::Serialize(nlohmann::json& j) const
{
	j["name"] = m_Name;
	j["components"] = nlohmann::json::array();
	for (const auto& component : m_Components)
	{
		const char* typeName = component.second->GetTypeName();

		if(strcmp(typeName, "TransformComponent") == 0 || strcmp(typeName, "SpriteRenderer") == 0)
		{
			nlohmann::json compJson;		
			compJson["type"] = typeName;
			component.second->Serialize(compJson["data"]);
			j["components"].push_back(compJson);
		}
	}
}

void GameObject::Deserialize(const nlohmann::json& j)
{
	m_Name = j.at("name");

	for (const auto& compJson : j.at("components"))
	{
		std::string typeName = compJson.at("type");

		// 기존 컴포넌트가 있으면 찾아서 갱신
		auto it = std::find_if(m_Components.begin(), m_Components.end(),
			[&](const auto& pair)
			{
				return pair.second->GetTypeName() == typeName;
			});

		if (it != m_Components.end())
		{
			it->second->Deserialize(compJson.at("data"));
		}
		else
		{
			// 없으면 새로 생성 후 추가
			auto comp = ComponentFactory::Instance().Create(typeName);
			if (comp)
			{
				comp->Deserialize(compJson.at("data"));
				AddComponent(std::move(comp));
			}
		}
	}
}

void GameObject::SendMessages(const myCore::MessageID msg, void* data /* = nullptr */)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->HandleMessage(msg, data);
	}
}


void GameObject::SendEvent(const std::string& evt)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		//it->second->OnEvent(evt);
	}
}