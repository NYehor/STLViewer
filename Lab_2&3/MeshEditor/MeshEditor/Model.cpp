#include "Model.h"

Model::Model(GLRenderSystem& rs, const std::vector<Vertex>& vertexs):
	renderSystem(rs)
{
	modelVertexs = vertexs;
	color = glm::vec3(1.f);
	modelMatrix = glm::mat4(1.0);

	normolizeModel(modelVertexs);
	translateToCenterOfMass(modelVertexs);
}

void Model::setVBO(unsigned int vbo) { VBO = vbo; }

void Model::setVAO(unsigned int vao) { VAO = vao; }

void Model::setModelMatrix(glm::mat4 matrix) { modelMatrix = matrix; }

void Model::setColor(glm::vec3 color) { this->color = color;  }

unsigned int Model::getVBO() const
{
	return VBO;
}

unsigned int Model::getVAO() const
{
	return VAO;
}

glm::vec3 Model::getColor() const
{
	return color;
}

std::vector<Vertex> Model::getVertexs() const
{
	return modelVertexs;
}

glm::mat4 Model::getModelMatrix() const
{
	return modelMatrix;
}

void Model::draw()
{
	renderSystem.renderObject(VAO, modelMatrix, color, modelVertexs);
}

void Model::normolizeModel(std::vector<Vertex>& vertexs)
{
	float maxLength = 0;
	for (size_t i = 1, ilen = vertexs.size(); i < ilen; i++)
	{
		float length = glm::length(vertexs[i].position);
		if (maxLength < length)
			maxLength = length;
	}

	if (maxLength < 1.f) return;

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i++)
	{
		vertexs[i].position = vertexs[i].position / maxLength;
		vertexs[i].normal = glm::normalize(vertexs[i].normal);
	}
}

void Model::translateToCenterOfMass(std::vector<Vertex>& vertexs)
{
	glm::vec3 sumOfVertex = glm::vec3(0.0);

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i += 3)
	{
		glm::vec3 p1 = vertexs[i].position;
		glm::vec3 p2 = vertexs[i + 1].position;
		glm::vec3 p3 = vertexs[i + 2].position;

		sumOfVertex += glm::vec3(
			(p1.x + p2.x + p3.x) / 3.f,
			(p1.y + p2.y + p3.y) / 3.f,
			(p1.z + p2.z + p3.z) / 3.f
		);
	}

	glm::vec3 centr = sumOfVertex / ((float)vertexs.size() / 3.f);
	glm::mat4 matrix = glm::translate(glm::mat4(1.f), -centr);

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i++)
	{
		vertexs[i].position = glm::vec3(matrix * glm::vec4(vertexs[i].position, 1));
		vertexs[i].normal = glm::vec3(matrix * glm::vec4(vertexs[i].normal, 1));
	}	
}