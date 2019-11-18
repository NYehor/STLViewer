#include "Sphere.h"
#include <sstream>

int Sphere::execute(const std::map<std::string, std::string>& args)
{
	TriangleSoup triangleCube = {};
	float R = std::stof(args.find("R")->second);
	int slices = std::stoi(args.find("slices")->second);
	int rings = std::stoi(args.find("rings")->second);
	std::string filepath = args.find("filepath")->second;
	Vec centralPoint;

	// add function in Command?
	std::string origin = args.find("origin")->second;
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

	

	parser.write(triangleCube, filepath);

	return 0;
}