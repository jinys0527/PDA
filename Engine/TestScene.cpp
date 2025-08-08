#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "AnimationController.h"
#include "SoundUI.h"
#include "SoundManager.h"
#include "ButtonUI.h"
#include "UIObject.h"
#include "UIImageComponent.h"
#include "UISliderComponent.h"
#include "UITextComponent.h"

void TestScene::Initialize()
{
	/*auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 300.0f, 300.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");

	auto animComp = gameObject->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("attack");
	sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
	sr->SetTextureKey("boss");*/

	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->m_Name = "sound";
	soundUI->SetSlider();
	auto uiText = soundUI->AddComponent<UITextComponent>();
	uiText->SetDWriteFactory(m_Renderer.GetDWriteFactory());
	uiText->SetText(L"UI 텍스트 예시");
	uiText->SetFontName(L"Segoe UI");
	uiText->SetFontSize(24.0f);
	uiText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	uiText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	uiText->SetLayoutSize(500.0f, 100.0f);
	m_SoundManager.BGM_Shot(L"bgm");
	m_SoundManager.SFX_Shot(L"sfx_b2b");
	m_SoundManager.UI_Shot(L"play");
	
	auto rect = soundUI->GetComponent<RectTransformComponent>();
	rect->SetAnchorPreset(AnchorPrset::FullStretch);
	rect->SetPivotPreset(RectTransformPivotPreset::Center);
	rect->SetPosition({ 0.0f, 0.0f });
	rect->SetSize({ 600.f, 600.f });

	auto uiObj1 = std::make_shared<UIObject>(m_EventDispatcher);
	auto uiImage1 = uiObj1->AddComponent<UIImageComponent>();
	uiImage1->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	uiImage1->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	uiImage1->SetPivotPreset(ImagePivotPreset::Center, uiImage1->GetTexture()->GetSize());
	auto rect1 = uiObj1->GetComponent<RectTransformComponent>();
	rect1->SetAnchorPreset(AnchorPrset::FullStretch);
	rect1->SetPivotPreset(RectTransformPivotPreset::Center);
	rect1->SetSize({ 300.0f, 200.0f });
	rect1->SetPosition({ 0.0f, -410.0f });
	soundUI->GetMaster()->SetFrame(uiObj1);
	soundUI->GetMaster()->SetFill(uiObj1);

	auto uiObj2 = std::make_shared<UIObject>(m_EventDispatcher);
	auto uiImage2 = uiObj2->AddComponent<UIImageComponent>();
	uiImage2->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	uiImage2->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	uiImage2->SetPivotPreset(ImagePivotPreset::Center, uiImage2->GetTexture()->GetSize());
	auto rect2 = uiObj2->GetComponent<RectTransformComponent>();
	rect2->SetAnchorPreset(AnchorPrset::FullStretch);
	rect2->SetPivotPreset(RectTransformPivotPreset::Center);
	rect2->SetSize({ 300.0f, 200.0f });
	rect2->SetPosition({ 0.0f, -160.0f }); 
	soundUI->GetBGM()->SetFrame(uiObj2);
	soundUI->GetBGM()->SetFill(uiObj2);

	auto uiObj3 = std::make_shared<UIObject>(m_EventDispatcher);
	auto uiImage3 = uiObj3->AddComponent<UIImageComponent>();
	uiImage3->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	uiImage3->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	uiImage3->SetPivotPreset(ImagePivotPreset::Center, uiImage3->GetTexture()->GetSize());
	auto rect3 = uiObj3->GetComponent<RectTransformComponent>();
	rect3->SetAnchorPreset(AnchorPrset::FullStretch);
	rect3->SetPivotPreset(RectTransformPivotPreset::Center);
	rect3->SetSize({ 300.0f, 200.0f });
	rect3->SetPosition({ 0.0f, 00.0f });
	soundUI->GetSFX()->SetFrame(uiObj3);
	soundUI->GetSFX()->SetFill(uiObj3);

	auto uiObj4 = std::make_shared<UIObject>(m_EventDispatcher);
	auto uiImage4 = uiObj4->AddComponent<UIImageComponent>();
	uiImage4->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	uiImage4->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	uiImage4->SetPivotPreset(ImagePivotPreset::Center, uiImage4->GetTexture()->GetSize());
	auto rect4 = uiObj4->GetComponent<RectTransformComponent>();
	rect4->SetAnchorPreset(AnchorPrset::FullStretch);
	rect4->SetPivotPreset(RectTransformPivotPreset::Center);
	rect4->SetSize({ 300.0f, 200.0f });
	rect4->SetPosition({ 0.0f, 340.0f });
	soundUI->GetUI()->SetFrame(uiObj4);
	soundUI->GetUI()->SetFill(uiObj4);


	/*auto buttonUI = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto uiButton = buttonUI->GetComponent<UIButtonComponent>();
	uiButton->Start();
	uiButton->GetFSM().SetOnEnter("Click", []() {std::cout << "Click" << std::endl; });
	auto uiImage5 = buttonUI->AddComponent<UIImageComponent>();
	uiImage5->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	uiImage5->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	uiImage5->SetPivotPreset(ImagePivotPreset::Center, uiImage5->GetTexture()->GetSize());
	auto rect5 = buttonUI->GetComponent<RectTransformComponent>();
	rect5->SetAnchorPreset(AnchorPrset::FullStretch);
	rect5->SetPivotPreset(RectTransformPivotPreset::Center);
	rect5->SetSize({ 300.0f, 200.0f });
	rect5->SetPosition({ 0.0f, 0.0f });*/
	/*sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");*/

	//auto gameObject2 = std::make_shared<GameObject>(m_EventDispatcher);
	//gameObject2->m_Name = "test2";
	//auto trans2 = gameObject2->GetComponent<TransformComponent>();
	//trans2->SetPosition({ 800.0f, 500.0f });
	//auto sr2 = gameObject2->AddComponent<SpriteRenderer>();
	//sr2->SetAssetManager(&m_AssetManager);
	//sr2->SetPath("../Resource/cat.png");
	//sr2->SetTextureKey("cat_texture");

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	SetMainCamera(cameraObject);

	/*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);
	AddUIObject(soundUI);
	//AddUIObject(buttonUI);
	AddGameObject(cameraObject);
}

void TestScene::Finalize()
{
}

void TestScene::Enter()
{
}

void TestScene::Leave()
{
}

void TestScene::FixedUpdate()
{

}

void TestScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Update(deltaTime);
	}
}

void TestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
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
