#include "GLWindow.h"

GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->width = width;
	this->height = height;

	handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	static bool initGLAD = false;
	if (!initGLAD)
	{
		initGLAD = true;

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	glfwSetWindowUserPointer(handle, this);
	glfwSetKeyCallback(handle, glfwKeyCallback);
	glfwSetMouseButtonCallback(handle, glfwMouseButtonCallback);
	glfwSetCursorPosCallback(handle, glfwCursorPositionCallback);
	glfwSetScrollCallback(handle, glfwScrollCallback);

}

GLWindow::~GLWindow() 
{
	glfwDestroyWindow(handle);
}

uint32_t GLWindow::getWidth() const
{
	return width;
}

uint32_t GLWindow::getHeight() const 
{
	return height;
}

void GLWindow::setKeyCallback(const KeyCallback& callback) 
{
	keyCallback = callback;
}

void GLWindow::setCursorPosCallback(const CursorPosCallback& callback) 
{
	cursorPosCallback = callback;
}

void GLWindow::setMouseCallback(const MouseCallback& callback) 
{
	mouseCallback = callback;
}

void GLWindow::setScrollCallback(const ScrollCallback& callback) 
{
	scrollCallback = callback;
}

GLFWwindow* GLWindow:: getGLFWHandle() const
{
	return handle;
}

void GLWindow::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GLWindow* glWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (glWindow->keyCallback != NULL)
		glWindow->keyCallback(static_cast<KeyCode>(key), static_cast<Action>(action), static_cast<Modifier>(mods));
}

void  GLWindow::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GLWindow* glWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (glWindow->mouseCallback != NULL)
	{
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glWindow->mouseCallback(static_cast<ButtonCode>(button), static_cast<Action>(action), static_cast<Modifier>(mods), xpos, ypos);
	}
}

void  GLWindow::glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	GLWindow* glWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if(glWindow->cursorPosCallback != NULL)
		glWindow->cursorPosCallback(xpos, ypos);
}

void  GLWindow::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	GLWindow* glWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if(glWindow->scrollCallback != NULL)
		glWindow->scrollCallback(xoffset, yoffset);
}