#pragma once
#include "glad.h"
#include "GLRenderSystem.h"

class Model
{
public:
	Model(GLRenderSystem& rs, const std::vector<Vertex>& vertexs);

	void setModelMatrix(glm::mat4 matrix);
	void setVBO(unsigned int vbo);
	void setVAO(unsigned int vao);
	void setColor(glm::vec3 color);

	std::vector<Vertex> getVertexs() const;
	glm::mat4 getModelMatrix() const;
	unsigned int getVBO() const;
	unsigned int getVAO() const;
	glm::vec3 getColor() const;

	void draw();
private:
	unsigned int VBO;
	unsigned int VAO;

	GLRenderSystem& renderSystem;
	std::vector<Vertex> modelVertexs;
	glm::mat4 modelMatrix;
	glm::vec3 color;

	void normolizeModel(std::vector<Vertex>& vertexs);
	void translateToCenterOfMass(std::vector<Vertex>& vertexs);
};

