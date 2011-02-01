// simple.vs
//
// Generic vertex transformation,

// copy primary color

void main()
{
	gl_FrontColor = gl_Color;

	gl_Position = ftransform();
}