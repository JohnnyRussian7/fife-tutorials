
#ifndef IWINDOW_SYSTEM_EVENT_LISTENER_H_
#define IWINDOW_SYSTEM_EVENT_LISTENER_H_

#include "stdint.h"

class IWindowSystemEventListener
{
public:
	virtual void OnResize(uint32_t width, uint32_t height) = 0;
};

#endif
