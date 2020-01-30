#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <vector>
#include <array>

#define TLF 0    // top left front
#define TRF 1    // top right front
#define BRF 2    // bottom right front
#define BLF 3    // bottom left front
#define TLB 4    // top left back
#define TRB 5    // top right back
#define BRB 6    // bottom right back
#define BLB 7    // bottom left back

class Octant
{
public:
	Octant(glm::vec3 center, float width, float height, float length);

	std::vector<glm::vec3> getBorders();

	void insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	void find(glm::vec3 point);


private:
	struct Triangle
	{
		const glm::vec3& a;
		const glm::vec3& b;
		const glm::vec3& c;

		Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) :
			a(a), b(b), c(c) {}
	};

	glm::vec3 center;
	float halfWidth;
	float halfHeight;
	float halfLength;
	std::vector<Triangle> triangles;
	std::array<std::unique_ptr<Octant>, 8> children;
	std::vector<glm::vec3> borders;
	std::vector<glm::vec3> generateBorders(glm::vec3 centerOfCube, float width, float height, float length);
	bool isCrossesPlane(const Triangle& plane, const glm::vec3& a, const glm::vec3& b);
	bool isCrossesXOY(const Triangle& triangle);
	bool isCrossesXOZ(const Triangle& triangle);
	bool isCrossesYOZ(const Triangle& triangle);
};

