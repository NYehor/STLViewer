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
	glm::vec2 lastPosition;
	glm::vec2 currentPosition;
	Modifier modifier;
	ButtonCode buttonCode;
	Action action;
};

