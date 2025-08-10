#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "ControlComponent.h"
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
	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->SetZOrder(5);
	soundUI->m_Name = "soundUI";
	auto soundUIRect = soundUI->GetComponent<RectTransformComponent>();

	auto soundBGMFrame = std::make_shared<UIObject>(m_EventDispatcher);
	soundBGMFrame->SetZOrder(5);
	auto soundBGMFrameImg = soundBGMFrame->AddComponent<UIImageComponent>();
	soundBGMFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-up-down", "../Resource/UI/Setting/sound-bar-up-down.png"));
	soundBGMFrameImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundBGMFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFrameImg->GetTexture()->GetSize());
	auto soundBGMFrameRect = soundBGMFrame->GetComponent<RectTransformComponent>();
	soundBGMFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFrameRect->SetSize({ 642.0f, 58.0f });
	soundBGMFrameRect->SetPosition({ 0.0f, -30.0f });
	soundBGMFrame->SetIsVisible(false);
	soundUI->GetBGM()->SetFrame(soundBGMFrame);

	auto soundBGMFill = std::make_shared<UIObject>(m_EventDispatcher);
	soundBGMFill->SetZOrder(5);
	auto soundBGMFillImg = soundBGMFill->AddComponent<UIImageComponent>();
	soundBGMFillImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-up", "../Resource/UI/Setting/sound-bar-up.png"));
	soundBGMFillImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundBGMFillImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFillImg->GetTexture()->GetSize());
	auto soundBGMFillRect = soundBGMFill->GetComponent<RectTransformComponent>();
	soundBGMFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFillRect->SetSize({ 642.0f, 58.0f });
	soundBGMFillRect->SetPosition({ 0.0f, -30.0f });
	soundBGMFill->SetIsVisible(false);
	soundUI->GetBGM()->SetFill(soundBGMFill);

	auto soundSFXFrame = std::make_shared<UIObject>(m_EventDispatcher);
	soundSFXFrame->SetZOrder(5);
	auto soundSFXFrameImg = soundSFXFrame->AddComponent<UIImageComponent>();
	soundSFXFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-down-down", "../Resource/UI/Setting/sound-bar-down-down.png"));
	soundSFXFrameImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundSFXFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFrameImg->GetTexture()->GetSize());
	auto soundSFXFrameRect = soundSFXFrame->GetComponent<RectTransformComponent>();
	soundSFXFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFrameRect->SetSize({ 642.0f, 58.0f });
	soundSFXFrameRect->SetPosition({ 0.0f, 180.0f });
	soundSFXFrame->SetIsVisible(false);
	soundUI->GetSFX()->SetFrame(soundSFXFrame);

	auto soundSFXFill = std::make_shared<UIObject>(m_EventDispatcher);
	soundSFXFill->SetZOrder(5);
	auto soundSFXFillImg = soundSFXFill->AddComponent<UIImageComponent>();
	soundSFXFillImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-down", "../Resource/UI/Setting/sound-bar-down.png"));
	soundSFXFillImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundSFXFillImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFillImg->GetTexture()->GetSize());
	
	auto soundSFXFillRect = soundSFXFill->GetComponent<RectTransformComponent>();
	soundSFXFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFillRect->SetSize({ 642.0f, 58.0f });
	soundSFXFillRect->SetPosition({ 0.0f, 180.0f });
	soundSFXFill->SetIsVisible(false);
	soundUI->GetSFX()->SetFill(soundSFXFill);

	auto settingBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	settingBackGround->m_Name = "settingBackGround";
	settingBackGround->SetIsFullScreen(true);
	settingBackGround->SetZOrder(4);
	auto settingBackGroundImg = settingBackGround->AddComponent<UIImageComponent>();
	settingBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_popup", "../Resource/UI/Setting/setting_popup.png"));
	auto settingBackGroundRect = settingBackGround->GetComponent<RectTransformComponent>();
	settingBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);
	settingBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	settingBackGroundRect->SetPosition({ 0.0f, 0.0f });

	auto settingOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingOkButton->m_Name = "settingOkButton";
	settingOkButton->SetZOrder(5);
	auto settingOkButtonImg = settingOkButton->AddComponent<UIImageComponent>();
	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png"));
	auto settingOkButtoComp = settingOkButton->GetComponent<UIButtonComponent>();

	settingOkButtoComp->GetFSM().SetOnEnter("Hover", [settingOkButtonImg, this]() { settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_on", "../Resource/UI/Setting/setting_ok_button_on.png")); });
	settingOkButtoComp->GetFSM().SetOnExit("Hover", [settingOkButtonImg, this]() {	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png")); });

	std::weak_ptr<UIObject> weaksettingBackGround = settingBackGround;
	std::weak_ptr<ButtonUI> weaksettingOkButton = settingOkButton;
	std::weak_ptr<SoundUI> weakSoundUI = soundUI;

	settingOkButtoComp->GetFSM().SetOnEnter("Click", [weaksettingBackGround, weaksettingOkButton, weakSoundUI]() {
		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(false);
		});
	auto settingOkButtonRect = settingOkButton->GetComponent<RectTransformComponent>();
	settingOkButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingOkButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
	settingOkButtonRect->SetSize({ 428.0f, 107.0f });
	settingOkButtonRect->SetPosition({ 0.0f, 325.0f });

// 	settingBackGroundRect->AddChild(settingOkButtonRect);
// 	settingBackGroundRect->AddChild(soundUIRect);

	settingBackGround->SetIsVisible(false);
	settingOkButton->SetIsVisible(false);
	soundUI->SetIsVisible(false);

	m_UIManager.AddUI("TitleScene", settingBackGround);
	m_UIManager.AddUI("TitleScene", settingOkButton);
	m_UIManager.AddUI("TitleScene", soundUI);
	
#pragma endregion


#pragma region Credit
	auto creditBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	creditBackGround->m_Name = "creditBackGround";
	creditBackGround->SetIsFullScreen(true);
	creditBackGround->SetZOrder(2);
	auto creditBackGroundImg = creditBackGround->AddComponent<UIImageComponent>();
	creditBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_popup", "../Resource/UI/Credit/credits_popup.png"));
	auto creditBackGroundRect = creditBackGround->GetComponent<RectTransformComponent>();

	auto creditMainButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	creditMainButton->SetZOrder(2);
	creditMainButton->m_Name = "creditMainButton";
	auto creditMainButtonImg = creditMainButton->AddComponent<UIImageComponent>();
	creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_off", "../Resource/UI/Credit/credits_button_off.png"));
	auto creditMainButtonComp = creditMainButton->GetComponent<UIButtonComponent>();
	creditMainButtonComp->GetFSM().SetOnEnter("Hover", [creditMainButtonImg, this]() { creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_on", "../Resource/UI/Credit/credits_button_on.png")); });
	creditMainButtonComp->GetFSM().SetOnExit("Hover", [creditMainButtonImg, this]() { creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_off", "../Resource/UI/Credit/credits_button_off.png")); });

	std::weak_ptr<UIObject> weakcreditBackGround = creditBackGround;
	std::weak_ptr<ButtonUI> weakcreditMainButton = creditMainButton;

	creditMainButtonComp->GetFSM().SetOnEnter("Click", [weakcreditBackGround, weakcreditMainButton]() {
		if (auto bg = weakcreditBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakcreditMainButton.lock()) btn->SetIsVisible(false);
		});
	auto creditMainButtonRect = creditMainButton->GetComponent<RectTransformComponent>();

	/*creditBackGroundRect->AddChild(creditMainButtonRect);*/

	creditBackGround->SetIsVisible(false);
	creditMainButton->SetIsVisible(false);

	m_UIManager.AddUI("TitleScene", creditBackGround);
	m_UIManager.AddUI("TitleScene", creditMainButton);	
#pragma endregion


#pragma region Exit
	auto exitBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	exitBackGround->m_Name = "exitBackGround";
	exitBackGround->SetIsFullScreen(true);
	exitBackGround->SetZOrder(2);
	auto exitBackGroundImg = exitBackGround->AddComponent<UIImageComponent>();
	exitBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_popup", "../Resource/UI/Exit/exitconfirm_popup.png"));
	auto exitBackGroundRect = exitBackGround->GetComponent<RectTransformComponent>();

	auto exitOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitOkButton->m_Name = "exitOkButton";
	exitOkButton->SetZOrder(2);
	auto exitOkButtonImg = exitOkButton->AddComponent<UIImageComponent>();
	exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_off", "../Resource/UI/Exit/exitconfirm_ok_button_off.png"));
	auto exitOkButtonComp = exitOkButton->GetComponent<UIButtonComponent>();
	exitOkButtonComp->GetFSM().SetOnEnter("Hover", [exitOkButtonImg, this]() { exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_on", "../Resource/UI/Exit/exitconfirm_ok_button_on.png")); });
	exitOkButtonComp->GetFSM().SetOnExit("Hover", [exitOkButtonImg, this]() { exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_off", "../Resource/UI/Exit/exitconfirm_ok_button_off.png")); });
	exitOkButtonComp->GetFSM().SetOnEnter("Click", [this]() {
		if (m_SceneManager)
		{
			m_SceneManager->RequestQuit();
		}
		});
	auto exitOkButtonRect = exitOkButton->GetComponent<RectTransformComponent>();

	auto exitNoButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitNoButton->m_Name = "exitNoButton";
	exitNoButton->SetZOrder(2);
	auto exitNoButtonImg = exitNoButton->AddComponent<UIImageComponent>();
	exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png"));
	auto exitNoButtonComp = exitNoButton->GetComponent<UIButtonComponent>();
	exitNoButtonComp->GetFSM().SetOnEnter("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_on", "../Resource/UI/Exit/exitconfirm_no_button_on.png")); });
	exitNoButtonComp->GetFSM().SetOnExit("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png")); });

	std::weak_ptr<UIObject> weakexitBackGround = exitBackGround;
	std::weak_ptr<ButtonUI> weakexitOkButton = exitOkButton;
	std::weak_ptr<ButtonUI> weakexitNoButton = exitNoButton;

	exitNoButtonComp->GetFSM().SetOnEnter("Click", [weakexitBackGround, weakexitOkButton, weakexitNoButton]() {
		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);
		});
	auto exitNoButtonRect = exitNoButton->GetComponent<RectTransformComponent>();

// 	exitBackGroundRect->AddChild(exitOkButtonRect);
// 	exitBackGroundRect->AddChild(exitNoButtonRect);

	exitBackGround->SetIsVisible(false);
	exitOkButton->SetIsVisible(false);
	exitNoButton->SetIsVisible(false);

	m_UIManager.AddUI("TitleScene", exitBackGround);
	m_UIManager.AddUI("TitleScene", exitOkButton);
	m_UIManager.AddUI("TitleScene", exitNoButton);
#pragma endregion

#pragma region Main
	auto pressAnyKey = std::make_shared<UIObject>(m_EventDispatcher);
	pressAnyKey->m_Name = "pressAnyKey";
	pressAnyKey->SetZOrder(1);
	auto pressAnyKeyImg = pressAnyKey->AddComponent<UIImageComponent>();
	pressAnyKeyImg->SetBitmap(m_AssetManager.LoadTexture(L"pressAnyKey", "../Resource/UI/Title/pressAnyKey.png"));


	auto backGround = std::make_shared<UIObject>(m_EventDispatcher);
	backGround->m_Name = "backGround";
	backGround->SetIsFullScreen(true);
	backGround->SetZOrder(0);
	backGround->SetIsVisible(false);
	auto backGroundImg = backGround->AddComponent<UIImageComponent>();
	backGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"title_illustration", "../Resource/UI/Title/title_illustration.png"));
	backGroundImg->SetUV({ 1920.0f, 1080.0f });


	auto backGroundRect = backGround->GetComponent<RectTransformComponent>();
	backGroundRect->SetPosition({ 0.0f, 0.0f });
	//backGroundRect->SetSize({ 1920.0f, 1080.0f });
	backGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	backGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);

#pragma region menuBox
	auto menuBox = std::make_shared<UIObject>(m_EventDispatcher);
	menuBox->m_Name = "menuBox";
	menuBox->SetIsFullScreen(true);
	menuBox->SetZOrder(2);
	auto menuBoxImg = menuBox->AddComponent<UIImageComponent>();
	menuBoxImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_bg_box", "../Resource/UI/Title/mainmenu_bg_box.png"));


	auto menuBoxRect = menuBox->GetComponent<RectTransformComponent>();
	menuBoxRect->SetSize({ 1920.0f, 1080.0f });
	menuBoxRect->SetPosition({ 0.0f, 0.0f });
	menuBoxRect->SetAnchorPreset(AnchorPrset::FullStretch);
	menuBoxRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto startButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	startButton->m_Name = "startButton";
	startButton->SetZOrder(3);
	auto startButtonImg = startButton->AddComponent<UIImageComponent>();
	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png"));
	startButtonImg->SetUV({ 650.0f, 161.0f });
	auto startButtonComp = startButton->GetComponent<UIButtonComponent>();
	startButtonComp->GetFSM().SetOnEnter("Hover", [startButtonImg, this]() { startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_on", "../Resource/UI/Title/mainmenu_startbutton_on.png")); });
	startButtonComp->GetFSM().SetOnExit("Hover", [startButtonImg, this]() {	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png")); });
	startButtonComp->GetFSM().SetOnEnter("Click", [this]() {
		m_SceneManager->ChangeScene("CharacterSelectScene"); 
		m_UIManager.SetCurrentScene("CharacterSelectScene"); 
		});
	
	auto startButtonRect = startButton->GetComponent<RectTransformComponent>();
	auto test = startButtonRect->GetOwner();
	auto ui = dynamic_cast<UIObject*>(test);
	startButtonRect->SetPosition({ 80.0f, -430.0f });
	startButtonRect->SetSize({ 650.0f, 161.0f });
	startButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	startButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);


	auto settingButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingButton->m_Name = "settingButton";
	settingButton->SetZOrder(3);
	auto settingButtonImg = settingButton->AddComponent<UIImageComponent>();
	settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png"));
	auto settingButtonComp = settingButton->GetComponent<UIButtonComponent>();
	settingButtonComp->GetFSM().SetOnEnter("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_on", "../Resource/UI/Title/mainmenu_settingbutton_on.png")); });
	settingButtonComp->GetFSM().SetOnExit("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png")); });

	settingButtonComp->GetFSM().SetOnEnter("Click", [weaksettingBackGround, weaksettingOkButton, weakSoundUI]() {
		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(true);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(true);
		});

	auto settingButtonRect = settingButton->GetComponent<RectTransformComponent>();
	settingButtonRect->SetPosition({ 80.0f, -150.0f });
	settingButtonRect->SetSize({ 650.0f, 161.0f });
	settingButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto creditButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	creditButton->m_Name = "creditButton";
	creditButton->SetZOrder(3);
	auto creditButtonImg = creditButton->AddComponent<UIImageComponent>();
	creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_off", "../Resource/UI/Title/mainmenu_CREDITSbutton_off.png"));
	auto creditButtonComp = creditButton->GetComponent<UIButtonComponent>();
	creditButtonComp->GetFSM().SetOnEnter("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_on", "../Resource/UI/Title/mainmenu_CREDITSbutton_on.png")); });
	creditButtonComp->GetFSM().SetOnExit("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_off", "../Resource/UI/Title/mainmenu_CREDITSbutton_off.png")); });



	creditButtonComp->GetFSM().SetOnEnter("Click", [weakcreditBackGround, weakcreditMainButton]() {
		if (auto bg = weakcreditBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakcreditMainButton.lock()) btn->SetIsVisible(false);
		});

	auto creditButtonRect = creditButton->GetComponent<RectTransformComponent>();
	creditButtonRect->SetPosition({ 80.0f, 130.0f });
	creditButtonRect->SetSize({ 650.0f, 161.0f });
	creditButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	creditButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

