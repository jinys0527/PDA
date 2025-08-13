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
	soundUIRect->SetPosition({ -321.0f, -50.0f });
	soundUIRect->SetSize({ 642.0f, 308.0f });
	soundUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundUIRect->SetPivotPreset(RectTransformPivotPreset::Center);

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
	soundBGMFill->SetZOrder(6);
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
	soundSFXFill->SetZOrder(6);
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

	soundUI->UpdateInteractableFlags();

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
	settingOkButton->UpdateInteractableFlags();
	auto settingOkButtonImg = settingOkButton->AddComponent<UIImageComponent>();
	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png"));
	auto settingOkButtoComp = settingOkButton->GetComponent<UIButtonComponent>();

	settingOkButtoComp->GetFSM().SetOnEnter("Hover", [settingOkButtonImg, this]() { settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_on", "../Resource/UI/Setting/setting_ok_button_on.png")); });
	settingOkButtoComp->GetFSM().SetOnExit("Hover", [settingOkButtonImg, this]() {	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png")); });

	std::weak_ptr<UIObject> weaksettingBackGround = settingBackGround;
	std::weak_ptr<ButtonUI> weaksettingOkButton = settingOkButton;
	std::weak_ptr<SoundUI> weakSoundUI = soundUI;

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
	m_UIManager.AddUI("TitleScene", soundBGMFrame);
	m_UIManager.AddUI("TitleScene", soundBGMFill);
	m_UIManager.AddUI("TitleScene", soundSFXFrame);
	m_UIManager.AddUI("TitleScene", soundSFXFill);

#pragma endregion


#pragma region Credit
	auto creditBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	creditBackGround->m_Name = "creditBackGround";
	creditBackGround->SetIsFullScreen(true);
	creditBackGround->SetZOrder(4);
	auto creditBackGroundImg = creditBackGround->AddComponent<UIImageComponent>();
	creditBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_popup", "../Resource/UI/Credit/credits_popup.png"));
	creditBackGroundImg->SetUV({ 1920.0f, 1080.0f });
	auto creditBackGroundRect = creditBackGround->GetComponent<RectTransformComponent>();
	creditBackGroundRect->SetPosition({ -960.0f, -540.0f });
	creditBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	creditBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	creditBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);


	auto creditMainButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	creditMainButton->SetZOrder(5);
	creditMainButton->m_Name = "creditMainButton";
	creditMainButton->UpdateInteractableFlags();
	auto creditMainButtonImg = creditMainButton->AddComponent<UIImageComponent>();
	creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_off", "../Resource/UI/Credit/credits_button_off.png"));
	creditMainButtonImg->SetUV({ 460.0f, 116.0f });
	auto creditMainButtonComp = creditMainButton->GetComponent<UIButtonComponent>();
	creditMainButtonComp->GetFSM().SetOnEnter("Hover", [creditMainButtonImg, this]() { creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_on", "../Resource/UI/Credit/credits_button_on.png")); });
	creditMainButtonComp->GetFSM().SetOnExit("Hover", [creditMainButtonImg, this]() { creditMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"credits_button_off", "../Resource/UI/Credit/credits_button_off.png")); });

	std::weak_ptr<UIObject> weakcreditBackGround = creditBackGround;
	std::weak_ptr<ButtonUI> weakcreditMainButton = creditMainButton;

	auto creditMainButtonRect = creditMainButton->GetComponent<RectTransformComponent>();
	creditMainButtonRect->SetPosition({ 380.0f, 240.0f }); // 후보 1
	creditMainButtonRect->SetSize({ 460.0f, 116.0f });
	creditMainButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	creditMainButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

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
	exitBackGround->SetZOrder(4);
	auto exitBackGroundImg = exitBackGround->AddComponent<UIImageComponent>();
	exitBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_popup", "../Resource/UI/Exit/exitconfirm_popup.png"));
	exitBackGroundImg->SetUV({ 1920.0f, 1080.0f });
	auto exitBackGroundRect = exitBackGround->GetComponent<RectTransformComponent>();
	exitBackGroundRect->SetPosition({ -960.0f, -540.0f });
	exitBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	exitBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitOkButton->m_Name = "exitOkButton";
	exitOkButton->SetZOrder(5);
	exitOkButton->UpdateInteractableFlags();
	auto exitOkButtonImg = exitOkButton->AddComponent<UIImageComponent>();
	exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_off", "../Resource/UI/Exit/exitconfirm_ok_button_off.png"));
	exitOkButtonImg->SetUV({ 405.0f, 102.0f });
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
	exitOkButtonRect->SetPosition({ -430.0f, 210.0f });
	exitOkButtonRect->SetSize({ 405.0f, 102.0f });
	exitOkButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitOkButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitNoButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitNoButton->m_Name = "exitNoButton";
	exitNoButton->SetZOrder(5);
	exitNoButton->UpdateInteractableFlags();
	auto exitNoButtonImg = exitNoButton->AddComponent<UIImageComponent>();
	exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png"));
	exitNoButtonImg->SetUV({ 405.0f, 102.0f });
	auto exitNoButtonComp = exitNoButton->GetComponent<UIButtonComponent>();
	exitNoButtonComp->GetFSM().SetOnEnter("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_on", "../Resource/UI/Exit/exitconfirm_no_button_on.png")); });
	exitNoButtonComp->GetFSM().SetOnExit("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png")); });

	std::weak_ptr<UIObject> weakexitBackGround = exitBackGround;
	std::weak_ptr<ButtonUI> weakexitOkButton = exitOkButton;
	std::weak_ptr<ButtonUI> weakexitNoButton = exitNoButton;


	auto exitNoButtonRect = exitNoButton->GetComponent<RectTransformComponent>();
	exitNoButtonRect->SetPosition({ 0.0f, 210.0f });
	exitNoButtonRect->SetSize({ 405.0f, 102.0f });
	exitNoButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitNoButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

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
	pressAnyKeyImg->SetUV({ 419.0f, 42.0f });
	auto pressAnyKeyRect = pressAnyKey->GetComponent<RectTransformComponent>();
	pressAnyKeyRect->SetPosition({ -209.5f, 400.0f });
	pressAnyKeyRect->SetSize({ 419.0f, 42.0f });
	pressAnyKeyRect->SetAnchorPreset(AnchorPrset::FullStretch);
	pressAnyKeyRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto backGround = std::make_shared<UIObject>(m_EventDispatcher);
	backGround->m_Name = "backGround";
	backGround->SetIsFullScreen(true);
	backGround->SetZOrder(0);
	backGround->SetIsVisible(true);
	auto backGroundImg = backGround->AddComponent<UIImageComponent>();
	backGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"title_illustration", "../Resource/UI/Title/title_illustration.png"));
	backGroundImg->SetUV({ 1920.0f, 1080.0f });


	auto backGroundRect = backGround->GetComponent<RectTransformComponent>();
	backGroundRect->SetPosition({ -960.0f, -540.0f });
	backGroundRect->SetSize({ 1920.0f, 1080.0f });
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
	startButton->UpdateInteractableFlags();
	auto startButtonImg = startButton->AddComponent<UIImageComponent>();
	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png"));
	startButtonImg->SetUV({ 650.0f, 161.0f });
	auto startButtonComp = startButton->GetComponent<UIButtonComponent>();
	startButtonComp->GetFSM().SetOnEnter("Hover", [startButtonImg, this]() { startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_on", "../Resource/UI/Title/mainmenu_startbutton_on.png")); });
	startButtonComp->GetFSM().SetOnExit("Hover", [startButtonImg, this]() {	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_startbutton_off", "../Resource/UI/Title/mainmenu_startbutton_off.png")); });

	auto startButtonRect = startButton->GetComponent<RectTransformComponent>();
	startButtonRect->SetPosition({ -10.0f, -430.0f });
	startButtonRect->SetSize({ 650.0f, 161.0f });
	startButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	startButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);


	auto settingButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingButton->m_Name = "settingButton";
	settingButton->SetZOrder(3);
	settingButton->UpdateInteractableFlags();
	auto settingButtonImg = settingButton->AddComponent<UIImageComponent>();
	settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png"));
	auto settingButtonComp = settingButton->GetComponent<UIButtonComponent>();
	settingButtonComp->GetFSM().SetOnEnter("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_on", "../Resource/UI/Title/mainmenu_settingbutton_on.png")); });
	settingButtonComp->GetFSM().SetOnExit("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_settingbutton_off", "../Resource/UI/Title/mainmenu_settingbutton_off.png")); });

	auto settingButtonRect = settingButton->GetComponent<RectTransformComponent>();
	settingButtonRect->SetPosition({ -10.0f, -150.0f });
	settingButtonRect->SetSize({ 650.0f, 161.0f });
	settingButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto creditButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	creditButton->m_Name = "creditButton";
	creditButton->SetZOrder(3);
	creditButton->UpdateInteractableFlags();
	auto creditButtonImg = creditButton->AddComponent<UIImageComponent>();
	creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_off", "../Resource/UI/Title/mainmenu_CREDITSbutton_off.png"));
	auto creditButtonComp = creditButton->GetComponent<UIButtonComponent>();
	creditButtonComp->GetFSM().SetOnEnter("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_on", "../Resource/UI/Title/mainmenu_CREDITSbutton_on.png")); });
	creditButtonComp->GetFSM().SetOnExit("Hover", [creditButtonImg, this]() {creditButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"mainmenu_CREDITSbutton_off", "../Resource/UI/Title/mainmenu_CREDITSbutton_off.png")); });


	// 약한 참조 만들기
	std::weak_ptr<UIObject> weakbackGround = backGround;
	std::weak_ptr<UIObject> weakMenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakStartButton = startButton;
	std::weak_ptr<ButtonUI> weakSettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakCreditButton = creditButton;

	// SettingButton 클릭 시
	settingButtonComp->GetFSM().SetOnEnter("Click", [weakbackGround, weakMenuBox, weakStartButton, weakSettingButton, weakCreditButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(false);
		if (auto box = weakMenuBox.lock()) box->SetIsVisible(false);
		if (auto startBtn = weakStartButton.lock()) startBtn->SetIsVisible(false);
		if (auto settingBtn = weakSettingButton.lock()) settingBtn->SetIsVisible(false);
		if (auto creditBtn = weakCreditButton.lock()) creditBtn->SetIsVisible(false);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(true);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	// CreditButton 클릭 시
	creditButtonComp->GetFSM().SetOnEnter("Click", [weakbackGround, weakMenuBox, weakStartButton, weakSettingButton, weakCreditButton, weakcreditBackGround, weakcreditMainButton, this]() {
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(false);
		if (auto box = weakMenuBox.lock()) box->SetIsVisible(false);
		if (auto startBtn = weakStartButton.lock()) startBtn->SetIsVisible(false);
		if (auto settingBtn = weakSettingButton.lock()) settingBtn->SetIsVisible(false);
		if (auto creditBtn = weakCreditButton.lock()) creditBtn->SetIsVisible(false);

		if (auto bg = weakcreditBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weakcreditMainButton.lock()) btn->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//Setting창 Ok
	settingOkButtoComp->GetFSM().SetOnEnter("Click", [weakbackGround, weakMenuBox, weakStartButton, weakSettingButton, weakCreditButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto box = weakMenuBox.lock()) box->SetIsVisible(true);
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(true);
		if (auto startBtn = weakStartButton.lock()) startBtn->SetIsVisible(true);
		if (auto settingBtn = weakSettingButton.lock()) settingBtn->SetIsVisible(true);
		if (auto creditBtn = weakCreditButton.lock()) creditBtn->SetIsVisible(true);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//CreditMain
	creditMainButtonComp->GetFSM().SetOnEnter("Click", [weakbackGround, weakMenuBox, weakStartButton, weakSettingButton, weakCreditButton, weakcreditBackGround, weakcreditMainButton, this]() {
		if (auto box = weakMenuBox.lock()) box->SetIsVisible(true);
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(true);
		if (auto startBtn = weakStartButton.lock()) startBtn->SetIsVisible(true);
		if (auto settingBtn = weakSettingButton.lock()) settingBtn->SetIsVisible(true);
		if (auto creditBtn = weakCreditButton.lock()) creditBtn->SetIsVisible(true);

		if (auto bg = weakcreditBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakcreditMainButton.lock()) btn->SetIsVisible(false);
		m_UIManager.RefreshUIListForCurrentScene();
		});

	//ExitNo
	exitNoButtonComp->GetFSM().SetOnEnter("Click", [weakbackGround, weakMenuBox, weakStartButton, weakSettingButton, weakCreditButton, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		if (auto box = weakMenuBox.lock()) box->SetIsVisible(true);
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(true);
		if (auto startBtn = weakStartButton.lock()) startBtn->SetIsVisible(true);
		if (auto settingBtn = weakSettingButton.lock()) settingBtn->SetIsVisible(true);
		if (auto creditBtn = weakCreditButton.lock()) creditBtn->SetIsVisible(true);

		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);
		m_UIManager.RefreshUIListForCurrentScene();
		});

	auto creditButtonRect = creditButton->GetComponent<RectTransformComponent>();
	creditButtonRect->SetPosition({ -10.0f, 130.0f });
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

	auto characterSelectBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	characterSelectBackGround->m_Name = "characterSelectBackGround";
	characterSelectBackGround->SetIsFullScreen(true);
	characterSelectBackGround->SetZOrder(4);
	characterSelectBackGround->SetIsVisible(false);
	auto characterSelectBackGroundImg = characterSelectBackGround->AddComponent<UIImageComponent>();
	characterSelectBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"Character_PickUp_BackGorund", "../Resource/UI/CharacterSelect/Character_PickUp_BackGorund.png"));
	characterSelectBackGroundImg->SetUV({ 1920.0f, 1080.0f });


	auto characterSelectBackGroundRect = characterSelectBackGround->GetComponent<RectTransformComponent>();
	characterSelectBackGroundRect->SetPosition({ -960.0f, -540.0f });
	characterSelectBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	characterSelectBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	characterSelectBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);

#pragma region sourBackGround
	auto sourBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	sourBackGround->m_Name = "sourBackGround";
	sourBackGround->SetIsFullScreen(true);
	sourBackGround->SetZOrder(5);
	sourBackGround->SetIsVisible(false);
	auto sourBackGroundImg = sourBackGround->AddComponent<UIImageComponent>();
	sourBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_ILLUST", "../Resource/UI/CharacterSelect/SOUR_ILLUST.png"));
	sourBackGroundImg->SetUV({ 829.0f, 1002.0f });


	auto sourBackGroundRect = sourBackGround->GetComponent<RectTransformComponent>();
	sourBackGroundRect->SetPosition({ -960.0f, -505.0f });
	sourBackGroundRect->SetSize({ 829.0f, 1002.0f });
	sourBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	sourBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion

#pragma region acidBackGround
	auto acidBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	acidBackGround->m_Name = "acidBackGround";
	acidBackGround->SetIsFullScreen(true);
	acidBackGround->SetZOrder(5);
	acidBackGround->SetIsVisible(false);
	auto acidBackGroundImg = acidBackGround->AddComponent<UIImageComponent>();
	acidBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_ILLUST", "../Resource/UI/CharacterSelect/ACID_ILLUST.png"));
	acidBackGroundImg->SetUV({ 863.0f, 1001.0f });


	auto acidBackGroundRect = acidBackGround->GetComponent<RectTransformComponent>();
	acidBackGroundRect->SetPosition({ 200.0f, -505.0f });
	acidBackGroundRect->SetSize({ 863.0f, 1001.0f });
	acidBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	acidBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion

	std::weak_ptr<UIObject> weaksourBackGround = sourBackGround;
	std::weak_ptr<UIObject> weakacidBackGround = acidBackGround;

#pragma region sour
	auto sourName = std::make_shared<UIObject>(m_EventDispatcher);
	sourName->m_Name = "sourName";
	sourName->SetZOrder(7);
	sourName->UpdateInteractableFlags();
	sourName->SetIsVisible(false);
	auto sourNameImg = sourName->AddComponent<UIImageComponent>();
	sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Down", "../Resource/UI/CharacterSelect/SOUR_Name_Down.png"));
	sourNameImg->SetUV({ 392.0f, 229.0f });

	auto sourNameRect = sourName->GetComponent<RectTransformComponent>();
	sourNameRect->SetPosition({ -500.0f, -420.0f });
	sourNameRect->SetSize({ 392.0f, 229.0f });
	sourNameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	sourNameRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto sourSelectButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	sourSelectButton->m_Name = "sourSelectButton";
	sourSelectButton->SetZOrder(6);
	sourSelectButton->UpdateInteractableFlags();
	sourSelectButton->SetIsVisible(false);
	auto sourSelectButtonImg = sourSelectButton->AddComponent<UIImageComponent>();
	sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Back", "../Resource/UI/CharacterSelect/SOUR_Back.png"));
	sourSelectButtonImg->SetUV({ 515.0f, 720.0f });
	auto sourSelectButtonComp = sourSelectButton->GetComponent<UIButtonComponent>();
	sourSelectButtonComp->GetFSM().SetOnEnter("Hover", [sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
		sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Up", "../Resource/UI/CharacterSelect/SOUR_Name_Up.png"));
		sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Up", "../Resource/UI/CharacterSelect/SOUR_Up.png")); 
		if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(true);
		});
	sourSelectButtonComp->GetFSM().SetOnExit("Hover", [sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
		sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Down", "../Resource/UI/CharacterSelect/SOUR_Name_Down.png"));
		sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Back", "../Resource/UI/CharacterSelect/SOUR_Back.png")); 
		if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(false);
		});
	

	auto sourSelectButtonRect = sourSelectButton->GetComponent<RectTransformComponent>();
	sourSelectButtonRect->SetPosition({ -525.0f, -370.0f });
	sourSelectButtonRect->SetSize({ 515.0f, 720.0f });
	sourSelectButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	sourSelectButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion



#pragma region acid
	auto acidName = std::make_shared<UIObject>(m_EventDispatcher);
	acidName->m_Name = "acidName";
	acidName->SetZOrder(7);
	acidName->UpdateInteractableFlags();
	acidName->SetIsVisible(false);
	auto acidNameImg = acidName->AddComponent<UIImageComponent>();
	acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Down", "../Resource/UI/CharacterSelect/ACID_Name_Down.png"));
	acidNameImg->SetUV({ 392.0f, 229.0f });

	auto acidNameRect = acidName->GetComponent<RectTransformComponent>();
	acidNameRect->SetPosition({ 120.0f, 190.0f });
	acidNameRect->SetSize({ 392.0f, 229.0f });
	acidNameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	acidNameRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto acidSelectButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	acidSelectButton->m_Name = "acidSelectButton";
	acidSelectButton->SetZOrder(6);
	acidSelectButton->UpdateInteractableFlags();
	acidSelectButton->SetIsVisible(false);
	auto acidSelectButtonImg = acidSelectButton->AddComponent<UIImageComponent>();
	acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Back", "../Resource/UI/CharacterSelect/ACID_Back.png"));
	acidSelectButtonImg->SetUV({ 518.0f, 723.0f });
	auto acidSelectButtonComp = acidSelectButton->GetComponent<UIButtonComponent>();
	acidSelectButtonComp->GetFSM().SetOnEnter("Hover", [acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
		acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Up", "../Resource/UI/CharacterSelect/ACID_Name_Up.png"));
		acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Up", "../Resource/UI/CharacterSelect/ACID_Up.png"));
		if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(true);
		});
	acidSelectButtonComp->GetFSM().SetOnExit("Hover", [acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
		acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Down", "../Resource/UI/CharacterSelect/ACID_Name_Down.png"));
		acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Back", "../Resource/UI/CharacterSelect/ACID_Back.png")); 
		if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(false);
		});
	

	auto acidSelectButtonRect = acidSelectButton->GetComponent<RectTransformComponent>();
	acidSelectButtonRect->SetPosition({ 0.0f, -330.0f });
	acidSelectButtonRect->SetSize({ 518.0f, 723.0f });
	acidSelectButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	acidSelectButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion

	sourSelectButtonComp->GetFSM().SetOnEnter("Click", [sourSelectButtonComp, acidSelectButtonComp, acidNameImg, weakacidBackGround, acidSelectButtonImg, sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
		m_isAcid = false;
		sourSelectButtonComp->GetFSM().SetOnExit("Hover", []() {
			});
		sourSelectButtonComp->GetFSM().SetOnEnter("Hover", [sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
			sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Up", "../Resource/UI/CharacterSelect/SOUR_Name_Up.png"));
			sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Up", "../Resource/UI/CharacterSelect/SOUR_Up.png"));
			if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(true);
			});
		acidSelectButtonComp->GetFSM().SetOnEnter("Hover", [acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
			acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Up", "../Resource/UI/CharacterSelect/ACID_Name_Up.png"));
			acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Up", "../Resource/UI/CharacterSelect/ACID_Up.png"));
			});
		acidSelectButtonComp->GetFSM().SetOnExit("Hover", [acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
			acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Down", "../Resource/UI/CharacterSelect/ACID_Name_Down.png"));
			acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Back", "../Resource/UI/CharacterSelect/ACID_Back.png"));
			if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(false);
			});
		acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Down", "../Resource/UI/CharacterSelect/ACID_Name_Down.png"));
		acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Back", "../Resource/UI/CharacterSelect/ACID_Back.png"));
		if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(false);
		});
	acidSelectButtonComp->GetFSM().SetOnEnter("Click", [acidSelectButtonComp, sourSelectButtonComp, sourNameImg, weaksourBackGround, sourSelectButtonImg, acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
		m_isAcid = true;
		acidSelectButtonComp->GetFSM().SetOnExit("Hover", []() {
			});
		acidSelectButtonComp->GetFSM().SetOnEnter("Hover", [acidNameImg, weakacidBackGround, acidSelectButtonImg, this]() {
			acidNameImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Name_Up", "../Resource/UI/CharacterSelect/ACID_Name_Up.png"));
			acidSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ACID_Up", "../Resource/UI/CharacterSelect/ACID_Up.png"));
			if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(true);
			});
		sourSelectButtonComp->GetFSM().SetOnEnter("Hover", [sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
			sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Up", "../Resource/UI/CharacterSelect/SOUR_Name_Up.png"));
			sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Up", "../Resource/UI/CharacterSelect/SOUR_Up.png"));
			});
		sourSelectButtonComp->GetFSM().SetOnExit("Hover", [sourNameImg, weaksourBackGround, sourSelectButtonImg, this]() {
			sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Down", "../Resource/UI/CharacterSelect/SOUR_Name_Down.png"));
			sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Back", "../Resource/UI/CharacterSelect/SOUR_Back.png"));
			if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(false);
			});
		sourNameImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Name_Down", "../Resource/UI/CharacterSelect/SOUR_Name_Down.png"));
		sourSelectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"SOUR_Back", "../Resource/UI/CharacterSelect/SOUR_Back.png"));
		if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(false);
		});

