#include "CInput.h"

GLFWwindow* CInput::mpWindow = 0;

void CInput::Init(GLFWwindow* w){
	mpWindow = w;
}

void CInput::GetMousePos(int *px, int*py)
{
	double xpos, ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = xpos;
	*py = ypos;
	return;
}