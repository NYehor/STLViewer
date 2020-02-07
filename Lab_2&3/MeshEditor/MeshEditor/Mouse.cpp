#include "Mouse.h"

Mouse::Mouse():
	lastPosition(glm::vec2(0, 0)),
	currentPosition(glm::vec2(0, 0)),
	modifier(Modifier::NoModifier),
	action(Action::NoAction),
	buttonCode(ButtonCode::Button_0)
{ }

void Mouse::setCurrentPosition(float x, float y)
{
	lastPosition = currentPosition;
	currentPosition = glm::vec2(x, y);
}

void Mouse::setLastPosition(float x, float y)
{
	lastPosition = glm::vec2(x, y);
}

void Mouse::setInput(ButtonCode button, Action action, Modifier modifier)
{
	this->buttonCode = button;
	this->action = action;
	this->modifier = modifier;
}

void Mouse::setModifier(Modifier value) { modifier = value; }
void Mouse::setAction(Action value) { action = value; }
void Mouse::setButtonCode(ButtonCode value) { buttonCode = buttonCode; }

glm::vec2 Mouse::getCurrentPosition() { return currentPosition; }
glm::vec2 Mouse::getLastPosition() { return lastPosition; }
Modifier Mouse::getModifier() { return modifier; }
Action Mouse::getAction() { return action; }
ButtonCode Mouse::getButtonCode() { return buttonCode; }