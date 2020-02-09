#include "Callbacks.h"

Callbacks::Callbacks(Viewport& viewport, Scene& scene, GLWindow& window):
	_viewport(viewport),
	_scene(scene)
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

void Callbacks::moveModel(glm::vec3 offset)
{
	if (_scene.getSelectedModel() == nullptr) return;
	
	glm::mat4 matrix = _scene.getSelectedModel()->getModelMatrix();
	_scene.getSelectedModel()->setModelMatrix(glm::translate(matrix, offset * 0.5f));
}

void Callbacks::onKeyCallback(KeyCode key, Action action, Modifier mods)
{
	if (key == KeyCode::UP && Action::Press == action)
		moveModel(glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::DOWN && Action::Press == action)
		moveModel(glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::LEFT && Action::Press == action)
		moveModel(glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::RIGHT && Action::Press == action)
		moveModel(glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::W && Action::Press == action)
		moveCamera(_viewport.getCamera(), glm::vec3{ 0, 1, 0 });
	if (key == KeyCode::S && Action::Press == action)
		moveCamera(_viewport.getCamera(), glm::vec3{ 0, -1, 0 });
	if (key == KeyCode::A && Action::Press == action)
		moveCamera(_viewport.getCamera(), glm::vec3{ -1, 0, 0 });
	if (key == KeyCode::D && Action::Press == action)
		moveCamera(_viewport.getCamera(), glm::vec3{ 1, 0, 0 });

	if (key == KeyCode::F1 && Action::Press == action)
		_viewport.getCamera().setFrontView();
	if (key == KeyCode::F2 && Action::Press == action)
		_viewport.getCamera().setRearView();
	if (key == KeyCode::F3 && Action::Press == action)
		_viewport.getCamera().setRightView();
	if (key == KeyCode::F4 && Action::Press == action)
		_viewport.getCamera().setLeftView();
	if (key == KeyCode::F5 && Action::Press == action)
		_viewport.getCamera().setTopView();
	if (key == KeyCode::F6 && Action::Press == action)
		_viewport.getCamera().setBottomView();
	if (key == KeyCode::F7 && Action::Press == action)
		_viewport.getCamera().setIsoView();

	if (key == KeyCode::F8 && Action::Press == action)
		_viewport.setParallelProjection(true);
	if (key == KeyCode::F9 && Action::Press == action)
		_viewport.setParallelProjection(false);

	if (key == KeyCode::F10 && Action::Press == action)
	{
		if (_scene.getSelectedModel() != nullptr)
			_scene.getSelectedModel()->setOctreeVisible(true);
	}

	if (key == KeyCode::F11 && Action::Press == action)
	{
		if (_scene.getSelectedModel() != nullptr)
			_scene.getSelectedModel()->setOctreeVisible(false);
	}
}

void Callbacks::onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y)
{
	_mouse.setInput(button, action, modifier);
	_mouse.setCurrentPosition((float)x, (float)y);
	_mouse.setLastPosition((float)x, (float)y);

	if (ButtonCode::Button_LEFT == _mouse.getButtonCode() &&
		Action::Press == _mouse.getAction() && Modifier::Control == _mouse.getModifier())
	{
		if(_scene.getSelectedModel() != nullptr)
		{
			_scene.getSelectedModel()->setColor(_scene.getBaseModelColor());
			_scene.setNullptrToSelectedModel();
		}

		ray r = _viewport.calcCursorRay((float)x, (float)y);
		if (!_scene.trySelectModel(r.orig, r.dir)) return;
		
		_scene.getSelectedModel()->setColor(glm::vec3(1, 0, 0));
	}
}

void Callbacks::onMouseMove(double x, double y)
{
	_mouse.setCurrentPosition((float)x, (float)y);

	if (ButtonCode::Button_LEFT == _mouse.getButtonCode() && Action::Press == _mouse.getAction())
	{
		if (_mouse.getCurrentPosition() == _mouse.getLastPosition()) return;
		
		glm::vec3 a = _viewport.getArcballVector(_mouse.getLastPosition().x, _mouse.getLastPosition().y);
		glm::vec3 b = _viewport.getArcballVector(_mouse.getCurrentPosition().x, _mouse.getCurrentPosition().y);

		_viewport.getCamera().orbit(a, b);	
	}

	if (ButtonCode::Button_RIGHT == _mouse.getButtonCode() && Action::Press == _mouse.getAction())
	{
	}
}