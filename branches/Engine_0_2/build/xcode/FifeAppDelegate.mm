/**********************************************************************
 *	Filename: FifeAppDelegate.mm
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

#import "FifeAppDelegate.h"

#include "../../src/Engine.h"

// sample includes
#include "../../src/test/SimpleKeyListener.h"
#include "../../src/test/SimpleMouseListener.h"
#include "../../src/test/SimpleAnimatedTextures.h"
#include "../../src/test/SimpleStaticTextures.h"
#include "../../src/test/SimpleIsometricView.h"
#include "../../src/test/SimpleParticleSystem.h"
#include "../../src/test/FpsCameraController.h"

@implementation FifeAppDelegate

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
    EngineSettings settings;
    settings.renderSystemSettings.useVbo = true;
	m_engine = new Engine(settings);
    
    m_fpsCamera = new FpsCameraController(m_engine->GetSceneManager());
    
    CreateSimpleAnimatedTextures(*m_engine);
    //CreateSimpleStaticTextures(*m_engine);
    //CreateSimpleIsometricView(*m_engine);
    //CreateSimpleParticleSystem(*m_engine);

    SimpleKeyListener* keyListener = new SimpleKeyListener(*m_engine, *m_fpsCamera);
    SimpleMouseListener* mouseListener = new SimpleMouseListener(*m_fpsCamera);
    m_engine->GetInputSystem()->AddKeyListener(keyListener);
    m_engine->GetInputSystem()->AddMouseListener(mouseListener);
    
    m_engine->StartRenderLoop();
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
    return YES;
}

-(void)applicationWillTerminate:(NSNotification*)notification
{
    m_engine->Quit();
    
    delete m_engine;
    delete m_fpsCamera;
}

@end
