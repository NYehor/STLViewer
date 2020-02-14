#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <memory>
#include "Octant.h"
#include "ModelBuffer.h"
#include "SplitMethods.h";

class Octree
{
public:
	Octree(GLRenderSystem& rs, const std::vector<Vertex>& vertexs);

	void insert(const Vertex& a, const Vertex& b, const Vertex& c);
	void split(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c,
					std::vector<Vertex>& firstHalf, std::vector<Vertex>& secondHalf);
	float calcDistanceIntersection(const glm::vec3& origin, const glm::vec3& direction);
	void draw(const glm::mat4& modelMatrix);

private:
	std::unique_ptr<ModelBuffer> buffer;
	GLRenderSystem& renderSystem;
	std::unique_ptr<Octant> octant;

	void insert(const std::vector<Vertex>& vertexs);
	void determineDimensions(const std::vector<Vertex>& vertexs, glm::vec3& topFrontRight, glm::vec3& buttonBackLeft);
};