// 	startButtonRect->SetParent(menuBoxRect);
// 	settingButtonRect->SetParent(menuBoxRect);
// 	creditButtonRect->SetParent(menuBoxRect);

	menuBox->SetIsVisible(false);
	startButton->SetIsVisible(false);
	settingButton->SetIsVisible(false);
	creditButton->SetIsVisible(false);

#pragma endregion

	m_UIManager.AddUI("TitleScene", pressAnyKey);
	m_UIManager.AddUI("TitleScene", backGround);
	m_UIManager.AddUI("TitleScene", menuBox);
	m_UIManager.AddUI("TitleScene", startButton);
	m_UIManager.AddUI("TitleScene", settingButton);
	m_UIManager.AddUI("TitleScene", creditButton);

#pragma endregion

	auto controlObject = std::make_shared<GameObject>(m_EventDispatcher);
	auto controlComp = controlObject->AddComponent<ControlComponent>();
	controlComp->Start();

	controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakexitBackGround, weakexitOkButton, weakexitNoButton]() {
		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);
		});

	std::weak_ptr<UIObject> weakmenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakstartButton = startButton;
	std::weak_ptr<ButtonUI> weaksettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakcreditButton = creditButton;

	controlComp->RegisterAnyKeyCallback([weakmenuBox, weakstartButton, weaksettingButton, weakcreditButton]() {
		if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakstartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakcreditButton.lock()) btn->SetIsVisible(true);
		});
	AddGameObject(controlObject);
	
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
	m_UIManager.GetUIObjects().erase("TitleScene");
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
