
#include "Camera.h"
#include "Matrix.h"
#include "Vector.h"
#include "MathUtil.h"

#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

Camera::Camera(const Vector3& position, const Quaternion& rotation)
: m_position(position), m_orientation(rotation), 
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

const Quaternion& Camera::GetOrientation() const
{
    return m_orientation;
}

const Matrix4& Camera::GetViewMatrix()
{
	// update the view matrix
	UpdateView();

	return m_viewMatrix;
}

Vector3 Camera::GetUp() const
{
	return m_orientation * Vector3::UnitY();
}

Vector3 Camera::GetRight() const
{
	return m_orientation * Vector3::UnitX();
}

Vector3 Camera::GetLookAt() const
{
	// always looking down the -z axis
	return m_orientation * -Vector3::UnitZ();
}

void Camera::Translate(const Vector3& translation)
{
	// translate in world space
	m_position += translation * m_translationVelocity;

	// TODO - implement translate in local space, using algorithm below 
	//m_position += m_orientation * (translation * m_translationVelocity);
}

void Camera::LookAt(const Vector3& target)
{
	Vector3 direction = -(target - m_position);

	// nothing to do if direction is zero vector
	if (direction == Vector3::Zero())
	{
		return;
	}

	// always looking down negative z-axis so need to 
	// negate and normalize direction vector
	Vector3 normDirection = Normalize(-direction);

	// get z-axis of current rotation
	Vector3 zAxis = ZAxis(m_orientation);

	// get shortest rotation arc to direction
	Quaternion rotation = GetRotationTo(zAxis, normDirection);

	m_orientation = rotation * m_orientation;
}

void Camera::Pitch(float angle)
{
	Vector3 xaxis = m_orientation * Vector3::UnitX();
	Rotate(xaxis, angle);
}

void Camera::Yaw(float angle)
{
	Vector3 yaxis = m_orientation * Vector3::UnitY();
	Rotate(yaxis, angle);
}

void Camera::Roll(float angle)
{
	Vector3 zaxis = m_orientation * Vector3::UnitZ();
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
	m_orientation = normQ * m_orientation;
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
	Matrix4 conjRotMatrix = ToMatrix(Conjugate(m_orientation));

	m_viewMatrix = posMatrix * conjRotMatrix;
}

void Camera::Render()
{
	const Matrix4& viewMatrix = GetViewMatrix();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)viewMatrix.matrix);
}
