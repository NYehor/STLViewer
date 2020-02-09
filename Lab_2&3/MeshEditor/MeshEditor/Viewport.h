#pragma once

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

struct ray
{
	glm::vec3 orig;
	glm::vec3 dir;

	ray(const glm::vec3& orig, const glm::vec3& dir) :
		orig(orig), dir(dir) {}
};

class Viewport
{
public:
	Viewport();
	glm::mat4 calcProjectionMatrix() const;

	void setViewportSize(uint32_t inWidth, uint32_t inHeight);
	void setFOV(float inFOV);
	void setZNear(float inZNear);
	void setZFar(float inZFar);
	void setParallelProjection(bool use);

	float getZNear() const;
	float getZFar() const;
	float getFov() const;
	float getWidth();
	float getHeight();
	bool isParallelProjection() const;

	ray calcCursorRay(float x, float y) const;

	float calcTargetPlaneWidth() const;
	float calcTargetPlaneHeight() const;
	float calcAspectRatio() const;

	glm::vec3 getArcballVector(float mouseX, float mouseY);

	Camera& getCamera();
	const Camera& getCamera() const;

private:
	float _zNear;
	float _zFar;
	float _fov;
	uint32_t _width;
	uint32_t _height;
	bool _parallelProjection;
	Camera _camera;
};

