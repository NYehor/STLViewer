#include "Octant.h"

Octant::Octant(glm::vec3 center, float width, float height, float length):
	center(center),
	halfWidth(width / 2.0),
	halfHeight(height / 2.0),
	halfLength(length / 2.0)
{
	borders = generateBorders(center, width, height, length);
}

void Octant::insert(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	Triangle triangle(a, b, c);
	if (isCrossesXOY(triangle) || isCrossesXOZ(triangle) || isCrossesYOZ(triangle))
	{
		triangles.push_back(triangle);
		return;
	}

	if (children[TLF] == nullptr)
	{
		float quaterWidth = halfWidth / 2.f;
		float quaterHeight = halfHeight / 2.f;
		float quaterLength = halfLength / 2.f;

		children[TLF] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x + quaterHeight, center.y - quaterWidth, center.z - quaterLength), halfWidth, halfHeight, halfLength));
		children[TRF] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x + quaterHeight, center.y + quaterWidth, center.z - quaterLength), halfWidth, halfHeight, halfLength));
		children[BRF] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x - quaterHeight, center.y + quaterWidth, center.z - quaterLength), halfWidth, halfHeight, halfLength));
		children[BLF] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x - quaterHeight, center.y - quaterWidth, center.z - quaterLength), halfWidth, halfHeight, halfLength));
		children[TLB] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x + quaterHeight, center.y - quaterWidth, center.z + quaterLength), halfWidth, halfHeight, halfLength));
		children[TRB] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x + quaterHeight, center.y + quaterWidth, center.z + quaterLength), halfWidth, halfHeight, halfLength));
		children[BRB] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x - quaterHeight, center.y + quaterWidth, center.z + quaterLength), halfWidth, halfHeight, halfLength));
		children[BLB] = std::unique_ptr<Octant>(new Octant(glm::vec3(center.x - quaterHeight, center.y - quaterWidth, center.z + quaterLength), halfWidth, halfHeight, halfLength));
	}

	if (center.x < triangle.a.x && triangle.a.x < center.x + halfHeight)
	{
		if (center.y < triangle.a.y && triangle.a.y < center.y + halfWidth)
		{
			if (center.z < triangle.a.z && triangle.a.z < center.z + halfLength)
				children[TRB]->insert(a, b, c);
			else
				if (triangle.a.z > center.z - halfLength)
					children[TRF]->insert(a, b, c);
		}
		else
			if (triangle.a.y > center.y - halfWidth)
			{
				if (center.z < triangle.a.z && triangle.a.z < center.z + halfLength)
					children[TLB]->insert(a, b, c);
				else
					if (triangle.a.z > center.z - halfLength)
						children[TLF]->insert(a, b, c);
			}
	}
	else
		if (triangle.a.x > center.x - halfHeight)
		{
			if (center.y < triangle.a.y && triangle.a.y < center.y + halfWidth)
			{
				if (center.z < triangle.a.z && triangle.a.z < center.z + halfLength)
					children[BRB]->insert(a, b, c);
				else
					if (triangle.a.z > center.z - halfLength)
						children[BRF]->insert(a, b, c);
			}
			else
				if (triangle.a.y > center.y - halfWidth)
				{
					if (center.z < triangle.a.z && triangle.a.z < center.z + halfLength)
						children[BLB]->insert(a, b, c);
					else
						if (triangle.a.z > center.z - halfLength)
							children[BLF]->insert(a, b, c);
				}
		}
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
			return true; // ветор ортогонален и пренадлижит плоскости

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

void Octant::find(glm::vec3 point)
{

}

std::vector<glm::vec3> Octant::getBorders()
{
	std::vector<glm::vec3> octantBorders;
	octantBorders.insert(octantBorders.end(), borders.begin(), borders.end());

	if (children[TLF] != nullptr)
	{
		for (size_t i = 0; i < 8; i++)
		{
			std::vector<glm::vec3> tmp = children[i]->getBorders();
			octantBorders.insert(octantBorders.end(), tmp.begin(), tmp.end());
		}
	}
	
	return octantBorders;
}

std::vector<glm::vec3> Octant::generateBorders(glm::vec3 centerOfCube, float width, float height, float length)
{
	std::vector<glm::vec3> vertexs;
	float halfWidth = width / 2.f;
	float halfHeight = height / 2.f;
	float halfLength = length / 2.f;

	glm::vec3 topFrontLeft{ centerOfCube.x + halfHeight, centerOfCube.y - halfWidth, centerOfCube.z - halfLength };
	glm::vec3 topFrontRight{ centerOfCube.x + halfHeight, centerOfCube.y + halfWidth, centerOfCube.z - halfLength };
	glm::vec3 buttonFrontLeft{ centerOfCube.x - halfHeight, centerOfCube.y - halfWidth, centerOfCube.z - halfLength };
	glm::vec3 buttonFrontRight{ centerOfCube.x - halfHeight, centerOfCube.y + halfWidth, centerOfCube.z - halfLength };

	glm::vec3 topBackLeft{ centerOfCube.x + halfHeight, centerOfCube.y - halfWidth, centerOfCube.z + halfLength };
	glm::vec3 topBackRight{centerOfCube.x + halfHeight, centerOfCube.y + halfWidth, centerOfCube.z + halfLength};
	glm::vec3 buttonBackLeft{centerOfCube.x - halfHeight, centerOfCube.y - halfWidth, centerOfCube.z + halfLength};
	glm::vec3 buttonBackRight{centerOfCube.x - halfHeight, centerOfCube.y + halfWidth, centerOfCube.z + halfLength};

	vertexs.push_back(topFrontLeft);
	vertexs.push_back(topFrontRight);
	vertexs.push_back(topFrontRight);
	vertexs.push_back(buttonFrontRight);
	vertexs.push_back(buttonFrontRight);
	vertexs.push_back(buttonFrontLeft);
	vertexs.push_back(buttonFrontLeft);
	vertexs.push_back(topFrontLeft);

	vertexs.push_back(topBackLeft);
	vertexs.push_back(topBackRight);
	vertexs.push_back(topBackRight);
	vertexs.push_back(buttonBackRight);
	vertexs.push_back(buttonBackRight);
	vertexs.push_back(buttonBackLeft);
	vertexs.push_back(buttonBackLeft);
	vertexs.push_back(topBackLeft);

	vertexs.push_back(topFrontLeft);
	vertexs.push_back(topBackLeft);
	vertexs.push_back(topFrontRight);
	vertexs.push_back(topBackRight);
	vertexs.push_back(buttonFrontLeft);
	vertexs.push_back(buttonBackLeft);
	vertexs.push_back(buttonFrontRight);
	vertexs.push_back(buttonBackRight);

	return vertexs;
}