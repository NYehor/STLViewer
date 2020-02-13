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
	Octree(GLRenderSystem& rs, const std::vector<Vertex>& vertexs);

	void insert(const Vertex& a, const Vertex& b, const Vertex& c);
	float calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction);
	void draw(const glm::mat4& modelMatrix);

private:
	std::unique_ptr<ModelBuffer> buffer;
	GLRenderSystem& renderSystem;
	std::unique_ptr<Octant> octant;

	void insert(const std::vector<Vertex>& vertexs);
	void determineDimensions(const std::vector<Vertex>& vertexs, glm::vec3& topFrontRight, glm::vec3& buttonBackLeft);
};
