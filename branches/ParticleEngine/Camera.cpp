
#include "Camera.h"
#include "Matrix.h"
#include "MathUtil.h"

#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

Camera::Camera(const Vector3& position, const Quaternion& rotation)
: m_position(position), m_rotation(rotation), 
  m_translationVelocity(0.01f), m_rotationVelocity(0.05f),
  m_viewMatrix(Matrix4::Identity())
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

const Matrix4& Camera::GetViewMatrix()
{
	// update the view matrix
	UpdateView();

	return m_viewMatrix;
}

Vector3 Camera::GetUp() const
{
	return m_rotation * Vector3::UnitY();
}

Vector3 Camera::GetRight() const
{
	return m_rotation * Vector3::UnitX();
}

Vector3 Camera::GetLookAt() const
{
	// always looking down the -z axis
	return m_rotation * -Vector3::UnitZ();
}

void Camera::Translate(const Vector3& translation)
{
	m_position += translation * m_translationVelocity;
}

void Camera::LookAt(const Vector3& direction)
{
	// TODO - need to implement
}

void Camera::Pitch(float angle)
{
	Vector3 xaxis = m_rotation * Vector3::UnitX();
	Rotate(xaxis, angle);
}

void Camera::Yaw(float angle)
{
	Vector3 yaxis = m_rotation * Vector3::UnitY();
	Rotate(yaxis, angle);
}

void Camera::Roll(float angle)
{
	Vector3 zaxis = m_rotation * Vector3::UnitZ();
	Rotate(zaxis, angle);
}

void Camera::Rotate(const Vector3& axis, float angle)
{
	Quaternion rotQ = FromAxisAngle(axis, angle);
	Rotate(rotQ);
}

void Camera::Rotate(const Quaternion& rotQ)
{
	Quaternion normQ = Normalize(rotQ);
	m_rotation = normQ * m_rotation;
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

	// process yaw first
	Yaw(yaw);
	Pitch(pitch);

	// create quaternion from pitch and yaw
// 	Quaternion pitchQuat = fromAxisAngle(Vector3(1.f, 0.f, 0.f), pitch);
// 	Quaternion yawQuat = fromAxisAngle(Vector3(0.f, 1.f, 0.f), yaw);
// 
// 	m_rotation = yawQuat * pitchQuat;
}

void Camera::UpdateView()
{
	// TODO - this should check whether the view needs to be updated
	//		  before performing update

	// create matrix for position
	Matrix4 posMatrix = Matrix4::Identity();
	posMatrix.matrix[12] = -m_position.x;
	posMatrix.matrix[13] = -m_position.y;
	posMatrix.matrix[14] = -m_position.z;

	// create rotation matrix
	Matrix4 conjRotMatrix = ToMatrix(Conjugate(m_rotation));

	m_viewMatrix = posMatrix * conjRotMatrix;
}

void Camera::Render()
{
	const Matrix4& viewMatrix = GetViewMatrix();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)viewMatrix.matrix);
	//glMultMatrixf((GLfloat*)GetViewMatrix().matrix);
	//glTranslatef(-m_position.x, -m_position.y, -m_position.z);
}