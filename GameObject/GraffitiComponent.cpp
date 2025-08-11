#include "GraffitiComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"
#include "iostream"

GraffitiComponent::GraffitiComponent()
{

}

GraffitiComponent::~GraffitiComponent()
{
	//m_Owner->GetEventDispatcher().RemoveListener(EventType::Hovered, this);
	//m_Owner->GetEventDispatcher().RemoveListener(EventType::MouseRightClick, this);
	m_Owner->GetEventDispatcher().RemoveListener(EventType::OnPlayerAttack, this);
}

void GraffitiComponent::Start()
{
	//m_Owner->GetEventDispatcher().AddListener(EventType::Hovered, this);
	//m_Owner->GetEventDispatcher().AddListener(EventType::MouseRightClick, this);
	m_Owner->GetEventDispatcher().AddListener(EventType::OnPlayerAttack, this);
}

void GraffitiComponent::Update(float deltatime)
{
	//std::cout << "m_IsHovered: " << m_IsHovered << std::endl;
	//std::cout << "m_IsClicked: " << m_IsClicked << std::endl;

}

void GraffitiComponent::OnEvent(EventType type, const void* data)
{
	if (type == EventType::OnPlayerAttack)
	{
		auto attackInfo = static_cast<const PlayerAttackInfo*>(data);
		IsHovered(attackInfo->mousePos);
		if (m_IsHovered)
		{
			//std::cout << mouseData->pos.x << " " << mouseData->pos.y << "에서 클릭됨 \n";
			m_IsClicked = true;
			if (!m_IsFirst)
			{
				m_IsFirst = true;
				int one = 1;
				GetEventDispatcher().Dispatch(EventType::OnPlayerReinforcedCollisionOccur, (const void*)one);//player 받아와서 그냥 바꿔야하나
				attackInfo->player->SetIsAttackSuccessed(true);
			}
			//attackInfo->damage 데미지도 가져옴
		}
	}
}

void GraffitiComponent::IsHovered(Math::Vector2F mousePos)
{
	auto objPos = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	auto objSize = m_Owner->GetComponent<SpriteRenderer>()->GetTexture()->GetSize();
	auto objPivot = m_Owner->GetComponent<SpriteRenderer>()->GetPivot();

	D2D1_POINT_2F topLeft;
	topLeft.x = objPos.x - objPivot.x;
	topLeft.y = objPos.y - objPivot.y;

	D2D1_POINT_2F mouse;
	mouse.x = mousePos.x;
	mouse.y = mousePos.y;

	if (mouse.x >= topLeft.x && mouse.x <= (topLeft.x + objSize.width) &&
		mouse.y >= topLeft.y && mouse.y <= (topLeft.y + objSize.height))
	{
		m_IsHovered = true;
	}
	else
	{
		m_IsHovered = false;
	}
}


