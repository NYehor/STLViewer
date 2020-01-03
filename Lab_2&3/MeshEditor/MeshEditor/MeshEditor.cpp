#include "GLWindow.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "GLRenderSystem.h"
#include "STLParser.h"


GLRenderSystem rs;
std::vector<Vertex> renderObject;


glm::vec3 setNormal(glm::vec3 A, glm::vec3 B, glm::vec3 C)
{
	return glm::normalize(glm::cross(C - A, B - A));
}

std::vector<Vertex> fillVec(float teta, float incPhi, float radious, int slices)
{
	std::vector<Vertex> vec = std::vector<Vertex>(slices);

	const float PI = 3.14159265;
	float phi = 0;
	for (size_t i = 0; i < slices; i++)
	{

		float x = radious * sin(teta * PI / 180) * cos(phi * PI / 180);
		float y = radious * sin(teta * PI / 180) * sin(phi * PI / 180);
		float z = radious * cos(teta * PI / 180);
		phi += incPhi;

		vec[i].position = glm::vec3{ x,y,z };
		vec[i].normal = glm::vec3{ x,y,z };
		vec[i].color = glm::vec3{ cos((double)i / slices), sin((double)i / slices),0 };
		/*vec[i].color = glm::vec3{ 1, 0, 0 };
		if (i%3==2)
		{
			glm::vec3 normal = setNormal(vec[i - 2].position, vec[i - 1].position, vec[i].position);
			vec[i].normal = normal;
			vec[i - 2].normal = normal;
			vec[i - 1].normal = normal;
		}*/
	}

	return vec;
}

std::vector<Vertex> getSphere()
{
	std::vector<Vertex> arrayOfVertexs = std::vector<Vertex>();
	float radious = 1;
	int slices = 8;
	int rings = 8;

	std::vector<Vertex> currentVertexs = std::vector<Vertex>(slices);
	std::vector<Vertex> nextVertexs = std::vector<Vertex>(slices);

	float incTeta = 180.0 / (rings + 1.0);
	float  incPhi = 360.0 / slices;

	float teta = 0;

	currentVertexs = fillVec(teta, incPhi, radious, slices);


	for (float teta = incTeta; teta <= 180.0; teta += incTeta)
	{
		nextVertexs = currentVertexs;
		currentVertexs = fillVec(teta, incPhi, radious, slices);

		for (size_t j = 0; j < slices - 1; j++)
		{
			arrayOfVertexs.push_back(currentVertexs[j + 1]);
			arrayOfVertexs.push_back(nextVertexs[j + 1]);
			arrayOfVertexs.push_back(nextVertexs[j]);

			arrayOfVertexs.push_back(currentVertexs[j]);
			arrayOfVertexs.push_back(currentVertexs[j + 1]);
			arrayOfVertexs.push_back(nextVertexs[j]);
		}

		arrayOfVertexs.push_back(currentVertexs[0]);
		arrayOfVertexs.push_back(nextVertexs[0]);
		arrayOfVertexs.push_back(nextVertexs[slices - 1]);

		arrayOfVertexs.push_back(currentVertexs[slices - 1]);
		arrayOfVertexs.push_back(currentVertexs[0]);
		arrayOfVertexs.push_back(nextVertexs[slices - 1]);

	}

	return arrayOfVertexs;
}

std::vector<Vertex> getCube()
{
	std::vector<Vertex> vec;
	std::vector<GLfloat> v = {
		-0.50f, -0.50f, -0.50f, // triangle 1 : begin
		-0.50f, -0.50f, 0.50f,
		-0.50f, 0.50f, 0.50f, // triangle 1 : end

		0.50f, 0.50f, -0.50f, // triangle 2 : begin
		-0.50f, -0.50f, -0.50f,
		-0.50f, 0.50f, -0.50f, // triangle 2 : end

		0.50f, -0.50f, 0.50f,
		-0.50f, -0.50f, -0.50f,
		0.50f, -0.50f, -0.50f,

		0.50f, 0.50f, -0.50f,
		0.50f, -0.50f, -0.50f,
		-0.50f, -0.50f, -0.50f,

		-0.50f, -0.50f, -0.50f,
		-0.50f, 0.50f, 0.50f,
		-0.50f, 0.50f, -0.50f,

		0.50f, -0.50f, 0.50f,
		-0.50f, -0.50f, 0.50f,
		-0.50f, -0.50f, -0.50f,

		-0.50f, 0.50f, 0.50f,
		-0.50f, -0.50f, 0.50f,
		0.50f, -0.50f, 0.50f,

		0.50f, 0.50f, 0.50f,
		0.50f, -0.50f, -0.50f,
		0.50f, 0.50f, -0.50f,

		0.50f, 0.50f, 0.50f,
		0.50f, -0.50f, 0.50f,
		0.50f, -0.50f, -0.50f,

		0.50f, 0.50f, 0.50f,
		0.50f, 0.50f, -0.50f,
		-0.50f, 0.50f, -0.50f,

		0.50f, 0.50f, 0.50f,
		-0.50f, 0.50f, -0.50f,
		-0.50f, 0.50f, 0.50f,

		0.50f, 0.50f, 0.50f,
		-0.50f, 0.50f, 0.50f,
		0.50f, -0.50f, 0.50f
	};

	for (size_t i = 0; i < v.size(); i += 3)
	{
		vec.push_back({ glm::vec3(v[i], v[i + 1], v[i + 2]), glm::normalize(glm::vec3(v[i], v[i + 1], v[i + 2])), glm::vec3(1.0f, 0.0, 0) });
		/*if (vec.size() % 3 == 0)
		{
			int j = vec.size() - 1;
			glm::vec3 normal = setNormal(vec[j - 2].position, vec[j - 1].position, vec[j].position);
			vec[j].normal =  normal;
			vec[j - 1].normal = normal;
			vec[vec.size() - 2].normal = normal;
		} */
	}

	return vec;
}

void renderScene(GLRenderSystem& rs)
{
	/*float radius = 30;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view= glm::lookAt(glm::vec3(camX, 20.f, camZ),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));*/

	rs.renderTriangleSoup(renderObject);
	//rs.renderLines(render);
}



void moveCube(GLRenderSystem& rs, glm::vec3 offset)
{
	auto model = rs.getWorldMatrix();
	model = glm::translate(model, offset);
	rs.setWorldMatrix(model);
}

void onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::DOWN && Action::Press == action)
		moveCube(rs, glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::LEFT && Action::Press == action)
		moveCube(rs, glm::vec3{ 1, 0, 0 });
	if (key == KeyCode::RIGHT && Action::Press == action)
		moveCube(rs, glm::vec3{ -1, 0, 0 });
}

int main()
{
	//renderObject = getCube();
	renderObject = getSphere();

	//STLParser parser;
	//renderObject = parser.read("D:\\teapot.stl");

	glfwInit();
	GLWindow window("myWindow", 640, 480);
	window.setKeyCallback(onKeyCallback);

	rs.init();
	rs.setupLight(0, glm::vec3{ 10, 10, 10 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 1,0,0 });
	rs.turnLight(0, true);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3{ 3,3,3}, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.0f, 1.0f,0.0f });
	rs.setViewMatrix(viewMatrix);

	glm::mat4 projMatrix = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.f);
	rs.setProjMatrix(projMatrix);

	glm::mat4 worldMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1,1,1));
	worldMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.0f, 0.0f));
	rs.setWorldMatrix(worldMatrix);

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
