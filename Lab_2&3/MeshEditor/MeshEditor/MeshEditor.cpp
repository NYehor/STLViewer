#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "GLRenderSystem.h"
#include "STLParser.h"
#include "Viewport.h";

size_t width = 640;
size_t height = 480;
GLRenderSystem rs;
Viewport viewport;

std::vector<Vertex> renderObject;

void renderScene(GLRenderSystem& rs)
{
	rs.renderTriangleSoup(renderObject);
}

void moveCamera(Camera& camera, glm::vec3 offset)
{
	camera.translate(offset * 0.5f);
}

void moveCube(GLRenderSystem& rs, glm::vec3 offset)
{
	auto model = rs.getWorldMatrix();
	model = glm::translate(model, offset * 0.5f);
	rs.setWorldMatrix(model);
}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::DOWN && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::LEFT && Action::Press == action)
		moveCube(rs, glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::RIGHT && Action::Press == action)
		moveCube(rs, glm::vec3{ 1, 0, 0 });
	if (key == KeyCode::W && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, 0, 1 });
	if (key == KeyCode::S && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, 0, -1 });

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
		viewport.getCamera().setTopView();
	if (key == KeyCode::F3 && Action::Press == action)
		viewport.getCamera().setRearView();
	if (key == KeyCode::F4 && Action::Press == action)
		viewport.getCamera().setRightView();
	if (key == KeyCode::F5 && Action::Press == action)
		viewport.getCamera().setLeftView();
	if (key == KeyCode::F6 && Action::Press == action)
		viewport.getCamera().setBottomView();
	if (key == KeyCode::F7 && Action::Press == action)
		viewport.getCamera().setIsoView();

	if (key == KeyCode::F8 && Action::Press == action)
	{
		rs.turnLight(0, false);
		rs.setWorldMatrix(glm::scale(glm::mat4(1.f), glm::vec3(280)));
		viewport.setParallelProjection(true);
	}
	if (key == KeyCode::F9 && Action::Press == action)
	{
		rs.turnLight(0, true);
		rs.setWorldMatrix(glm::mat4(1.0f));
		viewport.setParallelProjection(false);
	}

}

int lastMX = 0, lastMY = 0, curMX = 0, curMY = 0;
bool arcballOn = false;

glm::vec3 getArcballVector(float x, float y)
{
	glm::vec3 p = glm::vec3(x / (float)width * 2.f - 1, y / (float)height * 2.f - 1.f, 0.f);
	p.y = p.y;

	if (glm::length(p) >= 1.0f)
		p = glm::normalize(p);
	else
		p.z = sqrt(1.0f - p.x * p.x - p.y * p.y);
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
	STLParser parser;
	renderObject = parser.read("teapot.stl");

	glfwInit();
	GLWindow window("myWindow", width, height);

	viewport.setViewportSize(width, height);
	viewport.setFOV(60.f);
	viewport.setZNear(0.01f);
	viewport.setZFar(500.f);

	window.setKeyCallback(onKeyCallback);
	window.setMouseCallback(onMouseInput);
	window.setCursorPosCallback(onMouseMove);

	rs.init();
	rs.setupLight(0, glm::vec3{ 0,-5,0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0,0,1 });
	rs.turnLight(0, true);


	while (!glfwWindowShouldClose(window.getGLFWHandle()))
	{
		rs.setViewport(0, 0, window.getWidth(), window.getHeight());
		rs.clearDisplay(0.5f, 0.5f, 0.5f);

		rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
		rs.setProjMatrix(viewport.calcProjectionMatrix());
		renderScene(rs);
		glfwSwapBuffers(window.getGLFWHandle());
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}
