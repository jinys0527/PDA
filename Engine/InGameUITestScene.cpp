#include "pch.h"
#include "InGameUITestScene.h"
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
#include "UIGridComponent.h"
#include "UITextComponent.h"

#include "Telegraph.h"
#include "Background.h"
#include "InputManager.h"
#include "TestListener.h"
#include "PlayerObject.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "FSM.h"
#include "FlyingObstacleComponent.h"
#include "PlayerEffectComponent.h"
#include "DroneComponent.h"
#include "HeartUIComponent.h"
#include "BulletUIComponent.h"
#include "BlackBoard.h"
#include "TestNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Repeater.h"
#include "Inverter.h"
#include "BossBehaviorTree.h"
#include "BossBlackBoard.h"

#include "GameManager.h"

#include "ControlComponent.h"
#include "SceneManager.h"
#include "RectTransformComponent.h"

void InGameUITestScene::Initialize()
{
#pragma region camera

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 60.0f, 540.f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(1.0f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });

	SetMainCamera(cameraObject);

#pragma endregion

#pragma region soundUI
	
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

	m_UIManager.AddUI("InGameUITestScene", soundUI);
	m_UIManager.AddUI("InGameUITestScene", soundBGMFrame);
	m_UIManager.AddUI("InGameUITestScene", soundBGMFill);
	m_UIManager.AddUI("InGameUITestScene", soundSFXFrame);
	m_UIManager.AddUI("InGameUITestScene", soundSFXFill);
	

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

#pragma endregion







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


#pragma region Grid

	{
		auto uiObject = std::make_shared<UIObject>(m_EventDispatcher);
		uiObject->m_Name = "grid";
		auto uiRect = uiObject->GetComponent<RectTransformComponent>();
		uiRect->SetPosition({ -700.0f, -510.0f });
		uiRect->SetAnchorPreset(AnchorPrset::FullStretch);
		uiRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto grid = uiObject->AddComponent<UIGridComponent>();
		grid->SetCellSize({ 53, 44 });
		grid->SetPadding({ 10, 10 });
		grid->SetSpacing({ 5, 5 });
		grid->SetRowColumn(1, 5);

		auto heartUI = std::make_shared<UIObject>(m_EventDispatcher);
		auto heart = heartUI->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart1", "../Resource/UI/InGame/ingame_hp_icon_1.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		auto rect6 = heartUI->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI);
		auto heartUIComp = heartUI->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(0);

		auto heartUI2 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI2->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart2", "../Resource/UI/InGame/ingame_hp_icon_2.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI2->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI2);
		heartUIComp = heartUI2->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(1);

		auto heartUI3 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI3->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart3", "../Resource/UI/InGame/ingame_hp_icon_3.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI3->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI3);
		heartUIComp = heartUI3->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(2);

		auto heartUI4 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI4->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart1", "../Resource/UI/InGame/ingame_hp_icon_1.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI4->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI4);
		heartUIComp = heartUI4->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(3);

		auto heartUI5 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI5->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart2", "../Resource/UI/InGame/ingame_hp_icon_2.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI5->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI5);
		heartUIComp = heartUI5->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(4);


		grid->UpdateLayout();

		m_UIManager.AddUI("InGameUITestScene", uiObject);

		auto chargeUI = std::make_shared<UIObject>(m_EventDispatcher);
		chargeUI->m_Name = "chargeUI";
		auto chargeUIRect = chargeUI->GetComponent<RectTransformComponent>();
		chargeUIRect->SetPosition({ -925.0f, -330.0f });
		chargeUIRect->SetSize({ 112.0f, 58.0f });
		chargeUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		chargeUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto chargeImage = chargeUI->AddComponent<UIImageComponent>();
		chargeImage->SetBitmap(m_AssetManager.LoadTexture(L"charge", "../Resource/UI/InGame/ingame_chargeshot_icon.png"));
		chargeImage->SetPivotPreset(ImagePivotPreset::Center, chargeImage->GetTexture()->GetSize());

		m_UIManager.AddUI("InGameUITestScene", chargeUI);

		auto chargeCountUI = std::make_shared<UIObject>(m_EventDispatcher);
		chargeCountUI->m_Name = "chargeCountUI";
		auto chargeCountUIText = chargeCountUI->AddComponent<UITextComponent>();
		chargeCountUIText->SetDWriteFactory(m_Renderer.GetDWriteFactory());
		chargeCountUIText->SetText(L"0");
		chargeCountUIText->SetPosition({ -1050.0f, -395.0f });
		chargeCountUIText->SetFontName(L"Segoe UI");
		chargeCountUIText->SetFontSize(60.0f);
		chargeCountUIText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		chargeCountUIText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		chargeCountUIText->SetLayoutSize(500.0f, 100.0f);

		chargeCountUI->AddComponent<BulletUIComponent>()->Start();


		auto chargeCountUIRect = chargeCountUI->GetComponent<RectTransformComponent>();
		chargeCountUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		chargeCountUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		chargeCountUIRect->SetPosition({ 0.0f, 0.0f });
		chargeCountUIRect->SetSize({ 600.f, 600.f });
		
		m_UIManager.AddUI("InGameUITestScene", chargeCountUI);

		auto portraitUI = std::make_shared<UIObject>(m_EventDispatcher);
		portraitUI->m_Name = "portraitUI";
		auto portraitUIRect = portraitUI->GetComponent<RectTransformComponent>();
		portraitUIRect->SetPosition({ -935.0f, -540.0f });
		portraitUIRect->SetSize({ 303.0f, 210.0f });
		portraitUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		portraitUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto portraitImage = portraitUI->AddComponent<UIImageComponent>();
		portraitImage->SetBitmap(m_AssetManager.LoadTexture(L"portrait", "../Resource/UI/InGame/ingame_portrait.png"));
		portraitImage->SetPivotPreset(ImagePivotPreset::Center, portraitImage->GetTexture()->GetSize());

		m_UIManager.AddUI("InGameUITestScene", portraitUI);
	}

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

	m_UIManager.AddUI("InGameUITestScene", exitBackGround);
	m_UIManager.AddUI("InGameUITestScene", exitOkButton);
	m_UIManager.AddUI("InGameUITestScene", exitNoButton);
