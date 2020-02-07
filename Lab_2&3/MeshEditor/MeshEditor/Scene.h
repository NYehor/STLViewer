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

	void addModel(const char* filePath, glm::vec3 position);
	Model& trySelectModel(bool& isValid, const glm::vec3& origin, const glm::vec3& direction);
	void draw();

private:
	GLRenderSystem& renderSystem;
	std::vector<Model> models;
	std::map<std::string, std::shared_ptr<ModelBuffer>> dataModelReferences;

	void normolizeModel(std::vector<Vertex>& vertexs);
	void translateToCenterOfMass(std::vector<Vertex>& vertexs);
};

