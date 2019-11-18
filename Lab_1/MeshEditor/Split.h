#include "Command.h"
#include "STLParser.h"

class Split : public Command
{
public:
	const std::string& getName() const override
	{
		return name;
	}
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string name = "Split";
	STLParser parser;
};

