
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
#include "Image.h"
#include "Opengltexture.h"
#include "RendererEnums.h"
#include "MathUtil.h"

// TODO - this is temporary
#include "PngLoader.h"

bool keys[256];

Camera cam(Vector3(0.f, 0.f, 0.f));
ParticleEmitter* emitter = new ParticleEmitter(true, 
												AxisAlignedBoundingBox(Vector3(0.f, 0.f, 0.f), 
																		Vector3(1.f, 1.f, 1.f)),
												80, 100,
												0.01f, 0.05f,
												800, 2000, 
												Vector3(0.f, 0.0005f, 0.f));
ParticleRenderer renderer;
float updateRate = 1.0;
WindowInput winInput(800, 600, cam);
unsigned int textureId = -1;
Image* image = NULL;
Image* background = NULL;
OpenglTexture* texture = NULL;
OpenglTexture* bgTexture = NULL;

void DrawQuadPlane()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);			 // lower left
	glVertex3f(-2.0, -2.0, -2.0);

	glTexCoord2f(1.0, 0.0);			// lower right
	glVertex3f(2.0, -2.0, -2.0);	

	glTexCoord2f(1.0, 1.0);			// upper right
	glVertex3f(2.0, 2.0, -2.0);		

	glTexCoord2f(0.0, 1.0);			// upper left
	glVertex3f(-2.0, 2.0, -2.0);	
	glEnd();
}

void DrawPlane()
{
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);			// left bottom
	glVertex3f(-2.0, -2.0, -2.0);

	glTexCoord2f(1.0, 0.0);			// right bottom
	glVertex3f(2.0, -2.0, -2.0);

	glTexCoord2f(0.0, 1.0);			// top left
	glVertex3f(-2.0, 2.0, -2.0);

	glTexCoord2f(1.0, 1.0);			// top right
	glVertex3f(2.0, 2.0, -2.0);
	glEnd();
}

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
    //cam.Yaw(DegToRad(-45));
    //cam.Pitch(DegToRad(-30));
	cam.LookAt(Vector3(0, 0, 5));
	//cam.Rotate(45.f, 30.f, 0.f);

	ParticleFadeOutEffect* fadeOutEffect = new ParticleFadeOutEffect(Color(0.f, 0.f, 0.f, 0.f), 1000);
	emitter->AddEffect(fadeOutEffect);
	renderer.SetEmitter(emitter);

	// TODO - this is temporary here
	PngLoader loader;

	image = loader.Load("C:\\Documents and Settings\\jesse\\My Documents\\Programming\\ParticleEngine\\ParticleEngine\\data\\fireparticle.png");
	background = loader.Load("C:\\Documents and Settings\\JESSE\\My Documents\\Programming\\Particle Engine\\ParticleEngine\\data\\grass.png");

	texture = new OpenglTexture(TextureType::_2d, image);
	bgTexture = new OpenglTexture(TextureType::_2d, background);
}

void RenderFrame()
{
	winInput.ReadInput(keys);

	cam.Render();
	//glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
	glBindTexture(GL_TEXTURE_2D, bgTexture->GetTextureId());
	DrawPlane();
	//DrawQuadPlane();
	glBindTexture(GL_TEXTURE_2D, 0);

	//renderer.Update(updateRate);
    //renderer.Render(cam);

	//glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(0.0, 0.0, -10.0);
	//glRotatef(90, 0.0, 1.0, 0.0);
	//glRotatef(90, 1.0, 0.0, 0.0);

	//glBindTexture(GL_TEXTURE_2D, textureId);
	//DrawQuadPlane();
	//DrawPlane();
	//glPopMatrix();
}