#include "Model.h"

Model::Model(GLRenderSystem& rs, const std::shared_ptr<ModelBuffer> buffer):
	renderSystem(rs),
	modelBuffer(buffer),
	modelMatrix(glm::mat4(1.f)),
	color(glm::vec3(1.f)),
	octree(rs, buffer->getVertexs())
{
	isOctreeVisible = false;
}

void Model::setOctreeVisible(bool use)
{
	isOctreeVisible = use;
}

glm::vec3 Model::getColor() const
{
	return color;
}

void Model::setModelMatrix(glm::mat4 matrix)
{
	modelMatrix = matrix;
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
	if(isOctreeVisible)
		octree.draw(modelMatrix);

	renderSystem.setupShader(modelMatrix, color);
	renderSystem.renderTriangles(modelBuffer->getVAO(), modelBuffer->getVertexs());
}

float Model::calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction)
{
	glm::vec3 orig = glm::vec3(modelMatrix * glm::vec4(origin, 0));
	glm::vec3 dir = glm::vec3(modelMatrix * glm::vec4(direction, 0));

	return octree.calcDistanceIntersection(orig, dir);
}