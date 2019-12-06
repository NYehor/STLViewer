#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "GLRenderSystem.h"

GLRenderSystem rs;

void renderScene(GLRenderSystem& rs)
{
	std::vector<Vertex> vec;
	vec.push_back({ glm::vec3{ -0.5f, -0.5f, 0.0f },glm::vec3{0,0,0},  glm::vec3{ 1.0f, 0.0, 0.0 } });
	vec.push_back({ glm::vec3{ -0.5f, 0.5f, 0.0f },glm::vec3{0,0,0},  glm::vec3{ 1.0f, 0.0, 0.0 } });
	vec.push_back({ glm::vec3{ 0.5f, -0.5f, 0.0f }, glm::vec3{0,0,0}, glm::vec3{ 1.0f, 0.0, 0.0 } });

	vec.push_back({ glm::vec3{ 0.5f, 0.5f, 0.0f },glm::vec3{0,0,0},  glm::vec3{ 0.0f, 0.0, 1.0f } });
	vec.push_back({ glm::vec3{ -0.5f, 0.5f, 0.0f },glm::vec3{0,0,0},  glm::vec3{ 0.0f, 0.0, 1.0f } });
	vec.push_back({ glm::vec3{ 0.5f, -0.5f, 0.0f }, glm::vec3{0,0,0}, glm::vec3{ 0.0f, 0.0, 1.0f } });
	rs.renderTriangleSoup(vec);

	// rs.renderLines(vec);
}

void moveCube(GLRenderSystem& rs, glm::vec3 offset)
{

}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP)
		moveCube(rs, glm::vec3{ 0, 5, 0 });
	if (key == KeyCode::DOWN)
		moveCube(rs, glm::vec3{ 0, -5, 0 });
	if (key == KeyCode::LEFT)
		moveCube(rs, glm::vec3{ 5, 0, 0 });
	if (key == KeyCode::RIGHT)
		moveCube(rs, glm::vec3{ -5, 0, 0 });
}

int main()
{
	glfwInit();
	GLWindow window("myWindow", 640, 480);
	window.setKeyCallback(onKeyCallback);

	rs.init();
	rs.setupLight(0, glm::vec3{ 0, 5, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0,0,1 });
	rs.turnLight(0, true);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3{ 0.0f, 0.0f, -10.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f,1.0f,0.0f });
	rs.setViewMatrix(viewMatrix);

	glm::mat4 projMatrix = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 500.f);
	rs.setProjMatrix(projMatrix);

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
