#pragma once
#include "Object.h"
#include "json.hpp"

class TransformComponent;
class CameraObject;

class GameObject : public Object 
{
	friend class Editor;
	friend class Scene;
	friend class TitleScene;
	friend class InGameUITestScene;

public:
	GameObject(EventDispatcher& eventDispatcher);
	virtual ~GameObject() = default;

	using Object::AddComponent;

	void AddComponent(std::unique_ptr<Component> comp)	//Deserialize¿ë
	{
		comp->SetOwner(this);
		m_Components[comp->GetTypeName()].emplace_back(std::move(comp));
	}

	bool IsInView(CameraObject* camera) const;

	virtual void Render(std::vector<RenderInfo>& renderInfo);

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);

protected:
	TransformComponent* m_Transform;
};

