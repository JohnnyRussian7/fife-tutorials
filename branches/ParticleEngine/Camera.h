
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.h"
#include "Quaternion.h"

class Camera
{
public:
	Camera(float rotspeed, float movespeed);

	void Init();
	void Resize(int width, int height);

    const Vector3& GetPosition() const;
    const Quaternion& GetRotation() const;
	Matrix4 GetViewMatrix() const;

	void Camera::movex(float xmod);
	void Camera::movey(float ymod);
	void Camera::movez(float zmod);
	void Camera::rotatex(float xmod);
	void Camera::rotatey(float ymod);
	void update(float xrot, float yrot, float xmove, float ymove, float zmove, float delta=1.f);
	void render();

private:
	Vector3 position;
	Quaternion rotation;

	float rotspeed;
	float movespeed;
};

#endif
