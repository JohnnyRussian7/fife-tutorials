/**********************************************************************
*	Filename: Engine.cpp
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
#include "PrecompiledIncludes.h"

#include "Engine.h"
#include "scene/SceneManager.h"
#include "graphics/TextureManager.h"
#include "graphics/ImageManager.h"
#include "inputsystem/InputSystem.h"    // remove this in favor of create method

// TODO - should this be here?
#include "scene/Viewport.h"

Engine::Engine(const EngineSettings& settings)
: m_settings(settings), m_windowSystem(0), m_renderSystem(0), m_fileSystem(0), m_inputSystem(0),
  m_sceneManager(0), m_run(false), m_fps(30), m_fpsFrameCount(0), m_fpsStartTime(0), m_autoRendering(false)
{
    m_windowSystem = CreateWindowSystem(m_settings.windowSettings);
	m_windowSystem->Init();
	m_windowSystem->AddListener(this);

    m_renderSystem = CreateRenderSystem(m_settings.renderSystemSettings);
    m_fileSystem = CreateFileSystem(m_settings.fileSystemSettings);
    m_inputSystem = new InputSystem(m_settings.inputSystemSettings);
	
    m_sceneManager = new SceneManager(this, m_settings.sceneManagerSettings, m_renderSystem);
    m_textureManager = new TextureManager(m_settings.renderSystemSettings.renderSystemType);
    m_imageManager = new graphics::ImageManager();

    m_windowSystem->SetInputSystem(m_inputSystem);

	// TODO - this needs to be moved elsewhere
	m_renderSystem->SetViewPort(Viewport(0, 0, m_settings.windowSettings.width, m_settings.windowSettings.height));
}

Engine::~Engine()
{
    delete m_windowSystem;
    m_windowSystem = 0;

    delete m_renderSystem;
    m_renderSystem = 0;

    delete m_fileSystem;
    m_fileSystem = 0;

    delete m_inputSystem;
    m_inputSystem = 0;

    delete m_sceneManager;
    m_sceneManager = 0;
}

void Engine::SetWindowSystem(IWindowSystem* windowSystem)
{
    if (m_windowSystem)
    {
        delete m_windowSystem;
    }

    m_windowSystem = windowSystem;

    m_windowSystem->AddListener(this);
}

void Engine::SetRenderSystem(IRenderSystem* renderSystem)
{
    if (m_renderSystem)
    {
        delete m_renderSystem;
    }

    m_renderSystem = renderSystem;
}

void Engine::SetFileSystem(IFileSystem* fileSystem)
{
    if (m_fileSystem)
    {
        delete m_fileSystem;
    }

    m_fileSystem = fileSystem;
}

void Engine::SetInputSystem(IInputSystem* inputSystem)
{
    if (m_inputSystem)
    {
        delete m_inputSystem;
    }

    m_inputSystem = inputSystem;
}

void Engine::SetSceneManager(SceneManager* sceneManager)
{
    if (m_sceneManager)
    {
        delete m_sceneManager;
    }

	m_sceneManager = sceneManager;
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

IInputSystem* Engine::GetInputSystem() const
{
    return m_inputSystem;
}

SceneManager* Engine::GetSceneManager() const
{
	return m_sceneManager;
}

TextureManager* Engine::GetTextureManager() const
{
    return m_textureManager;
}

graphics::ImageManager* Engine::GetImageManager() const
{
    return m_imageManager;
}

uint32_t Engine::GetFps() const
{
	return m_fps;
}

void Engine::StartRenderLoop() 
{
    m_autoRendering = true;
}

void Engine::PerformRendering()
{
// for OS X we let the window system drive the render loop
#if !defined(MACOSX_OS)
    while (Run())
#else
    if (Run())
#endif
	{
        // TODO - jlm - fire scene begin event
        
		BeginScene();
        
        // TODO - jlm - fire render begin
        
		Render();
        
        // TODO - jlm - fire render end
        
		EndScene();
        
        // TODO - jlm - fire scene end
    }
}

void Engine::BeginScene()
{
	
}

void Engine::EndScene()
{
    m_windowSystem->SwapBuffers();
	ComputeFps();
}

void Engine::Render()
{
    m_sceneManager->RenderScene(m_timer.GetTime());
}

bool Engine::Run()
{
    static bool FirstTimeCheck = false;
    
    assert(m_windowSystem && m_renderSystem);

    if (FirstTimeCheck == false)
    {
        FirstTimeCheck = true;
        
        if (m_autoRendering == true)
        {
            m_run = true;
        }
    }
    
    if (m_run)
    {
        m_timer.Tick();

        // must save the run state in intermediate variable
        // and only set the overall engine state after all the
        // run states have been collected, otherwise the engine
        // run state will not be recorded correctly
        bool runState = m_windowSystem->Run();

        m_run &= runState;
    }

    return m_run;
}

void Engine::Quit()
{
    m_run = false;
}

void Engine::OnResize(uint32_t width, uint32_t height)
{
    m_renderSystem->SetViewPort(Viewport(0, 0, width, height));
}

void Engine::OnDisplayUpdate()
{
    // when auto rendering is disabled do nothing
    // as the user is controlling the render loop
    if (!m_autoRendering)
    {
        return;
    }
    
    // display has signaled an update, so its time to render
    PerformRendering();
}

void Engine::ComputeFps()
{
	// update the number of frames completed
	++m_fpsFrameCount;

	// get current system time
	uint32_t now = m_timer.QueryRealTime();

	// total elapsed time since last frame
	uint32_t deltaTime = now - m_fpsStartTime;

	// calculate fps approx. once a second
	if (deltaTime > 1000)
	{
		float inverseDelta = 1.f / deltaTime;

		// calculate fps, rounding up
		m_fps = static_cast<uint32_t>(std::ceil(1000 * m_fpsFrameCount * inverseDelta));

		// update the fps start time
		m_fpsStartTime = now;

		// reset frame counter
		m_fpsFrameCount = 0;
	}
}