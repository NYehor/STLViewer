#include "ModelBuffer.h"

ModelBuffer::ModelBuffer(GLRenderSystem& rs, const std::vector<Vertex>& vertexs):
	renderSystem(rs)
{
	modelVertexs = vertexs;
	VBO = renderSystem.setVBO(modelVertexs);
	VAO = renderSystem.setVAO(VBO, modelVertexs);
}

ModelBuffer::~ModelBuffer()
{
	renderSystem.deleteBuffers(VBO, VAO);
}

const unsigned int& ModelBuffer::getVBO() const
{
	return VBO;
}

const unsigned int& ModelBuffer::getVAO() const
{
	return VAO;
}

std::vector<Vertex>& ModelBuffer::getVertexs()
{
	return modelVertexs;
}

const std::vector<Vertex>& ModelBuffer::getVertexs() const
{
	return modelVertexs;
}