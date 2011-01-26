
#ifndef WINDOW_SYSTEM_TYPES_H_
#define WINDOW_SYSTEM_TYPES_H_

struct WindowSystemType
{
	enum Enum
	{
		Win32 = 0,
		MacOsx,
		Linux,
		Sdl,

		Max,
		Invalid = -1
	};
};

#endif