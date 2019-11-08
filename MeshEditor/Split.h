#include "Command.h"

class Split : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:

};

