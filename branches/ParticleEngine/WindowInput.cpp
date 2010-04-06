
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "WindowInput.h"
#include "Camera.h"
#include "MathUtil.h"

WindowInput::WindowInput(int windowWidth, int windowHeight, Camera& camera)
: camera(camera), centerX(windowWidth/2), centerY(windowWidth/2), mouseX(0), mouseY(0), 
  m_angleX(0.f), m_angleY(0.f), m_mouseSensitivity(1000000)
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
	float deltaMouseX;
	float deltaMouseY;
	POINT pt;

	GetCursorPos(&pt);

	int prevMouseX = mouseX;
	int prevMouseY = mouseY;

	mouseX = pt.x;
	mouseY = pt.y;

	m_angleX += float(centerY - mouseY) / m_mouseSensitivity;
	m_angleY += float(centerX - mouseX) / m_mouseSensitivity;
	//deltaMouseX = float(mouseX - centerX);
	//deltaMouseY = float(mouseY - centerY);

	if (mouseX != prevMouseX || mouseY != prevMouseY)
	{
		camera.Rotate(m_angleX, m_angleY, 0.f);
	}

	SetCursorPos(centerX, centerY);
}

void WindowInput::CheckKeyboard(bool keys[])
{
	bool keydown = false;
	float xrotation = 0.f;
	float yrotation = 0.f;

	if(keys[VK_UP])
	{
		xrotation = pi/8;	
		keydown = true;
		//camera.ChangePitch(5.0f);
	}
	else if(keys[VK_DOWN])
	{
		xrotation = -pi/8;
		keydown = true;
		//camera.ChangePitch(-5.0f);
	}

	if(keys[VK_LEFT])
	{
		yrotation = pi/8;
		keydown = true;
		//camera.ChangeHeading(-5.0f);
	}

	if(keys[VK_RIGHT])
	{
		yrotation = -pi/8;
		keydown = true;
		//camera.ChangeHeading(5.0f);
	}

	if(keys['W'] == TRUE)
	{
		camera.Translate(Vector3(0.f, 0.f, 1.f));
		//camera.ChangeVelocity(0.1f);	
	}

	if(keys['S'] == TRUE)
	{
		camera.Translate(Vector3(0.f, 0.f, -1.f));
		//camera.ChangeVelocity(-0.1f);
	}

	if (keydown)
	{
		camera.Rotate(xrotation, yrotation, 0.f);
	}
}