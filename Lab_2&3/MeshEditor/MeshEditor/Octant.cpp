#include "Octant.h"

Octant::Octant(const glm::vec3& topFrontRight, const glm::vec3& buttonBackLeft):
	_center((topFrontRight + buttonBackLeft) / 2.f),
	_topFrontRight(topFrontRight),
	_buttonBackLeft(buttonBackLeft)
{

}

void Octant::insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	Triangle triangle(a, b, c);
	Triangle xoy(_center + glm::vec3(1, 0, 0), _center, _center + glm::vec3(0, 1, 0));
	Triangle xoz(_center + glm::vec3(1, 0, 0), _center, _center + glm::vec3(0, 0, 1));
	Triangle yoz(_center + glm::vec3(0, 1, 0), _center, _center + glm::vec3(0, 0, 1));

	if (isCrossesPlane(xoy, triangle) || isCrossesPlane(xoz, triangle) || isCrossesPlane(yoz, triangle))
	{
		_triangles.push_back(triangle);
		return;
	}

	int child = determineChild(triangle.center);	
	if (_children[child] == nullptr)
		_children[child] = generateOctant(child); 

	_children[child]->insert(a, b, c);
}

std::unique_ptr<Octant> Octant::generateOctant(int child)
{
	glm::vec3 topFrontRight = _center;
	glm::vec3 buttonBackLeft = _buttonBackLeft;
	glm::vec3 translationVec(0);

	for (size_t i = 0, j = 4; i < 3; i++, j/=2)
	{
		if ((child & j))
			translationVec[i] = _topFrontRight[i] - _center[i];
	}
	
	glm::mat4 matrix = glm::translate(glm::mat4(1.f), translationVec);

	topFrontRight = matrix * glm::vec4(topFrontRight, 1.f);
	buttonBackLeft = matrix * glm::vec4(buttonBackLeft, 1.f);

	return std::unique_ptr<Octant>(new Octant(topFrontRight, buttonBackLeft));
}

char Octant::determineChild(glm::vec3 point)
{
	glm::vec3 p = point - _center;
	return !std::signbit(p.x) << 2 | !std::signbit(p.y) << 1 | !std::signbit(p.z);
}

bool Octant::isCrossesPlane(const Triangle& plane, const Triangle& triangle)
{
	if (isCrossesPlane(plane, triangle.a, triangle.b) ||
		isCrossesPlane(plane, triangle.b, triangle.c))
		return true;
	else
		return false;
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

std::vector<glm::vec3> Octant::getBorders()
{
	std::vector<glm::vec3> octantBorders = generateBorders();
	
	for (size_t i = 0; i < 8; i++)
	{
		if (_children[i] == nullptr) continue;

		std::vector<glm::vec3> tmp = _children[i]->getBorders();
		octantBorders.insert(octantBorders.end(), tmp.begin(), tmp.end());
	}
	
	return octantBorders;
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
	for (size_t i = 0, iLen = _triangles.size(); i < iLen; i++)
	{
		float dst = triangleIntersection(origin, direction, _triangles[i]);
		if (distance > dst)
			distance = dst;
	}

	for (size_t i = 0; i < 7; i++)
	{
		if (_children[i] == nullptr) continue;

		float dst = _children[i]->octantIntersection(origin, direction);
		if (distance > dst)
			distance = dst;
	}
	
	return distance;
}

bool Octant::boxIntersection(const glm::vec3& origin, const glm::vec3& direction)
{
	float txmin = (_buttonBackLeft.x - origin.x) / direction.x;
	float txmax = (_topFrontRight.x - origin.x) / direction.x;

	if (txmin > txmax)
	{
		float tmp = txmin;
		txmin = txmax;
		txmax = tmp;
	}

	float tymin = (_buttonBackLeft.y - origin.y) / direction.y;
	float tymax = (_topFrontRight.y - origin.y) / direction.y;

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

	float tzmin = (_buttonBackLeft.z - origin.z) / direction.z;
	float tzmax = (_topFrontRight.z- origin.z) / direction.z;

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


std::vector<glm::vec3> Octant::generateBorders()
{
	std::vector<glm::vec3> vertexs;

	std::vector<glm::vec3> v;
	v.push_back(_buttonBackLeft);
	for (size_t child = 1; child < 7; child++)
	{
		glm::vec3 corner = _buttonBackLeft;
		for (size_t i = 0, j = 4; i < 3; i++, j /= 2)
			if ((child & j))
				corner[i] += _topFrontRight[i] - _buttonBackLeft[i];

		v.push_back(corner);
	}
	v.push_back(_topFrontRight);

	for (size_t i = 0; i < 7; i += 2)
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