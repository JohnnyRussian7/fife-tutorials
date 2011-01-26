
#ifndef RENDER_SYSTEM_TYPES_H_
#define RENDER_SYSTEM_TYPES_H_

struct RenderSystemType
{
	enum Enum
	{
		Opengl = 0,
		Sdl,

		Max,
		Invalid = -1
	};
};

#endif