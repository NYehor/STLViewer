#pragma once
#include "Viewport.h"
#include "GLWindow.h"
#include "Scene.h"

class Callbacks
{
public:
	Callbacks(Viewport& viewport, Scene& scene, GLWindow& window);

private:
	Viewport& viewport;
	Scene& scene;

	void onKeyCallback(KeyCode key, Action action, Modifier mods);
	void moveCamera(Camera& camera, glm::vec3 offset);
	void moveCube(glm::vec3 offset);
	void onMouseMove(double x, double y);
	void onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y);
	glm::vec3 getArcballVector(float x, float y);
};

