
#ifndef WIN32_WINDOW_SYSTEM_H_
#define WIN32_WINDOW_SYSTEM_H_

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "IWindowSystem.h"

class IRenderSystem;

class Win32WindowSystem : public IWindowSystem
{
public:
	Win32WindowSystem(const WindowSettings& settings);
	~Win32WindowSystem();

	virtual WindowSystemType::Enum GetWindowSystemType() const;
	virtual void SetWindowTitle(const wchar_t* text);
	virtual void Minimize();
	virtual void Maximize();
	virtual void Restore();
	virtual void SetFullScreen(bool fullScreen);
	virtual bool IsActive() const;
	virtual bool HasFocus() const;
	virtual bool IsMinimized() const;
	virtual bool IsMaximized() const;
	virtual void OnResize();
	virtual bool Run();

	virtual IRenderSystem* GetRenderSystem() const;

private:
	void Resize();

private:
	WindowSettings m_settings;
	bool m_externalWindow;
	bool m_fullScreen;
	bool m_shouldResize;
	bool m_quit;

	HWND m_hwnd;

	IRenderSystem* m_renderSystem;
};

#endif