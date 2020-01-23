#include "Scene.h"
#include "STLParser.h"

Scene::Scene(GLRenderSystem& renderSystem) :
    renderSystem(renderSystem) {}

std::vector<std::string> Scene::getListOfExistModel()
{
    std::vector<std::string> retval;
    for (auto const& element : dataModelReferences) {
        retval.push_back(element.first);
    }
    return retval;
}

void Scene::addModel(const char* filePath)
{
    STLParser parser;
    std::string name = parser.getName(filePath);
    Model model(renderSystem, parser.read(filePath));

    unsigned int VBO = renderSystem.setVBO(model.getVertexs());
    unsigned int VAO = renderSystem.setVAO(VBO, model.getVertexs());
    model.setVBO(VBO);
    model.setVAO(VAO);

    dataModelReferences.insert(std::pair<std::string, DataModelReference>(name, { VBO, VAO }));
    models.push_back(model);
}

void Scene::addExistModel(const char* key)
{

}

void Scene::draw()
{
    for (size_t i = 0, ilen = models.size(); i < ilen; i++)
    {
        models[i].draw();
    }
}