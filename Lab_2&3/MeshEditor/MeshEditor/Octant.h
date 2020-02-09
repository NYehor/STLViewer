#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <array>
#include <memory>

class Octant
{
public:
	Octant(const glm::vec3& topFrontRight, const glm::vec3& buttonBackLeft);

	void insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

	std::vector<glm::vec3> getBorders();
	float octantIntersection(const glm::vec3& origin, const glm::vec3& direction);

private:
	struct Triangle
	{
		const glm::vec3& a;
		const glm::vec3& b;
		const glm::vec3& c;
		glm::vec3 center;

		Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) :
			a(a), b(b), c(c) 
		{
			center = (a + b + c) / 3.f;
		}
	};

	glm::vec3 _center;
	glm::vec3 _topFrontRight;
	glm::vec3 _buttonBackLeft;
	std::vector<Triangle> _triangles;
	std::array<std::unique_ptr<Octant>, 8> _children;

	char determineChild(glm::vec3 point);
	std::unique_ptr<Octant> generateOctant(int child);
	std::vector<glm::vec3> generateBorders();
	bool isCrossesPlane(const Triangle& plane, const Triangle& triangle);
	bool isCrossesPlane(const Triangle& plane, const glm::vec3& a, const glm::vec3& b);
	bool boxIntersection(const glm::vec3& origin, const glm::vec3& direction);
	float triangleIntersection(const glm::vec3& origin, const glm::vec3& direction, const Triangle& triangle);
};

