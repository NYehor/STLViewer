#include "GLRenderSystem.h"
#include <string>
#include "Model.h"

GLRenderSystem::GLRenderSystem(const char* vertexFilePath, const char* fragmentFilePath):
	shader(vertexFilePath, fragmentFilePath)
{
	viewMatrix = glm::mat4(1.0);
	projMatrix = glm::mat4(1.0);
}

void GLRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
	viewMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getViewMatrix() const
{
	return viewMatrix;
}

void GLRenderSystem::setProjMatrix(const glm::mat4& matrix)
{
	projMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getProjMatrix()
{
	return projMatrix;
}

Shader& GLRenderSystem::getShader()
{
	return shader;
}

const Shader& GLRenderSystem::getShader() const
{
	return shader;
}

void GLRenderSystem::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void GLRenderSystem::setViewport(double x, double y, double width, double height)
{
	glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}

void GLRenderSystem::clearDisplay(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderSystem::setupShader(const glm::mat4& worldMatrix, const glm::vec3& color)
{
	GLuint worldLoc = glGetUniformLocation(shader.getId(), "world");
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

	GLuint viewdLoc = glGetUniformLocation(shader.getId(), "view");
	glUniformMatrix4fv(viewdLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLuint projLoc = glGetUniformLocation(shader.getId(), "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

	shader.setVec3("color", color.x, color.y, color.z);
	shader.setInt("numLights", (int)lights.size());
	for (size_t i = 0, iLen = lights.size(); i < iLen; i++)
	{
		std::string number = std::to_string(i);
		shader.setFloat(("lights[" + number + "].isTurn").c_str(), lights[i].isTurn);
		shader.setVec3(("lights[" + number + "].position").c_str(), lights[i].position.x, lights[i].position.y, lights[i].position.z);
		shader.setVec3(("lights[" + number + "].ambient").c_str(), lights[i].ambient.x, lights[i].ambient.y, lights[i].ambient.z);
		shader.setVec3(("lights[" + number + "].diffuse").c_str(), lights[i].diffuse.x, lights[i].diffuse.y, lights[i].diffuse.z);
		shader.setVec3(("lights[" + number + "].specular").c_str(), lights[i].specular.x, lights[i].specular.y, lights[i].specular.z);
	}
}

void GLRenderSystem::renderTriangles(unsigned int VAO, const std::vector<Vertex>& vertexs)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexs.size());
}

void GLRenderSystem::renderLines(unsigned int VAO, const std::vector<Vertex>& vertexs)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, vertexs.size());
}

unsigned int GLRenderSystem::setVBO(const std::vector<Vertex>& vertices)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	return VBO;
}

unsigned int GLRenderSystem::setVAO(unsigned int vbo, const std::vector<Vertex>& vertices)
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));

	return VAO;
}

void GLRenderSystem::deleteBuffers(const unsigned int& vbo, const unsigned int& vao)
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void GLRenderSystem::setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
	lights.push_back({false, position, Ia, Id, Is});
}

void GLRenderSystem::turnLight(uint32_t index, bool enable)
{
	lights[0].isTurn = enable;
}
