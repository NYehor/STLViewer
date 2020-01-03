#include "Camera.h"

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(eye, forward, right);
}

glm::vec3 Camera::caclcForward()
{
	forward = glm::normalize(eye - target);
}

glm::vec3 Camera::calcRight()
{
	right = glm::normalize(glm::cross(up, forward));
}

double Camera::distanceFromEyeToTarget() const
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
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0,0,1 }, target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera:: setTopView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: setRearView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: setRightView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: setLeftView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,-1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: setBottomView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: setIsoView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera:: orbit(glm::vec3 a, glm::vec3 b){}
void Camera:: pan(double u, double v){}
void Camera:: zoom(double factor){}

void Camera:: translate(glm::vec3 delta)
{
	glm::mat4 matrix = glm::translate(glm::mat4(1.0), delta);
	eye = glm::vec3(matrix * glm::vec4(eye, 1.0));
	target = glm::vec3(matrix * glm::vec4(target, 1.0));
}

void Camera:: setDistanceToTarget(double D)
{
	eye = target - (target - eye) * glm::vec3(D);
}

void Camera:: transform(const glm::mat4& trf)
{
	eye = glm::vec3(trf * glm::vec4(eye, 1.0));
	target = glm::vec3(trf * glm::vec4(target, 1.0));
	up = glm::vec3(trf * glm::vec4(eye, 1.0));
	
}
void Camera::rotate(glm::vec3 point, glm::vec3 axis, float angle)
{
	translate(point);
	glm::mat4 matrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
	transform(matrix);
	translate(point);
}

void Camera:: setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)
{
	eye = newEye;
	target = newTarget;
	up = newUp;

	caclcForward();
	calcRight();
}