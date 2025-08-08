#pragma once
#include "GameObject.h"

class BoxColliderComponent;
class SpriteRenderer;

class ItemObject : public GameObject
{
public:
	ItemObject(EventDispatcher& eventDispatcher);
	virtual ~ItemObject();

	void SetZ(float value) { m_Z = value; }
	float GetZ() { return m_Z; }

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);
private:
	float m_Z;
	BoxColliderComponent* m_Collider;
	SpriteRenderer* m_Sprite;
};

