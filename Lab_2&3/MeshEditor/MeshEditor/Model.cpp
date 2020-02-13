#include "Model.h"

Model::Model(GLRenderSystem& rs, const std::shared_ptr<ModelBuffer> buffer):
	_renderSystem(rs),
	_modelBuffer(buffer),
	_modelMatrix(glm::mat4(1.f)),
	_color(glm::vec3(1.f)),
	_octree(rs, buffer->getVertexs())
{
	_isOctreeVisible = false;
}

void Model::setOctreeVisible(bool use)
{
	_isOctreeVisible = use;
}

glm::vec3 Model::getColor() const
{
	return _color;
}

void Model::setModelMatrix(const glm::mat4& matrix)
{
	_modelMatrix = matrix;
}

void Model::setColor(const glm::vec3& color)
{ 
	this->_color = color;
}

glm::mat4 Model::getModelMatrix() const
{
	return _modelMatrix;
}

void Model::draw()
{
	if(_isOctreeVisible)
		_octree.draw(_modelMatrix);

	_renderSystem.setupShader(_modelMatrix, _color);
	_renderSystem.renderTriangles(_modelBuffer->getVAO(), _modelBuffer->getVertexs());
}

float Model::calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction)
{
	glm::mat4 matrix = glm::inverse(_modelMatrix);
	glm::vec3 orig = glm::vec3(matrix * glm::vec4(origin, 1));
	glm::vec3 dir = glm::vec3(matrix * glm::vec4(direction, 0));

	return _octree.calcDistanceIntersection(orig, dir);
}