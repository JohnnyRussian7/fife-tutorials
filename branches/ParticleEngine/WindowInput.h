#ifndef WINDOW_INPUT_H_
#define WINDOW_INPUT_H_

class Camera;

class WindowInput
{
public:
	WindowInput(int windowWidth, int windowHeight, Camera& camera);
	void ReadInput(bool keys[]);
	void SetWindowWidth(int width);
	void SetWindowHeight(int height);
private:
	void CheckMouse();
	void CheckKeyboard(bool keys[]);

private:
	Camera& camera;
	int centerX;
	int centerY;
	int mouseX;
	int mouseY;
};

#endif

