#include "RectTransformComponent.h"

void RectTransformComponent::Update(float deltaTime)
{
}

void RectTransformComponent::OnEvent(EventType type, const void* data)
{
}

void RectTransformComponent::Serialize(nlohmann::json& j) const
{
}

void RectTransformComponent::Deserialize(const nlohmann::json& j)
{
}

void RectTransformComponent::SetAnchorPreset(AnchorPrset preset)
{
	switch (preset)
	{
	case AnchorPrset::TopLeft:
		m_Anchor = { 0.0f, 0.0f };
		break;
	case AnchorPrset::TopRight:
		m_Anchor = { 1.0f, 0.0f };
		break;
	case AnchorPrset::BottomLeft:
		m_Anchor = { 0.0f, 1.0f };
		break;
	case AnchorPrset::BottomRight:
		m_Anchor = { 1.0f, 1.0f };
		break;
	case AnchorPrset::Center:
		m_Anchor = { 0.5f, 0.5f };
		break;
	default:
		break;
	}
}

void RectTransformComponent::SetPivotPreset(PivotPreset preset)
{
	switch (preset)
	{
	case PivotPreset::TopLeft:
		m_Pivot = { 0.0f, 0.0f };
		break;
	case PivotPreset::TopRight:
		m_Pivot = { 1.0f, 0.0f };
		break;
	case PivotPreset::BottomLeft:
		m_Pivot = { 0.0f, 1.0f };
		break;
	case PivotPreset::BottomRight:
		m_Pivot = { 1.0f, 1.0f };
		break;
	case PivotPreset::Center:
		m_Pivot = { 0.5f, 0.5f };
		break;
	default:
		break;
	}
}

void RectTransformComponent::UpdateMatrices()
{
	if (!m_IsDirty) return;

	D2D1_POINT_2F pivotOffset = D2D1::Point2F(
		m_Size.x * m_Pivot.x,
		m_Size.y * m_Pivot.y
	);

	Vec2F anchorPosition = { 0, 0 };
	if (m_Parent)
	{
		auto parentSize = m_Parent->GetSize();
		anchorPosition = {
			m_Anchor.minPoint.x * parentSize.x,
			m_Anchor.minPoint.y * parentSize.y
		};
	}

	Vec2F finalPosition = anchorPosition + m_Position;

	// 변환 행렬 계산
	auto matScale = Mat3X2F::Scale(m_Scale.x, m_Scale.y, pivotOffset);
	auto matRot = Mat3X2F::Rotation(m_Rotation, pivotOffset);
	auto matTrans = Mat3X2F::Translation(finalPosition.x, finalPosition.y);

	m_LocalMatrix = matScale * matRot * matTrans;

	if (m_Parent)
		m_WorldMatrix = m_LocalMatrix * m_Parent->GetWorldMatrix();
	else
		m_WorldMatrix = m_LocalMatrix;

	m_IsDirty = false;
}


const RectTransformComponent::Mat3X2F& RectTransformComponent::GetWorldMatrix()
{
	if (m_IsDirty) UpdateMatrices();
	return m_WorldMatrix;
}

const RectTransformComponent::Mat3X2F& RectTransformComponent::GetLocalMatrix()
{
	if (m_IsDirty) UpdateMatrices();
	return m_LocalMatrix;
}