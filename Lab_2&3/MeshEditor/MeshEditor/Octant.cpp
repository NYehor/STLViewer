#include "Octant.h"

Octant::Octant(glm::vec3 center, float width, float height, float length):
	center(center),
	halfWidth(width / 2.f),
	halfHeight(height / 2.f),
	halfLength(length / 2.f)
{
	borders = generateBorders();
	topFrontRight = calcCornerOfCube(7, center, halfWidth, halfHeight, halfLength);
	buttonBackLeft = calcCornerOfCube(0, center, halfWidth, halfHeight, halfLength);
}

void Octant::insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	Triangle triangle(a, b, c);
	if (isCrossesXOY(triangle) || isCrossesXOZ(triangle) || isCrossesYOZ(triangle))
	{
		triangles.push_back(triangle);
		return;
	}

	int child = determineChild(triangle.center);	
	if (children[child] == nullptr)
		children[child] = generateOctant(child);

	children[child]->insert(a, b, c);
}

std::unique_ptr<Octant> Octant::generateOctant(int child)
{
	glm::vec3 octantCenter = calcCornerOfCube(child, center, halfWidth / 2.f, halfHeight / 2.f, halfLength / 2.f);
	return std::unique_ptr<Octant>(new Octant(octantCenter, halfWidth, halfHeight, halfLength));
}

int Octant::determineChild(glm::vec3 point)
{
	glm::vec3 p = point - center;
	return !std::signbit(p.x) << 2 | !std::signbit(p.y) << 1 | !std::signbit(p.z);
}

glm::vec3 Octant::calcCornerOfCube(int number, glm::vec3 center, float width, float height, float length)
{
	glm::vec3 corner(center);

	if (number & 4)
		corner.x += height;
	else
		corner.x -= height;

	if (number & 2)
		corner.y += width;
	else
		corner.y -= width;

	if (number & 1)
		corner.z += length;
	else
		corner.z -= length;

	return corner;
}

bool Octant::isCrossesPlane(const Triangle& plane, const glm::vec3& a, const glm::vec3& b)
{
	glm::vec3 normal = glm::triangleNormal(plane.a, plane.b, plane.c);
	glm::vec3 v = plane.a - a;
	float d = glm::dot(normal, v);
	glm::vec3 ab = b - a;
	float e = dot(normal, ab);

	if (e != 0)
	{
		if (d == 0)
			return true; 

		glm::vec3 m = a + ab * d / e;
		if (glm::dot(a - m, b - m) <= 0)
			return true;
	}

	return false;
}

bool Octant::isCrossesXOY(const Triangle& triangle)
{
	Triangle plane(center + glm::vec3(1, 0, 0), center, center + glm::vec3(0, 1, 0));

	if (isCrossesPlane(plane, triangle.a, triangle.b) ||
		isCrossesPlane(plane, triangle.b, triangle.c))
		return true;
	else
		return false;
}

bool Octant::isCrossesXOZ(const Triangle& triangle)
{
	Triangle plane(center + glm::vec3(1, 0, 0), center, center + glm::vec3(0, 0, 1));

	if (isCrossesPlane(plane, triangle.a, triangle.b) ||
		isCrossesPlane(plane, triangle.b, triangle.c))
		return true;
	else
		return false;
}

bool Octant::isCrossesYOZ(const Triangle& triangle)
{
	Triangle plane(center + glm::vec3(0, 1, 0), center, center + glm::vec3(0, 0, 1));

	if (isCrossesPlane(plane, triangle.a, triangle.b) ||
		isCrossesPlane(plane, triangle.b, triangle.c))
		return true;
	else
		return false;
}

std::vector<glm::vec3> Octant::getBorders()
{
	std::vector<glm::vec3> octantBorders;
	octantBorders.insert(octantBorders.end(), borders.begin(), borders.end());
	
	for (size_t i = 0; i < 8; i++)
	{
		if (children[i] == nullptr) continue;

		std::vector<glm::vec3> tmp = children[i]->getBorders();
		octantBorders.insert(octantBorders.end(), tmp.begin(), tmp.end());
	}
	
	return octantBorders;
}

