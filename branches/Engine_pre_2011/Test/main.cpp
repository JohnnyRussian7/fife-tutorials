
#include <string>
#include <sstream>
#include <cmath>

// Engine includes
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
#include "../TextureManager.h"
#include "../TextureEnums.h"

class TestKeyListener : public IKeyListener
{
public:
    TestKeyListener(Camera* cam) : m_yawAngle(0.f), m_pitchAngle(0.f), m_name("TestKeyListener"), m_cam(cam) { };

    virtual const std::string& GetName() { return m_name; };

    virtual bool OnKeyPressed(const IKeyEvent& event) 
    { 
        if (event.GetKeyCode() == KeyCodes::Left)
        {
            m_yawAngle += 1.0f; 

            m_yawAngle = (uint32_t)m_yawAngle % 360;
            //m_yawAngle = std::fmod(m_yawAngle, 360.f);

//             if (m_yawAngle > 360.f)
//             {
//                 m_yawAngle = 0.f;
//             }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }
        else if (event.GetKeyCode() == KeyCodes::Right)
        {
            m_yawAngle -= 1.0f;

            m_yawAngle = (uint32_t)m_yawAngle % 360;
            //m_yawAngle = std::fmod(m_yawAngle, 360.f);

//             if (m_yawAngle < -360.f)
//             {
//                 m_yawAngle = 0.f;
//             }

            m_cam->Yaw(DegToRad(m_yawAngle));
        }
        else if (event.GetKeyCode() == KeyCodes::Up)
        {
            m_pitchAngle += 1.0f;

            m_pitchAngle = (uint32_t)m_pitchAngle % 360;
            //m_pitchAngle = std::fmod(m_pitchAngle, 360.f);

//             if (m_pitchAngle > 360.f)
//             {
//                 m_pitchAngle = 0.f;
//             }

            m_cam->Pitch(DegToRad(m_pitchAngle));
        }
        else if (event.GetKeyCode() == KeyCodes::Down)
        {
            m_pitchAngle -= 1.0f;

            m_pitchAngle = (uint32_t)m_pitchAngle % 360;
            //m_pitchAngle = std::fmod(m_pitchAngle, 360.f);

//             if (m_pitchAngle < -360.f)
//             {
//                 m_pitchAngle = 0.f;
//             }

            m_cam->Pitch(DegToRad(m_pitchAngle));
        }

        return true;
    }

    virtual bool OnKeyReleased(const IKeyEvent& event) { return true; };

private:
    Camera* m_cam;
    float m_yawAngle;
    float m_pitchAngle;
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
    virtual bool OnMouseWheel(const IMouseEvent& event) 
    {
        static float ZoomAmount = 10;

        m_cam->Translate(Vector3(0.f, 0.f, -ZoomAmount*event.GetWheelDelta()));

        return true;
    }

private:
    Camera* m_cam;
    float m_yawAngle;
    std::string m_name;
};

int main()
{
    EngineSettings settings;
	Engine engine(settings);

    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
//     camera->Pitch(DegToRad(30));
//     camera->Yaw(DegToRad(45));
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));

    sceneManager->AddCamera(camera);   

    TestKeyListener* keyListener = new TestKeyListener(camera);
    TestMouseListener* mouseListener = new TestMouseListener(camera);
    engine.GetInputSystem()->AddKeyListener(keyListener);
    engine.GetInputSystem()->AddMouseListener(mouseListener);

    PngLoader loader;

    Image* image1 = loader.Load("..\\data\\torch_animation.png");
    IEntity* e1 = sceneManager->CreateEntity("e1");
    Billboard* b1 = sceneManager->CreateBillboard(4, 4);
    e1->SetVisual(b1);
    if (image1)
    {
        b1->SetAnimation(sceneManager->CreateAnimatedTexture(image1, 1, 24, 24, 2500));

        IMaterial* m1 = new Material();
        b1->GetRenderable()->SetMaterial(m1);
    }
    SceneNode* torchNode = sceneManager->CreateSceneNode("torch");
    torchNode->AddEntity(e1);
    sceneManager->GetRootSceneNode()->AddChild(torchNode);
    torchNode->Translate(0, 0, -5);

    Image* image2 = loader.Load("..\\data\\explosions_pot.png");
    IEntity* e2 = sceneManager->CreateEntity("e2");
    Billboard* b2 = sceneManager->CreateBillboard(4, 4);
    e2->SetVisual(b2);
    if (image2)
    {
        b2->SetAnimation(sceneManager->CreateAnimatedTexture(image2, 5, 5, 25, 3000));

        IMaterial* m2 = new Material();
        b2->GetRenderable()->SetMaterial(m2);
    }
    SceneNode* explosionNode = sceneManager->CreateSceneNode("explosions");
    explosionNode->AddEntity(e2);
    sceneManager->GetRootSceneNode()->AddChild(explosionNode);
    explosionNode->Translate(4, 0, -5);

    Image* image3 = loader.Load("..\\data\\torch_animation.png");
    IEntity* e3 = sceneManager->CreateEntity("e3");
    Billboard* b3 = sceneManager->CreateBillboard(4, 4);
    e3->SetVisual(b3);
    if (image3)
    {
        b3->SetAnimation(sceneManager->CreateAnimatedTexture(image1, 1, 24, 24, 2500));

        IMaterial* m3 = new Material();
        b3->GetRenderable()->SetMaterial(m3);
    }
    SceneNode* torchNode2 = sceneManager->CreateSceneNode("torchNode2");
    torchNode2->AddEntity(e3);
    sceneManager->GetRootSceneNode()->AddChild(torchNode2);
    torchNode2->Translate(-4, 0, -5);

//     Image* image3 = loader.Load("..\\data\\finalfantasy5_pot.png"); 
//     IEntity* e3 = sceneManager->CreateEntity("e3");
//     Billboard* b3 = sceneManager->CreateBillboard(4, 4, Vector3(0, 0, 0));
//     e3->SetVisual(b3);
//     if (image3)
//     {
//         b3->SetAnimation(sceneManager->CreateAnimatedTexture(image3, 4, 4, 15, 2000));
// 
//         IMaterial* m3 = new Material();
//         b3->GetRenderable()->SetMaterial(m3);
//     }
//     
//     SceneNode* ffBossNode = sceneManager->CreateSceneNode("ffBoss");
//     ffBossNode->AddEntity(e3);
//     sceneManager->GetRootSceneNode()->AddChild(ffBossNode);
//     ffBossNode->Translate(10, 0, 0);

//     IEntity* e4 = sceneManager->CreateEntity("e4");
//     Billboard* b4 = sceneManager->CreateBillboard(16, 16, Vector3(0, 0, 0));
//     e4->SetVisual(b4);
//     IMaterial* m4 = new Material();
//     if (m4)
//     {
//         IAnimation* animation = sceneManager->CreateAnimatedTexture(2000, true);
// 
//         if (animation)
//         {
//             Image* img = loader.Load("..\\data\\animation_1\\000.png");
//             Image* img2 = loader.Load("..\\data\\animation_1\\045.png");
//             animation->AddFrame(engine.GetTextureManager()->CreateTexture(TextureType::_2d, img));
//             animation->AddFrame(engine.GetTextureManager()->CreateTexture(TextureType::_2d, img2));
//             b4->SetAnimation(animation);
//         }
//     }
//     b4->GetRenderable()->SetMaterial(m3);
// 
//     SceneNode* maleNode = sceneManager->CreateSceneNode("anim_1");
//     maleNode->Translate(4, 0, 0);
//     maleNode->AddEntity(e4);
//     sceneManager->GetRootSceneNode()->AddChild(maleNode);

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