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
#include "BoxColliderComponent.h"
#include "Obstacle.h"
//================================
#include "BlackBoard.h"
#include "TestNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Repeater.h"
#include "Inverter.h"

//================================
#include "BossBehaviorTree.h"
#include "BossBlackBoard.h"
//================================

void TitleScene::Initialize()
{

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5);
	SetMainCamera(cameraObject);



	//// BT테스트
	//m_BlackBoard = new BlackBoard();

	//// 값 설정
	//m_BlackBoard->SetValue("AA", true);
	//m_BlackBoard->SetValue("BB", true);
	//m_BlackBoard->SetValue("A", true);
	//m_BlackBoard->SetValue("B", true);
	//m_BlackBoard->SetValue("C", true);
	//m_BlackBoard->SetValue("D", true);

	//// Leaf 노드
	//auto A = std::make_shared<TestNode>("A");
	//auto B = std::make_shared<TestNode>("B");
	//auto C = std::make_shared<TestNode>("C");
	//auto D = std::make_shared<TestNode>("D");

	//// Selector AA
	//auto AA = std::make_shared<Selector>("AA");
	//AA->AddChild(A);
	//AA->AddChild(B);

	//// Sequence BB
	//auto BB = std::make_shared<Sequence>("BB");
	//BB->AddChild(C);
	//BB->AddChild(D);

	//// Root (Selector)
	//auto Root = std::make_shared<Selector>("Root");
	//Root->AddChild(AA);
	//Root->AddChild(BB);

	//m_BehaviorTree = Root;
	//// BT테스트 끝================



	// 보스BT 테스트



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

void ObjectCollisionLeave(EventDispatcher &eventDispatcher, BoxColliderComponent *enemy, BoxColliderComponent* player)
{
}

void TitleScene::FixedUpdate()
{
}

void TitleScene::Update(float deltaTime)
{
}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);

		
	}

	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Render(uiRenderInfo);
	}
}
