#include "Mouse.h"

Mouse::Mouse():
	_lastPosition(glm::vec2(0, 0)),
	_currentPosition(glm::vec2(0, 0)),
	_modifier(Modifier::NoModifier),
	_action(Action::NoAction),
	_buttonCode(ButtonCode::Button_0)
{ }

void Mouse::setCurrentPosition(float x, float y)
{
	_lastPosition = _currentPosition;
	_currentPosition = glm::vec2(x, y);
}

void Mouse::setLastPosition(float x, float y)
{
	_lastPosition = glm::vec2(x, y);
}

void Mouse::setInput(ButtonCode button, Action action, Modifier modifier)
{
	this->_buttonCode = button;
	this->_action = action;
	this->_modifier = modifier;
}

void Mouse::setModifier(Modifier value) { _modifier = value; }
void Mouse::setAction(Action value) { _action = value; }
void Mouse::setButtonCode(ButtonCode value) { _buttonCode = _buttonCode; }

glm::vec2 Mouse::getCurrentPosition() { return _currentPosition; }
glm::vec2 Mouse::getLastPosition() { return _lastPosition; }
Modifier Mouse::getModifier() { return _modifier; }
Action Mouse::getAction() { return _action; }
ButtonCode Mouse::getButtonCode() { return _buttonCode; }