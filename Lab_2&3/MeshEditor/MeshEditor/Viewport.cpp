#include "Viewport.h"

Viewport::Viewport()
{
	 zNear = 0.01f;
	 zFar = 500.f;
	 fov = 60.f;
	 width = 1;
	 height = 1;
	 parallelProjection = false;
}

glm::mat4 Viewport::calcProjectionMatrix() const
{
	if (parallelProjection)
		return glm::ortho(-(float)width / 2.f, (float)width / 2.f, -(float)height / 2.f, (float)height / 2.f, zNear, zFar);
	else
		return glm::perspective(glm::radians(fov), calcAspectRatio(), zNear, zFar);
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
	return (float)width;
}

float Viewport::getHeight()
{
	return (float)height;
}

bool Viewport::isParallelProjection() const
{
	return parallelProjection;
}

ray Viewport::calcCursorRay(float x, float y) const
{
	glm::vec4 viewport(0.0f, 0.0f, width, height);
	glm::mat4 projection = calcProjectionMatrix();
	glm::mat4 model = glm::mat4(1.0f);

	float mauseX = x / (0.5 * width) - 1;
	float mauseY = x / (0.5 * height) - 1;
	
	glm::vec3 a = glm::unProject({ mauseX, -mauseY, -1 }, model, projection, viewport);
	glm::vec3 b = glm::unProject({ mauseX, -mauseY,  1 }, model, projection, viewport);

	return { a , glm::normalize(b - a) };
}

float Viewport::calcTargetPlaneWidth() const
{
	return (float)(calcTargetPlaneHeight() * calcAspectRatio());
}

float Viewport::calcTargetPlaneHeight() const
{
	return 2.0f * camera.distanceFromEyeToTarget() * (float)tan(glm::radians(fov / 2.0f));
}

float Viewport::calcAspectRatio() const
{
	return (float)width / height;
}

Camera& Viewport::getCamera()
{
	return camera;
}

const Camera& Viewport::getCamera() const
{
	return camera;
}

glm::vec2 Viewport::convertToTargetPlane(float cursorX, float cursorY) const
{
	ray r = calcCursorRay(cursorX, cursorY);
	glm::vec3 tmp = camera.getEye() + r.dir * camera.distanceFromEyeToTarget();
	return { tmp.x, tmp.y };
}