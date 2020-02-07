#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <iostream>
#include "Scene.h"
#include "Startup.h"
#include "Callbacks.h"

size_t width = 840;
size_t height = 680;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLWindow window("myWindow", width, height);

	GLRenderSystem renderSystem("VertexShader.glsl", "FragmentShader.glsl");
	renderSystem.init();
	renderSystem.setupLight(0, glm::vec3{ -5,0,0 }, glm::vec3{ 0.5,  0.5, 0.5 }, 
								glm::vec3{ 0.6,0.6,0.6 }, glm::vec3{ 0.5, 0.5,0.5 });
	renderSystem.turnLight(0, true);

	Viewport viewport;
	viewport.setViewportSize(width, height);
	viewport.setFOV(60.f);
	viewport.setZNear(0.01f);
	viewport.setZFar(500.f);

	Scene scene(renderSystem);
	scene.addModel("teapot.stl", {0.5,0,0});
	scene.addModel("teapot.stl", {0,0.5,0});

	Callbacks callbacks(viewport, scene, window);

	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		renderSystem.setViewport(0, 0, window.getWidth(), window.getHeight());
		renderSystem.clearDisplay(0, 0, 0);
		renderSystem.setViewMatrix(viewport.getCamera().calcViewMatrix());
		renderSystem.setProjMatrix(viewport.calcProjectionMatrix());
		renderSystem.getShader().use();
		scene.draw();

		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}
