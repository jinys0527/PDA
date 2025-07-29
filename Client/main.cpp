#include "pch.h"
#include "Engine.h"
#include "GameApplication.h"
#include "SceneManager.h"

namespace
{
	GameApplication* g_pMainApp = nullptr;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(528);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
		return -1;

    Engine engine;
	SceneManager sceneManager(engine.GetRenderer(), engine.GetEventDispatcher(), engine.GetAssetManager());

 	g_pMainApp = new GameApplication(engine, sceneManager);
 
 	if (!g_pMainApp->Initialize())
 	{
 		std::cerr << "Failed to initialize sample code." << std::endl;
 		return -1;
 	}

 	g_pMainApp->Run();
 
 	g_pMainApp->Finalize();
 
 	delete g_pMainApp;

	CoUninitialize();

	return 0;
}