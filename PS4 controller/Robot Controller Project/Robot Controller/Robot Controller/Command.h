#ifndef COMMAND_H
#define COMMAND_H

#include "Geometry.h"

#include "Switches.h"

//--------------CONTROLLER COMMAND-------------//
enum teamType {
	yellowTeam = 0,
	blueTeam = 1
};

struct Robot
{
	VecPosition velocity;
	double w;
	double speed;
	bool kickMode;
	bool chip;
	bool pass;
	short int kickPower;
};

struct Team
{
	Robot robot[NUM_OF_TEAM_ROBOT];
};

struct Command
{
	Team team[2]; ///team[0] is yellowTeam, team[1] is blueTeam
	
};




//-------------ROBOT COMMAND------------------//
char output[30 * NUM_OF_CONTROLLERS];

#endif // !COMMAND_H