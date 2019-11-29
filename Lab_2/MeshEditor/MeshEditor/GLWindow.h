#pragma once
#include "glad.h"
#include <glfw/glfw3.h>
#include <functional>
#include <string>


enum class Modifier : int
{
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Supper = 8,
};

enum class Action : int
{
	Release = 0,
	Press = 1,
	Reapeat = 2,
};

enum class ButtonCode : int
{
	Button_0 = 0,

	Button_1 = 0,
	Button_2 = 1,
	Button_3 = 2,
	Button_4 = 3,
	Button_5 = 4,
	Button_6 = 5,
	Button_7 = 6,
	Button_8 = 7,
	Button_LAST = Button_8,
	Button_LEFT = Button_1,
	Button_RIGHT = Button_2,
	Button_MIDDLE = Button_3,
};

enum class KeyCode : int
{
	UNKNOWN = -1,
	Space = 32,

	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
};

class GLWindow
{
public:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	using CursorPosCallback = std::function<void(double, double)>;
	using MouseCallback = std::function<void(ButtonCode, Action, Modifier, double, double)>;
	using ScrollCallback = std::function<void(double, double)>;

	GLWindow(const std::string& title, uint32_t width, uint32_t height);
	~GLWindow();
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	void setKeyCallback(const KeyCallback& callback);
	void setCursorPosCallback(const CursorPosCallback& callback);
	void setMouseCallback(const MouseCallback& callback);
	void setScrollCallback(const ScrollCallback& callback);

	GLFWwindow* getGLFWHandle() const;

private:
	uint32_t width;
	uint32_t height;
	GLFWwindow* handle;

	static KeyCallback keyCallback;
	static CursorPosCallback cursorPosCallback;
	static MouseCallback mouseCallback;
	static ScrollCallback scrollCallback;

	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

