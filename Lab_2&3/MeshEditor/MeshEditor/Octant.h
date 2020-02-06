#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <vector>
#include <array>

class Octant
{
public:
	Octant(glm::vec3 center, float width, float height, float length);

	std::vector<glm::vec3> getBorders();

	void insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
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

	glm::vec3 center;
	glm::vec3 topFrontRight;
	glm::vec3 buttonBackLeft;
	float halfWidth;
	float halfHeight;
	float halfLength;
	std::vector<Triangle> triangles;
	std::array<std::unique_ptr<Octant>, 8> children;
	std::vector<glm::vec3> borders;

	int determineChild(glm::vec3 point);
	glm::vec3 calcCornerOfCube(int number, glm::vec3 center, float width, float height, float length);
	std::unique_ptr<Octant> generateOctant(int child);
	std::vector<glm::vec3> generateBorders();
	bool isCrossesPlane(const Triangle& plane, const glm::vec3& a, const glm::vec3& b);
	bool isCrossesXOY(const Triangle& triangle);
	bool isCrossesXOZ(const Triangle& triangle);
	bool isCrossesYOZ(const Triangle& triangle);

	bool boxIntersection(const glm::vec3& origin, const glm::vec3& direction);
	float triangleIntersection(const glm::vec3& origin, const glm::vec3& direction, const Triangle& triangle);
};

