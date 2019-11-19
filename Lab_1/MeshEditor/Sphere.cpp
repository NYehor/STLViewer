#include "Sphere.h"
#include <sstream>
#define PI 3.14159265
#include <cmath>

int Sphere::execute(const std::map<std::string, std::string>& args)
{
	TriangleSoup triangleSphre = {};
	float radious = std::stof(args.find("R")->second);
	int slices = std::stoi(args.find("slices")->second);
	int rings = std::stoi(args.find("rings")->second);
	std::string filepath = args.find("filepath")->second;
	//Vec centralPoint = {};

	//// add function in Command?
	//std::string origin = args.find("origin")->second;
	//origin = origin.substr(1, origin.length() - 2);
	//std::vector<std::string> token;
	//std::stringstream input_stringstream(origin);
	//std::string parsed;
	//while (getline(input_stringstream, parsed, ','))
	//{
	//	if (parsed == "") continue;
	//	token.push_back(parsed);
	//}

	//centralPoint.x = std::stof(token[0]);
	//centralPoint.y = std::stof(token[1]);
	//centralPoint.z = std::stof(token[2]);

	std::vector<Vec> upperVec = std::vector<Vec>(slices);
	std::vector<Vec> downVec = std::vector<Vec>(slices);

	float incTeta =  180.0 / (rings + 1);
	float  incPhi = 360.0 / slices;

	float teta = 0;

	upperVec = fillVec(teta, incPhi, radious, slices);


	for (float teta = incTeta; teta <= 180.0; teta += incTeta)
	{
		downVec = upperVec;
		upperVec = fillVec(teta, incPhi, radious, slices);

		for (size_t j = 0; j < slices - 1; j++)
		{
			Triangle tri1;
			tri1.A = upperVec[j + 1];
			tri1.B = downVec[j + 1];
			tri1.C = downVec[j];
			triangleSphre.push_back(tri1);

			Triangle tri;
			tri.A = upperVec[j];
			tri.B = upperVec[j + 1];
			tri.C = downVec[j];
			triangleSphre.push_back(tri);
		}

		Triangle tri1;
		tri1.A = upperVec[0];
		tri1.B = downVec[0];
		tri1.C = downVec[slices - 1];
		triangleSphre.push_back(tri1);

		Triangle tri;
		tri.A = upperVec[slices - 1];
		tri.B = upperVec[0];
		tri.C = downVec[slices - 1];
		triangleSphre.push_back(tri);
	}

	for (size_t i = 0; i < triangleSphre.size()-1; i++)
	{
		setNormal(triangleSphre[i]);
	}

	parser.write(triangleSphre, filepath);

	return 0;
}

std::vector<Vec> Sphere::fillVec(float teta, float incPhi, float radious, int slices)
{
	std::vector<Vec> vec = std::vector<Vec>(slices);

	float phi = 0;
	for (size_t i = 0; i < slices; i++)
	{

		vec[i].x = radious * sin(teta * PI / 180) * cos(phi * PI / 180);
		vec[i].y = radious * sin(teta * PI / 180) * sin(phi * PI / 180);
		vec[i].z = radious * cos(teta * PI / 180);
		phi += incPhi;

	}

	return vec;
}

void Sphere::setNormal(Triangle& triangle)
{
	Vec AB = { (triangle.B.x - triangle.A.x), (triangle.B.y - triangle.A.y), (triangle.B.z - triangle.A.z) };
	Vec AC = { (triangle.C.x - triangle.A.x), (triangle.C.y - triangle.C.y), (triangle.C.z - triangle.C.z) };

	Vec normal = {
		(AB.y * AC.z - AB.z * AC.y),
		-(AB.x * AC.z - AB.z * AC.x),
		(AB.x * AC.y - AB.y * AC.x)
	};

	float lenNormal = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));

	triangle.normal.x = normal.x / lenNormal;
	triangle.normal.y = normal.y / lenNormal;
	triangle.normal.z = normal.z / lenNormal;
}