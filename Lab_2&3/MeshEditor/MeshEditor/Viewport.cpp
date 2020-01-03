#include "Viewport.h"

Viewport::Viewport()
{
	 zNear = 0.01;
	 zFar = 500;
	 fov = 60;
	 width = 1;
	 height = 1;
	 parallelProjection = false;
}

glm::mat4 Viewport::calcProjectionMatrix() const
{
	return glm::perspective(glm::radians(fov), (float)width / height, zNear, zFar);
}

void Viewport::setViewportSize(uint32_t inWidth, uint32_t inHeight)
{
	width = inWidth;
	height = inHeight;
}

void Viewport::setFOV(float inFOV)
{
	fov = inFOV;
}

void Viewport::setZNear(float inZNear)
{
	zNear = inZNear;
}

void Viewport::setZFar(float inZFar)
{
	zFar = inZFar;
}
void Viewport::setParallelProjection(bool use)
{
	parallelProjection = use;
}

float Viewport::getZNear() const
{
	return zNear;
}

float Viewport::getZFar() const
{
	return zFar;
}

float Viewport::getFov() const
{
	return fov;
}

float Viewport::getWidth()
{
	return width;
}

float Viewport::getHeight()
{
	return height;
}

bool Viewport::isParallelProjection() const
{
	return parallelProjection;
}

ray Viewport::calcCursorRay() const
{

}

float Viewport::calcTargetPlaneWidth() const
{
	return calcTargetPlaneHeight()* calcAspectRatio();
}

float Viewport::calcTargetPlaneHeight() const
{
	return 2.0 * camera.distanceFromEyeToTarget() * tan(glm::radians(fov / 2.0));
}

float Viewport::calcAspectRatio() const
{
	
}

Camera& Viewport::getCamera()
{
	return camera;
}

const Camera& Viewport::getCamera() const
{
	return camera;
}