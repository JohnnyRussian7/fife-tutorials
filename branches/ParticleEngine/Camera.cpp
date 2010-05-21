
#include "Camera.h"
#include "Matrix.h"
#include "MathUtil.h"

#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

Camera::Camera(const Vector3& position)
: m_position(0.f, 0.f, 0.f), m_rotation(0.0f, 0.0f, 0.0f, 1.0f), 
  m_translationVelocity(0.001f), m_rotationVelocity(0.05f)
{

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
    glFrustum(-0.5, 0.5, -aspectratio*0.5, aspectratio*0.5, 1, 5000);
	//gluPerspective(45.0f, aspectratio, 0.2f, 255.0f);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::SetTranslationVelocity(float velocity)
{
	m_translationVelocity = velocity;
}

void Camera::SetRotationVelocity(float velocity)
{
	m_rotationVelocity = velocity;
}

const Vector3& Camera::GetPosition() const
{
    return m_position;
}

const Quaternion& Camera::GetRotation() const
{
    return m_rotation;
}

Matrix4 Camera::GetViewMatrix() const
{
	return toMatrix(conjugate(m_rotation));
}

void Camera::Translate(const Vector3& translation)
{
	m_position += /*m_rotation * */(translation * m_translationVelocity);
}

void Camera::Rotate(float xrot, float yrot, float zrot)
{
	pitch += (xrot * m_rotationVelocity);
	yaw += (yrot * m_rotationVelocity);
	//roll += (zrot * m_rotationVelocity);

	if (pitch > pi)
	{
		pitch -= pi;
	}
	else if (pitch < -pi)
	{
		pitch += pi;
	}

	if (yaw > 2*pi)
	{
		yaw -= 2*pi;
	}
	else if (yaw < -2*pi)
	{
		yaw += 2*pi;
	}

	// create quaternion from pitch and yaw
	Quaternion pitchQuat = fromAxisAngle(Vector3(1.f, 0.f, 0.f), pitch);
	Quaternion yawQuat = fromAxisAngle(Vector3(0.f, 1.f, 0.f), yaw);

	m_rotation = yawQuat * pitchQuat;
}

// void Camera::rotatex(float xmod)
// {
// 	Quaternion nrot(1.0f, 0.0f, 0.0f, DegToRad(xmod));
// 	m_rotation = m_rotation * nrot;
// }
// 
// void Camera::rotatey(float ymod)
// {
// 	Quaternion nrot(0.0f, 1.0f, 0.0f, DegToRad(ymod));
// 	m_rotation = nrot * m_rotation;
// }

void Camera::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)GetViewMatrix().matrix);
	//glMultMatrixf((GLfloat*)GetViewMatrix().matrix);
	glTranslatef(-m_position.x, -m_position.y, -m_position.z);
}
