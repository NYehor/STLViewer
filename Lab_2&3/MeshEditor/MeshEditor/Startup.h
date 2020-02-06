#pragma once

#include "GLRenderSystem.h"
#include "GLWindow.h"
#include "Viewport.h"

class Startup
{
public:
	Startup(size_t width, size_t height, 
		const char* title,
		const char* vertexFilePath, 
		const char* fragmentFilePath);

	GLRenderSystem& getRenderSystem();
	GLWindow& getWindow();
	Viewport& getViewport();

	void mainLoop();

private:
	GLRenderSystem renderSystem;
	GLWindow window;
	Viewport viewport;
};

