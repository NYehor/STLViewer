#pragma once
#include <vector>
#include "GLRenderSystem.h"

class ModelBuffer
{
public:
	ModelBuffer(GLRenderSystem& rs, const std::vector<Vertex>& vertexs);
	~ModelBuffer();

	const unsigned int& getVBO() const;
	const unsigned int& getVAO() const;

	const std::vector<Vertex>& getVertexs() const;
	std::vector<Vertex>& getVertexs();

private:
	unsigned int VBO;
	unsigned int VAO;
	GLRenderSystem& renderSystem;
	std::vector<Vertex> modelVertexs;
};

