#pragma once
#include "GameObject.h"
#include "FlyingObstacleComponent.h"

class BoxColliderComponent;
class SpriteRenderer;
class FlyingObstacleComponent;

//struct DamageInfo
//{
//	int damage;
//	
//};

class Obstacle : public GameObject
{
public:
	Obstacle(EventDispatcher& eventDispatcher);
	virtual ~Obstacle() = default;
	
	void SetZ(float value) { m_Z = value; }
	float GetZ() { return m_Z; }
	void SetSlide(bool value) { m_IsSlide = value; }
	bool GetSlide() { return m_IsSlide; }

	virtual void Render(std::vector<RenderInfo>& renderInfo);

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);
private:
	float m_Z;
	bool m_IsSlide;
	BoxColliderComponent* m_Collider;
	SpriteRenderer* m_Sprite;
};

