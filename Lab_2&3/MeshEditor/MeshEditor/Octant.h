#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <array>
#include <memory>
#include "GLRenderSystem.h"

class Octant
{
public:
	Octant(const glm::vec3& topFrontRight, const glm::vec3& buttonBackLeft);

	void insert(const Vertex& a, const Vertex& b, const Vertex& c);

	std::vector<Vertex> getTriangles();
	std::vector<glm::vec3> getBorders();
	float octantIntersection(const glm::vec3& origin, const glm::vec3& direction);

private:
	struct Triangle
	{
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
		glm::vec3 center;

		Triangle(const Vertex& a, const Vertex& b, const Vertex& c) :
			a(a), b(b), c(c) 
		{
			center = (a.position + b.position + c.position) / 3.f;
		}
	};

	glm::vec3 _center;
	glm::vec3 _topFrontRight;
	glm::vec3 _buttonBackLeft;
	std::vector<Triangle> _triangles;
	std::array<std::unique_ptr<Octant>, 8> _children;
	std::vector<glm::vec3> _edges;

	char determineChild(glm::vec3 point);
	std::unique_ptr<Octant> generateOctant(int child);
	std::vector<glm::vec3> generateBorders();
	bool isCrossesPlane(const Triangle& plane, const Triangle& triangle);
	bool isCrossesPlane(const Triangle& plane, const glm::vec3& a, const glm::vec3& b);
	bool boxIntersection(const glm::vec3& origin, const glm::vec3& direction);
	float triangleIntersection(const glm::vec3& origin, const glm::vec3& direction, const Triangle& triangle);
};

