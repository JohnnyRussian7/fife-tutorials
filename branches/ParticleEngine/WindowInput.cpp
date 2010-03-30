
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "WindowInput.h"
#include "Camera.h"

WindowInput::WindowInput(int windowWidth, int windowHeight, Camera& camera)
: camera(camera), centerX(windowWidth/2), centerY(windowWidth/2), mouseX(0), mouseY(0)
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

void WindowInput::ReadInput()
{
	CheckMouse();
	CheckKeyboard();
}

void WindowInput::CheckMouse(void)
{
	float deltaMouse;
	POINT pt;

	GetCursorPos(&pt);

	mouseX = pt.x;
	mouseY = pt.y;

	if(mouseX < centerX)
	{
		deltaMouse = float(centerX - mouseX);

		//camera.ChangeHeading(-0.2f * deltaMouse);

	}
	else if(mouseX > centerX)
	{
		deltaMouse = float(mouseX - centerX);

		//camera.ChangeHeading(0.2f * deltaMouse);
	}

	if(mouseY < centerY)
	{
		deltaMouse = float(centerY - mouseY);

		//camera.ChangePitch(-0.2f * deltaMouse);
	}
	else if(mouseY > centerY)
	{
		deltaMouse = float(mouseY - centerY);

		//camera.ChangePitch(0.2f * deltaMouse);
	}

	mouseX = centerX;
	mouseY = centerY;

	SetCursorPos(centerX, centerY);
}

void WindowInput::CheckKeyboard(void)
{
	if(keys[VK_UP])
	{
		//camera.ChangePitch(5.0f);
	}

	if(keys[VK_DOWN])
	{
		//camera.ChangePitch(-5.0f);
	}

	if(keys[VK_LEFT])
	{
		//camera.ChangeHeading(-5.0f);
	}

	if(keys[VK_RIGHT])
	{
		//camera.ChangeHeading(5.0f);
	}

	if(keys['W'] == TRUE)
	{
		//camera.ChangeVelocity(0.1f);	
	}

	if(keys['S'] == TRUE)
	{
		//camera.ChangeVelocity(-0.1f);
	}
}