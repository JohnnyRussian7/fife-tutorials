//
//  FifeAppDelegate.m
//  Fife
//
//  Created by Jesse Manning on 12/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "FifeAppDelegate.h"

#include "../../src/Engine.h"

// sample includes
#include "../../src/test/SimpleKeyListener.h"
#include "../../src/test/SimpleMouseListener.h"
#include "../../src/test/SimpleAnimatedTextures.h"
#include "../../src/test/SimpleStaticTextures.h"
#include "../../src/test/SimpleIsometricView.h"
#include "../../src/test/SimpleParticleSystem.h"

@implementation FifeAppDelegate

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
    EngineSettings settings;
    settings.renderSystemSettings.useVbo = false;
	m_engine = new Engine(settings);
    
    CreateSimpleAnimatedTextures(*m_engine);
    //CreateSimpleStaticTextures(*m_engine);
    //CreateSimpleIsometricView(*m_engine);
    //CreateSimpleParticleSystem(*m_engine);
    
    Camera* camera = m_engine->GetSceneManager()->GetCamera();
    SimpleKeyListener* keyListener = new SimpleKeyListener(*m_engine, camera);
    SimpleMouseListener* mouseListener = new SimpleMouseListener(camera);
    m_engine->GetInputSystem()->AddKeyListener(keyListener);
    m_engine->GetInputSystem()->AddMouseListener(mouseListener);
    
    
    m_engine->StartRenderLoop();
     
}

@end
