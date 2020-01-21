#pragma once
#include "glad.h"
#include "GLRenderSystem.h"

class Model
{
public:
	Model(GLRenderSystem* renderSystem, std::vector<Vertex> vertexs);

	std::vector<Vertex> getVertexs();
	void setModelMatrix(glm::mat4 matrix);
	glm::mat4 getModelMatrix();

private:
	GLRenderSystem* renderSystem;
	std::vector<Vertex> modelVertexs;
	glm::mat4 modelMatrix;

	void normolizeModel(std::vector<Vertex>& vertexs);
	void translateToCenterOfMass(std::vector<Vertex>& vertexs);
};

