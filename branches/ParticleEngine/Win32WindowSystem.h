
#ifndef WIN32_WINDOW_SYSTEM_H_
#define WIN32_WINDOW_SYSTEM_H_

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <vector>

#include "IWindowSystem.h"

class IWindowSystemEventListener;
class IInputSystem;

class Win32WindowSystem : public IWindowSystem
{
public:
	Win32WindowSystem(const WindowSystemSettings& settings);
	~Win32WindowSystem();

	virtual void Init();
	virtual WindowSystemType::Enum GetWindowSystemType() const;
	virtual void SetWindowTitle(const wchar_t* text);
	virtual void Destroy();
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
	virtual void Update();
	virtual void SwapBuffers();
	virtual void AddListener(IWindowSystemEventListener* listener);
	virtual void RemoveListener(IWindowSystemEventListener* listener);
    virtual void SetInputSystem(IInputSystem* inputSystem);

private:
	void Resize();

private:
	WindowSystemSettings m_settings;
	bool m_externalWindow;
	bool m_fullScreen;
	bool m_shouldResize;
	bool m_quit;

	HWND m_hwnd;
	HDC m_hdc;
	HGLRC m_hglrc;

	typedef std::vector<IWindowSystemEventListener*> Listeners;
	Listeners m_listeners;

    IInputSystem* m_inputSystem;
};

#endif