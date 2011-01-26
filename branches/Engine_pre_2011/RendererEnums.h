
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

struct PrimitiveType
{
    enum Enum
    {
        Points = 0,
        Line,
        LineStrip,
        LineLoop,
        Triangles,
        TriangleStrip,
        TriangleFan,
        Quads,
        QuadStrip,
        Polygon
    };
};

#endif
