#include "Viewport.h"

Viewport::Viewport()
{
	 _zNear = 0.01f;
	 _zFar = 500.f;
	 _fov = 60.f;
	 _width = 1;
	 _height = 1;
	 _parallelProjection = false;
}

glm::mat4 Viewport::calcProjectionMatrix() const
{
	if (_parallelProjection)
	{
		float halfWidth = calcTargetPlaneWidth() / 2.f;
		float halfHeight = calcTargetPlaneHeight() / 2.f;
		return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, _zNear, _zFar);
	}
	else
		return glm::perspective(glm::radians(_fov), calcAspectRatio(), _zNear, _zFar);
}

void Viewport::setViewportSize(uint32_t inWidth, uint32_t inHeight)
{
	_width = inWidth;
	_height = inHeight;
}

void Viewport::setFOV(float inFOV)
{
	_fov = inFOV;
}

void Viewport::setZNear(float inZNear)
{
	_zNear = inZNear;
}

void Viewport::setZFar(float inZFar)
{
	_zFar = inZFar;
}
void Viewport::setParallelProjection(bool use)
{
	_parallelProjection = use;
}

float Viewport::getZNear() const
{
	return _zNear;
}

float Viewport::getZFar() const
{
	return _zFar;
}

float Viewport::getFov() const
{
	return _fov;
}

float Viewport::getWidth()
{
	return (float)_width;
}

float Viewport::getHeight()
{
	return (float)_height;
}

bool Viewport::isParallelProjection() const
{
	return _parallelProjection;
}

ray Viewport::calcCursorRay(float x, float y) const
{
	glm::vec4 viewport(0.0f, 0.0f, _width, _height);
	glm::mat4 projection = calcProjectionMatrix();
	glm::mat4 model = _camera.calcViewMatrix();
	
	glm::vec3 a = glm::unProject({ x, _height - y, 0.f }, model, projection, viewport);
	glm::vec3 b = glm::unProject({ x, _height - y, 1.f }, model, projection, viewport);

	return ray(a , glm::normalize(b - a));
}

float Viewport::calcTargetPlaneWidth() const
{
	return (float)(calcTargetPlaneHeight() * calcAspectRatio());
}

float Viewport::calcTargetPlaneHeight() const
{
	return 2.0f * _camera.distanceFromEyeToTarget() * (float)tan(glm::radians(_fov / 2.0f));
}

float Viewport::calcAspectRatio() const
{
	return (float)_width / (float)_height;
}

Camera& Viewport::getCamera()
{
	return _camera;
}

const Camera& Viewport::getCamera() const
{
	return _camera;
}

glm::vec3 Viewport::getArcballVector(float mouseX, float mouseY)
{
	float mx = mouseX / (0.5 * (float)_width) - 1.f;
	float my = -(mouseY / (0.5 * (float)_height) - 1.f);

	float tetha = sqrtf(mx * mx + my * my);
	float phi = atan2f(my, mx);

	glm::vec3 vec;
	vec.x = sinf(tetha) * cosf(phi);
	vec.y = sinf(tetha) * sinf(phi);
	vec.z = cosf(tetha);

	return vec;
}