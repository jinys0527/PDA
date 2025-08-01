#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

void PlayerObject::Update(float deltaTime)
{
	//float temp = m_Transform->GetPosition().y;

	GameObject::Update(deltaTime);

	m_Fsm.Update(deltaTime);
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto sprite = GetComponent<SpriteRenderer>();
	auto image = GetComponent<UIImageComponent>();

	if (sprite)
	{
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			info.worldMatrix = m_Transform->GetWorldMatrix(); // D2D1::Matrix3x2F::Translation(0, z * m_RailHeight) *  
			info.size = { 1,1 };
			info.pivot = Math::Vector2F(180, 360); // 바꾸어 놓음
			// UI가 아닌 일반 오브젝트 위치로 설정
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
			renderInfo.push_back(info);
		}
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			Math::Vector2F pos = m_Transform->GetPosition();
			float y = pos.y;
			pos.y = m_Z * m_RailHeight;
			m_Transform->SetPosition(pos);
			info.size = { 1,1 };
			D2D1::Matrix3x2F size = D2D1::Matrix3x2F::Identity();
			size._22 = 0.5f;
			info.worldMatrix = size * m_Transform->GetWorldMatrix();

			info.pivot = Math::Vector2F(180, 180);// 잠시 바꾸어놓음
			// UI가 아닌 일반 오브젝트 위치로 설정
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
			//float opacity = sprite->GetTexture().Get()->GetSize().height / (y + 1);
			float forSin = (y - m_Z*m_RailHeight) / (sprite->GetTexture().Get()->GetSize().height);
			forSin = forSin > asin(1) ? asin(1) : forSin;
			float opacity = sin(forSin);
			info.opacity = 1.0f - opacity;
			renderInfo.push_back(info);
			pos.y = y;
			m_Transform->SetPosition(pos);
		}
	}
	else if (image)
	{
		RenderInfo info;
		renderInfo.push_back(info);
	}
	else
	{
		return;
	}
}
