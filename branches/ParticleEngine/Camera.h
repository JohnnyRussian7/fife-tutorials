
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

class Camera
{
public:
	Camera(const Vector3& position = Vector3(0.f, 0.f, 0.f),
			const Quaternion& rotation = Quaternion());

	void Init();
	void Resize(int width, int height);

	void SetTranslationVelocity(float velocity);
	void SetRotationVelocity(float velocity);

    const Vector3& GetPosition() const;
    const Quaternion& GetRotation() const;
	const Matrix4& GetViewMatrix();

	Vector3 GetUp() const;
	Vector3 GetRight() const;
	Vector3 GetLookAt() const;

	void Translate(const Vector3& translation);
	void LookAt(const Vector3& direction);

	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);
	void Rotate(const Vector3& axis, float angle);
	void Rotate(float xrot, float yrot, float zrot);
	void Rotate(const Quaternion& rotQ);

	void UpdateView();

	void Render();

private:
	float pitch;
	float yaw;
	Vector3 m_position;
	Quaternion m_rotation;
	float m_translationVelocity;
	float m_rotationVelocity;
	Matrix4 m_viewMatrix;
};

#endif
