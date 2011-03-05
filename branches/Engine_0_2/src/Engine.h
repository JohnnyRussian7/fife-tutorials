/**********************************************************************
*	Filename: Engine.h
*	
*	Copyright (C) 2011, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#ifndef ENGINE_H_
#define ENGINE_H_

#include "StdIncludes.h"

// TODO - this should not really include these files here
// instead put the settings structs in their own headers
// and only forward declare the interface pointers
#include "windowsystem/IWindowSystem.h"
#include "rendersystem/IRenderSystem.h"
#include "filesystem/IFilesystem.h"
#include "scene/SceneManager.h"
#include "inputsystem/IInputSystem.h"

#include "timer/Timer.h"
#include "windowsystem/IWindowSystemEventListener.h"

class IWindowSystem;
class IRenderSystem;
class IFileSystem;
class IInputSystem;
class SceneManager;
class TextureManager;
class ImageManager;

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
    ImageManager* GetImageManager() const;

	uint32_t GetFps() const;

	void BeginScene();
	void EndScene();
    void Render();

    bool Run();
    void Quit();

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
    ImageManager* m_imageManager;

    bool m_run;
    Timer m_timer;
	uint32_t m_fps;
	uint32_t m_fpsFrameCount;
	uint32_t m_fpsStartTime;
};

#endif
