
#include "../Engine.h"

int main()
{
	Engine engine;

	while (engine.Run())
	{
		engine.GetWindowSystem()->SetWindowTitle(L"TEST WINDOW");
	}

// 	WindowSettings settings;
// 	settings.applicationType = WindowSystemType::Win32;
	//settings.allowResizeable = false;
	//settings.allowFullScreen = true;
// 	IWindowSystem* application = CreateWindowSystem(settings);
// 
// 	if (!application)
// 	{
// 		return 0;
// 	}
// 
// 	while (application->Run())
// 	{
// 		application->SetWindowTitle(L"Jesse's window");
// 	}
}