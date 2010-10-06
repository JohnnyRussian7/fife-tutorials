
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
#include "../KeyCodes.h"
#include "../IKeyListener.h"
#include "../IKeyEvent.h"
#include "../IInputSystem.h"
#include "../IMouseListener.h"
#include "../IMouseEvent.h"

class TestKeyListener : public IKeyListener
{
public:
    TestKeyListener(Camera* cam) : m_name("TestKeyListener"), m_cam(cam) { };

    virtual const std::string& GetName() { return m_name; };

    virtual bool OnKeyPressed(const IKeyEvent& event) 
    { 
        if (event.GetKeyCode() == KeyCodes::Left)
        {
            m_yawAngle += 0.1f; 

            if (m_yawAngle > 360.f)
            {
                m_yawAngle = 0.f;
            }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }
        else if (event.GetKeyCode() == KeyCodes::Right)
        {
            m_yawAngle -= 0.1f;

            if (m_yawAngle < -360.f)
            {
                m_yawAngle = 0.f;
            }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }

        return true;
    }

    virtual bool OnKeyReleased(const IKeyEvent& event) { return true; };

private:
    Camera* m_cam;
    float m_yawAngle;
    std::string m_name;
};

class TestMouseListener : public IMouseListener
{
public:
    TestMouseListener(Camera* cam) : m_name("TestMouseListener"), m_cam(cam) { };

    virtual const std::string& GetName() { return m_name; };

    virtual bool OnMouseMoved(const IMouseEvent& event) 
    { 
        if (event.IsButtonPressed(MouseButtons::LeftButton))
        {
            m_yawAngle += 0.1f; 

            if (m_yawAngle > 360.f)
            {
                m_yawAngle = 0.f;
            }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }
        else if (event.IsButtonPressed(MouseButtons::RightButton))
        {
            m_yawAngle -= 0.1f;

            if (m_yawAngle < -360.f)
            {
                m_yawAngle = 0.f;
            }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }

        return true;
    }

    virtual bool OnMousePressed(const IMouseEvent& event) { return true; };
    virtual bool OnMouseReleased(const IMouseEvent& event) { return true; };
    virtual bool OnMouseWheel(const IMouseEvent& event) { return true; };

private:
    Camera* m_cam;
    float m_yawAngle;
    std::string m_name;
};

int main()
{
    EngineSettings settings;
    settings.renderSystemSettings.useVbo = true;
	Engine engine(settings);

    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
	camera->Rotate(Vector3(1,0,0), DegToRad(30));		// pitch
    camera->Rotate(Vector3(0,1,0), DegToRad(45));		// yaw
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));

    sceneManager->AddCamera(camera);   

    TestKeyListener* keyListener = new TestKeyListener(camera);
    TestMouseListener* mouseListener = new TestMouseListener(camera);
    engine.GetInputSystem()->AddKeyListener(keyListener);
    engine.GetInputSystem()->AddMouseListener(mouseListener);

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