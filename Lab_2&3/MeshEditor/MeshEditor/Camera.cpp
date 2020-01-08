#include "Camera.h"

Camera::Camera()
{
	eye = glm::vec3(0, 0, 2);
	target = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(eye, target, up);
}

glm::vec3 Camera::caclcForward() const
{
	return glm::normalize(eye - target);
}

glm::vec3 Camera::calcRight() const
{
	return glm::normalize(glm::cross(caclcForward(), up));
}

float Camera::distanceFromEyeToTarget() const
{
	return glm::distance(eye, target);
}

const glm::vec3& Camera::getEye() const
{
	return eye;
}

const glm::vec3& Camera::getTarget() const
{
	return target;
}

void Camera:: setFrontView()
{
	float D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0,0,1 }, target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera:: setRearView()
{
	float D = distanceFromEyeToTarget();
	setEyeTargetUp(target - glm::vec3{ 0,0,1 }, target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera:: setRightView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setLeftView()
{
	glm::vec3 oldTarget = target;
	setRearView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5f);
}

void Camera::setTopView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setBottomView()
{
	glm::vec3 oldTarget = target;
	setRearView();
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setIsoView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,0,1 }, glm::pi<float>() / 6.f);
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() / 6.f);
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() / 6.f);
}

void Camera:: orbit(glm::vec3 a, glm::vec3 b)
{
	float angle = glm::acos(glm::dot(a, b));
	glm::vec3 axis = glm::cross(a, b);

	glm::mat4 T = glm::translate(glm::mat4(1.0f), eye);
	glm::mat4 R = calcViewMatrix() * glm::inverse(T);
	glm::mat4 worldCameraSpace = glm::inverse(R) * T;

	axis = glm::vec3(worldCameraSpace * glm::vec4(axis, 1));
	glm::mat4 orbitMatrix = glm::rotate(glm::degrees(angle), axis);

	eye = target + glm::vec3(orbitMatrix * glm::vec4((eye - target), 1.f));
	up = glm::vec3(orbitMatrix * glm::vec4(up, 1.f));
}

void Camera:: pan(float u, float v)
{
	auto right = calcRight();
	eye = glm::normalize(eye + right * u + up * v);
	target = glm::normalize(target + right * u + up * v);
}

void Camera:: zoom(float factor)
{
	eye += glm::vec3(0, 0, factor);
}

void Camera:: translate(glm::vec3 delta)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0), delta);

	eye = glm::vec3(matrix * glm::vec4(eye, 1.0));
	target = glm::vec3(matrix * glm::vec4(target, 1.0));
	up = glm::normalize(glm::cross(calcRight(), caclcForward()));
}

void Camera:: setDistanceToTarget(float D)
{
	eye = target - (target - eye) * glm::vec3(D);
}

void Camera:: transform(const glm::mat4& trf)
{
	glm::vec3 newEye = glm::vec3(trf * glm::vec4(eye, 1.0));
	glm::vec3 newTarget = glm::vec3(trf * glm::vec4(target, 1.0));
	glm::vec3 newUp = glm::vec3(trf * glm::vec4(up, 1.0));

	setEyeTargetUp(newEye, newTarget, newUp);
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float angle)
{
	translate(point);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), angle, axis);
	transform(matrix);
	translate(point);
}

void Camera:: setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
	eye = newEye;
	target = newTarget;
	up = newUp;
	up = glm::normalize(glm::cross(calcRight(), caclcForward()));
}