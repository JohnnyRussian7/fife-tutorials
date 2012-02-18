/**********************************************************************
 *	Filename: OsxCocoaView.mm
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

#import "OsxCocoaView.h"
#import "OsxWindowSystem.h"
#import "../../inputsystem/osx/OsxKeyConverter.h"
#import "../../inputsystem/keyboard/KeyEvent.h"
#import "../../inputsystem/mouse/MouseEvent.h"

#define DISPLAY_LINK

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
    //[self display];
    
    // this was in an apple dev. document
    // alert the window to redraw
    [self setNeedsDisplay:YES];
}

- (id)initWithFrame:(NSRect)frame andWindow:(OsxWindowSystem*)windowSystem
{
    self = [super initWithFrame:frame];
    if (self) 
    {
        m_windowSystem = windowSystem;
        
        // setup context
        NSOpenGLPixelFormatAttribute attribs[] = {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADoubleBuffer,
            0
        };
        
        m_pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
        
        if (m_pixelFormat == nil)
        {
            // TODO - report error here
            NSLog(@"Error creating pixel format");
            exit(0);
        }
        
        m_context = [[NSOpenGLContext alloc] initWithFormat:m_pixelFormat shareContext:nil];
        
        if (m_context == nil)
        {
            // TODO - report error here
            NSLog(@"Error creating OpenGL context");
            exit(0);
        }
        
        GLint vblSync = 1;
        [m_context setValues:&vblSync forParameter:NSOpenGLCPSwapInterval];
        
#if defined(DISPLAY_LINK)
        // setup display link for refreshing view
        CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
        CVDisplayLinkSetOutputCallback(displayLink, DisplayLinkCallback, self);
        CGLContextObj cglContext = static_cast<CGLContextObj>([m_context CGLContextObj]);
        CGLPixelFormatObj cglPixelFormat = static_cast<CGLPixelFormatObj>([m_pixelFormat CGLPixelFormatObj]);
        CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
        
        // activate the display link
        CVDisplayLinkStart(displayLink);
#else
        m_renderTimer = [[NSTimer alloc] initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:0.0] 
                        interval:0.001 
                        target:self 
                        selector:@selector(renderTimerCallback:) 
                        userInfo:nil 
                        repeats:YES];
        
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSEventTrackingRunLoopMode];
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSDefaultRunLoopMode];
        [[NSRunLoop currentRunLoop] addTimer:m_renderTimer forMode:NSModalPanelRunLoopMode];
#endif
        
        // add ourself as a listener for the terminate signal so we have a chance
        // to shut ourselves down properly
        [[NSNotificationCenter defaultCenter] addObserver:self 
                                                 selector:@selector(applicationWillTerminate:)
                                                     name:NSApplicationWillTerminateNotification
                                                     object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                selector:@selector(reshape:)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                     object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(windowResized:) name:NSWindowDidResizeNotification
                                                   object:nil];
        
    }
    
    return self;
}

- (BOOL)acceptsFirstResponser
{
    return YES;
}

- (void)mouseDown:(NSEvent*)mouseEvent
{
    // get pointer location and convert to view coordinates
    NSPoint location = [self convertPoint:[mouseEvent locationInWindow] fromView:nil];
    
    MouseEvent event;
    event.SetButtonPressed(MouseButtons::LeftButton);
    event.SetEventType(MouseEventType::MouseClick);
    event.SetXPos(location.x);
    event.SetYPos(location.y);
    event.SetRelativeX([mouseEvent deltaX]);
    event.SetRelativeY([mouseEvent deltaY]);
    
    if ([mouseEvent modifierFlags] & NSControlKeyMask)
    {
        event.SetModifier(MouseModifiers::Ctrl);
    }
    if ([mouseEvent modifierFlags] & NSAlternateKeyMask)
    {
        event.SetModifier(MouseModifiers::Alt);
    }
    if ([mouseEvent modifierFlags] & NSShiftKeyMask)
    {
        event.SetModifier(MouseModifiers::Shift);
    }
    
    m_windowSystem->OnMouseInput(event);
    
    [self setNeedsDisplay:YES];
}

-(void)mouseUp:(NSEvent*)mouseEvent
{
    NSLog(@"mouse up event received\n");
}

-(void)mouseMoved:(NSEvent*)mouseEvent
{
    // get pointer location and convert to view coordinates
    NSPoint location = [self convertPoint:[mouseEvent locationInWindow] fromView:nil];
    
    MouseEvent event;
    event.SetEventType(MouseEventType::MouseMoved);
    event.SetXPos(location.x);
    event.SetYPos(location.y);
    event.SetRelativeX([mouseEvent deltaX]);
    event.SetRelativeY([mouseEvent deltaY]);
    
    if ([mouseEvent modifierFlags] & NSControlKeyMask)
    {
        event.SetModifier(MouseModifiers::Ctrl);
    }
    if ([mouseEvent modifierFlags] & NSAlternateKeyMask)
    {
        event.SetModifier(MouseModifiers::Alt);
    }
    if ([mouseEvent modifierFlags] & NSShiftKeyMask)
    {
        event.SetModifier(MouseModifiers::Shift);
    }
    
    m_windowSystem->OnMouseInput(event);
    
    [self setNeedsDisplay:YES];
}

-(void)mouseDragged:(NSEvent*)mouseEvent
{
    NSLog(@"mouse dragged event received\n"); 
}

-(void)keyDown:(NSEvent*)keyEvent
{    
    KeyCodes::Enum keyCode = ConvertOsxVirtualKeyToKeyCode([keyEvent keyCode]);
    
    if (keyCode != KeyCodes::Invalid)
    {
        KeyEvent event;
        event.SetKeyCode(keyCode);
        event.SetKeyPressed(true);
        
        NSString *characters = [keyEvent characters];
        
        if ([characters length]) 
        {
            unichar character = [characters characterAtIndex:0];
            event.SetText(character);
        }
        
        if ([keyEvent modifierFlags] & NSShiftKeyMask)
        {
            event.SetModifier(KeyModifiers::Shift);
        }
        if ([keyEvent modifierFlags] & NSControlKeyMask)
        {
            event.SetModifier(KeyModifiers::Ctrl);
        }
        if ([keyEvent modifierFlags] & NSAlternateKeyMask)
        {
            event.SetModifier(KeyModifiers::Alt);
        }
        
        m_windowSystem->OnKeyboardInput(event);
    }
    else
    {
        NSString* error = [NSString stringWithFormat:@"unsupported key code: @i\n", [keyEvent keyCode]];
        NSLog(@"%@", error);
    }
}

-(void)keyUp:(NSEvent*)keyEvent
{
    KeyCodes::Enum keyCode = ConvertOsxVirtualKeyToKeyCode([keyEvent keyCode]);
    
    if (keyCode != KeyCodes::Invalid)
    {
        KeyEvent event;
        event.SetKeyCode(keyCode);
        event.SetKeyPressed(false);
        
        NSString *characters = [keyEvent characters];
        
        if ([characters length]) 
        {
            unichar character = [characters characterAtIndex:0];
            event.SetText(character);
        }
        
        if ([keyEvent modifierFlags] & NSShiftKeyMask)
        {
            event.SetModifier(KeyModifiers::Shift);
        }
        if ([keyEvent modifierFlags] & NSControlKeyMask)
        {
            event.SetModifier(KeyModifiers::Ctrl);
        }
        if ([keyEvent modifierFlags] & NSAlternateKeyMask)
        {
            event.SetModifier(KeyModifiers::Alt);
        }        
        
        m_windowSystem->OnKeyboardInput(event);
    }
    else
    {
        NSString* error = [NSString stringWithFormat:@"unsupported key code: @i\n", [keyEvent keyCode]];
        NSLog(@"%@", error);
    }
    
}

-(void)drawRect:(NSRect)rect
{    
    [self renderFrame];
}

-(void)windowResized:(NSNotification *)notification
{
    NSSize size = [[self window] frame].size;
    
    m_windowSystem->ResizeImpl(uint32_t(size.width), uint32_t(size.height));
}

-(void)reshape:(NSNotification*)notification
{
    // must lock GL context because display link is threaded
    CGLLockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));

    // lets the context update itself
    if (m_context && [m_context view] == self)
	{
        [m_context update];
	}
	
    CGLUnlockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));
    
    std::cout << "reshape called" << std::endl;
}

-(void)applicationWillTerminate:(NSNotification*)notification
{
#if defined(DISPLAY_LINK)
    CVDisplayLinkStop(displayLink);
#endif
}

- (void)dealloc
{
    // removes ourselves as a listener for events
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
#if defined(DISPLAY_LINK)
    CVDisplayLinkRelease(displayLink);
#else
    [m_renderTimer setFireDate:[NSDate distantFuture]];
    [m_renderTimer invalidate];
#endif
    
    [m_context release];
    [m_pixelFormat release];
    
    [super dealloc];
}

- (void)renderFrame
{
    // must lock GL context because display link is threaded
    CGLLockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));
    
    if ([m_context view] != self)
    {
        [m_context setView:self];
    }
    
    [m_context makeCurrentContext];
    
    // notify window system of update
    m_windowSystem->OnDisplayUpdate();
    
    [m_context flushBuffer];
    
    CGLUnlockContext(static_cast<CGLContextObj>([m_context CGLContextObj]));
}

@end
