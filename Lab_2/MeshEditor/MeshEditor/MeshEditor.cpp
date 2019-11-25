#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <iostream>


void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	std::cout << "Key " << glfwGetKeyName(static_cast<int>(key), 0) << " is pressed." << std::endl;
}

int main()
{
	glfwInit();
	GLWindow window("myWindow", 640, 480);

	window.setKeyCallback(onKeyCallback);

	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}

