#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

struct Vec { double x, y, z; };

struct Triangle
{
	Vec A, B, C;
	Vec nomal;
};

using TriangleSoup = std::vector<Triangle>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename)
	{
		TriangleSoup soup = {};
		std::string str;
		std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);

		char headerInfo[80] = "";
		char nTri[4];
		unsigned long nTriLong;

		if (fin) {
			fin.read(headerInfo, 80);
		}
		else {
			std::cout << "error" << std::endl;
		}

		if (fin) {
			fin.read(nTri, 4);
			nTriLong = *((unsigned*)nTri);
			std::cout << "n Tri: " << nTriLong << std::endl;

		}

		for (int i = 0; i < nTriLong; i++) {

			char facet[50];

			if (fin) {
				fin.read(facet, 50);

				Triangle triangle;
				triangle.nomal = convertToVec(facet);
				triangle.A = convertToVec(facet);
				triangle.B = convertToVec(facet);
				triangle.C = convertToVec(facet);

				soup.push_back(triangle);

			}
		}
		fin.close();

		return soup;
	}
	void write(const TriangleSoup& trianfleSoup, const std::string& filename);
private:
	Vec convertToVec(char* facet)
	{
		char f1[4] = { facet[0], facet[1], facet[2], facet[3] };
		char f2[4] = { facet[4], facet[5], facet[6], facet[7] };
		char f3[4] = { facet[8], facet[9], facet[10], facet[11] };

		Vec vector = { *((float*)f1), *((float*)f2), *((float*)f3) };

		return vector;
	};

	/*char convertToChar(Vec* vector)
	{


		return "";
	}*/
};

