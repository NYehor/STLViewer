#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <iostream>
#include "GLRenderSystem.h"

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if(action == Action::Press)
		std::cout << "Key " << glfwGetKeyName(static_cast<int>(key), 0) << " is pressed." << std::endl;
}

void renderScene(GLRenderSystem& rs)
{
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0, 0.0);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

}

int main()
{
	glfwInit();
	GLRenderSystem rs;
	GLWindow window("myWindow", 640, 480);
	window.setKeyCallback(onKeyCallback);

	// rs.init();

	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		rs.setViewport(0, 0, window.getWidth(), window.getHeight());
		rs.clearDisplay(0.5f, 0.5f, 0.5f);
		renderScene(rs);

		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}

