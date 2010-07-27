
#include "Engine.h"

#include <cassert>
#include <cmath>

Engine::Engine()
: m_settings(EngineSettings()), m_windowSystem(0), m_renderSystem(0), m_fileSystem(0),
  m_fps(30), m_fpsFrameCount(0), m_fpsStartTime(0)
{
    m_windowSystem = CreateWindowSystem(m_settings.windowSettings);
    m_renderSystem = CreateRenderSystem(m_settings.renderSystemSettings);
    m_fileSystem = CreateFileSystem(m_settings.fileSystemSettings);
}

Engine::Engine(const EngineSettings& settings)
: m_settings(settings), m_windowSystem(0), m_renderSystem(0), m_fileSystem(0)
{
    m_windowSystem = CreateWindowSystem(m_settings.windowSettings);
    m_renderSystem = CreateRenderSystem(m_settings.renderSystemSettings);
    m_fileSystem = CreateFileSystem(m_settings.fileSystemSettings);
}

Engine::~Engine()
{
    delete m_windowSystem;
    m_windowSystem = 0;

    delete m_renderSystem;
    m_renderSystem = 0;

    delete m_fileSystem;
    m_fileSystem = 0;
}

void Engine::SetWindowSystem(IWindowSystem* windowSystem)
{
    m_windowSystem = windowSystem;
}

void Engine::SetRenderSystem(IRenderSystem* renderSystem)
{
    m_renderSystem = renderSystem;
}

void Engine::SetFileSystem(IFileSystem* fileSystem)
{
    m_fileSystem = fileSystem;
}

IWindowSystem* Engine::GetWindowSystem() const
{
    return m_windowSystem;
}

IRenderSystem* Engine::GetRenderSystem() const
{
    return m_renderSystem;
}

IFileSystem* Engine::GetFileSystem() const
{
    return m_fileSystem;
}

unsigned int Engine::GetFps() const
{
	return m_fps;
}

void Engine::BeginScene()
{
	
}

void Engine::EndScene()
{
	ComputeFps();
}

bool Engine::Run()
{
    assert(m_windowSystem && m_renderSystem);

    m_timer.Tick();

    bool retVal = m_windowSystem->Run();

    return retVal;
}

void Engine::ComputeFps()
{
	// update the number of frames completed
	++m_fpsFrameCount;

	// get current system time
	unsigned int now = m_timer.QueryRealTime();

	// total elapsed time since last frame
	unsigned int deltaTime = now - m_fpsStartTime;

	// calculate fps approx. once a second
	if (deltaTime > 1000)
	{
		float inverseDelta = 1.f / deltaTime;

		// calculate fps, rounding up
		m_fps = static_cast<unsigned int>(std::ceil(1000 * m_fpsFrameCount * inverseDelta));

		// update the fps start time
		m_fpsStartTime = now;

		// reset frame counter
		m_fpsFrameCount = 0;
	}
}