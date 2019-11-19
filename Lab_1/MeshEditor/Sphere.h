#include "Command.h"
#include "STLParser.h"

class Sphere : public Command
{
private:
	const std::string name = "Sphere";
	STLParser parser;
	std::vector<Vec> fillVec(float phi, float incTeta, float radious, int slices);
	void setNormal(Triangle& triangle);
public:
	const std::string& getName() const override
	{
		return name;
	}

	int execute(const std::map<std::string, std::string>& args) override;
};


