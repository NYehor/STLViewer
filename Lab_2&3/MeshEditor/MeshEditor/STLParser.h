#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "GLRenderSystem.h"

using TriangleSoup = std::vector<Vertex>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
private:
	glm::vec3 convertToVec(char* facet);
	TriangleSoup readBinary(const std::string& filename);
	TriangleSoup readASCII(const std::string& filename);
	glm::vec3 readVec(std::ifstream& file);
	TriangleSoup readFacet(std::ifstream& file);
};