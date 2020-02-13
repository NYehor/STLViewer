#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>

class Camera
{
public:
	Camera();
	glm::mat4 calcViewMatrix() const;

	glm::vec3 caclcForward() const;
	glm::vec3 calcRight() const;
	float distanceFromEyeToTarget() const;

	const glm::vec3& getEye() const;
	const glm::vec3& getTarget() const;
	const glm::vec3& getUp() const;

	void setFrontView();
	void setTopView();
	void setRearView();
	void setRightView();
	void setLeftView();
	void setBottomView();
	void setIsoView();

	void orbit(glm::vec3 a, glm::vec3 b);
	void pan(float u, float v);
	void zoom(float factor);

	void translate(glm::vec3 delta);
	void setDistanceToTarget(float D);
	void transform(const glm::mat4& trf);
	void rotate(glm::vec3 point, glm::vec3 axis, float angle);
	void setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp);

private:
	glm::vec3 _eye;
	glm::vec3 _target;
	glm::vec3 _up;
};


