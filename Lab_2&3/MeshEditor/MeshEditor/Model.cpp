#include "Model.h"

Model::Model(GLRenderSystem& rs, const std::shared_ptr<ModelBuffer> buffer):
	renderSystem(rs),
	modelBuffer(buffer),
	modelMatrix(glm::mat4(1.f)),
	color(glm::vec3(1.f)),
	octree(rs, glm::vec3(0.0), 1.2, 1.6, 1.2)
{
	auto tmp = buffer->getVertexs();
	for (size_t i = 0, iLen = tmp.size(); i < iLen; i+=3)
	{
		octree.insert(tmp[i].position, tmp[i + 1].position, tmp[i + 2].position);
	}
}

Octree& Model::getOctree()
{
	return octree;
}

const Octree& Model::getOctree() const
{
	return octree;
}

glm::vec3 Model::getColor() const
{
	return color;
}

void Model::setModelMatrix(glm::mat4 matrix)
{
	modelMatrix = matrix;
	octree.setModelMatrix(matrix);
}

void Model::setColor(glm::vec3 color)
{ 
	this->color = color;
}

glm::mat4 Model::getModelMatrix() const
{
	return modelMatrix;
}

void Model::draw()
{
	renderSystem.setupShader(modelMatrix, color);
	renderSystem.renderTriangles(modelBuffer->getVAO(), modelBuffer->getVertexs());
}