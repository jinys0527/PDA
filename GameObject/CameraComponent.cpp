#include "CameraComponent.h"
#include "TransformComponent.h"
CameraComponent::CameraComponent(const float width, const float height)
{
	m_Width = width;
	m_Height = height;
}

void CameraComponent::Update(float deltaTime)
{
	m_Owner->GetComponent<TransformComponent>();
}

void CameraComponent::OnEvent(EventType type, const void* data)
{
}

void CameraComponent::Serialize(nlohmann::json& j) const
{
}

void CameraComponent::Deserialize(const nlohmann::json& j)
{
}

D2D1::Matrix3x2F CameraComponent::GetViewMatrix()
{
	Math::Vector2F position = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	

	auto pan = D2D1::Matrix3x2F::Translation(-position.x, -position.y);

	auto scaleFlip = D2D1::Matrix3x2F::Scale(m_Zoom, -m_Zoom);

	auto center = D2D1::Matrix3x2F::Translation(m_Width * 0.5f, m_Height * 0.5f);

	return pan * scaleFlip * center;
}

D2D1::Matrix3x2F CameraComponent::GetViewMatrixForUI()
{
	Math::Vector2F position = m_Owner->GetComponent<TransformComponent>()->GetPosition();

	auto pan = D2D1::Matrix3x2F::Translation(-(m_Width / 2), -(m_Height / 2));

	auto scaleFlip = D2D1::Matrix3x2F::Scale(1, -1);

	auto center = D2D1::Matrix3x2F::Translation(m_Width * 0.5f, m_Height * 0.5f);

	return pan * scaleFlip * center;
}

