#include "Camera.h"

Camera::Camera()
{
	_eye = glm::vec3(0, 0, 1.5);
	_target = glm::vec3(0, 0, 0);
	_up = glm::vec3(0, 1, 0);
}

const glm::vec3& Camera::getUp() const
{
	return _up;
}

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(_eye, _target, _up);
}

glm::vec3 Camera::caclcForward() const
{
	return glm::normalize(_eye - _target);
}

glm::vec3 Camera::calcRight() const
{
	return glm::normalize(glm::cross(caclcForward(), _up));
}

float Camera::distanceFromEyeToTarget() const
{
	return glm::distance(_eye, _target);
}

const glm::vec3& Camera::getEye() const
{
	return _eye;
}

const glm::vec3& Camera::getTarget() const
{
	return _target;
}

void Camera:: setFrontView()
{
	float D = distanceFromEyeToTarget();
	setEyeTargetUp(_target + glm::vec3{ 0,0,1 }, _target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera:: setRearView()
{
	float D = distanceFromEyeToTarget();
	setEyeTargetUp(_target - glm::vec3{ 0,0,1 }, _target, { 0, 1, 0});
	setDistanceToTarget(D);
}

void Camera:: setRightView()
{
	glm::vec3 oldTarget = _target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setLeftView()
{
	glm::vec3 oldTarget = _target;
	setRearView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5f);
}

void Camera::setTopView()
{
	glm::vec3 oldTarget = _target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setBottomView()
{
	glm::vec3 oldTarget = _target;
	setRearView();
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() * 0.5f);
}

void Camera:: setIsoView()
{
	glm::vec3 oldTarget = _target;
	setFrontView();
	rotate(oldTarget, { 0,0,1 }, glm::pi<float>() / 6.f);
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() / 6.f);
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() / 6.f);
}

void Camera:: orbit(glm::vec3 a, glm::vec3 b)
{
	float angle = glm::acos(glm::dot(a, b));
	glm::vec3 axis = glm::cross(a, b);

	glm::mat4 translation = glm::translate(_target - _eye);
	glm::mat4 toWorldSpase = glm::inverse( calcViewMatrix() * glm::inverse(translation) );
	axis = glm::vec3(toWorldSpase * glm::vec4(axis, 1));

	glm::mat4 orbitMatrix = glm::inverse(glm::rotate(angle, axis));
	_eye = _target + glm::vec3(orbitMatrix * glm::vec4((_eye - _target), 0.f));
	_up = glm::vec3(orbitMatrix * glm::vec4(_up, 0.f));
}

void Camera:: pan(float u, float v)
{
	auto right = calcRight();
	_eye = glm::normalize(_eye + right * u + _up * v);
	_target = glm::normalize(_target + right * u + _up * v);
}

void Camera:: zoom(float factor)
{
	_eye += glm::vec3(0, 0, factor);
}

void Camera:: translate(glm::vec3 delta)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0), delta);

	_eye = glm::vec3(matrix * glm::vec4(_eye, 1.0));
	_target = glm::vec3(matrix * glm::vec4(_target, 1.0));
	_up = glm::normalize(glm::cross(calcRight(), caclcForward()));
}

void Camera:: setDistanceToTarget(float D)
{
	_eye = _target - (_target - _eye) * glm::vec3(D);
}

void Camera:: transform(const glm::mat4& trf)
{
	glm::vec3 newEye = glm::vec3(trf * glm::vec4(_eye, 1.0));
	glm::vec3 newTarget = glm::vec3(trf * glm::vec4(_target, 1.0));
	glm::vec3 newUp = glm::vec3(trf * glm::vec4(_up, 1.0));

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
	_eye = newEye;
	_target = newTarget;
	_up = newUp;
	_up = glm::normalize(glm::cross(calcRight(), caclcForward()));
}