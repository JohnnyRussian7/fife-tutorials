
#ifndef ENGINE_H_
#define ENGINE_H_

// TODO - this should not really include these files here
// instead put the settings structs in their own headers
// and only forward declare the interface pointers
#include "IWindowSystem.h"
#include "IRenderSystem.h"
#include "IFilesystem.h"
#include "Timer.h"

// read comment above to know why these are here
class IWindowSystem;
class IRenderSystem;
class IFileSystem;

struct EngineSettings
{
    WindowSystemSettings windowSettings;
    RenderSystemSettings renderSystemSettings;
    FileSystemSettings fileSystemSettings;
};

class Engine
{
public:
    Engine();
    Engine(const EngineSettings& settings);

    ~Engine();

    void SetWindowSystem(IWindowSystem* windowSystem);
    void SetRenderSystem(IRenderSystem* renderSystem);
    void SetFileSystem(IFileSystem* fileSystem);

    IWindowSystem* GetWindowSystem() const;
    IRenderSystem* GetRenderSystem() const;
    IFileSystem* GetFileSystem() const;

    bool Run();

private:
    EngineSettings m_settings;
    IWindowSystem* m_windowSystem;
    IRenderSystem* m_renderSystem;
    IFileSystem* m_fileSystem;

    Timer m_timer;
};

#endif
