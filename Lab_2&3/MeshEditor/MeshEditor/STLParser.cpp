#include "STLParser.h"
#include <sstream>

std::string STLParser::getName(const std::string& filename)
{
	std::string name;
	std::string line;
	std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);

	if (fin.is_open()) {
		getline(fin, line);
	}
	
	fin.seekg(0, std::ios::beg);
	if (line.find("solid") != std::string::npos) 
	{

		std::string word;
		fin >> word;
		fin >> name; // read name file
	}
	else 
	{
		char headerInfo[80] = "";
		fin.read(headerInfo, 80);
		name = headerInfo;		
	}
	fin.close();

	return name;
}

std::vector<Vertex> STLParser::read(const std::string& filename)
{
	std::vector<Vertex> soup = {};
	std::string line;
	std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);

	if (fin.is_open()) {
		getline(fin, line);
	}
	fin.close();

	if (line.find("solid") != std::string::npos) {
		soup = readASCII(filename);
	}
	else {
		soup = readBinary(filename);
	}

	return soup;
}

glm::vec3 STLParser::convertToVec(char* facet)
{
	char f1[4] = { facet[0], facet[1], facet[2], facet[3] };
	char f2[4] = { facet[4], facet[5], facet[6], facet[7] };
	char f3[4] = { facet[8], facet[9], facet[10], facet[11] };

	glm::vec3 vector = glm::vec3( *((float*)f1), *((float*)f2), *((float*)f3) );

	return vector;
};

std::vector<Vertex> STLParser::readBinary(const std::string& filename)
{
	std::vector<Vertex> soup = {};
	std::ifstream fin(filename.c_str(), std::ios::binary);

	std::string str;
	char nTri[4];
	unsigned long nTriLong = 0;

	if (fin.is_open())

		if (fin) {
			char headerInfo[80] = "";
			fin.read(headerInfo, 80);
			str = headerInfo;
		}
		else {
			std::cout << "error" << std::endl;
		}

	if (fin) {
		fin.read(nTri, 4);
		nTriLong = *((unsigned*)nTri);
	}
	else {
		std::cout << "error" << std::endl;
	}

	for (unsigned long i = 0; i < nTriLong; i++) {

		char facet[50];

		if (fin) {
			fin.read(facet, 50);

			glm::vec3 normal = convertToVec(facet);
			soup.push_back({ convertToVec(facet + 12), normal });
			soup.push_back({ convertToVec(facet + 24), normal });
			soup.push_back({ convertToVec(facet + 36), normal });

		}
		else {
			std::cout << "error" << std::endl;
		}
	}
	fin.close();
	return soup;
}

std::vector<Vertex> STLParser::readASCII(const std::string& filename)
{
	std::vector<Vertex> soup = {};

	std::ifstream file(filename, std::ios::in);
	std::string word;


	if (file.is_open())
	{
		file >> word;
		if (word != "solid")
		{
			file.close();
			// throw execepetion
		}
		file >> word; // read name file

		while (true)
		{
			file >> word;
			if (word == "facet")
			{
				std::vector<Vertex> s = readFacet(file);
				soup.insert(soup.end(), s.begin(), s.end());
			}

			if (word == "endsolid")
				break;
			else
			{
				// throw 
			}
		}

		file.close();
	}

	return soup;
}

std::vector<Vertex> STLParser::readFacet(std::ifstream& file)
{
	std::vector<Vertex> triangle = {};
	std::string word;
	file >> word;
	glm::vec3 normal = glm::vec3(0, 0, 0);

	if (word == "normal")
		normal = readVec(file);
	else
	{
		// throw exception
		
	}

	file >> word;
	if (word == "outer")
	{
		file >> word;
		if (word == "loop")
		{
			for (size_t i = 0; i < 3; i++)
			{
				file >> word;
				if (word == "vertex")
					triangle.push_back({ readVec(file), normal });
			}
			file >> word;
			if (word == "endloop")
			{
				file >> word;
				if (word == "endfacet")
				{
					return triangle;
				}
			}
		}
	}

	// throw exception
	return triangle;
}

glm::vec3 STLParser::readVec(std::ifstream& file)
{
	std::string x, y, z;
	file >> x;
	file >> y;
	file >> z;

	glm::vec3 vec =
	{
		std::stof(x),
		std::stof(y),
		std::stof(z)
	};

	return vec;
}