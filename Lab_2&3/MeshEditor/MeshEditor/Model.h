#pragma once
#include "glad.h"
#include "GLRenderSystem.h"

class Model
{
public:
	Model(std::vector<Vertex> vertexs);
	std::vector<Vertex> getVertexs();
	void setModelMatrix(glm::mat4 matrix);
	glm::mat4 getModelMatrix();

private:
	std::vector<Vertex> modelVertexs;
	glm::mat4 modelMatrix;

	void normolizeModel(std::vector<Vertex>& vertexs);
	glm::vec3 centerOfMass(std::vector<Vertex> vertexs);
};

