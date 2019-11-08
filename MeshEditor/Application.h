#include <memory>
#include <string>
#include <iostream>
#include "Command.h"

class Application
{
private:
	std::map<std::string, std::unique_ptr<Command>> dictionary;
public: 
	void registerCommand(std::unique_ptr<Command> command)
	{
		std::string name = command->getName();
		dictionary.insert(std::make_pair(name, std::move(command)));
		std::cout << "Add: "<<name << std::endl;
	}

	int execute(int argc, char* argv[])
	{

		std::unique_ptr<Command> command(std::move(dictionary.find(argv[1])->second));
		std::string name = command->getName();

		std::map<std::string, std::string> args;

		for (int i = 2; i < argc; i++)
		{
			std::string str = argv[i];
			if (str[str.length() - 1] == ',')
				str=str.substr(0, str.length() - 1);

			int pos = str.find("=");
			int fin = (int)str.length() - 1;
			std::string key = str.substr(0, pos);
			std::string value = str.substr(pos+1, fin);
			args.insert(make_pair(key, value));
		}

		return command->execute(args);
	}
};

