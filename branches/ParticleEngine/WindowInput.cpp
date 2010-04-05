
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

	mouseX = pt.x;
	mouseY = pt.y;

	deltaMouseX = float(mouseX - centerX);
	deltaMouseY = float(mouseY - centerY);

	camera.Rotate(deltaMouseX, deltaMouseY, 0.f);

// 	if(mouseX < centerX)
// 	{
// 		deltaMouse = float(centerX - mouseX);
// 
// 		camera.rotate
// 		//camera.ChangeHeading(-0.2f * deltaMouse);
// 
// 	}
// 	else if(mouseX > centerX)
// 	{
// 		deltaMouse = float(mouseX - centerX);
// 
// 		//camera.ChangeHeading(0.2f * deltaMouse);
// 	}
// 
// 	if(mouseY < centerY)
// 	{
// 		deltaMouse = float(centerY - mouseY);
// 
// 		//camera.ChangePitch(-0.2f * deltaMouse);
// 	}
// 	else if(mouseY > centerY)
// 	{
// 		deltaMouse = float(mouseY - centerY);
// 
// 		//camera.ChangePitch(0.2f * deltaMouse);
// 	}

	//mouseX = centerX;
	//mouseY = centerY;

	SetCursorPos(centerX, centerY);
}

void WindowInput::CheckKeyboard(bool keys[])
{
	float xrotation = 0.f;
	float yrotation = 0.f;

	if(keys[VK_UP])
	{
		xrotation = 5.f;	
		//camera.ChangePitch(5.0f);
	}
	else if(keys[VK_DOWN])
	{
		xrotation = -5.f;
		//camera.ChangePitch(-5.0f);
	}

	if(keys[VK_LEFT])
	{
		yrotation = -5.f;
		//camera.ChangeHeading(-5.0f);
	}

	if(keys[VK_RIGHT])
	{
		yrotation = 5.f;
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

	camera.Rotate(xrotation, yrotation, 0.f);
}