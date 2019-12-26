#include "GLRenderSystem.h";

void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
	worldMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getWorldMatrix() const
{
	return worldMatrix;
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
	glViewport(x, y, width, height);
}

void GLRenderSystem::clearDisplay(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++)
	{
		glColor3f(vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
		glNormal3f(vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2]);
		glVertex3f(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2]);
	}
	glEnd();
}

void GLRenderSystem::renderLines(const std::vector<Vertex> vertices)
{
	glBegin(GL_LINES);
	for (int i = 0; i < vertices.size(); i++)
	{
		glColor3f(vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
		glNormal3f(vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2]);
		glVertex3f(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2]);
	}
	glEnd();
}

void GLRenderSystem::setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
	auto IA = glm::value_ptr(Ia);
	GLfloat* ID = glm::value_ptr(Id);
	glLightfv(GL_LIGHT0 + index, GL_POSITION, glm::value_ptr(position));
	glLightfv(GL_LIGHT0 + index, GL_AMBIENT, glm::value_ptr(Ia));
	glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, glm::value_ptr(Id));
	glLightfv(GL_LIGHT0 + index, GL_SPECULAR, glm::value_ptr(Is));
}

void GLRenderSystem::turnLight(uint32_t index, bool enable)
{
	if (enable)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + index);
	}
	else
	{
		glDisable(GL_LIGHT0 + index);
		glDisable(GL_LIGHTING);
	}
}
