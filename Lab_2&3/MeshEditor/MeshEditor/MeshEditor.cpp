#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "GLRenderSystem.h"
#include "STLParser.h"
#include "Viewport.h";
#include "Model.h";
#include "Scene.h"
#include "Octree.h"

size_t width = 840;
size_t height = 680;

Viewport viewport;

GLRenderSystem& getRS()
{
	static GLRenderSystem rs("VertexShader.glsl", "FragmentShader.glsl");
	return rs;
}


void moveCamera(Camera& camera, glm::vec3 offset)
{
	camera.translate(offset * 0.5f);
}

void moveCube(GLRenderSystem& rs, glm::vec3 offset)
{

}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP && Action::Press == action)
		moveCube(getRS(), glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::DOWN && Action::Press == action)
		moveCube(getRS(), glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::LEFT && Action::Press == action)
		moveCube(getRS(), glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::RIGHT && Action::Press == action)
		moveCube(getRS(), glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::W && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::S && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::A && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::D && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::F1 && Action::Press == action)
		viewport.getCamera().setFrontView();
	if (key == KeyCode::F2 && Action::Press == action)
		viewport.getCamera().setRearView();
	if (key == KeyCode::F3 && Action::Press == action)
		viewport.getCamera().setRightView();
	if (key == KeyCode::F4 && Action::Press == action)
		viewport.getCamera().setLeftView();
	if (key == KeyCode::F5 && Action::Press == action)
		viewport.getCamera().setTopView();
	if (key == KeyCode::F6 && Action::Press == action)
		viewport.getCamera().setBottomView();
	if (key == KeyCode::F7 && Action::Press == action)
		viewport.getCamera().setIsoView();

	if (key == KeyCode::F8 && Action::Press == action)
		viewport.setParallelProjection(true);
	if (key == KeyCode::F9 && Action::Press == action)
		viewport.setParallelProjection(false);
}

int lastMX = 0, lastMY = 0, curMX = 0, curMY = 0;
bool arcballOn = false;

glm::vec3 getArcballVector(float x, float y)
{
	glm::vec3 p = glm::vec3(x / (0.5 * (float)width) - 1.f,  y / (0.5 * (float)height) - 1.f, 0.f);
	p.y = - p.y;

	float length = p.x * p.x + p.y * p.y;
	if (length >= 1.0f)
		p = glm::normalize(p);
	else
		p.z = sqrt(1.0f - length);
	return p;
}

void onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y)
{
	if (ButtonCode::Button_LEFT == button && Action::Press == action)
	{
		arcballOn = true;
		lastMX = curMX = x;
		lastMY = curMY = y;
	}
	else
	{
		arcballOn = false;
	}
	auto r = viewport.calcCursorRay(lastMX, lastMY);
}

void onMouseMove(double x, double y)
{
	if (arcballOn)
	{
		curMX = x;
		curMY = y;

		if (curMX != lastMX || curMY != lastMY)
		{
			auto a = getArcballVector((float) lastMX, (float) lastMY);
			auto b = getArcballVector((float) curMX, (float) curMY);

			viewport.getCamera().orbit(a, b);

			lastMX = curMX;
			lastMY = curMY;
		}
	}

}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLWindow window("myWindow", width, height);

	viewport.setViewportSize(width, height);
	viewport.setFOV(60.f);
	viewport.setZNear(0.01f);
	viewport.setZFar(500.f);

	window.setKeyCallback(onKeyCallback);
	window.setMouseCallback(onMouseInput);
	window.setCursorPosCallback(onMouseMove);

	getRS().init();
	getRS().setupLight(0, glm::vec3{ -5,0,0 }, glm::vec3{ 0.5,  0.5, 0.5 }, glm::vec3{ 0.6,0.6,0.6 }, glm::vec3{ 0.5, 0.5,0.5 });
	getRS().turnLight(0, true);

	Scene scene(getRS());
	scene.addModel("teapot.stl");

	
	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		getRS().setViewport(0, 0, window.getWidth(), window.getHeight());
		getRS().clearDisplay(0, 0, 0);

		getRS().setViewMatrix(viewport.getCamera().calcViewMatrix());
		getRS().setProjMatrix(viewport.calcProjectionMatrix());
		getRS().getShader().use();
		scene.draw();
		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}
