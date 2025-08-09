#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "ButtonUI.h"
#include "GameObject.h"
#include "UIObject.h"
#include "SceneManager.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "RectTransformComponent.h"
#include "BoxColliderComponent.h"
#include "SoundUI.h"
#include "UIImageComponent.h"

void TitleScene::Initialize()
{
#pragma region Setting
	auto settingBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	settingBackGround->SetIsFullScreen(true);
	auto settingBackGroungImg = settingBackGround->GetComponent<UIImageComponent>();
	settingBackGroungImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_bg_popup", "../Resource/UI/Setting/setting_bg_popup.png"));
	auto settingBackGroundRect = settingBackGround->GetComponent<RectTransformComponent>();

	auto settingOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto settingOkButtonImg = settingOkButton->GetComponent<UIImageComponent>();
	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png"));
	auto settingOkButtoComp = settingOkButton->GetComponent<UIButtonComponent>();
	settingOkButtoComp->GetFSM().SetOnEnter("Hover", [settingOkButtonImg, this]() { settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_on", "../Resource/UI/Setting/setting_ok_button_on.png")); });
	settingOkButtoComp->GetFSM().SetOnExit("Hover", [settingOkButtonImg, this]() {	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png")); });
	settingOkButtoComp->GetFSM().SetOnEnter("Click", [settingBackGround]() { settingBackGround->SetIsVisible(false); });
	auto settingOkButtonRect = settingOkButton->GetComponent<RectTransformComponent>();

	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	auto soundUIRect = soundUI->GetComponent<RectTransformComponent>();

	auto soundBGMFrame = std::make_shared<UIObject>(m_EventDispatcher);
	auto soundBGMFrameImg = soundBGMFrame->AddComponent<UIImageComponent>();
	soundBGMFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_slider_bgm_frame", "../Resource/UI/Setting/setting_slider_bgm_frame.png"));
	soundBGMFrameImg->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	soundBGMFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFrameImg->GetTexture()->GetSize());
	auto soundBGMFrameRect = soundBGMFrame->GetComponent<RectTransformComponent>();
	soundBGMFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFrameRect->SetSize({ 300.0f, 200.0f });
	soundBGMFrameRect->SetPosition({ 0.0f, -160.0f });
	soundUI->GetBGM()->SetFrame(soundBGMFrame);

	auto soundBGMFill = std::make_shared<UIObject>(m_EventDispatcher);
	auto soundBGMFillImg = soundBGMFill->AddComponent<UIImageComponent>();
	soundBGMFillImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_slider_bgm_fill", "../Resource/UI/Setting/setting_slider_bgm_fill.png"));
	soundBGMFillImg->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	soundBGMFillImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFillImg->GetTexture()->GetSize());
	auto soundBGMFillRect = soundBGMFill->GetComponent<RectTransformComponent>();
	soundBGMFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFillRect->SetSize({ 300.0f, 200.0f });
	soundBGMFillRect->SetPosition({ 0.0f, -160.0f });
	soundUI->GetBGM()->SetFill(soundBGMFill);

	auto soundSFXFrame = std::make_shared<UIObject>(m_EventDispatcher);
	auto soundSFXFrameImg = soundSFXFrame->AddComponent<UIImageComponent>();
	soundSFXFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_slider_sfx_frame", "../Resource/UI/Setting/setting_slider_sfx_frame.png"));
	soundSFXFrameImg->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	soundSFXFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFrameImg->GetTexture()->GetSize());
	auto soundSFXFrameRect = soundSFXFrame->GetComponent<RectTransformComponent>();
	soundSFXFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFrameRect->SetSize({ 300.0f, 200.0f });
	soundSFXFrameRect->SetPosition({ 0.0f, -160.0f });
	soundUI->GetBGM()->SetFrame(soundSFXFrame);

	auto soundSFXFill = std::make_shared<UIObject>(m_EventDispatcher);
	auto soundSFXFillImg = soundSFXFill->AddComponent<UIImageComponent>();
	soundSFXFillImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_slider_sfx_fill", "../Resource/UI/Setting/setting_slider_sfx_fill.png"));
	soundSFXFillImg->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	soundSFXFillImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFillImg->GetTexture()->GetSize());
	auto soundSFXFillRect = soundSFXFill->GetComponent<RectTransformComponent>();
	soundSFXFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFillRect->SetSize({ 300.0f, 200.0f });
	soundSFXFillRect->SetPosition({ 0.0f, -160.0f });
	soundUI->GetBGM()->SetFill(soundSFXFill);

	settingBackGroundRect->AddChild(settingOkButtonRect);
	settingBackGroundRect->AddChild(soundUIRect);
	
	settingBackGround->SetIsVisible(false);
#pragma endregion


#pragma region Credit
	auto creditMainButton = std::make_shared<ButtonUI>(m_EventDispatcher);

	auto creditMainButtonRect = creditMainButton->GetComponent<RectTransformComponent>();

	auto creditBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	creditBackGround->SetIsFullScreen(true);
	auto creditBackGroundRect = creditBackGround->GetComponent<RectTransformComponent>();
	
	creditBackGroundRect->AddChild(creditMainButtonRect);

	creditBackGround->SetIsVisible(false);
#pragma endregion


#pragma region Exit
	auto exitBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	exitBackGround->SetIsFullScreen(true);
	exitBackGround->SetIsVisible(false);
	auto exitYesButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto exitNoButton = std::make_shared<ButtonUI>(m_EventDispatcher);
#pragma endregion

#pragma region Main
	auto pressAnyKey = std::make_shared<UIObject>(m_EventDispatcher);
	auto pressAnyKeyImg = pressAnyKey->AddComponent<UIImageComponent>();
	pressAnyKeyImg->SetBitmap(m_AssetManager.LoadTexture(L"pressAnyKey", "../Resource/UI/Title/pressAnyKey.png"));

	auto backGround = std::make_shared<UIObject>(m_EventDispatcher);
	backGround->SetIsFullScreen(true);
	auto backGroundImg = backGround->AddComponent<UIImageComponent>();
	backGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"title_illustration", "../Resource/UI/Title/title_illustration.png"));

