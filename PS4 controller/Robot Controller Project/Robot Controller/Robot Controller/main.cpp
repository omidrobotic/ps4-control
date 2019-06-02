///assumptions:
///each team must have the same robot number,otherwise this program assumes that each has same robot number.
///robot number, id of electrical board and controller index+1 are same.
///robot number for yellow team is 1,2,3,..,n and for blue team is n+1,n+2,...,m(= 2*NUM_OF_TEAM_ROBOT)

///LAWS of SFML
///no new controller can connect during runtime of program
///me:the order of controllers indexes wont be change during runtime

#include "SFML/Graphics.hpp"
#include <iostream>
#include <conio.h>
#include <array>
//#include <windows.h>
#include <stdlib.h>
#include "Command.h"
#include "Controller.h"
#include "DualShock4.h"
#include "Switches.h"
#include "nrf.h"
using namespace std;
using namespace sf;


Command command;
array<pair<teamType, controllerType>, NUM_OF_CONTROLLERS> cTeTy;
//tuple<short int, teamType, controllerType>cNTeTy;
//short int cTeTy[NUM_OF_CONTROLLERS][2];

void initialize_cTeTy()
{
	/*int cn = 0;
	for (int i = 0; i < NUM_OF_TEAM_ROBOT; i++, cn++)
	{
		cTeTy[cn][0] = yellowTeam;
		cTeTy[cn][1] = dualShock4;
	}
	for (int i=0 ; i < NUM_OF_TEAM_ROBOT*(NUM_OF_TEAM-1); i++, cn++)
	{
		cTeTy[cn][0] = blueTeam;
		cTeTy[cn][1] = dualShock4;
	}*/

	/*int cn = 0;
	for (int i = 0; i < NUM_OF_TEAM_ROBOT; i++, cn++)
	{
		cNTeTy = make_tuple(cn, yellowTeam, dualShock4);
	}
	for (int i=0 ; i < NUM_OF_TEAM_ROBOT*(NUM_OF_TEAM-1); i++, cn++)
	{
		cNTeTy = make_tuple(cn, blueTeam, dualShock4);
	}*/

	int cn = 0;
	for (int i = 0; i < NUM_OF_TEAM_ROBOT; i++, cn++)
	{
		cTeTy[cn] = make_pair(yellowTeam, dualShock4);
	}
	for (int i = 0; i < NUM_OF_TEAM_ROBOT*(NUM_OF_TEAM - 1); i++, cn++)
	{
		cTeTy[cn] = make_pair(blueTeam, dualShock4);
	}
}

void initial_check_controllers_connection()
{
	for (int i = 0; i < NUM_OF_CONTROLLERS; i++)
	{
		if (!sf::Joystick::isConnected(i))
		{
			cout << "controller " << i << " is not connected! press any key to close the program" << endl;
			_getch();
			exit(EXIT_SUCCESS);
		}
	}
}

void check_controllers_connection()
{
	for (int i = 0; i < NUM_OF_CONTROLLERS; i++)
	{
		if (!sf::Joystick::isConnected(i))
		{
			cout << "controller " << i << " is not connected!"<< endl;
		}
	}
}

bool check_controller_connection(short int cn)
{
	if (!sf::Joystick::isConnected(cn))
		return false;
	else
		return true;
}

///handle controller : get pressed buttons and axises,convert it to robot high level commands,save them into an object 1.
void handle_controller(short int cn /*controller number*/, controllerType ct )
{
	if (!check_controller_connection(cn))
	{
		cout << "controller " << cn << " is not connected" << endl;
		return;
	}
	if (ct == dualShock4)
	{
		command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].velocity = DS4_GET_ROBOT_VELOCITY(cn);
		command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].speed = DS4_GET_ROBOT_SPEED(cn);
		command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].w = DS4_GET_ROBOT_W(cn);
		command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].kickMode = 0;//DS4_GET_ROBOT_SHOOT(cn);
		//command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].chip = DS4_GET_ROBOT_CHIP(cn);
		//command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].pass = DS4_GET_ROBOT_PASS(cn);
		command.team[cTeTy[cn].first].robot[cn%NUM_OF_TEAM_ROBOT].kickPower = DS4_GET_ROBOT_SHOOT(cn)>0 ? 1 : 0;//DS4_GET_ROBOT_KICK_POWER(cn);
	}
}
void handle_controllers()
{
	for (int i = 0; i < NUM_OF_CONTROLLERS; i++)
	{
		handle_controller(i, cTeTy[i].second);
	}
}

void convert_controllers_commands_to_robots_commands_and_send_commands(int id)
{
	for (int i = 0; i < NUM_OF_TEAM_ROBOT; i++)
	{
		nrf::go(command.team[yellowTeam].robot[i].velocity * command.team[yellowTeam].robot[i].speed, command.team[yellowTeam].robot[i].w, command.team[yellowTeam].robot[i].kickMode, command.team[yellowTeam].robot[i].kickPower, id);
	}
}

///add when closing the program,all robots stop
int main()
{
	///handle controller : get pressed buttons and axises,convert it to robot high level commands,save them into an object 1.
	///convert high level commands to low level commands : get data from object 1 , convert to low level command , save it to object 2
	///send commands : send commands of object 2 to robot 
	
	int robot_id = 5;

	sf::Joystick::update();

	initial_check_controllers_connection();

	initialize_cTeTy();

	//nrf::output[25] = 0b11100000;


	while (true)
	{
		sf::Joystick::update();
		handle_controllers();
		convert_controllers_commands_to_robots_commands_and_send_commands(robot_id);
	}
	
	

}
