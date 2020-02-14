#pragma once

#include <memory>
#include <vector>
#include <map>
#include "Model.h"
#include <string>

class Scene
{
public:
	Scene(GLRenderSystem& renderSystem);
	std::vector<std::string> getListOfExistModel();

	void setNullptrToSelectedModel();
	void addModel(const char* filePath, glm::vec3 position);
	void addModel(std::string name, const std::vector<Vertex>& vertexs);
	void splitSelectedModel(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	void draw();

	Model* getSelectedModel();
	glm::vec3 getBaseModelColor();
	bool trySelectModel(const glm::vec3& origin, const glm::vec3& direction);

private:
	glm::vec3 _baseModelColor;
	Model* _selectedModel;

	GLRenderSystem& _renderSystem;
	std::vector<Model> _models;
	std::map<std::string, std::shared_ptr<ModelBuffer>> _dataModelReferences;

	void normolizeModel(std::vector<Vertex>& vertexs);
	void translateToCenterOfMass(std::vector<Vertex>& vertexs);
};

