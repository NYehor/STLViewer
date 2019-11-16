#include "Command.h"
#include "STLParser.h"

class Sphere : public Command
{
private:
	const std::string name = "Sphere";
	STLParser parser;
public:
	const std::string& getName() const override
	{
		return name;
	}

	int execute(const std::map<std::string, std::string>& args) override
	{
		return 0;
	}
};


