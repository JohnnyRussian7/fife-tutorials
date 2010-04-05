
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.h"
#include "Quaternion.h"

class Camera
{
public:
	Camera(const Vector3& position);

	void Init();
	void Resize(int width, int height);

	void SetTranslationVelocity(float velocity);
	void SetRotationVelocity(float velocity);

    const Vector3& GetPosition() const;
    const Quaternion& GetRotation() const;
	Matrix4 GetViewMatrix() const;

	void Translate(const Vector3& translation);
	void Rotate(float xrot, float yrot, float zrot);
	void Render();

private:
	float pitch;
	float yaw;
	Vector3 m_position;
	Quaternion m_rotation;
	float m_translationVelocity;
	float m_rotationVelocity;
};

#endif