std::vector<glm::vec3> Octant::generateBorders()
{
	std::vector<glm::vec3> vertexs;

	std::vector<glm::vec3> v;
	for (size_t i = 0; i < 8; i++)
		v.push_back(calcCornerOfCube(i, center, halfWidth, halfHeight, halfLength));

	for (size_t i = 0; i < 7; i+=2)
		vertexs.push_back(v[i]);
	for (size_t i = 0; i < 3; i += 2)
	{
		vertexs.push_back(v[i]);
		vertexs.push_back(v[i + 4]);
	}

	for (size_t i = 1; i < 8; i += 2)
		vertexs.push_back(v[i]);
	for (size_t i = 1; i < 4; i += 2)
	{
		vertexs.push_back(v[i]);
		vertexs.push_back(v[i + 4]);
	}

	for (size_t i = 0; i < 8; i++)	
		vertexs.push_back(v[i]);

	return vertexs;
}

float Octant::triangleIntersection(const glm::vec3& origin, const glm::vec3& direction, const Triangle& triangle) // Moller-Trumbore Algorithm
{
	glm::vec3 e1 = triangle.b - triangle.a;
	glm::vec3 e2 = triangle.c - triangle.a;
	
	glm::vec3 pvec = glm::cross(direction, e2);
	float det = dot(e1, pvec);

	if (det < 1e-8 && det > -1e-8) 
		return std::numeric_limits<float>::max();;

	float inv_det = 1 / det;
	glm::vec3 tvec = origin - triangle.a;
	float u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) 
		return std::numeric_limits<float>::max();;
	

	glm::vec3 qvec = cross(tvec, e1);
	float v = glm::dot(direction, qvec) * inv_det;
	if (v < 0 || u + v > 1) 
		return std::numeric_limits<float>::max();
	
	return dot(e2, qvec) * inv_det;
}

float Octant::octantIntersection(const glm::vec3& origin, const glm::vec3& direction) 
{
	if (!boxIntersection(origin, direction))
		return std::numeric_limits<float>::max();
	
	float distance = std::numeric_limits<float>::max();;
	for (size_t i = 0, iLen = triangles.size(); i < iLen; i++)
	{
		float dst = triangleIntersection(origin, direction, triangles[i]);
		if (distance > dst)
			distance = dst;
	}

	for (size_t i = 0; i < 7; i++)
	{
		if (children[i] == nullptr) continue;

		float dst = children[i]->octantIntersection(origin, direction);
		if (distance > dst)
			distance = dst;
	}
	
	return distance;
}

bool Octant::boxIntersection(const glm::vec3& origin, const glm::vec3& direction)
{
	float txmin = (buttonBackLeft.x - origin.x) / direction.x;
	float txmax = (topFrontRight.x - origin.x) / direction.x;

	if (txmin > txmax)
	{
		float tmp = txmin;
		txmin = txmax;
		txmax = tmp;
	}

	float tymin = (buttonBackLeft.y - origin.y) / direction.y;
	float tymax = (topFrontRight.y - origin.y) / direction.y;

	if (tymin > tymax)
	{
		float tmp = tymin;
		tymin = tymax;
		tymax = tmp;
	}

	if ((txmin > tymax) || (tymin > txmax))
		return false;

	if (tymin > txmin)
		txmin = tymin;

	if (tymax < txmax)
		txmax = tymax;

	float tzmin = (buttonBackLeft.z - origin.z) / direction.z;
	float tzmax = (topFrontRight.z- origin.z) / direction.z;

	if (tzmin > tzmax)
	{
		float tmp = tzmin;
		tzmin = tzmax;
		tzmax = tmp;
	}

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;

	if (tzmin > txmin)
		txmin = tzmin;

	if (tzmax < txmax)
		txmax = tzmax;

	return true;
}