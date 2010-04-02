
#include "Camera.h"
#include "Matrix.h"
#include "MathUtil.h"

#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

const float PIOVER180 = 3.14159265/180.f;

Camera::Camera(const Vector3& position, const Vector3& lookAt, float xrot, float yrot)
: position(position), lookAt(lookAt), rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
	rotation = fromAxisAngle(Vector3(0.f, 1.f, 0.f), deg_2_rad(yrot));
	rotation *= fromAxisAngle(Vector3(1.f, 0.f, 0.f), deg_2_rad(xrot));
}

void Camera::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
}

void Camera::Resize(int width, int height)
{
	if (height <= 0)
		height = 1;

	int aspectratio = width / height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspectratio, 0.2f, 255.0f);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(position.x, position.y, position.z);
}

const Vector3& Camera::GetPosition() const
{
    return position;
}

const Quaternion& Camera::GetRotation() const
{
    return rotation;
}

Matrix4 Camera::GetViewMatrix() const
{
	//Matrix4 view = toMatrix(rotation);
	//return toMatrix(rotation);
	return buildLookAt();
}

void Camera::movex(float xmod)
{
	position += rotation * Vector3(xmod, 0.0f, 0.0f);
}

void Camera::movey(float ymod)
{
	position.y -= ymod;
}

void Camera::movez(float zmod)
{
	position += rotation * Vector3(0.0f, 0.0f, -zmod);
}

void Camera::rotatex(float xmod)
{
	Quaternion nrot(1.0f, 0.0f, 0.0f, deg_2_rad(xmod));
	rotation = rotation * nrot;
}

void Camera::rotatey(float ymod)
{
	Quaternion nrot(0.0f, 1.0f, 0.0f, deg_2_rad(ymod));
	rotation = nrot * rotation;
}

void Camera::update(float xrot, float yrot, float xmove, float ymove, float zmove, float delta)
{
	if (xrot != 0.0f)
	{
		rotatex(xrot * delta * rotspeed);
	}

	if (yrot != 0.0f) 
	{
		rotatey(yrot * delta * rotspeed);
	}

	if (xmove != 0.0f) 
	{
		movex(xmove * delta * movespeed);
	}

	if (ymove != 0.0f) 
	{
		movey(ymove * delta * movespeed);
	}

	if (zmove != 0.0f) 
	{
		movez(zmove * delta * movespeed);
	}
}

void Camera::render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)buildLookAt().matrix);
	glTranslatef(position.x, position.y, position.z);

// 	glBegin(GL_TRIANGLES);
// 	glColor3f(1.0f, 0.0f, 0.0f);
// 	glVertex3f(-1.0f, -0.5f, 0.0f);    // A
// 	glColor3f(0.0f, 1.0f, 0.0f);
// 	glVertex3f( 1.0f, -0.5f, 0.0f);    // B
// 	glColor3f(0.0f, 0.0f, 1.0f);
// 	glVertex3f( 0.0f,  0.5f, 0.0f);    // C
// 	glEnd();
}

Matrix4 Camera::buildLookAt() const
{
	Vector3 up(0.f, 1.f, 0.f);
	Vector3 forward = normalize(lookAt - position);
	Vector3 right = normalize(cross(up, forward));
	up = cross(forward, right);

	return Matrix4(right.x, up.x, forward.x, 0, 
					right.y, up.y, forward.y, 0, 
					right.z, up.z, forward.z, 0, 
					-dot(right, position), -dot(up, position), -dot(forward, position), 1);
}