#ifndef WINDOW_INPUT_H_
#define WINDOW_INPUT_H_

class Camera;

class WindowInput
{
public:
	WindowInput(int windowWidth, int windowHeight, Camera& camera);
	void ReadInput();
	void SetWindowWidth(int width);
	void SetWindowHeight(int height);
private:
	void CheckMouse();
	void CheckKeyboard();

private:
	static bool keys[256];
	Camera& camera;
	int centerX;
	int centerY;
	int mouseX;
	int mouseY;
};

#endif

