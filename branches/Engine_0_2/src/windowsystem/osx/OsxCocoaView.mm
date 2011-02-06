//
//  CocoaView.m
//  ParticleEngine
//
//  Created by Jesse Manning on 1/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "OsxCocoaView.h"

//#define DISPLAY_LINK

@interface OsxCocoaView (InternalMethods)

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime;
- (void)renderFrame;

@end

@implementation OsxCocoaView

static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
                                    const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
                                    CVOptionFlags *flagsOut, void *displayLinkContext)
{
    // call back into our view class to handle the update
    CVReturn result = [(OsxCocoaView *)displayLinkContext getFrameForTime:outputTime];
    return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime
{
    [self renderFrame];
    
    return kCVReturnSuccess;
}

- (void)renderTimerCallback:(NSTimer*)timer
{
    [self display];
}

- (id)initWithFrame:(NSRect)frame 
{
    self = [super initWithFrame:frame];
    if (self) 
    {
        // setup context
        NSOpenGLPixelFormatAttribute attribs[] = {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADoubleBuffer,
            0
        };
        
        m_pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs] autorelease];
        
        if (m_pixelFormat == nil)
        {
            // TODO - report error here
            exit(0);
        }
        
        m_context = [[[NSOpenGLContext alloc] initWithFormat:m_pixelFormat shareContext:nil] autorelease];
        
        if (m_context == nil)
        {
            // TODO - report error here
            exit(0);
        }
        
        GLint vblSync = 1;
        [m_context setValues:&vblSync forParameter:NSOpenGLCPSwapInterval];
        
#if defined(DISPLAY_LINK)
        // setup dispaly link for refreshing view
        CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
        CVDisplayLinkSetOutputCallback(displayLink, DisplayLinkCallback, self);
        CGLContextObj cglContext = static_cast<CGLContextObj>([m_context CGLContextObj]);
        CGLPixelFormatObj cglPixelFormat = static_cast<CGLPixelFormatObj>([m_pixelFormat CGLPixelFormatObj]);
        CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
        
        // activate the display link
        CVDisplayLinkStart(displayLink);
#else
        m_renderTimer = [[[NSTimer alloc] initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:0.0] 
                        interval:0.001 
                        target:self 
                        selector:@selector(renderTimerCallback:) 
                        userInfo:nil 
                        repeats:YES] autorelease];
        
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSEventTrackingRunLoopMode];
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSDefaultRunLoopMode];
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSModalPanelRunLoopMode];
#endif
    }
    
    return self;
}

- (void)drawRect:(NSRect)rect
{    
    [self renderFrame];
}

- (void)dealloc
{
#if defined(DISPLAY_LINK)
    CVDisplayLinkRelease(displayLink);
#else
    [m_renderTimer setFireDate:[NSDate distantFuture]];
    [m_renderTimer invalidate];
#endif
    
    [super dealloc];
}

- (void)renderFrame
{
    [m_context makeCurrentContext];
    
    // must lock GL context because display link is threaded
    CGLLockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));
    
    [m_context flushBuffer];
    
    CGLUnlockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));
    // TODO - implement rendering code here, need to call back into engine
}

@end
