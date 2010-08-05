
#ifndef CAMERA_H_
#define CAMERA_H_

#include <string>

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

class Camera
{
public:
	Camera(const char* name, const Vector3& position = Vector3::Zero(),
            const Quaternion& orientation = Quaternion::Identity());

    const char* GetName() const;

    const Vector3& GetPosition() const;
    const Quaternion& GetOrientation() const;
	const Matrix4& GetViewMatrix();

	Vector3 GetUp() const;
	Vector3 GetRight() const;
	Vector3 GetLookAt() const;

	void Translate(const Vector3& translation);
	void LookAt(const Vector3& target);

	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
	void Rotate(const Vector3& axis, float angle);
	void Rotate(const Quaternion& rotQ);

	void UpdateView();

private:
    std::string m_name;
	Vector3 m_position;
	Quaternion m_orientation;
    Matrix4 m_viewMatrix;
};

#endif
