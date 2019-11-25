#include "GLWindow.h"

GLWindow::KeyCallback GLWindow::keyCallback = {};
GLWindow::CursorPosCallback GLWindow::cursorPosCallback = {};
GLWindow::MouseCallback GLWindow::mouseCallback = {};
GLWindow::ScrollCallback GLWindow::scrollCallback = {};

GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height)
{
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
 	if(keyCallback != NULL)
		keyCallback(static_cast<KeyCode>(key), static_cast<Action>(action), static_cast<Modifier>(mods));
}

void  GLWindow::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (mouseCallback != NULL)
	{
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		mouseCallback(static_cast<ButtonCode>(button), static_cast<Action>(action), static_cast<Modifier>(mods), xpos, ypos);
	}
}

void  GLWindow::glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (cursorPosCallback != NULL)
		cursorPosCallback(xpos, ypos);
}

void  GLWindow::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (scrollCallback != NULL)
		scrollCallback(xoffset, yoffset);
}