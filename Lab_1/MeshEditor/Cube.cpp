#include "Cube.h"
#include <sstream>

int Cube::execute(const std::map<std::string, std::string>& args) 
{
	Vec centralPoint;
	TriangleSoup triangleCube = {};
	std::string origin = args.find("origin")->second;
	float L = std::stof(args.find("L")->second);

	origin = origin.substr(1, origin.length() - 2);

	std::vector<std::string> token;
	std::stringstream input_stringstream(origin);
	std::string parsed;
	while (getline(input_stringstream, parsed, ','))
	{
		if (parsed == "") continue;
		token.push_back(parsed);
	}

	centralPoint.x = std::stof(token[0]);
	centralPoint.y = std::stof(token[1]);
	centralPoint.z = std::stof(token[2]);
	
	Triangle triangle;



	setNormal(triangle);

	parser.write(triangleCube, args.find("filepath")->second);

	return 0;
}

void Cube::setNormal(Triangle& triangle) 
{
	Vec AB = {(triangle.B.x - triangle.A.x), (triangle.B.y - triangle.A.y), (triangle.B.z - triangle.A.z) };
	Vec AC = { (triangle.C.x - triangle.A.x), (triangle.C.y - triangle.C.y), (triangle.C.z - triangle.C.z) };

	Vec normal = {
		(AB.y * AC.z - AB.z * AC.y),
		- (AB.x * AC.z - AB.z * AC.x),
		(AB.x * AC.y - AB.y * AC.x)
	};

	float lenNormal = sqrt(pow(normal.x, 2) + pow(normal.y, 2)+ pow(normal.z, 2));

	triangle.normal.x = normal.x / lenNormal;
	triangle.normal.y = normal.y / lenNormal;
	triangle.normal.z = normal.z / lenNormal;
}