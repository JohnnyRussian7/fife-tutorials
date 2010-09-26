
#ifndef IWINDOW_SYSTEM_H_
#define IWINDOW_SYSTEM_H_

#include "stdint.h"
#include "WindowSystemTypes.h"

class IWindowSystemEventListener;
class IInputSystem;

struct WindowSystemSettings
{
	WindowSystemSettings() 
	: windowSystemType(WindowSystemType::Invalid),
	width(800), height(600), bitsPerPixel(16), useExternalWindow(false), 
	allowFullScreen(true), useFullScreen(false), allowResizeable(true), windowId(0)
	{
#if defined(WIN32) || defined(WIN64) || defined(_WIN64)
		windowSystemType = WindowSystemType::Win32;
#elif defined(__APPLE__) || defined(MACOSX)
		windowSystemType = WindowSystemType::MacOsx;
#else
		windowSystemType = WindowSystemType::Linux;
#endif
	}
	
	WindowSystemType::Enum windowSystemType;
	uint32_t width;
	uint32_t height;
	uint32_t bitsPerPixel;
	bool useExternalWindow;
	bool allowFullScreen;
	bool useFullScreen;
	bool allowResizeable;
	void* windowId;
};

class IWindowSystem
{
public:

	virtual ~IWindowSystem() = 0 { };

	virtual void Init() = 0;
	virtual WindowSystemType::Enum GetWindowSystemType() const = 0;
	virtual void SetWindowTitle(const wchar_t* text) = 0;
	virtual void Destroy() = 0;
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
	virtual void Update() = 0;
	virtual void SwapBuffers() = 0;
	virtual void AddListener(IWindowSystemEventListener* listener) = 0;
	virtual void RemoveListener(IWindowSystemEventListener* listener) = 0;
    virtual void SetInputSystem(IInputSystem* inputSystem) = 0;
};

IWindowSystem* CreateWindowSystem(const WindowSystemSettings& settings);

#endif
