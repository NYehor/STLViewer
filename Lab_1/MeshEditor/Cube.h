#include "Command.h"
#include "STLParser.h"

class Cube: public Command
{
private:
	const std::string name = "Cube";
	STLParser parser;
	void setNormal(Triangle& triangle);
public:
	const std::string& getName() const override
	{
		return name;
	}

	int execute(const std::map<std::string, std::string>& args) override;
};

