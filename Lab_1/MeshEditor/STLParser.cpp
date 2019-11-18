#include "STLParser.h"
#include <sstream>

	TriangleSoup STLParser::read(const std::string& filename)
	{
		TriangleSoup soup = {};
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

	void STLParser::write(const TriangleSoup& trianfleSoup, const std::string& filename)
	{
		std::ofstream file;
		int nTri = trianfleSoup.size();

		file.open(filename);
		file << "solid NAME\n";
		for (int i = 0; i < nTri; i++)
		{
			Triangle triangle = trianfleSoup[i];
			file << " facet normal " + std::to_string(triangle.normal.x) + " " + std::to_string(triangle.normal.y) + " " + std::to_string(triangle.normal.z) + "\n";
			file << "  outer loop\n";
			file << "   vertex " + std::to_string(triangle.A.x) + " " + std::to_string(triangle.A.y) + " " + std::to_string(triangle.A.z) + "\n";
			file << "   vertex " + std::to_string(triangle.B.x) + " " + std::to_string(triangle.B.y) + " " + std::to_string(triangle.B.z) + "\n";
			file << "   vertex " + std::to_string(triangle.C.x) + " " + std::to_string(triangle.C.y) + " " + std::to_string(triangle.C.z) + "\n";
			file << "  endloop\n";
			file << " endfacet\n";


		}
		file << "endsolid NAME";
		file.close();
	}

	Vec STLParser::convertToVec(char* facet)
	{
		char f1[4] = { facet[0], facet[1], facet[2], facet[3] };
		char f2[4] = { facet[4], facet[5], facet[6], facet[7] };
		char f3[4] = { facet[8], facet[9], facet[10], facet[11] };

		Vec vector = { *((float*)f1), *((float*)f2), *((float*)f3) };

 		return vector;
	};

	TriangleSoup STLParser::readBinary(const std::string& filename)
	{
		TriangleSoup soup = {};
		std::ifstream fin(filename.c_str(), std::ios::binary);

		char headerInfo[80] = "";
		char nTri[4];
		unsigned long nTriLong = 0;

		if (fin.is_open())

			if (fin) {
				fin.read(headerInfo, 80);
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

		for (int i = 0; i < nTriLong; i++) {

			char facet[50];

			if (fin) {
				fin.read(facet, 50);

				Triangle triangle;
				triangle.normal = convertToVec(facet);
				triangle.A = convertToVec(facet + 12);
				triangle.B = convertToVec(facet + 24);
				triangle.C = convertToVec(facet + 36);
				soup.push_back(triangle);

			}
			else {
				std::cout << "error" << std::endl;
			}
		}
		fin.close();
		return soup;
	}

	TriangleSoup STLParser::readASCII(const std::string& filename)
	{
		TriangleSoup soup = {};

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

			while(true)
			{
				file >> word;
				if (word == "facet")
				{
					soup.push_back(readFacet(file));
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

	Triangle STLParser::readFacet(std::ifstream& file)
	{
		Triangle triangle = {};
		std::string word;
		file >> word;

		if (word == "normal")
			triangle.normal = readVec(file);
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
				file >> word;
				if (word == "vertex")
					triangle.A = readVec(file);
				file >> word;
				if (word == "vertex")
					triangle.B = readVec(file);
				file >> word;
				if (word == "vertex")
					triangle.C = readVec(file);

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

	Vec STLParser::readVec(std::ifstream& file)
	{
		std::string x, y, z;
		file >> x;
		file >> y;
		file >> z;
		Vec vec =
		{
			std::stof(x),
			std::stof(y),
			std::stof(z)
		};

		return vec;
	}