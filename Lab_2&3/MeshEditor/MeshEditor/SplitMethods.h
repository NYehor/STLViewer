#pragma once

#include <vector>
#include <glm\fwd.hpp>
#include <algorithm>
#include <vector>
#include <glm\gtx\normal.hpp>
#include "GLRenderSystem.h"

class SplitMethods
{
public:
	static std::vector<Vertex> triangulation(std::vector<Vertex> points, const glm::vec3& planeNormal);
	static bool isRightPartOfSpace(const glm::vec3& planeA, const glm::vec3& planeB, const glm::vec3& planeC, const glm::vec3 point);
	static glm::vec3 intersectionPoint(const glm::vec3& planeA, const glm::vec3& planeB, const glm::vec3& planeC, const glm::vec3& a, const glm::vec3& b);

private:
	SplitMethods() {}

	static void sortPoint(std::vector<Vertex>& points, const glm::vec3& planeNormal);

	static bool  isConvex(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& planeNormal);
	static bool  isConcave(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& planeNormal);
	static int findEar(std::vector<Vertex> points, const glm::vec3& planeNormal);
};