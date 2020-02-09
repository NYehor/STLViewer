#pragma once
#include <glm\glm.hpp>
#include "GLWindow.h"

class Mouse
{
public:
	Mouse();

	void setCurrentPosition(float x, float y);
	void setLastPosition(float x, float y);
	void setModifier(Modifier value);
	void setAction(Action value);
	void setButtonCode(ButtonCode value);
	void setInput(ButtonCode button, Action action, Modifier modifier);

	glm::vec2 getCurrentPosition();
	glm::vec2 getLastPosition();
	Modifier getModifier();
	Action getAction();
	ButtonCode getButtonCode();

private:
	glm::vec2 _lastPosition;
	glm::vec2 _currentPosition;
	Modifier _modifier;
	ButtonCode _buttonCode;
	Action _action;
};

