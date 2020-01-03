#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.h";

struct ray
{
	glm::vec3 orig;
	glm::vec3 dir{ 0,0,1};
};

class Viewport
{
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

	ray calcCursorRay() const;

	float calcTargetPlaneWidth() const;
	float calcTargetPlaneHeight() const;
	float calcAspectRatio() const;

	Camera& getCamera();
	const Camera& getCamera() const;

private:
	float zNear;
	float zFar;
	float fov;
	uint32_t width;
	uint32_t height;
	bool parallelProjection;
	Camera camera;
};
