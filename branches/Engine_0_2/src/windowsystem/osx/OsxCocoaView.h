//
//  OSxCocoaView.h
//  ParticleEngine
//
//  Created by Jesse Manning on 1/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

@interface OsxCocoaView : NSView {
	@private
	NSOpenGLContext* m_context;
	NSOpenGLPixelFormat* m_pixelFormat;
    
    CVDisplayLinkRef displayLink;
    NSTimer* m_renderTimer;
}

@end