#pragma region backButton
	auto backButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	backButton->m_Name = "backButton";
	backButton->SetZOrder(6);
	backButton->UpdateInteractableFlags();
	backButton->SetIsVisible(false);
	auto backButtonImg = backButton->AddComponent<UIImageComponent>();
	backButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_backbutton_off", "../Resource/UI/CharacterSelect/charselect_backbutton_off.png"));
	backButtonImg->SetUV({ 334.0f, 241.0f });
	auto backButtonComp = backButton->GetComponent<UIButtonComponent>();
	backButtonComp->GetFSM().SetOnEnter("Hover", [backButtonImg, this]() { backButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_backbutton_on", "../Resource/UI/CharacterSelect/charselect_backbutton_on.png")); });
	backButtonComp->GetFSM().SetOnExit("Hover", [backButtonImg, this]() { backButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_backbutton_off", "../Resource/UI/CharacterSelect/charselect_backbutton_off.png")); });

	auto backButtonRect = backButton->GetComponent<RectTransformComponent>();
	backButtonRect->SetPosition({ -960.0f, -450.0f });
	backButtonRect->SetSize({ 334.0f, 241.0f });
	backButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	backButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion

#pragma region select
	auto selectButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	selectButton->m_Name = "selectButton";
	selectButton->SetZOrder(6);
	selectButton->UpdateInteractableFlags();
	selectButton->SetIsVisible(false);
	auto selectButtonImg = selectButton->AddComponent<UIImageComponent>();
	selectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_selectbutton_off", "../Resource/UI/CharacterSelect/charselect_selectbutton_off.png"));
	selectButtonImg->SetUV({ 334.0f, 241.0f });
	auto selectButtonComp = selectButton->GetComponent<UIButtonComponent>();
	selectButtonComp->GetFSM().SetOnEnter("Hover", [selectButtonImg, this]() { selectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_selectbutton_on", "../Resource/UI/CharacterSelect/charselect_selectbutton_on.png")); });
	selectButtonComp->GetFSM().SetOnExit("Hover", [selectButtonImg, this]() { selectButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"charselect_selectbutton_off", "../Resource/UI/CharacterSelect/charselect_selectbutton_off.png")); });
	selectButtonComp->GetFSM().SetOnEnter("Click", [this]() {
		if(!m_isAcid)
		{
			m_SceneManager->ChangeScene("GameScene");
			m_UIManager.SetCurrentScene("GameScene");
		}
		});

	auto selectButtonRect = selectButton->GetComponent<RectTransformComponent>();
	selectButtonRect->SetPosition({ 650.0f, 220.0f });
	selectButtonRect->SetSize({ 334.0f, 241.0f });
	selectButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	selectButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
#pragma endregion

	m_UIManager.AddUI("TitleScene", characterSelectBackGround);
	m_UIManager.AddUI("TitleScene", sourBackGround);
	m_UIManager.AddUI("TitleScene", acidBackGround);
	m_UIManager.AddUI("TitleScene", sourName);
	m_UIManager.AddUI("TitleScene", acidName);
	m_UIManager.AddUI("TitleScene", sourSelectButton);
	m_UIManager.AddUI("TitleScene", acidSelectButton);
	m_UIManager.AddUI("TitleScene", backButton);
	m_UIManager.AddUI("TitleScene", selectButton);

	// 약한 참조 만들기
	std::weak_ptr<UIObject> weakcharacterSelectBackGround = characterSelectBackGround;
	std::weak_ptr<UIObject> weaksourName = sourName;
	std::weak_ptr<UIObject> weakacidName = acidName;
	std::weak_ptr<ButtonUI> weaksourSelectButton = sourSelectButton;
	std::weak_ptr<ButtonUI> weakacidSelectButton = acidSelectButton;
	std::weak_ptr<ButtonUI> weakbackButton = backButton;
	std::weak_ptr<ButtonUI> weakselectButton = selectButton;
	std::weak_ptr<UIObject> weakmenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakstartButton = startButton;
	std::weak_ptr<ButtonUI> weaksettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakcreditButton = creditButton;
	std::weak_ptr<UIObject> weakpressAnyKey = pressAnyKey;
	
	backButtonComp->GetFSM().SetOnEnter("Click", [weakcharacterSelectBackGround, weaksourBackGround, weakacidBackGround, weaksourName, weakacidName, weaksourSelectButton, weakacidSelectButton, weakbackButton, weakselectButton, weakmenuBox, weakstartButton, weaksettingButton, weakcreditButton]() {
		if (auto bg = weakcharacterSelectBackGround.lock()) bg->SetIsVisible(false);
		if (auto bg = weaksourName.lock()) bg->SetIsVisible(false);
		if (auto bg = weakacidName.lock()) bg->SetIsVisible(false);
		if (auto btn = weaksourSelectButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakacidSelectButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakbackButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakselectButton.lock()) btn->SetIsVisible(false);
		if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakstartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakcreditButton.lock()) btn->SetIsVisible(true);
		if (auto bg = weaksourBackGround.lock()) bg->SetIsVisible(false);
		if (auto bg = weakacidBackGround.lock()) bg->SetIsVisible(false);
		});


	startButtonComp->GetFSM().SetOnEnter("Click", [weakcharacterSelectBackGround, weaksourName, weakacidName, weaksourSelectButton, weakacidSelectButton, weakbackButton, weakselectButton, weakmenuBox, weakstartButton, weaksettingButton, weakcreditButton]() {
		if (auto bg = weakcharacterSelectBackGround.lock()) bg->SetIsVisible(true);
		if (auto bg = weaksourName.lock()) bg->SetIsVisible(true);
		if (auto bg = weakacidName.lock()) bg->SetIsVisible(true);
		if (auto btn = weaksourSelectButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakacidSelectButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakbackButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakselectButton.lock()) btn->SetIsVisible(true);
		if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakstartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakcreditButton.lock()) btn->SetIsVisible(false);
		});
#pragma region controlObject
	auto controlObject = std::make_shared<GameObject>(m_EventDispatcher);
	auto controlComp = controlObject->AddComponent<ControlComponent>();
	controlComp->Start();

	controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakbackGround, weakexitBackGround, weakexitOkButton, weakexitNoButton, weakmenuBox, weakstartButton, weaksettingButton, weakcreditButton, this]() {
		if (auto bg = weakbackGround.lock()) bg->SetIsVisible(false);
		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);
		if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakstartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakcreditButton.lock()) btn->SetIsVisible(false);
		m_UIManager.RefreshUIListForCurrentScene();
		});

	controlComp->RegisterAnyKeyCallback([weakpressAnyKey, weakmenuBox, weakstartButton, weaksettingButton, weakcreditButton, this]() {
		if (auto bg = weakpressAnyKey.lock()) bg->SetIsVisible(false);
		if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakstartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakcreditButton.lock()) btn->SetIsVisible(true);
		m_UIManager.RefreshUIListForCurrentScene();
		});
	AddGameObject(controlObject);
#pragma endregion



	m_UIManager.RefreshUIListForCurrentScene();
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
