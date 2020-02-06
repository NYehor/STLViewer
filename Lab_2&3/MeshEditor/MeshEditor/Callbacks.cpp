#include "Callbacks.h"

Callbacks::Callbacks(Viewport& viewport, Scene& scene, GLWindow& window):
	viewport(viewport),
	scene(scene)
{
	using namespace std::placeholders;
	window.setKeyCallback(std::bind(&Callbacks::onKeyCallback, this, _1, _2, _3));
	window.setMouseCallback(std::bind(&Callbacks::onMouseInput, this, _1, _2, _3, _4, _5));
	window.setCursorPosCallback(std::bind(&Callbacks::onMouseMove, this, _1, _2));
}

void Callbacks::moveCamera(Camera& camera, glm::vec3 offset)
{
	camera.translate(offset * 0.5f);
}

void Callbacks::moveCube(glm::vec3 offset)
{

}

void Callbacks::onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP && Action::Press == action)
		moveCube(glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::DOWN && Action::Press == action)
		moveCube(glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::LEFT && Action::Press == action)
		moveCube(glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::RIGHT && Action::Press == action)
		moveCube(glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::W && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::S && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::A && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::D && Action::Press == action)
		moveCamera(viewport.getCamera(), glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::F1 && Action::Press == action)
		viewport.getCamera().setFrontView();
	if (key == KeyCode::F2 && Action::Press == action)
		viewport.getCamera().setRearView();
	if (key == KeyCode::F3 && Action::Press == action)
		viewport.getCamera().setRightView();
	if (key == KeyCode::F4 && Action::Press == action)
		viewport.getCamera().setLeftView();
	if (key == KeyCode::F5 && Action::Press == action)
		viewport.getCamera().setTopView();
	if (key == KeyCode::F6 && Action::Press == action)
		viewport.getCamera().setBottomView();
	if (key == KeyCode::F7 && Action::Press == action)
		viewport.getCamera().setIsoView();

	if (key == KeyCode::F8 && Action::Press == action)
		viewport.setParallelProjection(true);
	if (key == KeyCode::F9 && Action::Press == action)
		viewport.setParallelProjection(false);
}

float lastMX = 0, lastMY = 0, curMX = 0, curMY = 0;
bool arcballOn = false;

glm::vec3 Callbacks::getArcballVector(float x, float y)
{
	glm::vec3 p = glm::vec3(x / (0.5 * viewport.getWidth()) - 1.f, y / (0.5 * viewport.getHeight()) - 1.f, 0.f);
	p.y = -p.y;

	float length = p.x * p.x + p.y * p.y;
	if (length >= 1.0f)
		p = glm::normalize(p);
	else
		p.z = sqrt(1.0f - length);
	return p;
}

void Callbacks::onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y)
{
	if (ButtonCode::Button_LEFT == button && Action::Press == action)
	{
		arcballOn = true;
		lastMX = curMX = (float)x;
		lastMY = curMY = (float)y;
	}
	else
	{
		arcballOn = false;
	}
	auto r = viewport.calcCursorRay(lastMX, lastMY);
}

void Callbacks::onMouseMove(double x, double y)
{
	if (arcballOn)
	{
		curMX = (float)x;
		curMY = (float)y;

		if (curMX != lastMX || curMY != lastMY)
		{
			auto a = getArcballVector((float)lastMX, (float)lastMY);
			auto b = getArcballVector((float)curMX, (float)curMY);

			viewport.getCamera().orbit(a, b);

			lastMX = curMX;
			lastMY = curMY;
		}
	}

}