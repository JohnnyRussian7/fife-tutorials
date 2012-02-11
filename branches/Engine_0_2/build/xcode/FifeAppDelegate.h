//
//  FifeAppDelegate.h
//  Fife
//
//  Created by Jesse Manning on 12/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

class Engine;

@interface FifeAppDelegate : NSObject {
    Engine* m_engine;
}

-(void)applicationDidFinishLaunching:(NSNotification*)notification;

@end
