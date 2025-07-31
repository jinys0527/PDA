#include "UIComponent.h"
#include "Event.h"
#include "iostream"

void UIComponent::Update(float deltaTime)
{
}

void UIComponent::OnEvent(EventType type, const void* data)
{
	auto mouseData = static_cast<const Events::MouseState*>(data);
	std::cout << mouseData->pos.x << " " << mouseData->pos.y << "¿¡¼­ Å¬¸¯µÊ \n";
}

void UIComponent::Serialize(nlohmann::json& j) const
{
}

void UIComponent::Deserialize(const nlohmann::json& j)
{
}
