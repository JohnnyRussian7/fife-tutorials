/**********************************************************************
 *	Filename: SimpleApplication.cpp
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

#include "SimpleApplication.h"

// sample includes
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"
#include "SimpleAnimatedTextures.h"
#include "SimpleStaticTextures.h"
#include "SimpleIsometricView.h"
#include "SimpleParticleSystem.h"
#include "FpsCameraController.h"

SimpleApplication::SimpleApplication()
{
    CreateEngine();
    CreateCamera();
    CreateKeyListener();
    CreateMouseListener();
    
    // add as a frame listener must be done after CreateEngine()
    m_engine->AddFrameListener(this);
}

SimpleApplication::~SimpleApplication()
{
    Stop();
    
    // remove as frame listener, must be done before engine deletion
    m_engine->RemoveFrameListener(this);
    
    m_engine->GetInputSystem()->RemoveAllListeners();
    
    delete m_fpsCamera;
    m_fpsCamera = 0;
    
    delete m_engine;
    m_engine = 0;
    
    delete m_keyListener;
    m_keyListener = 0;
    
    delete m_mouseListener;
    m_mouseListener = 0;
}

void SimpleApplication::CreateEngine()
{
    EngineSettings settings;
    settings.renderSystemSettings.useVbo = true;
	m_engine = new Engine(settings);
}

void SimpleApplication::CreateCamera()
{
    m_fpsCamera = new FpsCameraController(m_engine->GetSceneManager());
}

void SimpleApplication::CreateMouseListener()
{
    m_mouseListener = new SimpleMouseListener(m_fpsCamera);
    m_engine->GetInputSystem()->AddMouseListener(m_mouseListener);
}

void SimpleApplication::CreateKeyListener()
{
    m_keyListener = new SimpleKeyListener(m_engine, m_fpsCamera);
    m_engine->GetInputSystem()->AddKeyListener(m_keyListener);
}

void SimpleApplication::Run()
{
    //CreateSimpleAnimatedTextures(*m_engine);
    //CreateSimpleStaticTextures(*m_engine);
    //CreateSimpleIsometricView(*m_engine, *m_fpsCamera);
    CreateSimpleParticleSystem(*m_engine);
    
    m_engine->StartRenderLoop();
    
#if defined(WINDOWS_OS)
    while (engine.Run())
	{
        engine.OnSceneBegin();
		engine.BeginScene();
        
        engine.OnRenderBegin();
		engine.Render();
        engine.OnRenderEnd();
        
		engine.EndScene();
        engine.OnSceneEnd();
        
		std::stringstream oss;
		oss << "FPS: " << engine.GetFps();
		engine.GetWindowSystem()->SetWindowTitle(oss.str().c_str());
	}
#endif
}

void SimpleApplication::Stop()
{
    m_engine->Quit();
}

void SimpleApplication::OnSceneBegin(uint32_t time)
{
    // give the camera a chance to update
    m_fpsCamera->update(time);
}

void SimpleApplication::OnSceneEnd(uint32_t time)
{
    
}

void SimpleApplication::OnRenderBegin(uint32_t time)
{
    
}

void SimpleApplication::OnRenderEnd(uint32_t time)
{
    
}
