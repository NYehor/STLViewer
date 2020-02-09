#pragma once
#include "Viewport.h"
#include "GLWindow.h"
#include "Scene.h"
#include "Mouse.h"

class Callbacks
{
public:
	Callbacks(Viewport& viewport, Scene& scene, GLWindow& window);

private:
	Viewport& _viewport;
	Scene& _scene;
	Mouse _mouse;

	void onKeyCallback(KeyCode key, Action action, Modifier mods);
	void moveCamera(Camera& camera, glm::vec3 offset);
	void moveModel(glm::vec3 offset);
	void onMouseMove(double x, double y);
	void onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y);
};

