#pragma once
#include "glad.h"
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct Light {
	bool isTurn;

	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class GLRenderSystem
{
public:
	GLRenderSystem(const char* vertexFilePath, const char* fragmentFilePath);
	void init();
	void clearDisplay(float r, float g, float b);
	void setViewport(double x, double y, double width, double height);
	void setupShader(const glm::mat4& worldMatrix, const glm::vec3& color);
	void renderTriangles(unsigned int VAO, const std::vector<Vertex>& vertexs);
	void renderLines(unsigned int VAO, const std::vector<Vertex>& vertexs);
	unsigned int setVBO(const std::vector<Vertex>& vertices);
	unsigned int setVAO(unsigned int vbo, const std::vector<Vertex>& vertices);
	void deleteBuffers(const unsigned int& vbo, const unsigned int& vao);
	void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void turnLight(uint32_t index, bool enable);

	void setViewMatrix(const glm::mat4& matrix);
	const glm::mat4& getViewMatrix() const;

	void setProjMatrix(const glm::mat4& matrix);
	const glm::mat4& getProjMatrix();

	Shader& getShader();
	const Shader& getShader() const;

private:
	std::vector<Light> lights;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	Shader shader;
};