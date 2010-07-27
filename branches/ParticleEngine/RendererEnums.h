
#ifndef RENDERER_ENUMS_H_
#define RENDERER_ENUMS_H_

struct ProjectionType
{
	enum Enum
	{
		Perspective = 0,
		Ortho
	};
};

struct TransformType
{
	enum Enum
	{
		Model = 0,
		View,
		Projection,

		Num
	};
};

struct TextureType
{
	enum Enum
	{
		_1d = 0,
		_2d,
		_3d,
		Cube,

		Num
	};
};

#endif
