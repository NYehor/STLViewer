#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>
#include "Octant.h"
#include "ModelBuffer.h"

class Octree
{
public:
	Octree(GLRenderSystem& rs, glm::vec3 center, float width, float height, float length);

	void setModelMatrix(glm::mat4 matrix);

	void insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	void find(glm::vec3 point);
	void draw();

private:
	glm::mat4 modelMatrix;
	std::unique_ptr<ModelBuffer> buffer;
	Octant octant;
	GLRenderSystem& renderSystem;
};
