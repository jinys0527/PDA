#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

void PlayerObject::Update(float deltaTime)
{
	static float time = 0;

	time += deltaTime;

	if (time >= 1.0f)
	{
		time -= 1.0f;
		SpriteRenderer* sprite = GetComponent<SpriteRenderer>();

		//if (&it != nullptr)
		//{
			sprite->SetFlipX(!sprite->GetFlipX());
			sprite->SetFlipY(!sprite->GetFlipY());
		//}
	}

	GameObject::Update(deltaTime);
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto sprite = GetComponent<SpriteRenderer>();
	auto image = GetComponent<UIImageComponent>();

	float z = GetComponent<RunPlayerController>()->GetZ();

	if (sprite)
	{
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			D2D1::Matrix3x2F flip = D2D1::Matrix3x2F::Identity();
			if (sprite->GetFlipX())
			{
				flip._11 = -1;
			}
			else
			{
				flip._11 = 1;
			}
			if (sprite->GetFlipY())
			{
				flip._22 = -1;
			}
			else
			{
				flip._22 = 1;
			}
			info.worldMatrix = flip * D2D1::Matrix3x2F::Translation(0, z) *  m_Transform->GetWorldMatrix();
			info.size = { 1,1 };
			if (sprite->GetFlipX())
				info.size = { -1, 1 };
			info.pivot = sprite->GetPivot();
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) ������
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
			pos.y = z;
			m_Transform->SetPosition(pos);
			info.worldMatrix = m_Transform->GetWorldMatrix();
			info.size = { 1,1 };
			if (sprite->GetFlipX())
				info.size = { -1, 1 };
			info.pivot = sprite->GetPivot();
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) ������
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
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
