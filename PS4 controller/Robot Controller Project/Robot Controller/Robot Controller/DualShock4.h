#ifndef DUALSHOCK4_H
#define DUALSHOCK4_H

#include "Controller.h"
#include "Geometry.h"

#define DS4_LEFT_STICK_X sf::Joystick::Axis::X
#define DS4_LEFT_STICK_Y sf::Joystick::Axis::Y
#define DS4_RIGTH_STICK_X sf::Joystick::Axis::Z
#define DS4_RIGHT_STICK_Y sf::Joystick::Axis::R
#define DS4_R2_AXIS sf::Joystick::Axis::V
#define DS4_L2_AXIS sf::Joystick::Axis::U
#define DS4_LEFT_RIGHT_DPAD sf::Joystick::Axis::PovX
#define DS4_DOWN_UP_DPAD sf::Joystick::Axis::PovY



#define DS4_ROBOT_VELOCITY_X DS4_LEFT_STICK_Y
#define DS4_ROBOT_VELOCITY_Y DS4_LEFT_STICK_X
#define DS4_ROBOT_SHOOT DS4_square
#define DS4_ROBOT_CHIP DS4_circle
#define DS4_ROBOT_PASS DS4_cross
#define DS4_ROBOT_SPEED DS4_R2_AXIS
#define DS4_ROBOT_KICK_POWER DS4_L2_AXIS
#define DS4_ROBOT_W_CLOCKWISE DS4_R1_button
#define DS4_ROBOT_W_COUNTER_CLOCKWISE DS4_L1_button		///anti clockwise

#define DS4_GET_ROBOT_VELOCITY_FROM_CONTROLLER(cn) VecPosition(-GET_AXIS(cn,DS4_ROBOT_VELOCITY_X),-GET_AXIS(cn,DS4_ROBOT_VELOCITY_Y))		
#define DS4_GET_ROBOT_SPEED_FROM_CONTROLLER(cn) GET_AXIS(cn,DS4_ROBOT_SPEED)
#define DS4_GET_ROBOT_SHOOT_FROM_CONTROLLER(cn) IS_BUTTON_PRESSED(cn,DS4_ROBOT_SHOOT)
#define DS4_GET_ROBOT_CHIP_FROM_CONTROLLER(cn) IS_BUTTON_PRESSED(cn,DS4_ROBOT_CHIP)
#define DS4_GET_ROBOT_PASS_FROM_CONTROLLER(cn) IS_BUTTON_PRESSED(cn,DS4_ROBOT_PASS)
#define DS4_GET_ROBOT_KICK_POWER_FROM_CONTROLLER(cn) GET_AXIS(cn,DS4_ROBOT_KICK_POWER)
#define DS4_GET_ROBOT_W_FROM_CONTROLLER(cn) (IS_BUTTON_PRESSED(cn,DS4_ROBOT_W_CLOCKWISE) ? (IS_BUTTON_PRESSED(cn,DS4_ROBOT_W_COUNTER_CLOCKWISE) ? 0 : 1) : (IS_BUTTON_PRESSED(cn,DS4_ROBOT_W_COUNTER_CLOCKWISE) ? -1 : 0))



#define DS4_GET_ROBOT_VELOCITY(cn)		DS4_GET_ROBOT_VELOCITY_FROM_CONTROLLER(cn) * 3	///:for change the range from 0 to 10000
#define DS4_GET_ROBOT_SPEED(cn)			(DS4_GET_ROBOT_SPEED_FROM_CONTROLLER(cn)/160.000) + 1.625	///velocity is speed with direction	///:for change the range from 1  to 2.25
#define DS4_GET_ROBOT_SHOOT(cn) 		DS4_GET_ROBOT_SHOOT_FROM_CONTROLLER(cn)
#define DS4_GET_ROBOT_CHIP(cn)			DS4_GET_ROBOT_CHIP_FROM_CONTROLLER(cn)
#define DS4_GET_ROBOT_PASS(cn)		    DS4_GET_ROBOT_PASS_FROM_CONTROLLER(cn)
#define DS4_GET_ROBOT_KICK_POWER(cn)	DS4_GET_ROBOT_KICK_POWER_FROM_CONTROLLER(cn)+100 ///+100:for change the range from 0 to 200
#define DS4_GET_ROBOT_W(cn)				DS4_GET_ROBOT_W_FROM_CONTROLLER(cn)/30.000


enum Buttons {
	DS4_square = 0,
	DS4_cross = 1,
	DS4_circle = 2,
	DS4_triangle = 3,
	DS4_L1_button = 4,
	DS4_R1_button = 5,
	DS4_L2_button = 6,
	DS4_R2_button = 7,
	DS4_share = 8,
	DS4_option = 9,
	DS4_L3_button = 10,
	DS4_R3_button = 11,
	DS4_PS_button = 12,
	DS4_touchpad = 13,
	DS4_unknown = 14
};

#endif // !DUALSHOCK4_H
