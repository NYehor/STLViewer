#pragma once
#include <vector>
#include <map>
#include "Model.h"
#include <string>

struct DataModelReference
{
	unsigned int VBO;
	unsigned int VAO;
};

class Scene
{
public:
	Scene(GLRenderSystem& renderSystem);
	std::vector<std::string> getListOfExistModel();

	void addModel(const char* filePath);
	void addExistModel(const char* key);
	void draw();

private:
	GLRenderSystem& renderSystem;
	std::vector<Model> models;
	std::map<std::string, DataModelReference> dataModelReferences;
};

