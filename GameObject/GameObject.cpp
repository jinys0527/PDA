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
	auto it = m_Components.find(SpriteRenderer::StaticTypeName);
	auto it2 = m_Components.find(UIImageComponent::StaticTypeName);

	if (it != m_Components.end())
	{
		SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(it->second.get());
		if(sprite)
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			info.worldMatrix = m_Transform->GetWorldMatrix();
			info.pivot = sprite->GetPivot();
			// Opacity ����
			info.opacity = sprite->GetOpacity();
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) ������
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
			renderInfo.push_back(info);
		}
	}
	else if (it2 != m_Components.end())
	{
		UIImageComponent* image = dynamic_cast<UIImageComponent*>(it2->second.get());
		if (image)
		{
			RenderInfo info;
			renderInfo.push_back(info);
		}
	}
	else
	{
		return;
	}
}

TransformComponent* GameObject::RenderPosition()
{
	SpriteRenderer* sr = GetComponent<SpriteRenderer>();
	if (sr != nullptr)
	{
		//sr->Render();
		auto it = m_Components.find(TransformComponent::StaticTypeName);
		if (it != m_Components.end()) {
			return dynamic_cast<TransformComponent*>(it->second.get());
		}
	}
	return nullptr;
}

SpriteRenderer* GameObject::RenderTexture()
{
	auto it = m_Components.find(SpriteRenderer::StaticTypeName);
	if (it != m_Components.end())
	{
		return dynamic_cast<SpriteRenderer*>(it->second.get());
	}
	return nullptr;
}

void GameObject::Serialize(nlohmann::json& j) const
{
	j["name"] = m_Name;
	j["components"] = nlohmann::json::array();
	for (const auto& component : m_Components)
	{
		nlohmann::json compJson;
		compJson["type"] = component.second->GetTypeName();
		component.second->Serialize(compJson["data"]);
		j["components"].push_back(compJson);
	}
}

void GameObject::Deserialize(const nlohmann::json& j)
{
	m_Name = j.at("name");

	for (const auto& compJson : j.at("components"))
	{
		std::string typeName = compJson.at("type");

		// ���� ������Ʈ�� ������ ã�Ƽ� ����
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