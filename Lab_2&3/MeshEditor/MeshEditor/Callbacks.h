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
	Viewport& viewport;
	Scene& scene;
	Mouse mouse;
	Model* selectedModel;
	glm::vec3 baseModelColor;

	void onKeyCallback(KeyCode key, Action action, Modifier mods);
	void moveCamera(Camera& camera, glm::vec3 offset);
	void moveModel(glm::vec3 offset);
	void onMouseMove(double x, double y);
	void onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y);
	glm::vec3 getArcballVector(float x, float y);
};

