#include <memory>

#include "Application.h"
#include "Sphere.h"
#include "Cube.h"
//#include "Split.h"


int main(int argc, char *argv[])
{
	Application app;

	app.registerCommand(std::make_unique<Sphere>());
	app.registerCommand(std::make_unique<Cube>());
	//app.registerCommand(std::make_unique<Split>());

	return app.execute(argc, argv);
}