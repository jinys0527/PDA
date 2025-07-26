#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"

enum class AnchorPrset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

enum class PivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

struct Anchor
{
	D2D1_POINT_2F minPoint = { 0.0f, 0.0f };		// 왼쪽 하단		(0.0 ~ 1.0)
	D2D1_POINT_2F maxPoint = { 0.0f, 0.0f };		// 오른쪽 상단	(0.0 ~ 1.0)
};

class RectTransformComponent : public Component
{
	using Vec2F = Math::Vector2F;
	using Mat3X2F = D2D1::Matrix3x2F;

public:
	RectTransformComponent(const Vec2F& position,
		const Vec2F& size,
		AnchorPrset anchor = AnchorPrset::TopLeft,
		PivotPreset pivot = PivotPreset::Center,
		float rotation = 0.0f,
		const Vec2F& scale = { 1.0f, 1.0f }) { }
	virtual ~RectTransformComponent() = default;

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	std::string GetTypeName() override { return "RectTransformComponent"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	void SetAnchorPreset(AnchorPrset preset);
	void SetPivotPreset(PivotPreset preset);

	void SetPosition(const Vec2F& position)
	{
		m_Position = position;
	}

	Vec2F GetPosition() const 
	{
		return m_Position;
	}

	void SetSize(const Vec2F& size)
	{
		m_Size = size;
	}

	Vec2F GetSize() const
	{
		return m_Size;
	}

	void SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	float GetRotation() const
	{
		return m_Rotation;
	}

	void SetScale(const Vec2F& scale)
	{
		m_Scale = scale;
	}

	Vec2F GetScale() const
	{
		return m_Scale;
	}

	const Mat3X2F& GetWorldMatrix();
	const Mat3X2F& GetLocalMatrix();

private:
	void SetDirty()
	{
		m_IsDirty = true;
		for (auto* child : m_Children)
		{
			child->SetDirty();
		}
	}

	void UpdateMatrices();

private:
	Vec2F m_Position;
	Anchor m_Anchor;
	D2D1_POINT_2F m_Pivot = { 0.5f, 0.5f };			// 0.0 ~ 1.0
	Vec2F m_Size;
	float m_Rotation;
	Vec2F m_Scale;

	Mat3X2F m_LocalMatrix;
	Mat3X2F m_WorldMatrix;

	RectTransformComponent* m_Parent = nullptr;
	std::vector<RectTransformComponent*> m_Children;

	bool m_IsDirty = true;
};

