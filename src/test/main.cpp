// Test application for FIFE engine

// engine include
#include "../Fife.h"

// sample includes
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"
#include "SimpleAnimatedTextures.h"
#include "SimpleStaticTextures.h"
#include "SimpleIsometricView.h"

int main()
{
    EngineSettings settings;
	Engine engine(settings);

    //CreateSimpleAnimatedTextures(engine);
    //CreateSimpleStaticTextures(engine);
    CreateSimpleIsometricView(engine);

    Camera* camera = engine.GetSceneManager()->GetCamera();
    SimpleKeyListener* keyListener = new SimpleKeyListener(engine, camera);
    SimpleMouseListener* mouseListener = new SimpleMouseListener(camera);
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

    engine.GetInputSystem()->RemoveAllListeners();

    delete keyListener;
    delete mouseListener;
}