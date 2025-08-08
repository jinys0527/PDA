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

	m_BlackBoard = std::make_unique<BossBlackBoard>();
	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();


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
	if (enemy->GetFSM().GetCurrentState() == "None")
		return;

	CollisionInfo info;
	info.self = enemy;
	info.other = player;
	info.normal;
	info.contactPoint;
	info.penetrationDepth;

	eventDispatcher.Dispatch(EventType::CollisionExit, &info);
}

void TitleScene::FixedUpdate()
{
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("test")->second.get()); // 나중에 플레이어로 바꿀듯
	if (player == nullptr)
		return;
	BoxColliderComponent* playerBox = player->GetComponent<BoxColliderComponent>();
	if (playerBox == nullptr)
		return;
	Vec2F playerPos = playerBox->GetCenter();
	float playerZ = player->GetZ();
	Obstacle* enemy;
	BoxColliderComponent* enemyBox;
	Vec2F enemyPos;


	for (auto gameObject : m_GameObjects)
	{
		if (player == gameObject.second.get())
			continue;
		enemyBox = gameObject.second->GetComponent<BoxColliderComponent>();
		if (enemyBox)
		{
			auto state = enemyBox->GetFSM().GetCurrentState();

			enemyPos = enemyBox->GetCenter();

			if (enemyPos.x < playerPos.x - 500 || enemyPos.x > playerPos.x + 500)
			{
				continue;
			}

			enemy = (Obstacle*)gameObject.second.get();
			float enemyZ = enemy->GetZ();
			if (enemyZ - 0.5f > playerZ || enemyZ + 0.5f < playerZ) // 질문 Z 축 검사를 먼저하는게 비용이 좋을까요 X 축 검사를 먼저하는게 비용이 좋을까요
			{
				ObjectCollisionLeave(m_EventDispatcher, enemyBox, playerBox);
				continue;
			}


			if (enemyBox->BoxVsBox(*playerBox))
			{
				CollisionInfo info;
				info.self = enemyBox;
				info.other = playerBox;
				info.normal = enemyPos - playerPos;
				info.contactPoint;
				info.penetrationDepth;
			

				
				if (state == "None")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionEnter, &info);
				}
				else if(state == "Enter")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionStay, &info);
				}
				else if (state == "Stay")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionStay, &info);
				}
				else if (state == "Exit")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionEnter, &info);
				}

				continue;
			}

			ObjectCollisionLeave(m_EventDispatcher, enemyBox, playerBox);
		}
	}
}

void TitleScene::Update(float deltaTime)
{
	m_BTElapsedTime += deltaTime;
	m_OneSecondTimer += deltaTime;

	if (m_BTElapsedTime >= 0.016f)
	{
		if (m_BehaviorTree)
		{
			m_BehaviorTree->Tick(m_BTElapsedTime);
		}

		m_BTElapsedTime = 0.0f;

	}

	if (m_OneSecondTimer >= 1.0f)
	{
		m_OneSecondTimer = 0.0f;

		float curHP = m_BlackBoard->GetValue<float>("BossCurrHP").value();
		//std::cout << "현재 HP: " << curHP << std::endl;
		m_BlackBoard->SetValue("BossCurrHP", curHP - 5);

		// 가중치 로그 출력
		//float w1 = m_BlackBoard->GetValue<float>("SkillWeight_1").value();
		//float w2 = m_BlackBoard->GetValue<float>("SkillWeight_2").value();
		//float w3 = m_BlackBoard->GetValue<float>("SkillWeight_3").value();

		//std::cout << "Skill Weights: [1] " << w1 << "  [2] " << w2 << "  [3] " << w3 << std::endl;
	}

	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	//Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();
	//m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 100 * deltaTime, pos.y});

	//std::cout << pos.x << " " << pos.y << std::endl;

}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);

		
	}

	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Render(uiRenderInfo);
		uiObject.second->Render(uiTextInfo);
	}
}
