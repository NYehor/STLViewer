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

void Callbacks::moveModel(glm::vec3 offset)
{
	if (selectedModel == nullptr) return;
	
	glm::mat4 matrix = selectedModel->getModelMatrix();
	selectedModel->setModelMatrix(glm::translate(matrix, offset * 0.5f));
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

	if (key == KeyCode::F10 && Action::Press == action)
	{
		if (selectedModel != nullptr) 
			selectedModel->setOctreeVisible(true);
	}

	if (key == KeyCode::F11 && Action::Press == action)
	{
		if (selectedModel != nullptr) 
			selectedModel->setOctreeVisible(false);
	}
}

glm::vec3 Callbacks::getArcballVector(float x, float y)
{
	glm::vec3 p = glm::vec3(x / (0.5 * viewport.getWidth()) - 1.f, 
							y / (0.5 * viewport.getHeight()) - 1.f, 0.f);
	p.y = -p.y;

	p.x = glm::clamp(p.x, -1.f, 1.f);
	p.y = glm::clamp(p.y, -1.f, 1.f);

	float length = p.x * p.x + p.y * p.y;
	if (length >= 1.0f)
		p = glm::normalize(p);
	else
		p.z = sqrt(1.0f - length);
	return p;
}

void Callbacks::onMouseInput(ButtonCode button, Action action, Modifier modifier, double x, double y)
{
	mouse.setInput(button, action, modifier);
	mouse.setCurrentPosition((float)x, (float)y);
	mouse.setLastPosition((float)x, (float)y);

	if (ButtonCode::Button_LEFT == mouse.getButtonCode() &&
		Action::Press == mouse.getAction() && Modifier::Control == mouse.getModifier())
	{
		if(selectedModel != nullptr)
		{
			selectedModel->setColor(baseModelColor);
			selectedModel = nullptr;
		}

		ray r = viewport.calcCursorRay((float)x, (float)y);

		bool isValid;
		Model& model = scene.trySelectModel(isValid, r.orig, r.dir);

		if (!isValid) return;
		
		selectedModel = &model;
		baseModelColor = selectedModel->getColor();
		selectedModel->setColor(glm::vec3(1, 0, 0));
	}
}

void Callbacks::onMouseMove(double x, double y)
{
	mouse.setCurrentPosition((float)x, (float)y);

	if (ButtonCode::Button_LEFT == mouse.getButtonCode() && Action::Press == mouse.getAction())
	{
		if (mouse.getCurrentPosition() == mouse.getLastPosition()) return;
		
		glm::vec3 a = getArcballVector(mouse.getLastPosition().x, mouse.getLastPosition().y);
		glm::vec3 b = getArcballVector(mouse.getCurrentPosition().x, mouse.getCurrentPosition().y);

		viewport.getCamera().orbit(a, b);	
	}

	if (ButtonCode::Button_RIGHT == mouse.getButtonCode() && Action::Press == mouse.getAction())
	{
	}
}