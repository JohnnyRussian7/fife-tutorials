
#ifndef WINDOW_SYSTEM_H_
#define WINDOW_SYSTEM_H_

#include "WindowSystemTypes.h"
#include "RenderSystemTypes.h"

class IRenderSystem;

struct WindowSettings
{
	WindowSettings() 
		: applicationType(WindowSystemType::Invalid),
		renderSystemType(RenderSystemType::Opengl),
		width(800), height(600), bitsPerPixel(16), useExternalWindow(false), 
		allowFullScreen(false), allowResizeable(true), windowId(0)
	{
#if defined(WIN32) || defined(WIN64) || defined(_WIN64)
		applicationType = WindowSystemType::Win32;
#elif defined(__APPLE__) || defined(MACOSX)
		applicationType = WindowSystemType::MacOsx;
#else
		applicationType = WindowSystemType::Linux;
#endif
	}
	
	WindowSystemType::Enum applicationType;
	RenderSystemType::Enum renderSystemType;
	unsigned int width;
	unsigned int height;
	unsigned int bitsPerPixel;
	bool useExternalWindow;
	bool allowFullScreen;
	bool allowResizeable;
	void* windowId;
};

class IWindowSystem
{
public:

	virtual ~IWindowSystem() = 0 { };

	virtual WindowSystemType::Enum GetWindowSystemType() const = 0;
	virtual void SetWindowTitle(const wchar_t* text) = 0;
	virtual void Minimize() = 0;
	virtual void Maximize() = 0;
	virtual void Restore() = 0;
	virtual void SetFullScreen(bool fullScreen) = 0;
	virtual bool IsActive() const = 0;
	virtual bool HasFocus() const = 0;
	virtual bool IsMinimized() const = 0;
	virtual bool IsMaximized() const = 0;
	virtual void OnResize() = 0;
	virtual bool Run() = 0;

	virtual IRenderSystem* GetRenderSystem() const = 0;
};

IWindowSystem* CreateWindowSystem(const WindowSettings& settings);

#endif
