#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <memory>
#include "Octant.h"
#include "ModelBuffer.h"

class Octree
{
public:
	Octree(GLRenderSystem& rs, float width, float height, float length);
	Octree(GLRenderSystem& rs, const std::vector<Vertex>& vertexs);

	void insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	float calcDistanceIntersection(glm::vec3 origin, glm::vec3 direction);
	void draw(const glm::mat4& modelMatrix);

private:
	std::unique_ptr<ModelBuffer> buffer;
	GLRenderSystem& renderSystem;
	std::unique_ptr<Octant> octant;

	void insert(const std::vector<Vertex>& vertexs);
	void determineDimensions(const std::vector<Vertex>& vertexs, float& width, float& height, float& length);
};
