#include "Octree.h"
#include <glm/gtx/normal.hpp>

Octree::Octree(GLRenderSystem& rs, glm::vec3 center, float width, float height, float length):
	renderSystem(rs),
	octant(center, width, height, length),
	modelMatrix(glm::mat4(1.f))
{
	
}

void Octree::setModelMatrix(glm::mat4 matrix)
{
	modelMatrix = matrix;
}

void Octree::insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	octant.insert(a, b, c);
}

void Octree::find(glm::vec3 point)
{

}

void Octree::draw()
{
	if (buffer == nullptr)
	{
		std::vector<Vertex> vertexs;
		std::vector<glm::vec3> arr = octant.getBorders();
		for (size_t i = 0, ilen = arr.size(); i < ilen; i++)
			vertexs.push_back({arr[i], glm::vec3(0)});

		buffer = std::unique_ptr<ModelBuffer>(new ModelBuffer(renderSystem, vertexs));
	}

	renderSystem.setupShader(modelMatrix, glm::vec3(1.f));
	renderSystem.renderLines(buffer->getVAO(), buffer->getVertexs());
}