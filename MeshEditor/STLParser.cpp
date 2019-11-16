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
		std::ofstream fout;
		int nTri = trianfleSoup.size();

		std::string file;
		file += "solid NAME\n";
		for (int i = 0; i < nTri; i++)
		{
			Triangle triangle = trianfleSoup[i];
			file += " facet normal " + std::to_string(triangle.normal.x) + " " + std::to_string(triangle.normal.y) + " " + std::to_string(triangle.normal.z) + "\n";
			file += "  outer loop\n";
			file += "   vertex " + std::to_string(triangle.A.x) + " " + std::to_string(triangle.A.y) + " " + std::to_string(triangle.A.z) + "\n";
			file += "   vertex " + std::to_string(triangle.B.x) + " " + std::to_string(triangle.B.y) + " " + std::to_string(triangle.B.z) + "\n";
			file += "   vertex " + std::to_string(triangle.C.x) + " " + std::to_string(triangle.C.y) + " " + std::to_string(triangle.C.z) + "\n";
			file += "  endloop\n";
			file += " endfacet\n";


		}
		file += "endsolid NAME";

		fout.open(filename);
		fout << file << "\0";
		fout.close();
	}

	Vec STLParser::convertToVec(char* facet)
	{
		char f1[4] = { facet[0], facet[1], facet[2], facet[3] };
		char f2[4] = { facet[4], facet[5], facet[6], facet[7] };
		char f3[4] = { facet[8], facet[9], facet[10], facet[11] };

		Vec vector = { *((float*)f1), *((float*)f2), *((float*)f3) };

 		return vector;
	};

	Vec STLParser::convertToVec(std::vector<std::string> token, int idx)
	{
		float x = std::stof(token[idx]);
		float y = std::stof(token[idx + 1]);
		float z = std::stof(token[idx + 2]);
		Vec vector = { x, y , z };

		return vector;
	};

	TriangleSoup STLParser::readBinary(const std::string& filename)
	{
		TriangleSoup soup = {};
		std::ifstream fin(filename.c_str(), std::ios::binary);
		
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
				triangle.A = convertToVec(facet);
				triangle.B = convertToVec(facet);
				triangle.C = convertToVec(facet);
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
		std::ifstream fin(filename.c_str(), std::ios::in );
		std::string text;
		std::string tmp;
		if (fin.is_open())
		{
			while (getline(fin, tmp))
				text += tmp + " ";
		}
		fin.close();

		std::vector<std::string> token;
		std::stringstream input_stringstream(text);
		std::string parsed;
		
		while (getline(input_stringstream, parsed, ' '))
		{		
			if (parsed == "") continue;
			token.push_back(parsed);
		}

		if (token[0] != "solid"); // exption
		for (int i = 2; i < token.size(); i++)
		{
			Triangle triangle;
			if (token[i] == "facet" && token[i + 1] == "normal")
			{
				i += 2;
				triangle.normal = convertToVec(token, i);
				i += 3;

				if (token[i] == "outer" && token[i + 1] == "loop")
				{
					i += 2;
					if (token[i] == "vertex")
					{
						i++;
						triangle.A = convertToVec(token, i);
						i += 3;
					}
					if (token[i] == "vertex")
					{
						i++;
						triangle.B = convertToVec(token, i);
						i += 3;
					}
					if (token[i] == "vertex")
					{
						i++;
						triangle.C = convertToVec(token, i);
						i += 3;
					}

					if (token[i] == "endloop" && token[i + 1] == "endfacet") i++;
				}
			}

			soup.push_back(triangle);
		}

		return soup;
	}