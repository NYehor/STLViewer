#include "SplitMethods.h"

std::vector<Vertex> SplitMethods::triangulation(std::vector<Vertex> points, const glm::vec3& planeNormal)
{
	sortPoint(points, planeNormal); 
	std::vector<Vertex> triangles;

	while (points.size() > 3)
	{
		int i = findEar(points, planeNormal);

		if (i == 0)
		{
			triangles.push_back(points[points.size() - 2]);
			triangles.push_back(points[i]);
			triangles.push_back(points[i + 1]);
		}

		if (i == points.size() - 1)
		{
			triangles.push_back(points[i - 1]);
			triangles.push_back(points[i]);
			triangles.push_back(points[0]);
		}

		if (i != 0 && i != points.size() - 1)
		{
			triangles.push_back(points[i - 1]);
			triangles.push_back(points[i]);
			triangles.push_back(points[i + 1]);
		}

		points.erase(points.begin() + i);
	}

	if (points.size() == 3)
		triangles.insert(triangles.end(), points.begin(), points.end());

	for (size_t i = 0, iLen = triangles.size(); i < iLen; i++)
		triangles[i].normal = planeNormal;

	return triangles;
}

bool SplitMethods::isRightPartOfSpace(const glm::vec3& planeA, const glm::vec3& planeB, const glm::vec3& planeC, const glm::vec3 point)
{
	glm::vec3 vec = point - planeA;
	glm::vec3 normal = glm::triangleNormal(planeA, planeB, planeC);

	if (glm::dot(vec, normal) > 0)
		return true;
	else
		return false;
}

glm::vec3 SplitMethods::intersectionPoint(const glm::vec3& planeA, const glm::vec3& planeB, const glm::vec3& planeC, const glm::vec3& a, const glm::vec3& b)
{
	glm::vec3 normal = glm::triangleNormal(planeA, planeB, planeC);
	glm::vec3 ray = b - a;
	float e = dot(normal, ray);

	glm::vec3 v = planeA - a;
	float d = glm::dot(normal, v);

	return a + ray * d / e;
}

void SplitMethods::sortPoint(std::vector<Vertex>& points, const glm::vec3& planeNormal)
{
	const glm::vec3 origin = points[0].position;
	std::sort(points.begin(), points.end(), [&](const Vertex& lhs, const Vertex& rhs) -> bool {
		glm::vec3 vec = glm::cross((lhs.position - origin), (rhs.position - origin));
		return glm::dot(vec, planeNormal) > 0;
		});
}

bool SplitMethods::isConvex(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& planeNormal)
{
	glm::vec3 vec = glm::cross((b - a), (c - a));
	return glm::dot(vec, planeNormal) < 0;
}

bool SplitMethods::isConcave(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& planeNormal)
{
	const glm::vec3 origin = a;

	glm::vec3 vec = glm::cross((b - origin), (c - origin));
	return glm::dot(vec, planeNormal) < 0;
}

int SplitMethods::findEar(std::vector<Vertex> points, const glm::vec3& planeNormal)
{
	int i = 0;
	int iLen = points.size();
	bool earNotFound = true;

	while (earNotFound && i < iLen - 2)
	{
		if (i == 0)
		{
			if (isConvex(points[iLen - 2].position, points[i].position, points[i + 1].position, planeNormal))
				if (!isConcave(points[iLen - 2].position, points[i].position, points[i + 1].position, planeNormal) &&
					!isConcave(points[iLen - 2].position, points[i].position, points[i + 1].position, planeNormal) &&
					!isConcave(points[iLen - 2].position, points[i].position, points[i + 1].position, planeNormal))
					earNotFound = false;
		}
		else
		{
			if (isConvex(points[i - 1].position, points[i].position, points[i + 1].position, planeNormal))
				if (!isConcave(points[i - 1].position, points[i].position, points[i + 1].position, planeNormal) &&
					!isConcave(points[i - 1].position, points[i].position, points[i + 1].position, planeNormal) &&
					!isConcave(points[i - 1].position, points[i].position, points[i + 1].position, planeNormal))
					earNotFound = false;
		}

		if (earNotFound) i++;
	}

	return i;
}