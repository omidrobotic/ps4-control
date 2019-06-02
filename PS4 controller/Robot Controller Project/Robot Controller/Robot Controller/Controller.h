#ifndef CONTROLLER_H
#define CONTROLLER_H

#define GET_AXIS(con_num,axis) sf::Joystick::getAxisPosition(con_num,axis)
#define IS_BUTTON_PRESSED(con_num,button) sf::Joystick::isButtonPressed(con_num,button)

enum controllerType {dualShock4 = 0};

#endif // !CONTROLLER_H
