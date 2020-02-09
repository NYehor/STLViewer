#include "Octree.h"
#include <glm/gtx/normal.hpp>

Octree::Octree(GLRenderSystem& rs, const std::vector<Vertex>& vertexs):
	renderSystem(rs)
{
	glm::vec3 topFrontRight;
	glm::vec3 buttonBackLeft;
	determineDimensions(vertexs, topFrontRight, buttonBackLeft);
	octant = std::unique_ptr<Octant>(new Octant(topFrontRight, buttonBackLeft));
	insert(vertexs);
}

void Octree::determineDimensions(const std::vector<Vertex>& vertexs, glm::vec3& topFrontRight, glm::vec3& buttonBackLeft)
{
	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;

	for (size_t i = 0, iLen = vertexs.size(); i < iLen; i += 3)
	{
		if (maxX < abs(vertexs[i].position.x))
			maxX = abs(vertexs[i].position.x);

		if (maxY < abs(vertexs[i].position.y))
			maxY = abs(vertexs[i].position.y);

		if (maxZ < abs(vertexs[i].position.z))
			maxZ = abs(vertexs[i].position.z);
	}

	topFrontRight = glm::vec3(maxX, maxY, maxZ);
	buttonBackLeft = glm::vec3(-maxX, -maxY, -maxZ);
}

void Octree::insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	octant->insert(a, b, c);
}

void Octree::insert(const std::vector<Vertex>& vertexs)
{
	for (size_t i = 0, iLen = vertexs.size(); i < iLen; i += 3)
		octant->insert(vertexs[i].position, vertexs[i + 1].position, vertexs[i + 2].position);
}

float Octree::calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction)
{
	return octant->octantIntersection(origin, direction);
}

void Octree::draw(const glm::mat4& modelMatrix)
{
	if (buffer == nullptr)
	{
		std::vector<Vertex> vertexs;
		std::vector<glm::vec3> arr = octant->getBorders();
		for (size_t i = 0, ilen = arr.size(); i < ilen; i++)
			vertexs.push_back({arr[i], glm::vec3(0)});

		buffer = std::unique_ptr<ModelBuffer>(new ModelBuffer(renderSystem, vertexs));
	}

	renderSystem.setupShader(modelMatrix, glm::vec3(1.f));
	renderSystem.renderLines(buffer->getVAO(), buffer->getVertexs());
}