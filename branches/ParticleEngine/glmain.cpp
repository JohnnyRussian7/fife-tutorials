#include <windows.h>

#include <gl/gl.h>			// OpenGL headers
#include <gl/glu.h>

#include "winmain.h"
#include "system.h"
#include "glmain.h"

#include "Camera.h"
#include "Vector.h"
#include "AxisAlignedBoundingBox.h"
#include "ParticleEmitter.h"
#include "ParticleRenderer.h"
#include "ParticleFadeOutEffect.h"
#include "Color.h"
#include "WindowInput.h"

bool keys[256];

Camera cam(Vector3(0.f, 0.f, 0.f));
ParticleEmitter* emitter = new ParticleEmitter(true, 
												AxisAlignedBoundingBox(Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f)),
												80, 100,
												0.01f, 0.05f,
												800, 2000,
												Vector3(0.f, 0.f, 10.f), 
												Vector3(0.f, 0.0005f, 0.f));
ParticleRenderer renderer;
float updateRate = 1.0;
WindowInput winInput(800, 600, cam);

void DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);    // A
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f( 1.0f, -0.5f, 0.0f);    // B
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f( 0.0f,  0.5f, 0.0f);    // C
	glEnd();
}

void InitFrame()
{
    // initialize camera
    cam.Init();
    cam.Resize(800,600);
	//cam.Rotate(45.f, 30.f, 0.f);

	ParticleFadeOutEffect* fadeOutEffect = new ParticleFadeOutEffect(Color(0.f, 0.f, 0.f, 0.f), 1000);
	emitter->AddEffect(fadeOutEffect);
	renderer.SetEmitter(emitter);
}

void RenderFrame()
{
	winInput.ReadInput(keys);

	cam.Render();
	renderer.Update(updateRate);
    renderer.Render(cam);
	

    //cam.update(0.f, 0.f, angle, 0.f, 0.f);
    //cam.render();

// 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
// 
// 	glLoadIdentity();
// 	glTranslatef(0.0f, 0.0f, -4.0f);
// 	glRotatef(angle, 0.0f, 1.0f, 0.0f);
// 
// 	DrawTriangle();
// 
// 	glLoadIdentity();
// 	glTranslatef(0.0f, 0.0f, -5.0f);
// 	glRotatef(-angle, 0.0f, 0.0f, 1.0f);
// 
// 	DrawTriangle();

// 	angle += 0.5f;
// 
// 	if (angle >= 360.0f)
// 	{
// 		angle = 0.0f;
// 	}
}