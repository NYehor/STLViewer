#include <vector>
#include <string>

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
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& trianfleSoup, const std::string& filename);
private:

};

