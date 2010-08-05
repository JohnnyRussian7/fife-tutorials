
#include <sstream>

#include "../Engine.h"
#include "../SceneManager.h"
#include "../Camera.h"

int main()
{
	Engine engine;
	
    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));
    sceneManager->AddCamera(camera);   

	while (engine.Run())
	{
		engine.BeginScene();
		engine.Render();
		engine.EndScene();

		std::wstringstream oss;
		oss << "FPS: " << engine.GetFps();
		engine.GetWindowSystem()->SetWindowTitle(oss.str().c_str());
	}
}