#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "GLRenderSystem.h"

class STLParser
{
public:
	std::string getName(const std::string& filename);
	std::vector<Vertex> read(const std::string& filename);

private:
	glm::vec3 convertToVec(char* faceht);
	std::vector<Vertex> readBinary(const std::string& filename);
	std::vector<Vertex> readASCII(const std::string& filename);
	glm::vec3 readVec(std::ifstream& file);
	std::vector<Vertex> readFacet(std::ifstream& file);
};