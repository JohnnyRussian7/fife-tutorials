
#include <sstream>

#include "../Engine.h"
#include "../SceneManager.h"
#include "../Camera.h"
#include "../Entity.h"
#include "../SceneNode.h"
#include "../MathUtil.h"
#include "../Quaternion.h"

int main()
{
	Engine engine;
	
    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));
    sceneManager->AddCamera(camera);   

    // TODO - more development needed to work properly
    Entity* entity = sceneManager->CreateEntity();
    SceneNode* node = sceneManager->CreateSceneNode();
    node->SetOrientation(FromAxisAngle(Vector3(0, 1, 0), DegToRad(30)));
    node->AddEntity(entity);
    sceneManager->GetRootSceneNode()->AddChild(node);

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