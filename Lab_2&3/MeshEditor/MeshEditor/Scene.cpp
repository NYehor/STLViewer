#include "Scene.h"
#include "STLParser.h"

Scene::Scene(GLRenderSystem& renderSystem) :
    _renderSystem(renderSystem),
	_baseModelColor(1.f),
	_selectedModel(nullptr) {}

glm::vec3 Scene::getBaseModelColor()
{
	return _baseModelColor;
}

Model* Scene::getSelectedModel()
{
	return _selectedModel;
}

void Scene::setNullptrToSelectedModel()
{
	_selectedModel = nullptr;
}

std::vector<std::string> Scene::getListOfExistModel()
{
    std::vector<std::string> retval;
    for (auto const& element : _dataModelReferences) {
        retval.push_back(element.first);
    }
    return retval;
}

void Scene::addModel(const char* filePath, glm::vec3 position)
{
    STLParser parser;
    std::string name = parser.getName(filePath);

	auto itr = _dataModelReferences.find(name);
	if (itr != _dataModelReferences.end() && itr->first == name)
	{
		_models.push_back(Model(_renderSystem, itr->second));
		glm::mat4 matrix = glm::translate(glm::mat4(1.f), position);
		_models.back().setModelMatrix(matrix);
		
		return;
	}

	auto arr = parser.read(filePath);
	normolizeModel(arr);
	translateToCenterOfMass(arr);
	std::shared_ptr<ModelBuffer> bufferPtr(new ModelBuffer(_renderSystem, arr));
	_dataModelReferences.insert(std::pair<std::string, std::shared_ptr<ModelBuffer>>(name, bufferPtr));

    _models.push_back(Model(_renderSystem, bufferPtr));
	glm::mat4 matrix = glm::translate(glm::mat4(1.f), position);
	_models.back().setModelMatrix(matrix);
}

bool Scene::trySelectModel(const glm::vec3& origin, const glm::vec3& direction)
{
	int index = -1;
	float minDistance = std::numeric_limits<float>::max();
	for (size_t i = 0, ilen = _models.size(); i < ilen; i++)
	{
		float distance = _models[i].calcDistanceIntersection(origin, direction);
		if (minDistance > distance)
		{
			minDistance = distance;
			index = i;
		}
	}

	if (index != -1)
	{

		_selectedModel = &_models[index];
		return true;
	}

	return false;
}

void Scene::draw()
{
    for (size_t i = 0, ilen = _models.size(); i < ilen; i++)
    {
        _models[i].draw();
    }
}

void Scene::normolizeModel(std::vector<Vertex>& vertexs)
{
	float maxLength = 0;
	for (size_t i = 1, ilen = vertexs.size(); i < ilen; i++)
	{
		float length = glm::length(vertexs[i].position);
		if (maxLength < length)
			maxLength = length;
	}

	if (maxLength < 1.f) return;

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i++)
	{
		vertexs[i].position = vertexs[i].position / maxLength;
		vertexs[i].normal = glm::normalize(vertexs[i].normal);
	}
}

void Scene::translateToCenterOfMass(std::vector<Vertex>& vertexs)
{
	glm::vec3 sumOfVertex = glm::vec3(0.0);

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i += 3)
	{
		glm::vec3 p1 = vertexs[i].position;
		glm::vec3 p2 = vertexs[i + 1].position;
		glm::vec3 p3 = vertexs[i + 2].position;

		sumOfVertex += glm::vec3(
			(p1.x + p2.x + p3.x) / 3.f,
			(p1.y + p2.y + p3.y) / 3.f,
			(p1.z + p2.z + p3.z) / 3.f
		);
	}

	glm::vec3 centr = sumOfVertex / ((float)vertexs.size() / 3.f);
	glm::mat4 matrix = glm::translate(glm::mat4(1.f), -centr);

	for (size_t i = 0, ilen = vertexs.size(); i < ilen; i++)
	{
		vertexs[i].position = glm::vec3(matrix * glm::vec4(vertexs[i].position, 1));
		vertexs[i].normal = glm::vec3(matrix * glm::vec4(vertexs[i].normal, 1));
	}
}