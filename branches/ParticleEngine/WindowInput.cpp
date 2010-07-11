
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "WindowInput.h"
#include "Camera.h"
#include "MathUtil.h"

WindowInput::WindowInput(int windowWidth, int windowHeight, Camera& camera)
: camera(camera), centerX(windowWidth/2), centerY(windowWidth/2), mouseX(0), mouseY(0), 
  m_angleX(0.f), m_angleY(0.f), m_mouseSensitivity(100)
{

}

void WindowInput::SetWindowWidth(int width)
{
	centerX = width/2;
}

void WindowInput::SetWindowHeight(int height)
{
	centerY = height/2;
}

void WindowInput::ReadInput(bool keys[])
{
	CheckMouse();
	CheckKeyboard(keys);
}

void WindowInput::CheckMouse(void)
{
	float pitch = 0.0;
	float heading = 0.0;
	POINT pt;
	bool isActive = false;

	GetCursorPos(&pt);

	if (mouseY != pt.y)
	{
		pitch += float(mouseY - pt.y) / m_mouseSensitivity;

		mouseY = pt.y;

		isActive = true;
	}

	if (mouseX != pt.x)
	{
		heading += float(mouseX - pt.x) / m_mouseSensitivity;

		mouseX = pt.x;

		isActive = true;
	}

	if (isActive)
	{
		camera.Rotate(pitch, heading, 0.f);
	}
}

void WindowInput::CheckKeyboard(bool keys[])
{
	bool shouldYaw = false;
	bool shouldPitch = false;
	float xrotation = 0.f;
	float yrotation = 0.f;

	if(keys[VK_UP])
	{
        camera.Translate(Vector3(0.f, 1.f, 0.f));
	}
	else if(keys[VK_DOWN])
	{
        camera.Translate(Vector3(0.f, -1.f, 0.f));
	}

    if(keys[VK_LEFT])
    {
        camera.Translate(Vector3(-1.f, 0.f, 0.f));
    }
    else if(keys[VK_RIGHT])
    {
        camera.Translate(Vector3(1.f, 0.f, 0.f));
    }

    if(keys['W'])
    {
        // rotate up
        xrotation = pi/4;
        shouldPitch = true;
    }
    else if(keys['S'])
    {
        // rotate down
        xrotation = -pi/4;
        shouldPitch = true;
    }

	if(keys['A'])
	{
        // rotation left
		yrotation = pi/4;
		shouldYaw = true;
	}
	else if(keys['D'])
	{
        // rotate right
		yrotation = -pi/4;
		shouldYaw = true;
	}

	if(keys['I'] == TRUE)
	{
        // zoom in
		camera.Translate(Vector3(0.f, 0.f, -1.f));
	}

	if(keys['O'] == TRUE)
	{
        // zoom out
		camera.Translate(Vector3(0.f, 0.f, 1.f));
	}

	if (shouldYaw)
	{
		if (yrotation > 2*pi)
		{
			yrotation -= 2*pi;
		}
		else if (yrotation < -2*pi)
		{
			yrotation += 2*pi;
		}

		camera.Yaw(yrotation);
	}

	if (shouldPitch)
	{
		if (xrotation > pi)
		{
			xrotation -= pi;
		}
		else if (xrotation < -pi)
		{
			xrotation += pi;
		}

		camera.Pitch(xrotation);
	}
}