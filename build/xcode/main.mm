//
//  main.m
//  ParticleEngine
//
//  Created by Jesse Manning on 1/13/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "Fife.h"

int main(int argc, char *argv[])
{
    Engine engine;
    
    SceneManager* sceneManager = engine.GetSceneManager();
    Camera* camera = sceneManager->CreateCamera();
    //     camera->Pitch(DegToRad(30));
    //     camera->Yaw(DegToRad(45));
    camera->Translate(Vector3(0, 0, 50));
    camera->LookAt(Vector3(0, 0, 0));
    
    sceneManager->AddCamera(camera);   
    

    //while (engine.Run())
    //{
    //    engine.BeginScene();
    //    engine.Render();
    //    engine.EndScene();
    //}
    
    return NSApplicationMain(argc,  (const char **) argv);
    
    return 0;
}
