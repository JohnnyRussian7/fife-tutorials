
#include <string>
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
#include "../IAnimation.h"
#include "../AnimatedTexture.h"
#include "../ISpriteSheet.h"
#include "../SpriteSheet.h"

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
    Image* image1 = loader.Load("..\\data\\grassalpha.png");
    Image* image2 = loader.Load("..\\data\\torch_animation.png");

    Billboard* b1 = sceneManager->CreateBillboard(16, 16, Vector3::Zero());
    IMaterial* m1 = new Material();
    
    if (image1)
    {
        if (m1)
        {
            ITexture* texture = new OpenglTexture(TextureType::_2d, image1);
            m1->SetTexture(texture);
        }
        b1->SetMaterial(m1);
    }

    Billboard* b2 = sceneManager->CreateBillboard(16, 16, Vector3(10, 10, 0));
    IMaterial* m2 = new Material();
    if (image2)
    {
        if (m2)
        {
            ISpriteSheet* spriteSheet = new SpriteSheet(image2);
            spriteSheet->SetNumRows(1);
            spriteSheet->SetNumCols(24);
            spriteSheet->SetNumTiles(24);
            IAnimation* animation = new AnimatedTexture(spriteSheet);
            animation->SetLooping(true);
            animation->SetTotalRunTime(20000);
            for (uint32_t i=0; i < spriteSheet->GetNumTiles(); ++i)
            {
                std::ostringstream oss;
                oss << "Frame_" << i;
                animation->AddFrame((char*)oss.str().c_str(), spriteSheet->GetTileCoords(i));
            }
            b2->SetAnimation(animation);
        }
        b2->SetMaterial(m2);
    }
    
    sceneManager->GetRootSceneNode()->AddEntity(b1);
    sceneManager->GetRootSceneNode()->AddEntity(b2);

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