// Test application for FIFE engine

// engine include
#include "../Fife.h"

// sample includes
#include "SimpleAnimatedTextures.h"
#include "SimpleStaticTextures.h"

class TestKeyListener : public IKeyListener
{
public:
    TestKeyListener(Camera* cam) 
    : m_name("TestKeyListener"), m_cam(cam), m_xTrans(0.f), m_yTrans(0.f), m_zTrans(0.f)
    { 
    
    };

    virtual const std::string& GetName() { return m_name; };

    virtual bool OnKeyPressed(const IKeyEvent& event) 
    { 
        const float TranslationAmount = 1.f;

        if (event.GetKeyCode() == KeyCodes::Left)
        {
            m_xTrans -= TranslationAmount;
        }
        else if (event.GetKeyCode() == KeyCodes::Right)
        {
            m_xTrans += TranslationAmount;
        }
        else if (event.GetKeyCode() == KeyCodes::Up)
        {
            m_zTrans -= TranslationAmount;
        }
        else if (event.GetKeyCode() == KeyCodes::Down)
        {
            m_zTrans += TranslationAmount;
        }

        m_cam->Translate(m_xTrans, m_yTrans, m_zTrans);

        return true;
    }

    virtual bool OnKeyReleased(const IKeyEvent& event) { return true; };

private:
    Camera* m_cam;
    std::string m_name;
    float m_xTrans;
    float m_yTrans;
    float m_zTrans;
};

class TestMouseListener : public IMouseListener
{
public:
    TestMouseListener(Camera* cam) 
    : m_name("TestMouseListener"), m_cam(cam), m_lastX(0), m_lastY(0), m_initialized(false)
    { 
    
    };

    virtual const std::string& GetName() { return m_name; };

    virtual bool OnMouseMoved(const IMouseEvent& event) 
    {
        float yawAmount = (event.GetXPos() - m_lastX) * 0.015;
        float pitchAmount = (event.GetYPos() - m_lastY) * 0.015;

        if  (m_initialized)
        {
            m_cam->Yaw(yawAmount);
            m_cam->Pitch(pitchAmount);

            std::cout << "relative pos: " << "(" << (event.GetYPos() - m_lastY) << "," << (event.GetXPos() - m_lastX) << ")" << std::endl;
        }

        m_lastX = event.GetXPos();
        m_lastY = event.GetYPos();

        m_initialized = true;

        if (event.IsButtonPressed(MouseButtons::LeftButton))
        {
            // TODO - add something fun here
        }
        else if (event.IsButtonPressed(MouseButtons::RightButton))
        {
            // TODO - maybe something else fun here
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
    int32_t m_lastX;
    int32_t m_lastY;
    bool m_initialized;
};

int main()
{
    EngineSettings settings;
	Engine engine(settings);

    //CreateSimpleAnimatedTextures(engine);
    CreateSimpleStaticTextures(engine);

    Camera* camera = engine.GetSceneManager()->GetCamera();
    TestKeyListener* keyListener = new TestKeyListener(camera);
    TestMouseListener* mouseListener = new TestMouseListener(camera);
    engine.GetInputSystem()->AddKeyListener(keyListener);
    engine.GetInputSystem()->AddMouseListener(mouseListener);

	while (engine.Run())
	{
		engine.BeginScene();
		engine.Render();
		engine.EndScene();

		std::stringstream oss;
		oss << "FPS: " << engine.GetFps();
		engine.GetWindowSystem()->SetWindowTitle(oss.str().c_str());
	}
}