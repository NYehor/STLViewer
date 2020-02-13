#pragma once

#include <vector>
#include "glad.h"
#include "GLRenderSystem.h"
#include "ModelBuffer.h"
#include "Octree.h"

class Model
{
public:
	Model(GLRenderSystem& rs, const std::shared_ptr<ModelBuffer> buffer);

	void setModelMatrix(const glm::mat4& matrix);
	void setColor(const glm::vec3& color);
	void setOctreeVisible(bool use);

	glm::mat4 getModelMatrix() const;
	glm::vec3 getColor() const;

	float calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction);
	void draw();

private:
	std::shared_ptr<ModelBuffer> _modelBuffer;
	GLRenderSystem& _renderSystem;
	Octree _octree;

	glm::mat4 _modelMatrix;
	glm::vec3 _color;
	bool _isOctreeVisible;
};