#pragma endregion


#pragma region menuBox
	auto menuBox = std::make_shared<UIObject>(m_EventDispatcher);
	menuBox->m_Name = "menuBox";
	menuBox->SetIsFullScreen(true);
	menuBox->SetZOrder(2);
	auto menuBoxImg = menuBox->AddComponent<UIImageComponent>();
	menuBoxImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_popup", "../Resource/UI/Pause/pause_popup.png"));


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
	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_off", "../Resource/UI/Pause/pause_resume_button_off.png"));
	startButtonImg->SetUV({ 650.0f, 161.0f });
	auto startButtonComp = startButton->GetComponent<UIButtonComponent>();
	startButtonComp->GetFSM().SetOnEnter("Hover", [startButtonImg, this]() { startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_on", "../Resource/UI/Pause/pause_resume_button_on.png")); });
	startButtonComp->GetFSM().SetOnExit("Hover", [startButtonImg, this]() {	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_off", "../Resource/UI/Pause/pause_resume_button_off.png")); });


	auto startButtonRect = startButton->GetComponent<RectTransformComponent>();
	auto test = startButtonRect->GetOwner();
	auto ui = dynamic_cast<UIObject*>(test);
	startButtonRect->SetPosition({ -346.0f, -200.0f });
	startButtonRect->SetSize({ 692.0f, 68.0f });
	startButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	startButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);


	auto settingButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingButton->m_Name = "settingButton";
	settingButton->SetZOrder(3);
	settingButton->UpdateInteractableFlags();
	auto settingButtonImg = settingButton->AddComponent<UIImageComponent>();
	settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_off", "../Resource/UI/Pause/pause_setting_button_off.png"));
	auto settingButtonComp = settingButton->GetComponent<UIButtonComponent>();
	settingButtonComp->GetFSM().SetOnEnter("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_on", "../Resource/UI/Pause/pause_setting_button_on.png")); });
	settingButtonComp->GetFSM().SetOnExit("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_off", "../Resource/UI/Pause/pause_setting_button_off.png")); });

	auto settingButtonRect = settingButton->GetComponent<RectTransformComponent>();
	settingButtonRect->SetPosition({ -346.0f, -100.0f });
	settingButtonRect->SetSize({ 692.0f, 68.0f });
	settingButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto mainButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	mainButton->m_Name = "mainButton";
	mainButton->SetZOrder(3);
	mainButton->UpdateInteractableFlags();
	auto mainButtonImg = mainButton->AddComponent<UIImageComponent>();
	mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_off", "../Resource/UI/Pause/pause_main_button_off.png"));
	auto mainButtonComp = mainButton->GetComponent<UIButtonComponent>();
	mainButtonComp->GetFSM().SetOnEnter("Hover", [mainButtonImg, this]() {mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_on", "../Resource/UI/Pause/pause_main_button_on.png")); });
	mainButtonComp->GetFSM().SetOnExit("Hover", [mainButtonImg, this]() {mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_off", "../Resource/UI/Pause/pause_main_button_off.png")); });

	auto mainButtonRect = mainButton->GetComponent<RectTransformComponent>();
	mainButtonRect->SetPosition({ -346.0f, 0.0f });
	mainButtonRect->SetSize({ 692.0f, 68.0f });
	mainButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	mainButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto retryButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	retryButton->m_Name = "retryButton";
	retryButton->SetZOrder(3);
	retryButton->UpdateInteractableFlags();
	auto retryButtonImg = retryButton->AddComponent<UIImageComponent>();
	retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_off", "../Resource/UI/Pause/pause_retry_button_off.png"));
	auto retryButtonComp = retryButton->GetComponent<UIButtonComponent>();
	retryButtonComp->GetFSM().SetOnEnter("Hover", [retryButtonImg, this]() {retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_on", "../Resource/UI/Pause/pause_retry_button_on.png")); });
	retryButtonComp->GetFSM().SetOnExit("Hover", [retryButtonImg, this]() {retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_off", "../Resource/UI/Pause/pause_retry_button_off.png")); });

	auto retryButtonRect = retryButton->GetComponent<RectTransformComponent>();
	retryButtonRect->SetPosition({ -346.0f, 100.0f });
	retryButtonRect->SetSize({ 692.0f, 68.0f });
	retryButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	retryButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitButton->m_Name = "exitButton";
	exitButton->SetZOrder(3);
	exitButton->UpdateInteractableFlags();
	auto exitButtonImg = exitButton->AddComponent<UIImageComponent>();
	exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_off", "../Resource/UI/Pause/pause_exit_button_off.png"));
	auto exitButtonComp = exitButton->GetComponent<UIButtonComponent>();
	exitButtonComp->GetFSM().SetOnEnter("Hover", [exitButtonImg, this]() {exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_on", "../Resource/UI/Pause/pause_exit_button_on.png")); });
	exitButtonComp->GetFSM().SetOnExit("Hover", [exitButtonImg, this]() {exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_off", "../Resource/UI/Pause/pause_exit_button_off.png")); });

	auto exitButtonRect = exitButton->GetComponent<RectTransformComponent>();
	exitButtonRect->SetPosition({ -346.0f, 200.0f });
	exitButtonRect->SetSize({ 692.0f, 68.0f });
	exitButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);


	// 약한 참조 만들기
	std::weak_ptr<UIObject> weakMenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakStartButton = startButton;
	std::weak_ptr<ButtonUI> weakSettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakMainButton = mainButton;
	std::weak_ptr<ButtonUI> weakRetryButton = retryButton;
	std::weak_ptr<ButtonUI> weakExitButton = exitButton;

	startButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	// SettingButton 클릭 시
	settingButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(true);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//Setting창 Ok
	settingOkButtoComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(true);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//ExitNo
	exitNoButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(true);

		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);
		m_UIManager.RefreshUIListForCurrentScene();
		});

	mainButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	retryButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//std::weak_ptr<UIObject> weakexitBackGround = exitBackGround;
//std::weak_ptr<ButtonUI> weakexitOkButton = exitOkButton;
//std::weak_ptr<ButtonUI> weakexitNoButton = exitNoButton;

	exitButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	// 	startButtonRect->SetParent(menuBoxRect);
	// 	settingButtonRect->SetParent(menuBoxRect);
	// 	creditButtonRect->SetParent(menuBoxRect);

	menuBox->SetIsVisible(false);
	startButton->SetIsVisible(false);
	settingButton->SetIsVisible(false);
	mainButton->SetIsVisible(false);
	retryButton->SetIsVisible(false);
	exitButton->SetIsVisible(false);

#pragma endregion

	m_UIManager.AddUI("InGameUITestScene", settingBackGround);
	m_UIManager.AddUI("InGameUITestScene", settingOkButton);
	m_UIManager.AddUI("InGameUITestScene", menuBox);
	m_UIManager.AddUI("InGameUITestScene", startButton);
	m_UIManager.AddUI("InGameUITestScene", settingButton);
	m_UIManager.AddUI("InGameUITestScene", mainButton);
	m_UIManager.AddUI("InGameUITestScene", retryButton);
	m_UIManager.AddUI("InGameUITestScene", exitButton);

	auto controlObject = std::make_shared<GameObject>(m_EventDispatcher);
	auto controlComp = controlObject->AddComponent<ControlComponent>();
	controlComp->Start();

	std::weak_ptr<UIObject> weakmenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakstartButton = startButton;
	std::weak_ptr<ButtonUI> weaksettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakmainButton = mainButton;
	std::weak_ptr<ButtonUI> weakretryButton = retryButton;
	std::weak_ptr<ButtonUI> weakexitButton = exitButton;

	controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakmenuBox, weakstartButton, weaksettingButton, weakmainButton, weakretryButton, weakexitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		auto snd = weakSoundUI.lock();
		auto eb = weakexitBackGround.lock();
		if (snd && eb)
		{
			if (snd->IsVisible() || eb->IsVisible())
			{
				if (auto bg = weakmenuBox.lock())	bg->SetIsVisible(true);
				if (auto btn = weakstartButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weaksettingButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakmainButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakretryButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakexitButton.lock())	btn->SetIsVisible(true);
			}
			else
			{
				if (auto bg = weakmenuBox.lock())
				{
					bg->SetIsVisible(!bg->IsVisible());
				}
				if (auto btn = weakstartButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weaksettingButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakmainButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakretryButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakexitButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
			}
			if (snd->IsVisible())
			{
				if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
				if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
				snd->SetIsVisible(false);
			}
			if(eb->IsVisible())
			{
				eb->SetIsVisible(false);
				if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);

				if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);

			}
		}

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
	//	if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
	//	if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
	//	if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);
	//	m_UIManager.RefreshUIListForCurrentScene();
	//	});

	//controlComp->RegisterAnyKeyCallback([weakmenuBox, weakstartButton, weaksettingButton, this]() {
	//	if (auto bg = weakmenuBox.lock()) bg->SetIsVisible(true);
	//	if (auto btn = weakstartButton.lock()) btn->SetIsVisible(true);
	//	if (auto btn = weaksettingButton.lock()) btn->SetIsVisible(true);
	//	m_UIManager.RefreshUIListForCurrentScene();
	//	});

	AddGameObject(controlObject);

//#pragma region loading
//
//	auto loadingBackGround = std::make_shared<UIObject>(m_EventDispatcher);
//	loadingBackGround->m_Name = "loadingUIGround";
//	//exitBackGround->SetIsFullScreen(true);
//	loadingBackGround->SetZOrder(6);
//	auto loadingBackGroundImg = loadingBackGround->AddComponent<UIImageComponent>();
//	loadingBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"Switch_screen", "../Resource/UI/Loading/Switch_screen.png"));
//	loadingBackGroundImg->SetUV({ 1920.0f, 1080.0f });
//	auto loadingBackGroundRect = loadingBackGround->GetComponent<RectTransformComponent>();
//	loadingBackGroundRect->SetPosition({ -960.0f, -540.0f });
//	loadingBackGroundRect->SetSize({ 1920.0f, 1080.0f });
//	loadingBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
//	loadingBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);
//
//	loadingBackGround->SetIsVisible(true);
//
//	m_UIManager.AddUI("InGameUITestScene", loadingBackGround);
//
//
//#pragma endregion
	//AddGameObject(gameObject);
  /*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);


	//m_UIManager.AddUI(buttonUI);

	m_UIManager.RefreshUIListForCurrentScene();
	AddGameObject(cameraObject);

	{
		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
		auto trans = gameObject->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.0f, 540.0f });
		auto sr = gameObject->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto animComp = gameObject->AddComponent<AnimationComponent>();
		animComp->SetAssetManager(&m_AssetManager);
		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"shadow", L"../Resource/Character/Sour/Shadow.png"));

		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Attack_Ani", L"../Resource/Character/Sour/Sour_Attack_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Charge_Ani", L"../Resource/Character/Sour/Sour_Charge_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Charge_Shot_Ani", L"../Resource/Character/Sour/Sour_Charge_Shot_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Dead_Ani", L"../Resource/Character/Sour/Sour_Dead_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Heal_Ani", L"../Resource/Character/Sour/Sour_Heal_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Hitted_ani", L"../Resource/Character/Sour/Sour_Hitted_ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Ani", L"../Resource/Character/Sour/Sour_Jump_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Down_Ani", L"../Resource/Character/Sour/Sour_Jump_Down_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Top_Ani", L"../Resource/Character/Sour/Sour_Jump_Top_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Up_Ani", L"../Resource/Character/Sour/Sour_Jump_Up_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Kick_Ground_Ani", L"../Resource/Character/Sour/Sour_Kick_Ground_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Success_Ani", L"../Resource/Character/Sour/Sour_Marking_Success_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Slide_Ani", L"../Resource/Character/Sour/Sour_Slide_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		{
			auto& clips = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");
			for (const auto& [clipName, clip] : clips)
			{
				animComp->AddClip(clipName, &clip);
			}
		}
		animComp->Play("run");
		sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
		sr->SetTextureKey("boss");
		gameObject->SetCameraObject(GetMainCamera());

		AddGameObject(gameObject);

		{
			auto effect = std::make_shared<GameObject>(m_EventDispatcher);
			effect->m_Name = "PlayerEffect";
			auto effecttrans = effect->GetComponent<TransformComponent>();
			effecttrans->SetParent(trans);
			effecttrans->SetPosition({ 0, 0 });
			auto effectsr = effect->AddComponent<SpriteRenderer>();
			effectsr->SetAssetManager(&m_AssetManager);

			auto& effectclips = m_AssetManager.LoadAnimation(L"Sour_Heal_Ani", L"../Resource/Character/Sour/Sour_Heal_Ani.json");
			auto effectanim = effect->AddComponent<AnimationComponent>();
			effectanim->SetAssetManager(&m_AssetManager);
			for (const auto& [clipName, clip] : effectclips)
			{
				effectanim->AddClip(clipName, &clip);
			}

			effectanim->Play("heal");
			effectanim->SetLoop(false);
			effectanim->Finish();

			effectsr->SetPath("../Resource/Character/Sour/Sour_Heal_Ani.json");
			effectsr->SetTextureKey("Sour_Heal_Ani");


			effectsr->SetPivotPreset(SpritePivotPreset::HealPivot, { 400, 400 });

			auto effectComp = effect->AddComponent<PlayerEffectComponent>();
			effectComp->Start();

			AddGameObject(effect);
		}

		auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
		graffiti->m_Name = "graffiti";
		auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
		graffitiTrans->SetPosition({ 200,300 });
		sr = graffiti->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"Garbage_bag", L"../Resource/Obstacle/Garbage_bag.png");
		sr->SetPath("../Resource/Garbage_bag.png");
		sr->SetTextureKey("Garbage_bag");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
		graffiti->GetComponent<GraffitiComponent>()->Start();

		graffiti->SetGravitti(&m_AssetManager);


		AddGameObject(graffiti);
	}


	{
		//auto background = std::make_shared<GameObject>(m_EventDispatcher);
		//background->m_Name = "background";
		//auto obstacleTrans = background->GetComponent<TransformComponent>();
		//obstacleTrans->SetPosition({ -500.0f, 0.0f });
		//auto sr = background->AddComponent<SpriteRenderer>();
		//sr->SetAssetManager(&m_AssetManager);
		//auto bitmap = m_AssetManager.LoadTexture(L"Background", L"../Resource/Background/Background.png");
		//sr->SetPath("../Resource/Background/Background.png");
		//sr->SetTextureKey("Background");
		//sr->SetTexture(bitmap);
		//sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		//AddGameObject(background);

		auto back1 = std::make_shared<Background>(m_EventDispatcher);
 		back1->m_Name = "back1";
 		auto backtr1 = back1->GetComponent<TransformComponent>();
 		backtr1->SetPosition({ 0, 540 });
 		auto backimage1 = m_AssetManager.LoadTexture(L"Background", L"../Resource/Background/Background.png");
 		auto backsr1 = back1->AddComponent<SpriteRenderer>();
 		backsr1->SetAssetManager(&m_AssetManager);
 		backsr1->SetTexture(backimage1);
 		backsr1->SetPivotPreset(SpritePivotPreset::Center, backimage1->GetSize());
 
 		AddGameObject(back1);
	}


	//{
	//	auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
	//	obstacle->m_Name = "obstacle3";
	//	auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
	//	obstacleTrans->SetPosition({ 3000.0f, 350.0f });
	//	auto sr = obstacle->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);
	//	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//	sr->SetPath("../Resource/cat.png");
	//	sr->SetTextureKey("cat_texture");
	//	sr->SetTexture(bitmap);
	//	sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

	//	obstacle->SetZ(1);
	//	obstacle->SetSlide(false);

	//	auto lambdaObstacle = obstacle.get();
	//	auto lambdaCamera = cameraObject.get();

	//	auto rect = obstacle->GetComponent<BoxColliderComponent>();
	//	rect->SetCenter(obstacleTrans->GetPosition());
	//	m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
	//	rect->SetOnTrigger(
	//		[lambdaObstacle, lambdaCamera](const CollisionInfo& info)
	//		{
	//			if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
	//				return;
	//			lambdaObstacle->GetComponent<TransformComponent>()->SetParent(lambdaCamera->GetComponent<TransformComponent>());
	//			auto component = lambdaObstacle->AddComponent<FlyingObstacleComponent>();
	//			component->Start();
	//			lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
	//		}
	//	);



	//	AddGameObject(obstacle);
	//}
	//{
	//	auto obstacle = std::make_shared<GameObject>(m_EventDispatcher);
	//	obstacle->m_Name = "drone3";
	//	auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
	//	obstacleTrans->SetPosition({ 3000.0f, 350.0f });
	//	auto sr = obstacle->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);
	//	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//	sr->SetPath("../Resource/cat.png");
	//	sr->SetTextureKey("cat_texture");
	//	sr->SetTexture(bitmap);
	//	sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

	//	auto lambdaObstacle = obstacle.get();
	//	auto lambdaCamera = cameraObject.get();

	//	auto rect = obstacle->AddComponent<BoxColliderComponent>();
	//	//m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
	//	rect->SetSize({ 100, 100 });
	//	rect->Start();
	//	rect->SetOnTrigger(
	//		[lambdaObstacle, lambdaCamera](const CollisionInfo& info)
	//		{
	//			if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
	//				return;
	//			lambdaObstacle->GetComponent<TransformComponent>()->SetParent(lambdaCamera->GetComponent<TransformComponent>());
	//			auto component = lambdaObstacle->AddComponent<DroneComponent>();
	//			component->Start();
	//			lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
	//		}
	//	);


	//	AddGameObject(obstacle);
	//}
	//{
	//	auto obstacle = std::make_shared<GameObject>(m_EventDispatcher);
	//	obstacle->m_Name = "savepoint";
	//	auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
	//	obstacleTrans->SetPosition({ 3000.0f, 350.0f });
	//	auto sr = obstacle->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);
	//	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//	sr->SetPath("../Resource/cat.png");
	//	sr->SetTextureKey("cat_texture");
	//	sr->SetTexture(bitmap);
	//	sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

	//	auto lambdaObstacle = obstacle.get();
	//	auto lambdaCamera = cameraObject.get();

	//	auto rect = obstacle->AddComponent<BoxColliderComponent>();
	//	//m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
	//	rect->SetSize({ 100, 10000 });
	//	rect->Start();
	//	rect->SetOnTrigger(
	//		[lambdaObstacle, this](const CollisionInfo& info)
	//		{
	//			if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
	//				return;
	//			this->SavePlayerInfo();
	//		}
	//	);


	//	AddGameObject(obstacle);
	//}
}

void InGameUITestScene::Finalize()
{
}

void InGameUITestScene::Enter()
{
	//LoadPlayerInfo();
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	player->SetScene(true);
}

void InGameUITestScene::Leave()
{
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	player->SetScene(false);
}

void InGameUITestScene::FixedUpdate()
{
}

void InGameUITestScene::Update(float deltaTime)
{

//#pragma region BT
//	m_BTElapsedTime += deltaTime;
//	m_OneSecondTimer += deltaTime;
//
//	if (m_BTElapsedTime >= 0.016f)
//	{
//		if (m_BehaviorTree)
//		{
//			m_BehaviorTree->Tick(m_BTElapsedTime);
//		}
//
//
//		m_GameManager->m_scrollSpeed += deltaTime*500;
//		if (m_GameManager->m_scrollSpeed >= 2000)
//		m_GameManager->m_scrollSpeed = 2000;
//
//		Vec2F move = { 0, 0 };
//		move.x += m_GameManager->m_scrollSpeed * deltaTime;
//		//m_GameObjects.find("Camera")->second->GetComponent<TransformComponent>()->Translate(move);
//		//m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->Translate(move);
//
//
//		//	m_BTElapsedTime = 0.0f;
//
//		//}
//
//		//if (m_OneSecondTimer >= 1.0f)
//		//{
//		//	m_OneSecondTimer = 0.0f;
//		float curHP = m_BlackBoard->GetValue<float>("BossCurrHP").value();
//		m_BlackBoard->SetValue("BossCurrHP", curHP - 1);
//
//	}
//
//#pragma endregion



	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	m_UIManager.Update(deltaTime);
}

void InGameUITestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}

void InGameUITestScene::SavePlayerInfo()
{
}

void InGameUITestScene::LoadPlayerInfo()
{
}

void InGameUITestScene::RandomSpawnObstacle()
{
}
