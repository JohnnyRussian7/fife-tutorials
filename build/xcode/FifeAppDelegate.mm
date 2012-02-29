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

#include "../../src/test/SimpleApplication.h"

@implementation FifeAppDelegate

-(void)applicationDidFinishLaunching:(NSNotification*)notification
{
    // create the sample application now that we are loaded
    m_application = new SimpleApplication();
    
    // start the application
    m_application->Run();
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
    return YES;
}

-(void)applicationWillTerminate:(NSNotification*)notification
{
    // delete the application, it will take care of everything else
    delete m_application;
    m_application = 0;
}

@end
