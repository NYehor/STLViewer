#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

struct Vec { float x, y, z; };

struct Triangle
{
	Vec A, B, C;
	Vec normal;
};

using TriangleSoup = std::vector<Triangle>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& trianfleSoup, const std::string& filename);
private:
	Vec convertToVec(char* facet);
	Vec convertToVec(std::vector<std::string> token, int idx);
	TriangleSoup readBinary(const std::string& filename);
	TriangleSoup readASCII(const std::string& filename);
};

