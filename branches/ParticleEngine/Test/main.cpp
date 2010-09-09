
#include <sstream>

#include "../Engine.h"
#include "../SceneManager.h"
#include "../Camera.h"
#include "../Entity.h"
#include "../SceneNode.h"
#include "../MathUtil.h"
#include "../Quaternion.h"
#include "../Billboard.h"
#include "../PngLoader.h"
#include "../Image.h"
#include "../IMaterial.h"
#include "../Material.h"
#include "../ITexture.h"
#include "../OpenglTexture.h"

int main()
{
	Engine engine;
	
    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
	camera->Rotate(Vector3(1,0,0), DegToRad(30));		// pitch
    camera->Rotate(Vector3(0,1,0), DegToRad(45));		// yaw
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));

    sceneManager->AddCamera(camera);   

    // TODO - more development needed to work properly
    //Entity* entity = sceneManager->CreateEntity();
    //SceneNode* node = sceneManager->CreateSceneNode();
    //node->SetOrientation(FromAxisAngle(Vector3(0, 1, 0), DegToRad(30)));
    //node->AddEntity(entity);
    //sceneManager->GetRootSceneNode()->AddChild(node);

    PngLoader loader;
    Image* image = loader.Load("..\\data\\grassalpha.png");

    Billboard* b = sceneManager->CreateBillboard(16, 16, Vector3::Zero());
    IMaterial* m = new Material();
    
    if (image)
    {
        if (m)
        {
            ITexture* texture = new OpenglTexture(TextureType::_2d, image);
            m->SetTexture(texture);
        }
        b->SetMaterial(m);
    }
    
    sceneManager->GetRootSceneNode()->AddEntity(b);

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