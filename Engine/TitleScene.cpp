#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "TestListener.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"
#include "ButtonUI.h"
#include "CameraComponent.h"
#include "UIImageComponent.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
//================================
#include "TestNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Repeater.h"
#include "Inverter.h"

//================================

void TitleScene::Initialize()
{
	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5);
	SetMainCamera(cameraObject);

	// 값 설정
	m_BlackBoard.SetValue("AA", true);
	m_BlackBoard.SetValue("BB", true);
	m_BlackBoard.SetValue("A", true);
	m_BlackBoard.SetValue("B", true);
	m_BlackBoard.SetValue("C", true);
	m_BlackBoard.SetValue("D", true);

	// Leaf 노드
	auto A = std::make_shared<TestNode>("A");
	auto B = std::make_shared<TestNode>("B");
	auto C = std::make_shared<TestNode>("C");
	auto D = std::make_shared<TestNode>("D");

	// Selector AA
	auto AA = std::make_shared<Selector>("AA");
	AA->AddChild(A);
	AA->AddChild(B);

	// Sequence BB
	auto BB = std::make_shared<Sequence>("BB");
	BB->AddChild(C);
	BB->AddChild(D);

	// Root (Selector)
	auto Root = std::make_shared<Selector>("Root");
	Root->AddChild(AA);
	Root->AddChild(BB);

	m_BehaviorTree = Root;

	AddGameObject(cameraObject);
}

void TitleScene::Finalize()
{
	
}

void TitleScene::Enter()
{
}

void TitleScene::Leave()
{
}

void TitleScene::Update(float deltaTime)
{
	m_BTElapsedTime += deltaTime;

	if (m_BTElapsedTime >= 1.0f)
	{
		std::cout << "cnt: " << cnt++ << std::endl;

		m_BTElapsedTime = 0.0f;

		if (m_BehaviorTree)
			m_BehaviorTree->Tick(m_BlackBoard);


	}

	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	//Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();
	//m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 100 * deltaTime, pos.y});

	//std::cout << pos.x << " " << pos.y << std::endl;

}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);

		
	}
}
