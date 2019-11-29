#include "GLRenderSystem.h";

void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
	worldMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getWorldMatrix() const
{
	return worldMatrix;
}

void GLRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
	viewMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getViewMatrix() const
{
	return viewMatrix;
}

void GLRenderSystem::setProjMatrix(const glm::mat4& matrix)
{
	projMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getProjMatrix()
{
	return projMatrix;
}

void GLRenderSystem::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void GLRenderSystem::setViewport(double x, double y, double width, double height)
{
	glViewport(x, y, width, height);
}

void GLRenderSystem::clearDisplay(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}