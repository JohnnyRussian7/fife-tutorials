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
#include "SceneManager.h"
#include "InputSystem.h"

// TODO - should this be here
#include "Viewport.h"

Engine::Engine(const EngineSettings& settings)
: m_settings(settings), m_windowSystem(0), m_renderSystem(0), m_fileSystem(0), m_inputSystem(0),
  m_sceneManager(0), m_fps(30), m_fpsFrameCount(0), m_fpsStartTime(0)
{
    m_windowSystem = CreateWindowSystem(m_settings.windowSettings);
	m_windowSystem->Init();
	m_windowSystem->AddListener(this);

    m_renderSystem = CreateRenderSystem(m_settings.renderSystemSettings);
    m_fileSystem = CreateFileSystem(m_settings.fileSystemSettings);
    m_inputSystem = new InputSystem(m_settings.inputSystemSettings);
	
    m_sceneManager = new SceneManager(this, m_settings.sceneManagerSettings, m_renderSystem);
    m_textureManager = new TextureManager(m_settings.renderSystemSettings.renderSystemType);

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

uint32_t Engine::GetFps() const
{
	return m_fps;
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
    assert(m_windowSystem && m_renderSystem);

    m_timer.Tick();

    bool retVal = m_windowSystem->Run();

    return retVal;
}

void Engine::OnResize(uint32_t width, uint32_t height)
{
    m_renderSystem->SetViewPort(Viewport(0, 0, width, height));
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