#pragma region menuBox
	auto menuBox = std::make_shared<UIObject>(m_EventDispatcher);
	menuBox->SetIsFullScreen(true);
	auto menuBoxImg = menuBox->AddComponent<UIImageComponent>();
	menuBoxImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_bg_box", "../Resource/UI/Title/mainmenu_bg_box.png"));

	auto menuBoxRect = menuBox->GetComponent<RectTransformComponent>();

	auto startButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto startButtonImg = startButton->AddComponent<UIImageComponent>();
	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png"));
	auto startButtonComp = startButton->GetComponent<UIButtonComponent>();
	startButtonComp->GetFSM().SetOnEnter("Hover", [startButtonImg, this]() { startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_on", "../Resource/UI/Title/mainmenu_startbutton_on.png")); });
	startButtonComp->GetFSM().SetOnExit("Hover", [startButtonImg, this]() {	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png")); });
	startButtonComp->GetFSM().SetOnEnter("Click", [this]() {m_SceneManager->SetCurrentScene("CharacterSelectScene"); });

	auto startButtonRect = startButton->GetComponent<RectTransformComponent>();

	auto settingButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto settingButtonImg = settingButton->AddComponent<UIImageComponent>();
	settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png"));
	auto settingButtonComp = settingButton->GetComponent<UIButtonComponent>();
	settingButtonComp->GetFSM().SetOnEnter("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_setting_on", "../Resource/UI/Title/mainmenu_settingbutton_on.png")); });
	settingButtonComp->GetFSM().SetOnExit("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_setting_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png")); });
	settingButtonComp->GetFSM().SetOnEnter("Click", [settingBackGround]() { settingBackGround->SetIsVisible(true); });

	auto settingButtonRect = settingButton->GetComponent<RectTransformComponent>();

	auto creditButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	auto creditButtonImg = creditButton->AddComponent<UIImageComponent>();
	creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_creditbutton_off", "../Resource/UI/Title/mainmenu_creditbutton_off.png"));
	auto creditButtonComp = creditButton->GetComponent<UIButtonComponent>();
	creditButtonComp->GetFSM().SetOnEnter("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_creditbutton_on", "../Resource/UI/Title/mainmenu_creditbutton_on.png")); });
	creditButtonComp->GetFSM().SetOnExit("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_creditbutton_off", "../Resource/UI/Title/mainmenu_creditbutton_off.png")); });
	creditButtonComp->GetFSM().SetOnEnter("Click", []() {});

	auto creditButtonRect = creditButton->GetComponent<RectTransformComponent>();

	menuBoxRect->AddChild(startButtonRect);
	menuBoxRect->AddChild(settingButtonRect);
	menuBoxRect->AddChild(creditButtonRect);
#pragma endregion

	m_UIManager.AddUI(pressAnyKey);
	m_UIManager.AddUI(backGround);
	m_UIManager.AddUI(menuBox);
#pragma endregion

	
#pragma region Camera
	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans = cameraObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	cameraCol->SetSize({ 1920, 1080 });
	SetMainCamera(cameraObject);

	AddGameObject(cameraObject);
#pragma endregion
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



void ObjectCollisionLeave(EventDispatcher& eventDispatcher, BoxColliderComponent* enemy, BoxColliderComponent* player);

void TitleScene::FixedUpdate()
{
}

void TitleScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	m_UIManager.Update(deltaTime);
}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	if (!m_UIManager.IsFullScreenUIActive())
	{
		for (auto& pair : m_GameObjects)
		{
			auto& gameObject = pair.second;
			if (gameObject->IsInView(m_Camera))
			{
				gameObject->Render(renderInfo);
			}
		}
	}
	
	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}
