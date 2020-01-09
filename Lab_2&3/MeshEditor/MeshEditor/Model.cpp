#include "Model.h"

Model::Model(std::vector<Vertex> vertexs)
{
	modelVertexs = vertexs;

	normolizeModel(modelVertexs);
	glm::vec3 center = centerOfMass(modelVertexs);
	modelMatrix = glm::translate(glm::mat4(1.f), -center);
}

std::vector<Vertex> Model::getVertexs()
{
	return modelVertexs;
}

void Model::setModelMatrix(glm::mat4 matrix)
{
	modelMatrix = matrix;
}

glm::mat4 Model::getModelMatrix()
{
	return modelMatrix;
}

void Model::normolizeModel(std::vector<Vertex>& vertexs)
{
	float maxLength = 0;
	for (size_t i = 1, ilen = vertexs.size(); i < ilen; i++)
	{
		glm::vec3 v = vertexs[i].position;
		float length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		if (maxLength < length)
			maxLength = length;
	}

	if (maxLength < 1.f) return;

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i++)
	{
		vertexs[i].position = vertexs[i].position / maxLength;
		vertexs[i].normal = glm::normalize(vertexs[i].normal);
		vertexs[i].color = glm::vec3(1, 0, 0);
	}
}

glm::vec3 Model::centerOfMass(std::vector<Vertex> vertexs)
{
	glm::vec3 center = glm::vec3(0.0);

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i += 3)
	{
		glm::vec3 p1 = vertexs[i].position;
		glm::vec3 p2 = vertexs[i + 1].position;
		glm::vec3 p3 = vertexs[i + 2].position;

		center += glm::vec3(
			(p1.x + p2.x + p3.x) / 3.f,
			(p1.y + p2.y + p3.y) / 3.f,
			(p1.z + p2.z + p3.z) / 3.f
		);
	}

	return center / ((float)vertexs.size() / 3.f);
}