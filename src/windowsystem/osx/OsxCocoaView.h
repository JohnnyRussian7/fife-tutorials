/**********************************************************************
 *	Filename: OsxCocoaView.h
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

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

struct OsxWindowSystem;

@interface OsxCocoaView : NSView {    
	NSOpenGLContext* m_context;
	NSOpenGLPixelFormat* m_pixelFormat;
    
    CVDisplayLinkRef displayLink;
    NSTimer* m_renderTimer;
    
    OsxWindowSystem* m_windowSystem;
}

- (id)initWithFrame:(NSRect)frame andWindow:(OsxWindowSystem*)windowSystem;

@end