
#include <sstream>

#include "../Engine.h"

int main()
{
	Engine engine;
	
	while (engine.Run())
	{
		engine.BeginScene();
		std::wstringstream oss;
		oss << "FPS: " << engine.GetFps();

		engine.GetWindowSystem()->SetWindowTitle(oss.str().c_str());
		engine.EndScene();
	}
}