
#ifndef ENGINE_H_
#define ENGINE_H_

// TODO - this should not really include these files here
// instead put the settings structs in their own headers
// and only forward declare the interface pointers
#include "IWindowSystem.h"
#include "IRenderSystem.h"
#include "IFilesystem.h"
#include "IInputSystem.h"
#include "SceneManager.h"
#include "TextureManager.h"

#include "Timer.h"
#include "stdint.h"
#include "IWindowSystemEventListener.h"

// read comment above to know why these are here
class IWindowSystem;
class IRenderSystem;
class IFileSystem;
class IInputSystem;
class SceneManager;

struct EngineSettings
{
    WindowSystemSettings windowSettings;
    RenderSystemSettings renderSystemSettings;
    FileSystemSettings fileSystemSettings;
    InputSystemSettings inputSystemSettings;
	SceneManagerSettings sceneManagerSettings;
};

class Engine : public IWindowSystemEventListener
{
public:
    Engine(const EngineSettings& settings = EngineSettings());

    ~Engine();

    void SetWindowSystem(IWindowSystem* windowSystem);
    void SetRenderSystem(IRenderSystem* renderSystem);
    void SetFileSystem(IFileSystem* fileSystem);
    void SetInputSystem(IInputSystem* inputSystem);
	void SetSceneManager(SceneManager* sceneManager);

    IWindowSystem* GetWindowSystem() const;
    IRenderSystem* GetRenderSystem() const;
    IFileSystem* GetFileSystem() const;
    IInputSystem* GetInputSystem() const;

	SceneManager* GetSceneManager() const;
    TextureManager* GetTextureManager() const;

	uint32_t GetFps() const;

	void BeginScene();
	void EndScene();
    void Render();

    bool Run();

	virtual void OnResize(uint32_t width, uint32_t height);

private:
	void ComputeFps();

private:
    EngineSettings m_settings;
    IWindowSystem* m_windowSystem;
    IRenderSystem* m_renderSystem;
    IFileSystem* m_fileSystem;
    IInputSystem* m_inputSystem;
	SceneManager* m_sceneManager;
    TextureManager* m_textureManager;

    Timer m_timer;

	uint32_t m_fps;
	uint32_t m_fpsFrameCount;
	uint32_t m_fpsStartTime;
};

#endif
