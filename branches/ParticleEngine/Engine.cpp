
#include "Engine.h"

#include <cassert>

Engine::Engine()
: m_settings(EngineSettings()), m_windowSystem(0), m_renderSystem(0), m_fileSystem(0)
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

bool Engine::Run()
{
    assert(m_windowSystem && m_renderSystem);

    m_timer.Tick();

    bool retVal = m_windowSystem->Run();

    return retVal;
}