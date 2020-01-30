#pragma once

#include "glad.h"
#include "GLRenderSystem.h"
#include "ModelBuffer.h"
#include "Octree.h"

class Model
{
public:
	Model(GLRenderSystem& rs, const std::shared_ptr<ModelBuffer> buffer);

	void setModelMatrix(glm::mat4 matrix);
	void setColor(glm::vec3 color);

	glm::mat4 getModelMatrix() const;
	glm::vec3 getColor() const;

	void draw();

	Octree& getOctree();
	const Octree& getOctree() const;

private:
	std::shared_ptr<ModelBuffer> modelBuffer;
	GLRenderSystem& renderSystem;
	Octree octree;

	glm::mat4 modelMatrix;
	glm::vec3 color;
};

