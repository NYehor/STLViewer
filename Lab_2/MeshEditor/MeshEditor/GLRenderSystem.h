#pragma once
#include "glad.h"
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

class GLRenderSystem
{
public:
	void init();
	void clearDisplay(float r, float g, float b);
	void setViewport(double x, double y, double width, double height);
	void renderTriangleSoup(const std::vector<Vertex>& vertices);
	void renderLines(const std::vector<Vertex> vertices);
	void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
	void turnLight(uint32_t index, bool enable);

	void setWorldMatrix(const glm::mat4& matrix);
	const glm::mat4& getWorldMatrix() const;

	void setViewMatrix(const glm::mat4& matrix);
	const glm::mat4& getViewMatrix() const;

	void setProjMatrix(const glm::mat4& matrix);
	const glm::mat4& getProjMatrix();

private:
	glm::mat4 viewMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 projMatrix;
};